/*
 * Copyright (C) 2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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

#include "QuestDef.h"
#include "GossipDef.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Formulas.h"

GossipMenu::GossipMenu()
{
    _menuId = 0;
}

GossipMenu::~GossipMenu()
{
    ClearMenu();
}

void GossipMenu::AddMenuItem(int32 menuItemId, uint8 icon, std::string const& message, uint32 sender, uint32 action, std::string const& boxMessage, uint32 boxMoney, bool coded /*= false*/)
{
    ASSERT(_menuItems.size() <= GOSSIP_MAX_MENU_ITEMS);

    // Find a free new id - script case
    if (menuItemId == -1)
    {
        menuItemId = 0;
        if (!_menuItems.empty())
        {
            for (GossipMenuItemContainer::const_iterator itr = _menuItems.begin(); itr != _menuItems.end(); ++itr)
            {
                if (int32(itr->first) > menuItemId)
                {
                    menuItemId = menuItemId;
                    break;
                }

                menuItemId = itr->first + 1;
            }
        }
    }

    GossipMenuItem& menuItem = _menuItems[menuItemId];

    menuItem.MenuItemIcon    = icon;
    menuItem.Message         = message;
    menuItem.IsCoded         = coded;
    menuItem.Sender          = sender;
    menuItem.OptionType      = action;
    menuItem.BoxMessage      = boxMessage;
    menuItem.BoxMoney        = boxMoney;
}

void GossipMenu::AddGossipMenuItemData(uint32 menuItemId, uint32 gossipActionMenuId, uint32 gossipActionPoi)
{
    GossipMenuItemData& itemData = _menuItemData[menuItemId];

    itemData.GossipActionMenuId  = gossipActionMenuId;
    itemData.GossipActionPoi     = gossipActionPoi;
}

uint32 GossipMenu::GetMenuItemSender(uint32 menuItemId) const
{
    GossipMenuItemContainer::const_iterator itr = _menuItems.find(menuItemId);
    if (itr == _menuItems.end())
        return 0;

    return itr->second.Sender;
}

uint32 GossipMenu::GetMenuItemAction(uint32 menuItemId) const
{
    GossipMenuItemContainer::const_iterator itr = _menuItems.find(menuItemId);
    if (itr == _menuItems.end())
        return 0;

    return itr->second.OptionType;
}

bool GossipMenu::IsMenuItemCoded(uint32 menuItemId) const
{
    GossipMenuItemContainer::const_iterator itr = _menuItems.find(menuItemId);
    if (itr == _menuItems.end())
        return false;

    return itr->second.IsCoded;
}

void GossipMenu::ClearMenu()
{
    _menuItems.clear();
    _menuItemData.clear();
}

PlayerMenu::PlayerMenu(WorldSession *session) : _session(session)
{
}

PlayerMenu::~PlayerMenu()
{
    ClearMenus();
}

void PlayerMenu::ClearMenus()
{
    _gossipMenu.ClearMenu();
    _questMenu.ClearMenu();
}

