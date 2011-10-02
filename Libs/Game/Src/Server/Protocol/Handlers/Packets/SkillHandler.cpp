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
#include "DatabaseEnv.h"
#include "Log.h"
#include "OpcodeHandler.h"
#include "Player.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "ObjectAccessor.h"
#include "UpdateMask.h"

void WorldSession::HandleLearnTalentOpcode(WorldPacket & recv_data)
{
    uint32 talent_id, requested_rank;
    recv_data >> talent_id >> requested_rank;

    _player->LearnTalent(talent_id, requested_rank, true);
    _player->SendTalentsInfoData(false);
}

void WorldSession::HandleSetPrimaryTalentTree(WorldPacket& recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_SET_PRIMARY_TALENT_TREE");

    uint32 talentTabId;
    recv_data >> talentTabId;
}

void WorldSession::HandleLearnPreviewTalents(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LEARN_PREVIEW_TALENTS");

    uint32 spec;
    uint32 talentsCount;
    recvPacket >> spec >> talentsCount;

    if(spec != ((uint32)-1))
    {
        uint32 specID = 0;
        for(uint32 i = 0; i < sTalentTabStore.GetNumRows(); i++)
        {
            TalentTabEntry const * entry = sTalentTabStore.LookupEntry(i);
            if(entry)
            {
                if(entry->ClassMask == _player->getClassMask() && entry->tabpage == spec)
                {
                    specID = entry->TalentTabID;
                    break;
                }
            }
        }
    
        if(_player->m_usedTalentCount == 0 || _player->GetTalentBranchSpec(_player->m_activeSpec) == 0)
        {
            if(_player->m_usedTalentCount != 0)
                _player->resetTalents();

            _player->SetTalentBranchSpec(specID, _player->m_activeSpec);

            for (uint32 i = 0; i < sTalentTreePrimarySpellsStore.GetNumRows(); ++i)
            {
                TalentTreePrimarySpellsEntry const *talentInfo = sTalentTreePrimarySpellsStore.LookupEntry(i);
                if (!talentInfo )
                    continue;
                
                _player->learnSpell(talentInfo->SpellID, true);
            }    
        }
        else if(_player->GetTalentBranchSpec(_player->m_activeSpec) != specID) //cheat
            return;
    }

    uint32 talentId, talentRank;

    for (uint32 i = 0; i < talentsCount; ++i)
    {
        recvPacket >> talentId >> talentRank;

        _player->LearnTalent(talentId, talentRank);
    }

    _player->SendTalentsInfoData(false);
}

void WorldSession::HandleTalentWipeConfirmOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "MSG_TALENT_WIPE_CONFIRM");
    uint64 guid;
    recv_data >> guid;

    Creature *unit = GetPlayer()->GetNPCIfCanInteractWith(guid,UNIT_NPC_FLAG_TRAINER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleTalentWipeConfirmOpcode - Unit (GUID: %u) not found or you can't interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STAT_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    if (!(_player->resetTalents()))
    {
        WorldPacket data(MSG_TALENT_WIPE_CONFIRM, 8+4);    //you have not any talent
        data << uint64(0);
        data << uint32(0);
        SendPacket(&data);
        return;
    }

    _player->SendTalentsInfoData(false);
    unit->CastSpell(_player, 14867, true);                  //spell: "Untalent Visual Effect"
}

void WorldSession::HandleUnlearnSkillOpcode(WorldPacket & recv_data)
{
    uint32 skill_id;
    recv_data >> skill_id;
    GetPlayer()->SetSkill(skill_id, 0, 0, 0);
}
