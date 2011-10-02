/*
 * Copyright (C) 2010-2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
 *
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "Language.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "ObjectMgr.h"
#include "Log.h"
#include "OpcodeHandler.h"
#include "Guild.h"
#include "ArenaTeam.h"
#include "GossipDef.h"
#include "SocialMgr.h"

#define CHARTER_DISPLAY_ID 16161

// Charters ID in item_template
enum CharterItemIDs
{
    GUILD_CHARTER                                 = 5863,
};

enum CharterCosts
{
    GUILD_CHARTER_COST                            = 1000,
};

void WorldSession::HandlePetitionBuyOpcode(WorldPacket & recv_data)
{
    if (_player->GetGuildId())
       return;
    
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_PETITION_BUY");
    recv_data.hexlike();

    uint64 guidNPC;
    uint32 clientIndex;                                     // 1 for guild and arenaslot+1 for arenas in client
    std::string name;

    recv_data >> guidNPC;                                   // NPC GUID
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint64>();                          // 0
    recv_data >> name;                                      // name
    recv_data.read_skip<std::string>();                     // some string
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint16>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0
    recv_data.read_skip<uint32>();                          // 0

    for (int i = 0; i < 10; ++i)
        recv_data.read_skip<std::string>();

    recv_data >> clientIndex;                               // index
    recv_data.read_skip<uint32>();                          // 0

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Petitioner with GUID %u tried sell petition: name %s", GUID_LOPART(guidNPC), name.c_str());

    // prevent cheating
    Creature *pCreature = GetPlayer()->GetNPCIfCanInteractWith(guidNPC,UNIT_NPC_FLAG_PETITIONER);
    if (!pCreature)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandlePetitionBuyOpcode - Unit (GUID: %u) not found or you can't interact with him.", GUID_LOPART(guidNPC));
        return;
    }

    if (!pCreature->isTabardDesigner())
        return;

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STAT_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    uint32 charterid = GUILD_CHARTER;
    uint32 cost = GUILD_CHARTER_COST;

    if (sObjectMgr->GetGuildByName(name))
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NAME_EXISTS_S, name);
        return;
    }
    
    if (sObjectMgr->IsReservedName(name) || !ObjectMgr::IsValidCharterName(name))
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NAME_INVALID, name);
        return;
    }

    ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(charterid);
    if (!pProto)
    {
        _player->SendBuyError(BUY_ERR_CANT_FIND_ITEM, NULL, charterid, 0);
        return;
    }

    if (!_player->HasEnoughMoney(cost))
    {                                                       //player hasn't got enough money
        _player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, charterid, 0);
        return;
    }

    ItemPosCountVec dest;
    uint8 msg = _player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, charterid, pProto->BuyCount);
    if (msg != EQUIP_ERR_OK)
    {
        _player->SendBuyError(msg, pCreature, charterid, 0);
        return;
    }

    _player->ModifyMoney(-(int32)cost);
    Item *charter = _player->StoreNewItem(dest, charterid, true);
    if (!charter)
        return;

    charter->SetUInt32Value(ITEM_FIELD_ENCHANTMENT_1_1, charter->GetGUIDLow());
    // ITEM_FIELD_ENCHANTMENT_1_1 is guild/arenateam id
    // ITEM_FIELD_ENCHANTMENT_1_1+1 is current signatures count (showed on item)
    charter->SetState(ITEM_CHANGED, _player);
    _player->SendNewItem(charter, 1, true, false);

    // a petition is invalid, if both the owner and the type matches
    // we checked above, if this player is in an arenateam, so this must be
    // datacorruption
    QueryResult result = CharDB.PQuery("SELECT petitionguid FROM petition WHERE ownerguid = '%u'", _player->GetGUIDLow());

    std::ostringstream ssInvalidPetitionGUIDs;

    if (result)
    {
        do
        {
            Field *fields = result->Fetch();
            ssInvalidPetitionGUIDs << "'" << fields[0].GetUInt32() << "' , ";
        } while (result->NextRow());
    }

    // delete petitions with the same guid as this one
    ssInvalidPetitionGUIDs << "'" << charter->GetGUIDLow() << "'";

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Invalid petition GUIDs: %s", ssInvalidPetitionGUIDs.str().c_str());
    CharDB.escape_string(name);
    SQLTransaction trans = CharDB.BeginTransaction();
    trans->PAppend("DELETE FROM petition WHERE petitionguid IN (%s)",  ssInvalidPetitionGUIDs.str().c_str());
    trans->PAppend("DELETE FROM petition_sign WHERE petitionguid IN (%s)", ssInvalidPetitionGUIDs.str().c_str());
    trans->PAppend("INSERT INTO petition (ownerguid, petitionguid, name) VALUES ('%u', '%u', '%s')",
        _player->GetGUIDLow(), charter->GetGUIDLow(), name.c_str());
    CharDB.CommitTransaction(trans);
}

void WorldSession::HandlePetitionShowSignOpcode(WorldPacket & recv_data)
{
     if (_player->GetGuildId())
         return;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_PETITION_SHOW_SIGNATURES");

    uint8 signs = 0;
    uint64 petitionguid;
    recv_data >> petitionguid;                              // petition guid

    // solve (possible) some strange compile problems with explicit use GUID_LOPART(petitionguid) at some GCC versions (wrong code optimization in compiler?)
    uint32 petitionguid_low = GUID_LOPART(petitionguid);

    QueryResult result = CharDB.PQuery("SELECT playerguid FROM petition_sign WHERE petitionguid = '%u'", petitionguid_low);

    // result == NULL also correct in case no sign yet
    if (result)
        signs = uint8(result->GetRowCount());

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_PETITION_SHOW_SIGNATURES petition entry: '%u'", petitionguid_low);

    WorldPacket data(SMSG_PETITION_SHOW_SIGNATURES, (8+8+4+1+signs*12));
    data << uint64(petitionguid);                           // petition guid
    data << uint64(_player->GetGUID());                     // owner guid
    data << uint32(petitionguid_low);                       // guild guid
    data << uint8(signs);                                   // sign's count

    for (uint8 i = 1; i <= signs; ++i)
    {
        Field *fields2 = result->Fetch();
        uint64 plguid = fields2[0].GetUInt64();

        data << uint64(plguid);                             // Player GUID
        data << uint32(0);                                  // there 0 ...

        result->NextRow();
    }
    SendPacket(&data);
}

void WorldSession::HandlePetitionQueryOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_PETITION_QUERY");   // ok
    //recv_data.hexlike();

    uint32 guildguid;
    uint64 petitionguid;
    recv_data >> guildguid;                                 // in Strawberry always same as GUID_LOPART(petitionguid)
    recv_data >> petitionguid;                              // petition guid
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_PETITION_QUERY Petition GUID %u Guild GUID %u", GUID_LOPART(petitionguid), guildguid);

    SendPetitionQueryOpcode(petitionguid);
}

void WorldSession::SendPetitionQueryOpcode(uint64 petitionguid)
{
    uint64 ownerguid = 0;
    std::string name = "NO_NAME_FOR_GUID";
    uint8 signs = 0;

    QueryResult result = CharDB.PQuery(
        "SELECT ownerguid, name, "
        "  (SELECT COUNT(playerguid) FROM petition_sign WHERE petition_sign.petitionguid = '%u') AS signs "
        "FROM petition WHERE petitionguid = '%u'", GUID_LOPART(petitionguid), GUID_LOPART(petitionguid));

    if (result)
    {
        Field* fields = result->Fetch();
        ownerguid = MAKE_NEW_GUID(fields[0].GetUInt32(), 0, HIGHGUID_PLAYER);
        name      = fields[1].GetString();
        signs     = fields[2].GetUInt8();
    }
    else
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_PETITION_QUERY failed for petition (GUID: %u)", GUID_LOPART(petitionguid));
        return;
    }

    WorldPacket data(SMSG_PETITION_QUERY_RESPONSE, (4+8+name.size()+1+1+4*12+2+10));
    data << uint32(GUID_LOPART(petitionguid));              // guild/team guid (in Strawberry always same as GUID_LOPART(petition guid)
    data << uint64(ownerguid);                              // charter owner guid
    data << name;                                           // name (guild/arena team)
    data << uint8(0);                                       // some string
    data << uint32(9);
    data << uint32(9);
    data << uint32(0);                                      // bypass client - side limitation, a different value is needed here for each petition
    data << uint32(0);                                      // 5
    data << uint32(0);                                      // 6
    data << uint32(0);                                      // 7
    data << uint32(0);                                      // 8
    data << uint16(0);                                      // 9 2 bytes field
    data << uint32(0);                                      // 10
    data << uint32(0);                                      // 11
    data << uint32(0);                                      // 13 count of next strings?

    for (int i = 0; i < 10; ++i)
        data << uint8(0);                                   // some string

    data << uint32(0);                                      // 14
    data << uint32(0);                                      // 15 0 - guild

    SendPacket(&data);
}

void WorldSession::HandlePetitionRenameOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode MSG_PETITION_RENAME");   // ok
    //recv_data.hexlike();

    uint64 petitionguid;
    std::string newname;

    recv_data >> petitionguid;                              // guid
    recv_data >> newname;                                   // new name

    Item *item = _player->GetItemByGuid(petitionguid);
    if (!item)
        return;

    if (sObjectMgr->GetGuildByName(newname))
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NAME_EXISTS_S, newname);
        return;
    }

    if (sObjectMgr->IsReservedName(newname) || !ObjectMgr::IsValidCharterName(newname))
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NAME_INVALID, newname);
        return;
    }

    std::string db_newname = newname;
    CharDB.escape_string(db_newname);
    CharDB.PExecute("UPDATE petition SET name = '%s' WHERE petitionguid = '%u'",
        db_newname.c_str(), GUID_LOPART(petitionguid));

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Petition (GUID: %u) renamed to '%s'", GUID_LOPART(petitionguid), newname.c_str());
    WorldPacket data(MSG_PETITION_RENAME, (8+newname.size()+1));
    data << uint64(petitionguid);
    data << newname;
    SendPacket(&data);
}

void WorldSession::HandlePetitionSignOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_PETITION_SIGN");    // ok
    //recv_data.hexlike();

    Field *fields;
    uint64 petitionguid;
    uint8 unk;
    recv_data >> petitionguid;                              // petition guid
    recv_data >> unk;

    QueryResult result = CharDB.PQuery(
        "SELECT ownerguid, "
        "  (SELECT COUNT(playerguid) FROM petition_sign WHERE petition_sign.petitionguid = '%u') AS signs "
        "FROM petition WHERE petitionguid = '%u'", GUID_LOPART(petitionguid), GUID_LOPART(petitionguid));

    if (!result)
    {
        sLog->outError("Petition %u is not found for player %u %s", GUID_LOPART(petitionguid), GetPlayer()->GetGUIDLow(), GetPlayer()->GetName());
        return;
    }

    fields = result->Fetch();
    uint64 ownerguid = MAKE_NEW_GUID(fields[0].GetUInt32(), 0, HIGHGUID_PLAYER);
    uint8 signs = fields[1].GetUInt8();

    uint32 plguidlo = _player->GetGUIDLow();
    if (GUID_LOPART(ownerguid) == plguidlo)
        return;

    // do not let enemies sign guild charter
    if (!sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_INTERACTION_GUILD) && GetPlayer()->GetTeam() != sObjectMgr->GetPlayerTeamByGUID(ownerguid))
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NOT_ALLIED);
        return;
    }

    if (_player->GetGuildId())
    {
        Guild::SendCommandResult(this, GUILD_INVITE_S, ERR_ALREADY_IN_GUILD_S, _player->GetName());
        return;
    }
    if (_player->GetGuildIdInvited())
    {
        Guild::SendCommandResult(this, GUILD_INVITE_S, ERR_ALREADY_INVITED_TO_GUILD_S, _player->GetName());
        return;
    }

    if (++signs > 9)                                        // client signs maximum
        return;

    //client doesn't allow to sign petition two times by one character, but not check sign by another character from same account
    //not allow sign another player from already sign player account
    result = CharDB.PQuery("SELECT playerguid FROM petition_sign WHERE player_account = '%u' AND petitionguid = '%u'", GetAccountId(), GUID_LOPART(petitionguid));

    if (result)
    {
        WorldPacket data(SMSG_PETITION_SIGN_RESULTS, (8+8+4));
        data << uint64(petitionguid);
        data << uint64(_player->GetGUID());
        data << (uint32)PETITION_SIGN_ALREADY_SIGNED;

        // close at signer side
        SendPacket(&data);

        // update for owner if online
        if (Player *owner = sObjectMgr->GetPlayer(ownerguid))
            owner->GetSession()->SendPacket(&data);
        return;
    }

    CharDB.PExecute("INSERT INTO petition_sign (ownerguid,petitionguid, playerguid, player_account) VALUES ('%u', '%u', '%u','%u')", GUID_LOPART(ownerguid),GUID_LOPART(petitionguid), plguidlo,GetAccountId());

    sLog->outDebug(LOG_FILTER_NETWORKIO, "PETITION SIGN: GUID %u by player: %s (GUID: %u Account: %u)", GUID_LOPART(petitionguid), _player->GetName(),plguidlo,GetAccountId());

    WorldPacket data(SMSG_PETITION_SIGN_RESULTS, (8+8+4));
    data << uint64(petitionguid);
    data << uint64(_player->GetGUID());
    data << uint32(PETITION_SIGN_OK);

    // close at signer side
    SendPacket(&data);

    // update for owner if online
    if (Player *owner = sObjectMgr->GetPlayer(ownerguid))
        owner->GetSession()->SendPacket(&data);
}

void WorldSession::HandlePetitionDeclineOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode MSG_PETITION_DECLINE");  // ok
    //recv_data.hexlike();

    uint64 petitionguid;
    uint64 ownerguid;
    recv_data >> petitionguid;                              // petition guid
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Petition %u declined by %u", GUID_LOPART(petitionguid), _player->GetGUIDLow());

    QueryResult result = CharDB.PQuery("SELECT ownerguid FROM petition WHERE petitionguid = '%u'", GUID_LOPART(petitionguid));
    if (!result)
        return;

    Field *fields = result->Fetch();
    ownerguid = MAKE_NEW_GUID(fields[0].GetUInt32(), 0, HIGHGUID_PLAYER);

    Player *owner = sObjectMgr->GetPlayer(ownerguid);
    if (owner)                                               // petition owner online
    {
        WorldPacket data(MSG_PETITION_DECLINE, 8);
        data << uint64(_player->GetGUID());
        owner->GetSession()->SendPacket(&data);
    }
}

void WorldSession::HandleOfferPetitionOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_OFFER_PETITION");   // ok
    //recv_data.hexlike();

    uint8 signs = 0;
    uint64 petitionguid, plguid;
    uint32 junk;
    Player *player;
    recv_data >> junk;                                      // this is not petition type!
    recv_data >> petitionguid;                              // petition guid
    recv_data >> plguid;                                    // player guid

    player = ObjectAccessor::FindPlayer(plguid);
    if (!player)
        return;

    if (!sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_INTERACTION_GUILD) && GetPlayer()->GetTeam() != player->GetTeam())
    {
        Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NOT_ALLIED);
        return;
    }

    if (player->GetGuildId())
    {
        Guild::SendCommandResult(this, GUILD_INVITE_S, ERR_ALREADY_IN_GUILD_S, _player->GetName());
        return;
    }
    
    if (player->GetGuildIdInvited())
    {
        Guild::SendCommandResult(this, GUILD_INVITE_S, ERR_ALREADY_INVITED_TO_GUILD_S, _player->GetName());
        return;
    }

    QueryResult result = CharDB.PQuery("SELECT playerguid FROM petition_sign WHERE petitionguid = '%u'", GUID_LOPART(petitionguid));
    // result == NULL also correct charter without signs
    if (result)
        signs = uint8(result->GetRowCount());

    WorldPacket data(SMSG_PETITION_SHOW_SIGNATURES, (8+8+4+signs+signs*12));
    data << uint64(petitionguid);                           // petition guid
    data << uint64(_player->GetGUID());                     // owner guid
    data << uint32(GUID_LOPART(petitionguid));              // guild guid
    data << uint8(signs);                                   // sign's count

    for (uint8 i = 1; i <= signs; ++i)
    {
        Field *fields2 = result->Fetch();
        plguid = fields2[0].GetUInt64();

        data << uint64(plguid);                             // Player GUID
        data << uint32(0);                                  // there 0 ...

        result->NextRow();
    }

    player->GetSession()->SendPacket(&data);
}

void WorldSession::HandleTurnInPetitionOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_TURN_IN_PETITION");

    // Get petition guid from packet
    WorldPacket data;
    uint64 petitionGuid;

    recv_data >> petitionGuid;

    // Check if player really has the required petition charter
    Item* item = _player->GetItemByGuid(petitionGuid);
    if (!item)
        return;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Petition %u turned in by %u", GUID_LOPART(petitionGuid), _player->GetGUIDLow());

    // Get petition data from db
    uint32 ownerguidlo;
    std::string name;

    PreparedStatement* stmt = CharDB.GetPreparedStatement(CHAR_LOAD_PETITION);
    stmt->setUInt32(0, GUID_LOPART(petitionGuid));
    PreparedQueryResult result = CharDB.Query(stmt);

    if (result)
    {
        Field *fields = result->Fetch();
        ownerguidlo = fields[0].GetUInt32();
        name = fields[1].GetString();
    }
    else
    {
        sLog->outError("Player %s (guid: %u) tried to turn in petition (guid: %u) that is not present in the database", _player->GetName(), _player->GetGUIDLow(), GUID_LOPART(petitionGuid));
        return;
    }

    // Only the petition owner can turn in the petition
    if (_player->GetGUIDLow() != ownerguidlo)
        return;

    // Petition type (guild/arena) specific checks
    if (_player->GetGuildId())
    {
        data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
        data << (uint32)PETITION_TURN_ALREADY_IN_GUILD; // already in guild
        _player->GetSession()->SendPacket(&data);
        return;
    }

    // Get petition signatures from db
    uint8 signatures;

    stmt = CharDB.GetPreparedStatement(CHAR_LOAD_PETITION_SIGNATURE);
    stmt->setUInt32(0, GUID_LOPART(petitionGuid));
    result = CharDB.Query(stmt);

    if (result)
        signatures = uint8(result->GetRowCount());
    else
        signatures = 0;

    if (signatures < sWorld->getIntConfig(CONFIG_MIN_PETITION_SIGNS))
    {
        data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
        data << (uint32)PETITION_TURN_NEED_MORE_SIGNATURES;
        SendPacket(&data);
        return;
    }

    // Delete charter item
    _player->DestroyItem(item->GetBagSlot(),item->GetSlot(), true);

    if (sObjectMgr->GetGuildByName(name))
    {
        Guild* guild = new Guild;
        if (!guild->Create(_player, name))
        {
            delete guild;
            return;
        }

        // Register guild and add guild master
        sObjectMgr->AddGuild(guild);

        // Add members from signatures
        for (uint8 i = 0; i < signatures; ++i)
        {
            Field* fields = result->Fetch();
            guild->AddMember(MAKE_NEW_GUID(fields[0].GetUInt32(), 0, HIGHGUID_PLAYER));
            result->NextRow();
        }
    }
    else
    {
        // ToDo: Fix Arena Team creation
        // Receive the rest of the packet in arena team creation case
        /*uint32 background, icon, iconcolor, border, bordercolor;
        recv_data >> background >> icon >> iconcolor >> border >> bordercolor;

        // Create arena team
        ArenaTeam* arenaTeam = new ArenaTeam();

        if (!arenaTeam->Create(_player->GetGUID(), type, name, background, icon, iconcolor, border, bordercolor))
        {
            delete arenaTeam;
            return;
        }

        // Register arena team
        sObjectMgr->AddArenaTeam(arenaTeam);
        sLog->outDebug(LOG_FILTER_NETWORKIO, "PetitonsHandler: Arena team (guid: %u) added to ObjectMgr", arenaTeam->GetId());

        // Add members
        for (uint8 i = 0; i < signatures; ++i)
        {
            Field* fields = result->Fetch();
            uint32 memberGUID = fields[0].GetUInt32();
            sLog->outDebug(LOG_FILTER_NETWORKIO, "PetitionsHandler: Adding arena team (guid: %u) member %u", arenaTeam->GetId(), memberGUID);
            arenaTeam->AddMember(MAKE_NEW_GUID(memberGUID, 0, HIGHGUID_PLAYER));
            result->NextRow();
        }*/
    }

    SQLTransaction trans = CharDB.BeginTransaction();
    trans->PAppend("DELETE FROM petition WHERE petitionguid = '%u'", GUID_LOPART(petitionGuid));
    trans->PAppend("DELETE FROM petition_sign WHERE petitionguid = '%u'", GUID_LOPART(petitionGuid));
    CharDB.CommitTransaction(trans);

    // created
    sLog->outDebug(LOG_FILTER_NETWORKIO, "TURN IN PETITION GUID %u", GUID_LOPART(petitionGuid));

    data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
    data << (uint32)PETITION_TURN_OK;
    SendPacket(&data);
}

void WorldSession::HandlePetitionShowListOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received CMSG_PETITION_SHOWLIST");       // ok

    uint64 guid;
    recv_data >> guid;

    SendPetitionShowList(guid);
}

void WorldSession::SendPetitionShowList(uint64 guid)
{
    Creature *pCreature = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_PETITIONER);
    if (!pCreature)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandlePetitionShowListOpcode - Unit (GUID: %u) not found or you can't interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    WorldPacket data(SMSG_PETITION_SHOWLIST, 8+1+4*6);
    data << guid;                                       // npc guid

    data << uint8(1);                                   // count
    data << uint32(1);                                  // index
    data << uint32(GUILD_CHARTER);                      // charter entry
    data << uint32(CHARTER_DISPLAY_ID);                 // charter display id
    data << uint32(GUILD_CHARTER_COST);                 // charter cost
    data << uint32(0);                                  // unknown
    data << uint32(9);                                  // required signs?

    SendPacket(&data);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Sent SMSG_PETITION_SHOWLIST");
}