void PlayerMenu::SendGossipMenu(uint32 titleTextId, uint64 objectGUID) const
{
    WorldPacket data(SMSG_GOSSIP_MESSAGE, 100);         // guess size
    data << uint64(objectGUID);
    data << uint32(_gossipMenu.GetMenuId());            // new 2.4.0
    data << uint32(titleTextId);
    data << uint32(_gossipMenu.GetMenuItemCount());     // max count 0x10

    for (GossipMenuItemContainer::const_iterator itr = _gossipMenu.GetMenuItems().begin(); itr != _gossipMenu.GetMenuItems().end(); ++itr)
    {
        GossipMenuItem const& item = itr->second;
        data << uint32(itr->first);
        data << uint8(item.MenuItemIcon);
        data << uint8(item.IsCoded);                    // makes pop up box password
        data << uint32(item.BoxMoney);                  // money required to open menu, 2.0.3
        data << item.Message;                           // text for gossip item
        data << item.BoxMessage;                        // accept text (related to money) pop up box, 2.0.3
    }

    data << uint32(_questMenu.GetMenuItemCount());      // max count 0x20

    for (uint32 iI = 0; iI < _questMenu.GetMenuItemCount(); ++iI)
    {
        QuestMenuItem const& item = _questMenu.GetItem(iI);
        uint32 questID = item.QuestId;
        Quest const* quest = sObjectMgr->GetQuestTemplate(questID);

        data << uint32(questID);
        data << uint32(item.QuestIcon);
        data << int32(quest->GetQuestLevel());
        data << uint32(quest->GetFlags());              // 3.3.3 quest flags
        data << uint8(0);                               // 3.3.3 changes icon: blue question or yellow exclamation
        std::string title = quest->GetTitle();

        int locale = _session->GetSessionDbLocaleIndex();
        if (locale >= 0)
            if (QuestLocale const* localeData = sObjectMgr->GetQuestLocale(questID))
                ObjectMgr::GetLocaleString(localeData->Title, locale, title);

        data << title;                                  // max 0x200
    }

    _session->SendPacket(&data);
}

void PlayerMenu::SendCloseGossip() const
{
    WorldPacket data(SMSG_GOSSIP_COMPLETE, 0);
    _session->SendPacket(&data);
}

void PlayerMenu::SendPointOfInterest(uint32 poiId) const
{
    PointOfInterest const* poi = sObjectMgr->GetPointOfInterest(poiId);
    if (!poi)
    {
        sLog->outErrorDb("Request to send non-existing POI (Id: %u), ignored.", poiId);
        return;
    }

    std::string iconText = poi->icon_name;
    int32 locale = _session->GetSessionDbLocaleIndex();
    if (locale >= 0)
        if (PointOfInterestLocale const *localeData = sObjectMgr->GetPointOfInterestLocale(poiId))
            ObjectMgr::GetLocaleString(localeData->IconName, locale, iconText);

    WorldPacket data(SMSG_GOSSIP_POI, 4 + 4 + 4 + 4 + 4 + 10);  // guess size
    data << uint32(poi->flags);
    data << float(poi->x);
    data << float(poi->y);
    data << uint32(poi->icon);
    data << uint32(poi->data);
    data << iconText;

    _session->SendPacket(&data);
}

/*********************************************************/
/***                    QUEST SYSTEM                   ***/
/*********************************************************/

QuestMenu::QuestMenu()
{
    _questMenuItems.reserve(16);                                   // can be set for max from most often sizes to speedup push_back and less memory use
}

QuestMenu::~QuestMenu()
{
    ClearMenu();
}

void QuestMenu::AddMenuItem(uint32 QuestId, uint8 Icon)
{
    if (!sObjectMgr->GetQuestTemplate(QuestId))
        return;

    ASSERT(_questMenuItems.size() <= GOSSIP_MAX_MENU_ITEMS);

    QuestMenuItem questMenuItem;

    questMenuItem.QuestId        = QuestId;
    questMenuItem.QuestIcon      = Icon;

    _questMenuItems.push_back(questMenuItem);
}

bool QuestMenu::HasItem(uint32 questId) const
{
    for (QuestMenuItemList::const_iterator i = _questMenuItems.begin(); i != _questMenuItems.end(); ++i)
        if (i->QuestId == questId)
            return true;

    return false;
}

void QuestMenu::ClearMenu()
{
    _questMenuItems.clear();
}

void PlayerMenu::SendQuestGiverQuestList(QEmote eEmote, const std::string& Title, uint64 npcGUID)
{
    WorldPacket data(SMSG_QUESTGIVER_QUEST_LIST, 100);    // guess size
    data << uint64(npcGUID);
    data << Title;
    data << uint32(eEmote._Delay);                         // player emote
    data << uint32(eEmote._Emote);                         // NPC emote

    size_t count_pos = data.wpos();
    data << uint8 (_questMenu.GetMenuItemCount());
    uint32 count = 0;
    for (; count < _questMenu.GetMenuItemCount(); ++count)
    {
        QuestMenuItem const& qmi = _questMenu.GetItem(count);

        uint32 questID = qmi.QuestId;

        if (Quest const *pQuest = sObjectMgr->GetQuestTemplate(questID))
        {
            std::string title = pQuest->GetTitle();

            int loc_idx = _session->GetSessionDbLocaleIndex();
            if (loc_idx >= 0)
                if (QuestLocale const *ql = sObjectMgr->GetQuestLocale(questID))
                    ObjectMgr::GetLocaleString(ql->Title, loc_idx, title);

            data << uint32(questID);
            data << uint32(qmi.QuestIcon);
            data << int32(pQuest->GetQuestLevel());
            data << uint32(pQuest->GetFlags());             // 3.3.3 quest flags
            data << uint8(0);                               // 3.3.3 changes icon: blue question or yellow exclamation
            data << title;
        }
    }

    data.put<uint8>(count_pos, count);
    _session->SendPacket(&data);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent SMSG_QUESTGIVER_QUEST_LIST NPC Guid=%u", GUID_LOPART(npcGUID));
}

void PlayerMenu::SendQuestGiverStatus(uint32 questStatus, uint64 npcGUID) const
{
    WorldPacket data(SMSG_QUESTGIVER_STATUS, 12);
    data << uint64(npcGUID);
    data << uint32(questStatus);

    _session->SendPacket(&data);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent SMSG_QUESTGIVER_STATUS NPC Guid=%u, status=%u", GUID_LOPART(npcGUID), questStatus);
}

void PlayerMenu::SendQuestGiverQuestDetails(Quest const *pQuest, uint64 npcGUID, bool ActivateAccept)
{
    std::string Title                   = pQuest->GetTitle();
    std::string Details                 = pQuest->GetDetails();
    std::string Objectives              = pQuest->GetObjectives();
    std::string EndText                 = pQuest->GetEndText();

    int loc_idx = _session->GetSessionDbLocaleIndex();
    if (loc_idx >= 0)
    {
        if (QuestLocale const *ql = sObjectMgr->GetQuestLocale(pQuest->GetQuestId()))
        {
            sObjectMgr->GetLocaleString(ql->Title, loc_idx, Title);
            sObjectMgr->GetLocaleString(ql->Details, loc_idx, Details);
            sObjectMgr->GetLocaleString(ql->Objectives, loc_idx, Objectives);
            sObjectMgr->GetLocaleString(ql->EndText, loc_idx, EndText);
        }
    }

    WorldPacket data(SMSG_QUESTGIVER_QUEST_DETAILS, 150);   // guess size
    data << uint64(npcGUID);
    data << uint64(0);                                      // wotlk, something todo with quest sharing?
    data << uint32(pQuest->GetQuestId());
    data << Title;
    data << Details;
    data << Objectives;
    data << pQuest->GetQuestGiverPortraitText();;
    data << pQuest->GetQuestGiverPortraitUnk();;
    data << pQuest->GetQuestTurnInPortraitText();;
    data << pQuest->GetQuestTurnInPortraitUnk();;
    data << uint32(0);
    data << uint32(0);
    data << uint8(ActivateAccept ? 1 : 0);                  // auto finish
    data << uint32(pQuest->GetFlags());                     // 3.3.3 questFlags
    data << uint32(pQuest->GetSuggestedPlayers());
    data << uint8(0);
    data << uint8(0);                                       // IsFinished? value is sent back to server in quest accept packet
    data << uint32(0);

    ItemTemplate const* IProto;
    data << uint32(pQuest->GetRewChoiceItemsCount());
    for (uint32 i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        data << uint32(pQuest->RewChoiceItemId[i]);

    for (uint32 i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        data << uint32(pQuest->RewChoiceItemCount[i]);

    for (uint32 i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
    {
        IProto = ObjectMgr::GetItemTemplate(pQuest->RewChoiceItemId[i]);
        if (IProto)
            data << uint32(IProto->DisplayInfoID);
        else
            data << uint32(0);
    }

    data << uint32(pQuest->GetRewItemsCount());

    for (uint32 i = 0; i < QUEST_REWARDS_COUNT; ++i)
        data << uint32(pQuest->RewItemId[i]);
    for (uint32 i  =0; i < QUEST_REWARDS_COUNT; ++i)
        data << uint32(pQuest->RewItemCount[i]);
    for (uint32 i = 0; i < QUEST_REWARDS_COUNT; ++i)
    {
        IProto = ObjectMgr::GetItemTemplate(pQuest->RewItemId[i]);

        if (IProto)
            data << uint32(IProto->DisplayInfoID);
        else
            data << uint32(0);
    }

    data << uint32(pQuest->GetQuestTurnInPortraitID());
    data << uint32(pQuest->GetQuestGiverPortraitId());
    data << uint32(pQuest->GetRewOrReqMoney());
    data << uint32(pQuest->XPValue(_session->GetPlayer())*sWorld->getRate(RATE_XP_QUEST));

    // rewarded honor points. Multiply with 10 to satisfy client
    data << float(10 * Strawberry::Honor::hk_honor_at_level(_session->GetPlayer()->getLevel(), pQuest->GetRewHonorMultiplier()));
    data << uint32(pQuest->GetRewSkillLineId());              // 4.0.1
    data << uint32(pQuest->GetRewSkillPoints());              // 4.0.1
    data << uint32(pQuest->GetRewFactionMask());              // 4.0.1

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        data << uint32(pQuest->RewRepFaction[i]);

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        data << int32(pQuest->RewRepValueId[i]);

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        data << int32(pQuest->RewRepValue[i]);

    data << uint32(0);                                      // unk
    data << uint32(pQuest->GetCriteriaSpellID());           // 4.0.1

    for(int i = 0; i < QUEST_CURRENCY_COUNT; i++)
        data << uint32(pQuest->RewCurrencyId[i]);

    for(int i = 0; i < QUEST_CURRENCY_COUNT; i++)
        data << uint32(pQuest->RewCurrencyCount[i]);

    data << uint32(pQuest->GetSoundId());
    data << uint32(pQuest->GetSoundId2());

    data << uint32(QUEST_EMOTE_COUNT);
    for (uint32 i = 0; i < QUEST_EMOTE_COUNT; ++i)
    {
        data << uint32(pQuest->DetailsEmote[i]);
        data << uint32(pQuest->DetailsEmoteDelay[i]);       // DetailsEmoteDelay (in ms)
    }
    _session->SendPacket(&data);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent SMSG_QUESTGIVER_QUEST_DETAILS NPCGuid=%u, questid=%u", GUID_LOPART(npcGUID), pQuest->GetQuestId());
}

void PlayerMenu::SendQuestQueryResponse(Quest const *pQuest)
{
    std::string Title, Details, Objectives, EndText, CompletedText;
    std::string ObjectiveText[QUEST_OBJECTIVES_COUNT];
    Title = pQuest->GetTitle();
    Details = pQuest->GetDetails();
    Objectives = pQuest->GetObjectives();
    EndText = pQuest->GetEndText();
    CompletedText = pQuest->GetCompletedText();

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        ObjectiveText[i]=pQuest->ObjectiveText[i];

    int loc_idx = _session->GetSessionDbLocaleIndex();
    if (loc_idx >= 0)
    {
        if (QuestLocale const *ql = sObjectMgr->GetQuestLocale(pQuest->GetQuestId()))
        {
            sObjectMgr->GetLocaleString(ql->Title, loc_idx, Title);
            sObjectMgr->GetLocaleString(ql->Details, loc_idx, Details);
            sObjectMgr->GetLocaleString(ql->Objectives, loc_idx, Objectives);
            sObjectMgr->GetLocaleString(ql->EndText, loc_idx, EndText);
            sObjectMgr->GetLocaleString(ql->CompletedText, loc_idx, CompletedText);

            for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
                sObjectMgr->GetLocaleString(ql->ObjectiveText[i], loc_idx, ObjectiveText[i]);
        }
    }

    WorldPacket data(SMSG_QUEST_QUERY_RESPONSE, 220);     // guess size

    data << uint32(pQuest->GetQuestId());                   // quest id
    data << uint32(pQuest->GetQuestMethod());               // Accepted values: 0, 1 or 2. 0 == IsAutoComplete() (skip objectives/details)
    data << uint32(pQuest->GetQuestLevel());                // may be -1, static data, in other cases must be used dynamic level: Player::GetQuestLevel (0 is not known, but assuming this is no longer valid for quest intended for client)
    data << uint32(pQuest->GetMinLevel());                  // min level
    data << uint32(pQuest->GetZoneOrSort());                // zone or sort to display in quest log

    data << uint32(pQuest->GetType());                      // quest type
    data << uint32(pQuest->GetSuggestedPlayers());          // suggested players count

    data << uint32(pQuest->GetRepObjectiveFaction());       // shown in quest log as part of quest objective
    data << uint32(pQuest->GetRepObjectiveValue());         // shown in quest log as part of quest objective

    data << uint32(pQuest->GetRepObjectiveFaction2());       // shown in quest log as part of quest objective OPOSITE faction
    data << uint32(pQuest->GetRepObjectiveValue2());         // shown in quest log as part of quest objective OPPOSITE faction

    data << uint32(pQuest->GetNextQuestInChain());          // client will request this quest from NPC, if not 0
    data << uint32(pQuest->GetXPId());                      // used for calculating rewarded experience

    if (pQuest->HasFlag(QUEST_FLAGS_HIDDEN_REWARDS))
        data << uint32(0);                                  // Hide money rewarded
    else
        data << uint32(pQuest->GetRewOrReqMoney());         // reward money (below max lvl)

    data << uint32(pQuest->GetRewMoneyMaxLevel());          // used in XP calculation at client
    data << uint32(pQuest->GetRewSpell());                  // reward spell, this spell will display (icon) (casted if RewSpellCast == 0)
    data << int32(pQuest->GetRewSpellCast());               // casted spell

    // rewarded honor points
    data << uint32(Strawberry::Honor::hk_honor_at_level(_session->GetPlayer()->getLevel(), pQuest->GetRewHonorMultiplier()));
    data << float(0);                                       // new reward honor (multipled by ~62 at client side)
    data << uint32(pQuest->GetSrcItemId());                 // source item id
    data << uint32(pQuest->GetFlags() & 0xFFFF);            // quest flags
    data << uint32(0);                                      // 401
    data << uint32(pQuest->GetCharTitleId());               // CharTitleId, new 2.4.0, player gets this title (id from CharTitles)
    data << uint32(pQuest->GetPlayersSlain());              // players slain
    data << uint32(pQuest->GetBonusTalents());              // bonus talents
    data << uint32(pQuest->GetRewArenaPoints());            // bonus arena points
    data << uint32(pQuest->GetRewSkillLineId());            // reward skill line id
    data << uint32(pQuest->GetRewSkillPoints());            // reward skill points
    data << uint32(pQuest->GetRewFactionMask());            // review rep show mask
    data << uint32(pQuest->GetQuestGiverPortraitId());      // questgiver portrait entry
    data << uint32(pQuest->GetQuestTurnInPortraitID());     // quest turn in portrait entry

    int iI;

    if (pQuest->HasFlag(QUEST_FLAGS_HIDDEN_REWARDS))
    {
        for (iI = 0; iI < QUEST_REWARDS_COUNT; ++iI)
            data << uint32(0) << uint32(0);
        for (iI = 0; iI < QUEST_REWARD_CHOICES_COUNT; ++iI)
            data << uint32(0) << uint32(0);
    }
    else
    {
        for (iI = 0; iI < QUEST_REWARDS_COUNT; ++iI)
        {
            data << uint32(pQuest->RewItemId[iI]);
            data << uint32(pQuest->RewItemCount[iI]);
        }
        for (iI = 0; iI < QUEST_REWARD_CHOICES_COUNT; ++iI)
        {
            data << uint32(pQuest->RewChoiceItemId[iI]);
            data << uint32(pQuest->RewChoiceItemCount[iI]);
        }
    }

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)         // reward factions ids
        data << uint32(pQuest->RewRepFaction[i]);

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)         // columnid+1 QuestFactionReward.dbc?
        data << int32(pQuest->RewRepValueId[i]);

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)         // unk (0)
        data << int32(pQuest->RewRepValue[i]);

    data << pQuest->GetPointMapId();
    data << pQuest->GetPointX();
    data << pQuest->GetPointY();
    data << pQuest->GetPointOpt();

    data << Title;
    data << Objectives;
    data << Details;
    data << EndText;
    data << CompletedText;                                  // display in quest objectives window once all objectives are completed

    for (iI = 0; iI < QUEST_OBJECTIVES_COUNT; ++iI)
    {
        if (pQuest->ReqCreatureOrGOId[iI] < 0)
        {
            // client expected gameobject template id in form (id|0x80000000)
            data << uint32((pQuest->ReqCreatureOrGOId[iI]*(-1))|0x80000000);
        }
        else
        {
            data << uint32(pQuest->ReqCreatureOrGOId[iI]);
        }
        data << uint32(pQuest->ReqCreatureOrGOCount[iI]);
        data << uint32(pQuest->ReqSourceId[iI]);
        data << uint32(pQuest->ReqSourceCount[iI]);
    }

    for (iI = 0; iI < QUEST_ITEM_OBJECTIVES_COUNT; ++iI)
    {
        data << uint32(pQuest->ReqItemId[iI]);
        data << uint32(pQuest->ReqItemCount[iI]);
    }

    data << uint32(pQuest->GetCriteriaSpellID());

    for (iI = 0; iI < QUEST_OBJECTIVES_COUNT; ++iI)
        data << ObjectiveText[iI];

    for(iI = 0; iI < QUEST_CURRENCY_COUNT; ++iI)
    {
        data << uint32(pQuest->RewCurrencyId[iI]);
        data << uint32(pQuest->RewCurrencyCount[iI]);
    }

    for(iI = 0; iI < QUEST_CURRENCY_OBJECTIVES_COUNT; ++iI)
    {
        data << uint32(pQuest->ReqCurrencyId[iI]);
        data << uint32(pQuest->ReqCurrencyCount[iI]);
    }

    data << pQuest->GetQuestGiverPortraitText();
    data << pQuest->GetQuestGiverPortraitUnk();
    data << pQuest->GetQuestTurnInPortraitText();
    data << pQuest->GetQuestTurnInPortraitUnk();

    data << int32(pQuest->GetSoundId());
    data << int32(pQuest->GetSoundId2());

    _session->SendPacket(&data);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent SMSG_QUEST_QUERY_RESPONSE questid = %u", pQuest->GetQuestId());
}

void PlayerMenu::SendQuestGiverOfferReward(Quest const* pQuest, uint64 npcGUID, bool EnableNext)
{
    std::string Title = pQuest->GetTitle();
    std::string OfferRewardText = pQuest->GetOfferRewardText();
    std::string unk = "";

    int loc_idx = _session->GetSessionDbLocaleIndex();
    if (loc_idx >= 0)
    {
        if (QuestLocale const *ql = sObjectMgr->GetQuestLocale(pQuest->GetQuestId()))
        {
            sObjectMgr->GetLocaleString(ql->Title, loc_idx, Title);
            sObjectMgr->GetLocaleString(ql->OfferRewardText, loc_idx, OfferRewardText);
        }
    }

    WorldPacket data(SMSG_QUESTGIVER_OFFER_REWARD, 120);   // guess size

    data << uint64(npcGUID);
    data << uint32(pQuest->GetQuestId());
    data << Title;
    data << OfferRewardText;

    data << pQuest->GetQuestGiverPortraitText();
    data << pQuest->GetQuestGiverPortraitUnk();
    data << pQuest->GetQuestTurnInPortraitText();
    data << pQuest->GetQuestTurnInPortraitUnk();

    data << uint32(0);
    data << uint32(0);

    data << uint8(EnableNext ? 1 : 0);                      // Auto Finish
    data << uint32(pQuest->GetFlags());                     // 3.3.3 questFlags
    data << uint32(pQuest->GetSuggestedPlayers());          // SuggestedGroupNum

    uint32 EmoteCount = 0;
    for (uint32 i = 0; i < QUEST_EMOTE_COUNT; ++i)
    {
        if (pQuest->OfferRewardEmote[i] <= 0)
            break;
        ++EmoteCount;
    }

    data << EmoteCount;                                     // Emote Count
    for (uint32 i = 0; i < EmoteCount; ++i)
    {
        data << uint32(pQuest->OfferRewardEmoteDelay[i]);   // Delay Emote
        data << uint32(pQuest->OfferRewardEmote[i]);
    }

    ItemTemplate const* IProto;

    data << uint32(pQuest->GetRewChoiceItemsCount());
    for (uint32 i=0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        data << uint32(pQuest->RewChoiceItemId[i]);
    for (uint32 i=0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        data << uint32(pQuest->RewChoiceItemCount[i]);
    for (uint32 i=0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
    {
        IProto = ObjectMgr::GetItemTemplate(pQuest->RewChoiceItemId[i]);
        if (IProto)
            data << uint32(IProto->DisplayInfoID);
        else
            data << uint32(0);
    }

    data << uint32(pQuest->GetRewItemsCount());

    for (uint32 i=0; i < QUEST_REWARDS_COUNT; ++i)
        data << uint32(pQuest->RewItemId[i]);
    for (uint32 i=0; i < QUEST_REWARDS_COUNT; ++i)
        data << uint32(pQuest->RewItemCount[i]);
    for (uint32 i=0; i < QUEST_REWARDS_COUNT; ++i)
    {
        IProto = ObjectMgr::GetItemTemplate(pQuest->RewItemId[i]);

        if (IProto)
            data << uint32(IProto->DisplayInfoID);
        else
            data << uint32(0);
    }

    data << uint32(pQuest->GetQuestTurnInPortraitID());
    data << uint32(pQuest->GetQuestGiverPortraitId());
    data << uint32(pQuest->GetRewOrReqMoney());
    data << uint32(pQuest->XPValue(_session->GetPlayer())*sWorld->getRate(RATE_XP_QUEST));

    // rewarded honor points. Multiply with 10 to satisfy client
    data << 10 * Strawberry::Honor::hk_honor_at_level(_session->GetPlayer()->getLevel(), pQuest->GetRewHonorMultiplier());
    data << float(0);                                       // unk, honor multiplier?
    data << uint32(pQuest->GetRewSkillLineId());              // 4.0.1
    data << uint32(pQuest->GetRewSkillPoints());              // 4.0.1
    data << uint32(pQuest->GetRewFactionMask());              // 4.0.1

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)        // reward factions ids
        data << uint32(pQuest->RewRepFaction[i]);

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)        // columnid in QuestFactionReward.dbc (zero based)?
        data << int32(pQuest->RewRepValueId[i]);

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)        // reward reputation override?
        data << uint32(pQuest->RewRepValue[i]);

    data << uint32(0);
    data << uint32(pQuest->GetCriteriaSpellID());           // 4.0.1

    for(int i = 0; i < QUEST_CURRENCY_COUNT; i++)
        data << uint32(pQuest->RewCurrencyId[i]);

    for(int i = 0; i < QUEST_CURRENCY_COUNT; i++)
        data << uint32(pQuest->RewCurrencyCount[i]);

    data << uint32(pQuest->GetSoundId());
    data << uint32(pQuest->GetSoundId2());

    _session->SendPacket(&data);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent SMSG_QUESTGIVER_OFFER_REWARD NPCGuid=%u, questid=%u", GUID_LOPART(npcGUID), pQuest->GetQuestId());
}

void PlayerMenu::SendQuestGiverRequestItems(Quest const *pQuest, uint64 npcGUID, bool Completable, bool CloseOnCancel)
{
    // We can always call to RequestItems, but this packet only goes out if there are actually
    // items.  Otherwise, we'll skip straight to the OfferReward

    std::string Title = pQuest->GetTitle();
    std::string RequestItemsText = pQuest->GetRequestItemsText();

    int loc_idx = _session->GetSessionDbLocaleIndex();
    if (loc_idx >= 0)
    {
        if (QuestLocale const *ql = sObjectMgr->GetQuestLocale(pQuest->GetQuestId()))
        {
            sObjectMgr->GetLocaleString(ql->Title, loc_idx, Title);
            sObjectMgr->GetLocaleString(ql->RequestItemsText, loc_idx, RequestItemsText);
        }
    }

    if (!pQuest->GetReqItemsCount() && Completable)
    {
        SendQuestGiverOfferReward(pQuest, npcGUID, true);
        return;
    }

    WorldPacket data(SMSG_QUESTGIVER_REQUEST_ITEMS, 60);  // guess size
    data << uint64(npcGUID);
    data << uint32(pQuest->GetQuestId());
    data << Title;
    data << RequestItemsText;

    data << uint32(0);                                    // unk

    if (Completable)
        data << pQuest->GetCompleteEmote();
    else
        data << pQuest->GetIncompleteEmote();

    // Close Window after cancel
    if (CloseOnCancel)
        data << uint32(0x01);
    else
        data << uint32(0x00);

    data << uint32(pQuest->GetFlags());                     // 3.3.3 questFlags
    data << uint32(pQuest->GetSuggestedPlayers());          // SuggestedGroupNum

    // Required Money
    data << uint32(pQuest->GetRewOrReqMoney() < 0 ? -pQuest->GetRewOrReqMoney() : 0);

    data << uint32(pQuest->GetReqItemsCount());
    ItemTemplate const *pItem;
    for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
    {
        if (!pQuest->ReqItemId[i])
            continue;

        pItem = ObjectMgr::GetItemTemplate(pQuest->ReqItemId[i]);

        data << uint32(pQuest->ReqItemId[i]);
        data << uint32(pQuest->ReqItemCount[i]);

        if (pItem)
            data << uint32(pItem->DisplayInfoID);
        else
            data << uint32(0);
    }

    uint32 counter = 0;
    data << counter;
    for(uint32 i = 0; i < counter; i++)
    {
        data << uint32(0);
        data << uint32(0);
    }

    if (!Completable)
        data << uint32(0x00);
    else
        data << uint32(0x02);

    data << uint32(0x04);
    data << uint32(0x08);
    data << uint32(0x10);
    data << uint32(0x40);

    _session->SendPacket(&data);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Sent SMSG_QUESTGIVER_REQUEST_ITEMS NPCGuid = %u, questid = %u", GUID_LOPART(npcGUID), pQuest->GetQuestId());
}
