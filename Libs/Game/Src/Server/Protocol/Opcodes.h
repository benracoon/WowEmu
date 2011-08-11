/*
 * Copyright (C) 2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
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

#ifndef OPCODE_HANDLER
#define OPCODE_HANDLER

#include "Common.h"

// Note: this include need for be sure have full definition of class WorldSession
//       if this class definition not complete then VS for x64 release use different size for
//       struct OpcodeHandler in this header and Opcode.cpp and get totally wrong data from
//       table opcodeTable in source when Opcode.h included but WorldSession.h not included
#include "WorldSession.h"

typedef UNORDERED_MAP<std::string, uint16> OpcodeTableContainer;
extern OpcodeTableContainer opcodeTableMap;

class OpcodeTableHandler
{
    public:
        void LoadOpcodesFromDB();

        uint16 GetOpcodeTable(const char* name);
};

#define sOpcodeTableHandler ACE_Singleton<OpcodeTableHandler, ACE_Null_Mutex>::instance()

enum Opcodes
{
    /**************************************************************************************
    ####################################CLIENTOPCODES#####################################
    **************************************************************************************/

    /********************************************/
    /******************AUTHCHECK*****************/
    /********************************************/
    MSG_RESUME_COMMS,

    /***********************************************************/
    /*********************ATTACKOPCODES**********************/
    /***********************************************************/
    CMSG_ATTACKSWING,
    CMSG_ATTACKSTOP,

    /***********************************************************/
    /********************AUCTIONOPCODES**********************/
    /***********************************************************/
    CMSG_AUCTION_SELL_ITEM,
    CMSG_AUCTION_REMOVE_ITEM,
    CMSG_AUCTION_LIST_ITEMS,
    CMSG_AUCTION_LIST_OWNER_ITEMS,
    CMSG_AUCTION_PLACE_BID,
    CMSG_AUCTION_LIST_BIDDER_ITEMS,
    CMSG_AUCTION_LIST_PENDING_SALES,

    /***********************************************************/
    /*****************AUTHENTICATIONOPCODES******************/
    /***********************************************************/
    CMSG_AUTH_SESSION,
    CMSG_REALM_SPLIT,
    CMSG_REDIRECTION_AUTH_PROOF,

    //SRP6
    CMSG_AUTH_SRP6_BEGIN,
    CMSG_AUTH_SRP6_PROOF,
    CMSG_AUTH_SRP6_RECODE,

    /***********************************************************/
    /*******************BATTLEFIELDOPCODES*******************/
    /***********************************************************/
    CMSG_BATTLEFIELD_LIST,
    CMSG_BATTLEFIELD_JOIN,
    CMSG_REQUEST_RATED_BG_INFO,
    CMSG_BATTLEFIELD_STATUS,
    CMSG_BATTLEFIELD_PORT,
    CMSG_BATTLEMASTER_HELLO,
    CMSG_LEAVE_BATTLEFIELD,
    CMSG_BATTLEMASTER_JOIN_ARENA,
    CMSG_BATTLEMASTER_JOIN,
    CMSG_BATTLEFIELD_MGR_ENTRY_INVITE_RESPONSE,
    CMSG_BATTLEFIELD_MGR_QUEUE_INVITE_RESPONSE,
    CMSG_BATTLEFIELD_MGR_QUEUE_REQUEST,
    CMSG_BATTLEFIELD_MGR_EXIT_REQUEST,

    /***********************************************************/
    /*******************BATTLEFIELDOPCODES*******************/
    /***********************************************************/
    CMSG_REQUEST_RATED_BATTLEGROUND_INFO,

    /***********************************************************/
    /********************CALENDAROPCODES*********************/
    /***********************************************************/
    CMSG_CALENDAR_GET_CALENDAR,
    CMSG_CALENDAR_GET_EVENT,
    CMSG_CALENDAR_GUILD_FILTER,
    CMSG_CALENDAR_ARENA_TEAM,
    CMSG_CALENDAR_ADD_EVENT,
    CMSG_CALENDAR_UPDATE_EVENT,
    CMSG_CALENDAR_REMOVE_EVENT,
    CMSG_CALENDAR_COPY_EVENT,
    CMSG_CALENDAR_EVENT_INVITE,
    CMSG_CALENDAR_EVENT_RSVP,
    CMSG_CALENDAR_EVENT_REMOVE_INVITE,
    CMSG_CALENDAR_EVENT_STATUS,
    CMSG_CALENDAR_EVENT_MODERATOR_STATUS,
    CMSG_CALENDAR_COMPLAIN,
    CMSG_CALENDAR_GET_NUM_PENDING,
    CMSG_CALENDAR_CONTEXT_EVENT_SIGNUP,

    /***********************************************************/
    /********************CHARACTEROPCODES********************/
    /***********************************************************/
    CMSG_MOVE_CHARACTER_CHEAT,
    CMSG_CHAR_CREATE,
    CMSG_CHAR_ENUM,
    CMSG_CHAR_DELETE,
    CMSG_CHARACTER_POINT_CHEAT,
    CMSG_CHAR_RENAME,
    CMSG_CHAR_CUSTOMIZE,
    CMSG_CHAR_FACTION_CHANGE,
    CMSG_CHAR_RACE_CHANGE,

    //CharacterWorldLogin/Logout
    CMSG_PLAYER_LOGIN,
    CMSG_PLAYER_LOGOUT,
    CMSG_LOGOUT_REQUEST,
    CMSG_LOGOUT_CANCEL,

    /***********************************************************/
    /**********************CHATOPCODES***********************/
    /***********************************************************/
    CMSG_CHAT_IGNORED,
    CMSG_CHAT_FILTERED,

    //ChatMessage
    CMSG_MESSAGECHAT_SAY,
    CMSG_MESSAGECHAT_YELL,
    CMSG_MESSAGECHAT_CHANNEL,
    CMSG_MESSAGECHAT_WHISPER,
    CMSG_MESSAGECHAT_GUILD,
    CMSG_MESSAGECHAT_OFFICER,
    CMSG_MESSAGECHAT_AFK,
    CMSG_MESSAGECHAT_DND,
    CMSG_MESSAGECHAT_EMOTE,
    CMSG_MESSAGECHAT_PARTY,
    CMSG_MESSAGECHAT_PARTY_LEADER,
    CMSG_MESSAGECHAT_RAID,
    CMSG_MESSAGECHAT_RAID_LEADER,
    CMSG_MESSAGECHAT_BATTLEGROUND,
    CMSG_MESSAGECHAT_BATTLEGROUND_LEADER,
    CMSG_MESSAGECHAT_RAID_WARNING,

    //Channel
    CMSG_JOIN_CHANNEL,
    CMSG_LEAVE_CHANNEL,
    CMSG_CHANNEL_LIST,
    CMSG_CHANNEL_PASSWORD,
    CMSG_CHANNEL_SET_OWNER,
    CMSG_CHANNEL_OWNER,
    CMSG_CHANNEL_MODERATOR,
    CMSG_CHANNEL_UNMODERATOR,
    CMSG_CHANNEL_MUTE,
    CMSG_CHANNEL_UNMUTE,
    CMSG_CHANNEL_INVITE,
    CMSG_CHANNEL_KICK,
    CMSG_CHANNEL_ROSTER_INFO,
    CMSG_CHANNEL_BAN,
    CMSG_CHANNEL_UNBAN,
    CMSG_CHANNEL_ANNOUNCEMENTS,
    CMSG_CHANNEL_SILENCE_VOICE,
    CMSG_CHANNEL_SILENCE_ALL,
    CMSG_CHANNEL_UNSILENCE_VOICE,
    CMSG_CHANNEL_UNSILENCE_ALL,
    CMSG_CHANNEL_DISPLAY_LIST,
    CMSG_GET_CHANNEL_MEMBER_COUNT,
    CMSG_SET_CHANNEL_WATCH,
    CMSG_CLEAR_CHANNEL_WATCH,
    CMSG_DECLINE_CHANNEL_INVITE,

    /***********************************************************/
    /**********************DUELOPCODES***********************/
    /***********************************************************/
    CMSG_DUEL_ACCEPTED,
    CMSG_DUEL_CANCELLED,

    /***********************************************************/
    /********************FACTIONOPCODES**********************/
    /***********************************************************/
    CMSG_SET_FACTION_ATWAR,
    CMSG_SET_ACTION_BUTTON,
    CMSG_RESET_FACTION_CHEAT,
    CMSG_SET_FACTION_INACTIVE,
    CMSG_SET_WATCHED_FACTION,

    /***********************************************************/
    /*******************GAMEMASTEROPCODES********************/
    /***********************************************************/
    CMSG_GMRESPONSE_RESOLVE,
    CMSG_GM_REPORT_LAG,

    //GamemasterTicket
    CMSG_GMTICKET_CREATE,
    CMSG_GMTICKET_UPDATETEXT,
    CMSG_GMTICKET_GETTICKET,
    CMSG_GMTICKET_DELETETICKET,
    CMSG_GMTICKET_SYSTEMSTATUS,
    CMSG_GMSURVEY_SUBMIT,

    /***********************************************************/
    /******************(GAME)OBJECTOPCODES*******************/
    /***********************************************************/
    CMSG_GAMEOBJ_USE,
    CMSG_GAMEOBJ_REPORT_USE,

    /***********************************************************/
    /**********************GOSSIPOPCODES*********************/
    /***********************************************************/
    CMSG_GOSSIP_HELLO,
    CMSG_GOSSIP_SELECT_OPTION,
    CMSG_NPC_TEXT_QUERY,

    //GossipQuestgiver
    CMSG_QUESTGIVER_STATUS_QUERY,
    CMSG_QUESTGIVER_HELLO,
    CMSG_QUESTGIVER_QUERY_QUEST,
    CMSG_QUESTGIVER_QUEST_AUTOLAUNCH,
    CMSG_QUESTGIVER_ACCEPT_QUEST,
    CMSG_QUESTGIVER_COMPLETE_QUEST,
    CMSG_QUESTGIVER_REQUEST_REWARD,
    CMSG_QUESTGIVER_CHOOSE_REWARD,
    CMSG_QUESTGIVER_CANCEL,

    //GossipTrainer
    CMSG_TRAINER_LIST,
    CMSG_TRAINER_BUY_SPELL,

    /***********************************************************/
    /**********************GROUPOPCODES**********************/
    /***********************************************************/
    CMSG_GROUP_INVITE,
    CMSG_GROUP_CANCEL,
    CMSG_GROUP_ACCEPT,
    CMSG_GROUP_DECLINE,
    CMSG_GROUP_UNINVITE,
    CMSG_GROUP_UNINVITE_GUID,
    CMSG_GROUP_SET_LEADER,
    CMSG_GROUP_DISBAND,
    CMSG_GROUP_CHANGE_SUB_GROUP,
    CMSG_GROUP_SWAP_SUB_GROUP,
    CMSG_GROUP_RAID_CONVERT,
    CMSG_GROUP_ASSISTANT_LEADER,

    /***********************************************************/
    /**********************GUILDOPCODES**********************/
    /***********************************************************/
    CMSG_GUILD_CREATE,
    CMSG_GUILD_INVITE,
    CMSG_GUILD_ACCEPT,
    CMSG_GUILD_DECLINE,
    CMSG_GUILD_INFO,
    CMSG_GUILD_ROSTER,
    CMSG_GUILD_PROMOTE,
    CMSG_GUILD_DEMOTE,
    CMSG_GUILD_LEAVE,
    CMSG_GUILD_REMOVE,
    CMSG_GUILD_DISBAND,
    CMSG_GUILD_LEADER,
    CMSG_GUILD_MOTD,
    CMSG_QUERY_GUILD_REWARDS,
    CMSG_QUERY_GUILD_MAX_XP,
    CMSG_QUERY_GUILD_XP,
    CMSG_GUILD_RANK,
    CMSG_GUILD_ADD_RANK,
    CMSG_GUILD_DEL_RANK,
    CMSG_GUILD_SET_NOTE,
    CMSG_GUILD_INFO_TEXT,
    CMSG_MAELSTROM_RENAME_GUILD,

    //GuildBank
    CMSG_GUILD_BANKER_ACTIVATE,
    CMSG_GUILD_BANK_QUERY_TAB,
    CMSG_GUILD_BANK_SWAP_ITEMS,
    CMSG_GUILD_BANK_BUY_TAB,
    CMSG_GUILD_BANK_UPDATE_TAB,
    CMSG_GUILD_BANK_DEPOSIT_MONEY,
    CMSG_GUILD_BANK_WITHDRAW_MONEY,
    CMSG_GUILD_BANK_NOTE,
    CMSG_SET_GUILD_BANK_TEXT,

    //GuildPetition
    CMSG_PETITION_SHOWLIST,
    CMSG_PETITION_BUY,
    CMSG_PETITION_SHOW_SIGNATURES,
    CMSG_PETITION_SIGN,
    CMSG_OFFER_PETITION,
    CMSG_TURN_IN_PETITION,
    CMSG_PETITION_QUERY,

    //GuildParty
    CMSG_REQUEST_PARTY_MEMBER_STATS,
    CMSG_PARTY_SILENCE,
    CMSG_PARTY_UNSILENCE,

    /***********************************************************/
    /********************INSTANCEOPCODES*********************/
    /***********************************************************/
    CMSG_INSTANCE_LOCK_WARNING_RESPONSE,
    CMSG_REQUEST_RAID_INFO,
    CMSG_SET_ALLOW_LOW_LEVEL_RAID1,
    CMSG_SET_ALLOW_LOW_LEVEL_RAID2,

    //LFG
    CMSG_LFG_JOIN,
    CMSG_LFG_LEAVE,
    CMSG_SEARCH_LFG_JOIN,
    CMSG_SEARCH_LFG_LEAVE,
    CMSG_LFG_PROPOSAL_RESULT,
    CMSG_SET_LFG_COMMENT,
    CMSG_LFG_SET_ROLES,
    CMSG_LFG_SET_NEEDS,
    CMSG_LFG_SET_BOOT_VOTE,
    CMSG_LFD_PLAYER_LOCK_INFO_REQUEST,
    CMSG_LFG_TELEPORT,
    CMSG_LFD_PARTY_LOCK_INFO_REQUEST,

    //Meetingstone
    CMSG_MEETINGSTONE_INFO,

    /***********************************************************/
    /**********************ITEMOPCODES***********************/
    /***********************************************************/
    CMSG_USE_ITEM,
    CMSG_OPEN_ITEM,
    CMSG_READ_ITEM,
    CMSG_SWAP_ITEM,
    CMSG_SWAP_INV_ITEM,
    CMSG_SPLIT_ITEM,
    CMSG_DESTROYITEM,
    CMSG_SELL_ITEM,
    CMSG_BUY_ITEM,
    CMSG_WRAP_ITEM,
    CMSG_BUYBACK_ITEM,
    CMSG_REPAIR_ITEM,
    CMSG_SHOWING_HELM,
    CMSG_SHOWING_CLOAK,
    CMSG_SOCKET_GEMS,
    CMSG_CANCEL_TEMP_ENCHANTMENT,
    CMSG_UPDATE_MISSILE_TRAJECTORY,
    CMSG_ITEM_REFUND_INFO,
    CMSG_ITEM_REFUND,
    CMSG_UPDATE_PROJECTILE_POSITION,

    //ItemEquipment
    CMSG_AUTOSTORE_GROUND_ITEM,
    CMSG_AUTOSTORE_LOOT_ITEM,
    CMSG_AUTOEQUIP_ITEM,
    CMSG_AUTOSTORE_BAG_ITEM,
    CMSG_AUTOEQUIP_ITEM_SLOT,
    CMSG_EQUIPMENT_SET_DELETE,
    CMSG_AUTOSTORE_BANK_ITEM,
    CMSG_AUTOBANK_ITEM,
    CMSG_EQUIPMENT_SET_SAVE,
    CMSG_EQUIPMENT_SET_USE,

    //Inventory/Trade
    CMSG_INSPECT,
    CMSG_INITIATE_TRADE,
    CMSG_BEGIN_TRADE,
    CMSG_BUSY_TRADE,
    CMSG_IGNORE_TRADE,
    CMSG_ACCEPT_TRADE,
    CMSG_UNACCEPT_TRADE,
    CMSG_CANCEL_TRADE,
    CMSG_SET_TRADE_ITEM,
    CMSG_CLEAR_TRADE_ITEM,
    CMSG_SET_TRADE_GOLD,
    CMSG_LIST_INVENTORY,

    /***********************************************************/
    /**********************LOOTOPCODES***********************/
    /***********************************************************/
    CMSG_LOOT_METHOD,
    CMSG_STORE_LOOT_IN_SLOT,
    CMSG_LOOT,
    CMSG_LOOT_MONEY,
    CMSG_LOOT_RELEASE,
    CMSG_OPT_OUT_OF_LOOT,

    //LootGroup
    CMSG_LOOT_ROLL,
    CMSG_LOOT_MASTER_GIVE,

    /***********************************************************/
    /********************MOVEMENTOPCODES*********************/
    /***********************************************************/
    CMSG_MOVE_SET_RAW_POSITION,
    CMSG_MOVE_KNOCK_BACK_ACK,
    CMSG_MOVE_HOVER_ACK,
    CMSG_MOVE_TIME_SKIPPED,
    CMSG_MOVE_NOT_ACTIVE_MOVER,
    CMSG_MINIGAME_MOVE,
    CMSG_MOVE_CHNG_TRANSPORT,
    CMSG_UNKNOWN_1303,

    //MovementStart/Stop
    CMSG_MOVE_START_SWIM_CHEAT,
    CMSG_MOVE_STOP_SWIM_CHEAT,

    //MovementForce
    CMSG_FORCE_RUN_SPEED_CHANGE_ACK,
    CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK,
    CMSG_FORCE_SWIM_SPEED_CHANGE_ACK,
    CMSG_FORCE_MOVE_ROOT_ACK,
    CMSG_FORCE_MOVE_UNROOT_ACK,
    CMSG_FORCE_WALK_SPEED_CHANGE_ACK,
    CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK,
    CMSG_FORCE_TURN_RATE_CHANGE_ACK,
    CMSG_FORCE_FLIGHT_SPEED_CHANGE_ACK,
    CMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK,
    CMSG_FORCE_PITCH_RATE_CHANGE_ACK,
    CMSG_FORCE_UNK1_SPEED_CHANGE_ACK,
    CMSG_FORCE_UNK2_SPEED_CHANGE_ACK,

    //MovementTeleport/Fall/Fly/Water
    CMSG_MOVE_FALL_RESET,
    CMSG_MOVE_FEATHER_FALL_ACK,
    CMSG_MOVE_WATER_WALK_ACK,
    CMSG_MOVE_FLIGHT_ACK,

    //MovementSet/Unset
    CMSG_MOVE_SET_CAN_FLY_ACK,
    CMSG_MOVE_SET_FLY,
    CMSG_MOVE_SET_RUN_SPEED,

    //Spline
    CMSG_MOVE_SPLINE_DONE,

    //SplineSet/Unset

    /***********************************************************/
    /*********************MOVIEOPCODES***********************/
    /***********************************************************/
    //Cinematic
    CMSG_TRIGGER_CINEMATIC_CHEAT,
    CMSG_OPENING_CINEMATIC,
    CMSG_NEXT_CINEMATIC_CAMERA,
    CMSG_COMPLETE_CINEMATIC,

    //Movie
    CMSG_COMPLETE_MOVIE,

    /***********************************************************/
    /******************MOUNT/PETOPCODES********************/
    /***********************************************************/
    CMSG_MOUNTSPECIAL_ANIM,
    CMSG_CANCEL_MOUNT_AURA,

    //Pet
    CMSG_PET_SET_ACTION,
    CMSG_PET_ACTION,
    CMSG_PET_ABANDON,
    CMSG_PET_RENAME,
    CMSG_PET_STOP_ATTACK,
    CMSG_PET_UNLEARN,
    CMSG_PET_LEARN_TALENT,
    CMSG_PET_UNLEARN_TALENTS,

    /***********************************************************/
    /*********************PLAYEROPCODES**********************/
    /***********************************************************/
    CMSG_PLAYER_DIFFICULTY_CHANGE,
    CMSG_SET_ACTIONBAR_TOGGLES,
    CMSG_SET_PLAYER_DECLINED_NAMES,

    //PlayerAchievement
    CMSG_QUERY_INSPECT_ACHIEVEMENTS,
    CMSG_CHECK_LOGIN_CRITERIA,

    //Friends/Contacts/...
    CMSG_WHO,
    CMSG_WHOIS,
    CMSG_CONTACT_LIST,
    CMSG_ADD_FRIEND,
    CMSG_DEL_FRIEND,
    CMSG_ADD_IGNORE,
    CMSG_DEL_IGNORE,
    CMSG_SET_CONTACT_NOTES,

    //PlayerDance
    CMSG_PLAY_DANCE,
    CMSG_STOP_DANCE,
    CMSG_SYNC_DANCE,
    CMSG_DANCE_QUERY,

    //PlayerLevel
    CMSG_GRANT_LEVEL,
    CMSG_ACCEPT_LEVEL_GRANT,

    //PlayerPet
    CMSG_STABLE_REVIVE_PET,
    CMSG_STABLE_CHANGE_SLOT,
    CMSG_REQUEST_PET_INFO,

    //PlayerPVP/Honor/...
    CMSG_REQUEST_PVP_OPTIONS_ENABLED,
    CMSG_TOGGLE_PVP,
    CMSG_SET_TITLE,
    CMSG_REPORT_PVP_AFK,

    //PlayerArena
    CMSG_ARENA_TEAM_CREATE,
    CMSG_ARENA_TEAM_QUERY,
    CMSG_ARENA_TEAM_ROSTER,
    CMSG_ARENA_TEAM_INVITE,
    CMSG_ARENA_TEAM_ACCEPT,
    CMSG_ARENA_TEAM_DECLINE,
    CMSG_ARENA_TEAM_LEAVE,
    CMSG_ARENA_TEAM_REMOVE,
    CMSG_ARENA_TEAM_DISBAND,
    CMSG_ARENA_TEAM_LEADER,

    //PlayerTutorial
    CMSG_TUTORIAL_FLAG,
    CMSG_TUTORIAL_CLEAR,
    CMSG_TUTORIAL_RESET,

    //PlayerEmote
    CMSG_EMOTE,
    CMSG_TEXT_EMOTE,

    //PlayerCorpse/Resurrect/Death
    CMSG_SETDEATHBINDPOINT,
    CMSG_REPOP_REQUEST,
    CMSG_RESURRECT_RESPONSE,
    CMSG_RECLAIM_CORPSE,
    CMSG_HEARTH_AND_RESURRECT,
    CMSG_RETURN_TO_GRAVEYARD,

    //PlayerGlyph
    CMSG_REMOVE_GLYPH,//Testitingame

    //PlayerTalent/Skill
    CMSG_LEARN_TALENT,
    CMSG_LEARN_PREVIEW_TALENTS,
    CMSG_LEARN_PREVIEW_TALENTS_PET,

    //PlayerMail
    CMSG_SEND_MAIL,
    CMSG_GET_MAIL_LIST,
    CMSG_MAIL_TAKE_MONEY,
    CMSG_MAIL_TAKE_ITEM,
    CMSG_MAIL_MARK_AS_READ,
    CMSG_MAIL_RETURN_TO_SENDER,
    CMSG_MAIL_DELETE,
    CMSG_MAIL_CREATE_TEXT_ITEM,

    //PlayerVoice
    CMSG_VOICE_SESSION_ENABLE,
    CMSG_SET_ACTIVE_VOICE_CHANNEL,
    CMSG_CHANNEL_VOICE_ON,
    CMSG_CHANNEL_VOICE_OFF,
    CMSG_ADD_VOICE_IGNORE,
    CMSG_DEL_VOICE_IGNORE,

    //PlayerTotem
    CMSG_TOTEM_DESTROYED,

    /***********************************************************/
    /*********************QUERYOPCODES***********************/
    /***********************************************************/
    CMSG_NAME_QUERY,
    CMSG_PET_NAME_QUERY,
    CMSG_GUILD_QUERY,
    CMSG_PAGE_TEXT_QUERY,
    CMSG_QUEST_QUERY,
    CMSG_GAMEOBJECT_QUERY,
    CMSG_CREATURE_QUERY,
    CMSG_ITEM_TEXT_QUERY,
    CMSG_CORPSE_MAP_POSITION_QUERY,

    /***********************************************************/
    /*********************QUESTOPCODES***********************/
    /***********************************************************/
    CMSG_QUESTLOG_SWAP_QUEST,
    CMSG_QUESTLOG_REMOVE_QUEST,
    CMSG_QUEST_CONFIRM_ACCEPT,
    CMSG_PUSHQUESTTOPARTY,
    CMSG_QUEST_POI_QUERY,
    CMSG_QUERY_QUESTS_COMPLETED,

    //Questgiver
    CMSG_QUESTGIVER_STATUS_MULTIPLE_QUERY,

    /***********************************************************/
    /*********************SPELLOPCODES***********************/
    /***********************************************************/
    CMSG_CAST_SPELL,
    CMSG_CANCEL_CAST,
    CMSG_CANCEL_CHANNELLING,
    CMSG_CANCEL_AUTO_REPEAT_SPELL,
    CMSG_SUMMON_RESPONSE,
    CMSG_SPELLCLICK,

    //SpellAura
    CMSG_CANCEL_AURA,
    CMSG_PET_CANCEL_AURA,
    CMSG_CANCEL_GROWTH_AURA,

    //SpellPet
    CMSG_PET_CAST_SPELL,
    CMSG_PET_SPELL_AUTOCAST,

    /***********************************************************/
    /*******************TRANSPORTOPCODES*********************/
    /***********************************************************/
    //TransportTaxi
    CMSG_TAXISHOWNODES,
    CMSG_TAXINODE_STATUS_QUERY,
    CMSG_TAXIQUERYAVAILABLENODES,
    CMSG_ACTIVATETAXI,
    CMSG_ACTIVATETAXIEXPRESS,
    CMSG_SET_TAXI_BENCHMARK_MODE,
    CMSG_ENABLETAXI,

    /***********************************************************/
    /******************TIME/SPEEDOPCODES*******************/
    /***********************************************************/
    //Time
    CMSG_GAMETIME_SET,
    CMSG_SERVERTIME,
    CMSG_PLAYED_TIME,
    CMSG_QUERY_TIME,
    CMSG_TIME_SYNC_RESP,
    CMSG_KEEP_ALIVE,
    CMSG_WORLD_STATE_UI_TIMER_UPDATE,
    CMSG_READY_FOR_ACCOUNT_DATA_TIMES,

    //Speed
    CMSG_GAMESPEED_SET,

    /***********************************************************/
    /******************UNCATEGORZIEDOPCODES******************/
    /***********************************************************/
    CMSG_AREATRIGGER,
    CMSG_STANDSTATECHANGE,
    CMSG_SET_SELECTION,
    CMSG_BINDER_ACTIVATE,
    CMSG_BANKER_ACTIVATE,
    CMSG_BUY_BANK_SLOT,
    CMSG_BUG,
    CMSG_PING,
    CMSG_SETSHEATHED,
    CMSG_ZONEUPDATE,
    CMSG_UNLEARN_SKILL,
    CMSG_SPIRIT_HEALER_ACTIVATE,
    CMSG_SET_AMMO,
    CMSG_SET_ACTIVE_MOVER,
    CMSG_FAR_SIGHT,
    CMSG_SELF_RES,
    CMSG_AREA_SPIRIT_HEALER_QUERY,
    CMSG_AREA_SPIRIT_HEALER_QUEUE,
    CMSG_WARDEN_DATA,
    CMSG_COMPLAIN,
    CMSG_GET_MIRRORIMAGE_DATA,
    CMSG_ALTER_APPEARANCE,
    CMSG_DISMISS_CRITTER,

    //Commentator
    CMSG_COMMENTATOR_ENABLE,
    CMSG_COMMENTATOR_GET_MAP_INFO,
    CMSG_COMMENTATOR_GET_PLAYER_INFO,
    CMSG_COMMENTATOR_ENTER_INSTANCE,
    CMSG_COMMENTATOR_EXIT_INSTANCE,
    CMSG_COMMENTATOR_INSTANCE_COMMAND,
    CMSG_COMMENTATOR_SKIRMISH_QUEUE_COMMAND,
    CMSG_COMMENTATOR_START_WARGAME,

    //Vehicle
    CMSG_DISMISS_CONTROLLED_VEHICLE,
    CMSG_REQUEST_VEHICLE_EXIT,
    CMSG_REQUEST_VEHICLE_PREV_SEAT,
    CMSG_REQUEST_VEHICLE_NEXT_SEAT,
    CMSG_REQUEST_VEHICLE_SWITCH_SEAT,
    CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE,
    CMSG_QUERY_VEHICLE_STATUS,
    CMSG_PLAYER_VEHICLE_ENTER,
    CMSG_EJECT_PASSENGER,

    /***********************************************************/
    /**********************WORLDOPCODES**********************/
    /***********************************************************/
    //WorldTeleport
    CMSG_WORLD_TELEPORT,
    CMSG_WORLD_LOGIN,
    CMSG_TELEPORT_TO_UNIT,
    CMSG_REQUEST_ACCOUNT_DATA,
    CMSG_UPDATE_ACCOUNT_DATA,

    /**************************************************************************************
    #################################CLIENTSERVEROPCODES##################################
    **************************************************************************************/

    /********************************************/
    /*************CHANNELOPCODES**************/
    /********************************************/
    MSG_CHANNEL_START,
    MSG_CHANNEL_UPDATE,

    /********************************************/
    /************GAMEMASTEROPCODES************/
    /********************************************/
    MSG_GM_BIND_OTHER,
    MSG_GM_SUMMON,
    MSG_GM_SHOWLABEL,
    MSG_GM_ACCOUNT_ONLINE,
    MSG_GM_DESTROY_CORPSE,
    MSG_GM_RESETINSTANCELIMIT,
    MSG_GM_GEARRATING,
    MSG_GM_CHANGE_ARENA_RATING,

    /********************************************/
    /**************GUILDOPCODES***************/
    /********************************************/
    MSG_SAVE_GUILD_EMBLEM,
    MSG_GUILD_BANK_LOG_QUERY,
    MSG_GUILD_PERMISSIONS,
    MSG_GUILD_BANK_MONEY_WITHDRAWN,
    MSG_GUILD_EVENT_LOG_QUERY,
    MSG_QUERY_GUILD_BANK_TEXT,

    /********************************************/
    /************INSTANCESOPCODES*************/
    /********************************************/
    CMSG_BATTLEGROUND_PLAYER_POSITIONS,
    SMSG_BATTLEGROUND_PLAYER_POSITIONS,
    MSG_RAID_TARGET_UPDATE,
    MSG_RAID_READY_CHECK,
    MSG_SET_DUNGEON_DIFFICULTY,
    MSG_PARTY_ASSIGNMENT,
    MSG_RAID_READY_CHECK_CONFIRM,
    MSG_RAID_READY_CHECK_FINISHED,
    MSG_NOTIFY_PARTY_SQUELCH,
    MSG_SET_RAID_DIFFICULTY,

    /********************************************/
    /*************MOVEMENTOPCODES*************/
    /********************************************/
    //MovementStart
    MSG_MOVE_START_FORWARD,
    MSG_MOVE_START_BACKWARD,
    MSG_MOVE_START_STRAFE_LEFT,
    MSG_MOVE_START_STRAFE_RIGHT,
    MSG_MOVE_START_TURN_LEFT,
    MSG_MOVE_START_TURN_RIGHT,
    MSG_MOVE_START_PITCH_UP,
    MSG_MOVE_START_PITCH_DOWN,
    MSG_MOVE_START_SWIM,
    MSG_MOVE_START_SWIM_CHEAT,
    MSG_MOVE_START_ASCEND,
    MSG_MOVE_START_DESCEND,

    //MovementStop
    MSG_MOVE_STOP,
    MSG_MOVE_STOP_STRAFE,
    MSG_MOVE_STOP_TURN,
    MSG_MOVE_STOP_PITCH,
    MSG_MOVE_STOP_SWIM,
    MSG_MOVE_STOP_SWIM_CHEAT,
    MSG_MOVE_STOP_ASCEND,

    //MovementToggle
    MSG_MOVE_TOGGLE_LOGGING,
    MSG_MOVE_TOGGLE_FALL_LOGGING,
    MSG_MOVE_TOGGLE_COLLISION_CHEAT,
    MSG_MOVE_TOGGLE_GRAVITY_CHEAT,

    //MovementTeleport/Fall/Fly/Water
    MSG_MOVE_TELEPORT,
    MSG_MOVE_TELEPORT_CHEAT,
    MSG_MOVE_TELEPORT_ACK,
    MSG_MOVE_JUMP,
    MSG_MOVE_FALL_LAND,
    MSG_MOVE_WORLDPORT_ACK,
    MSG_MOVE_FEATHER_FALL,
    MSG_MOVE_WATER_WALK,
    MSG_MOVE_UPDATE_CAN_FLY,

    //MovementSet...
    MSG_MOVE_SET_RUN_MODE,
    MSG_MOVE_SET_WALK_MODE,
    MSG_MOVE_SET_RUN_SPEED_CHEAT,
    MSG_MOVE_SET_RUN_SPEED,
    MSG_MOVE_SET_RUN_BACK_SPEED_CHEAT,
    MSG_MOVE_SET_RUN_BACK_SPEED,
    MSG_MOVE_SET_WALK_SPEED_CHEAT,
    MSG_MOVE_SET_WALK_SPEED,
    MSG_MOVE_SET_SWIM_SPEED_CHEAT,
    MSG_MOVE_SET_SWIM_SPEED,
    MSG_MOVE_SET_SWIM_BACK_SPEED_CHEAT,
    MSG_MOVE_SET_SWIM_BACK_SPEED,
    MSG_MOVE_SET_ALL_SPEED_CHEAT,
    MSG_MOVE_SET_TURN_RATE_CHEAT,
    MSG_MOVE_SET_TURN_RATE,
    MSG_MOVE_SET_FACING,
    MSG_MOVE_SET_PITCH,
    MSG_MOVE_SET_RAW_POSITION_ACK,
    MSG_MOVE_SET_FLIGHT_SPEED_CHEAT,
    MSG_MOVE_SET_FLIGHT_SPEED,
    MSG_MOVE_SET_FLIGHT_BACK_SPEED_CHEAT,
    MSG_MOVE_SET_FLIGHT_BACK_SPEED,
    MSG_MOVE_SET_PITCH_RATE_CHEAT,
    MSG_MOVE_SET_PITCH_RATE,

    //MovementUncategorized
    MSG_MOVE_ROOT,
    MSG_MOVE_UNROOT,
    MSG_MOVE_HEARTBEAT,
    MSG_MOVE_KNOCK_BACK,
    MSG_MOVE_HOVER,
    MSG_MOVE_TIME_SKIPPED,
    MSG_MOVE_UNKNOWN_1234,

    /********************************************/
    /*************PETITIONOPCODES*************/
    /********************************************/
    MSG_PETITION_DECLINE,
    MSG_PETITION_RENAME,

    /********************************************/
    /***********UNCATEGORIZEDOPCODES**********/
    /********************************************/
    MSG_MINIMAP_PING,
    MSG_TABARDVENDOR_ACTIVATE,
    MSG_RANDOM_ROLL,
    MSG_CORPSE_QUERY,
    MSG_AUCTION_HELLO,
    MSG_LIST_STABLED_PETS,
    MSG_QUEST_PUSH_RESULT,
    MSG_QUERY_NEXT_MAIL_TIME,
    MSG_TALENT_WIPE_CONFIRM,
    MSG_DELAY_GHOST_TELEPORT,

    //PVP/Arena
    CMSG_INSPECT_HONOR_STATS,
    SMSG_INSPECT_HONOR_STATS,
    MSG_PVP_LOG_DATA,
    CMSG_BATTLEFIELD_REQUEST_SCORE_DATA,
    MSG_INSPECT_ARENA_TEAMS,

    /**************************************************************************************
    ####################################SERVEROPCODES#####################################
    **************************************************************************************/

    /***********************************************************/
    /*********************ATTACKOPCODES**********************/
    /***********************************************************/
    SMSG_ATTACKSTART,
    SMSG_ATTACKSTOP,
    SMSG_ATTACKSWING_NOTINRANGE,
    SMSG_ATTACKSWING_BADFACING,
    SMSG_ATTACKSWING_DEADTARGET,
    SMSG_ATTACKSWING_CANT_ATTACK,
    SMSG_ATTACKERSTATEUPDATE,

    /***********************************************************/
    /********************AUCTIONOPCODES**********************/
    /***********************************************************/
    SMSG_AUCTION_COMMAND_RESULT,
    SMSG_AUCTION_LIST_RESULT,
    SMSG_AUCTION_OWNER_LIST_RESULT,
    SMSG_AUCTION_BIDDER_NOTIFICATION,
    SMSG_AUCTION_OWNER_NOTIFICATION,
    SMSG_AUCTION_BIDDER_LIST_RESULT,
    SMSG_AUCTION_REMOVED_NOTIFICATION,
    SMSG_AUCTION_LIST_PENDING_SALES,

    /***********************************************************/
    /*****************AUTHENTICATIONOPCODES******************/
    /***********************************************************/
    SMSG_AUTH_SRP6_RESPONSE,
    SMSG_AUTH_CHALLENGE,
    SMSG_AUTH_RESPONSE,
    SMSG_REALM_SPLIT,
    SMSG_REDIRECT_CLIENT,

    /***********************************************************/
    /*******************BATTLEFIELDOPCODES*******************/
    /***********************************************************/
    SMSG_BATTLEFIELD_PORT_DENIED,
    SMSG_BATTLEFIELD_MGR_ENTRY_INVITE,
    SMSG_BATTLEFIELD_MGR_ENTERED,
    SMSG_BATTLEFIELD_MGR_QUEUE_INVITE,
    SMSG_BATTLEFIELD_MGR_QUEUE_REQUEST_RESPONSE,
    SMSG_BATTLEFIELD_MGR_EJECT_PENDING,
    SMSG_BATTLEFIELD_MGR_EJECTED,
    SMSG_BATTLEFIELD_MGR_STATE_CHANGE,
    SMSG_BATTLEFIELD_LIST,
    SMSG_BATTLEFIELD_STATUS1,
    SMSG_BATTLEFIELD_STATUS2,
    SMSG_BATTLEFIELD_STATUS3,
    SMSG_BATTLEFIELD_STATUS4,

    /***********************************************************/
    /*********************BINDINGOPCODES*********************/
    /***********************************************************/
    SMSG_BINDPOINTUPDATE,
    SMSG_BINDZONEREPLY,
    SMSG_PLAYERBOUND,
    SMSG_PLAYERBINDERROR,
    SMSG_BINDER_CONFIRM,

    /***********************************************************/
    /********************CALENDAROPCODES*********************/
    /***********************************************************/
    SMSG_CALENDAR_SEND_CALENDAR,
    SMSG_CALENDAR_SEND_EVENT,
    SMSG_CALENDAR_FILTER_GUILD,
    SMSG_CALENDAR_ARENA_TEAM,
    SMSG_CALENDAR_EVENT_INVITE,
    SMSG_CALENDAR_EVENT_INVITE_REMOVED,
    SMSG_CALENDAR_EVENT_STATUS,
    SMSG_CALENDAR_COMMAND_RESULT,
    SMSG_CALENDAR_RAID_LOCKOUT_ADDED,
    SMSG_CALENDAR_RAID_LOCKOUT_REMOVED,
    SMSG_CALENDAR_EVENT_INVITE_ALERT,
    SMSG_CALENDAR_EVENT_INVITE_REMOVED_ALERT,
    SMSG_CALENDAR_EVENT_INVITE_STATUS_ALERT,
    SMSG_CALENDAR_EVENT_REMOVED_ALERT,
    SMSG_CALENDAR_EVENT_UPDATED_ALERT,
    SMSG_CALENDAR_EVENT_MODERATOR_STATUS_ALERT,
    SMSG_CALENDAR_SEND_NUM_PENDING,
    SMSG_CALENDAR_UPDATE_INVITE_LIST,
    SMSG_CALENDAR_UPDATE_INVITE_LIST2,
    SMSG_CALENDAR_UPDATE_INVITE_LIST3,
    SMSG_CALENDAR_ACTION_PENDING,

    /***********************************************************/
    /********************CHARACTEROPCODES********************/
    /***********************************************************/
    SMSG_CHAR_CREATE,
    SMSG_CHAR_ENUM,
    SMSG_COMPRESSED_CHAR_ENUM,
    SMSG_CHAR_DELETE,
    SMSG_CHARACTER_LOGIN_FAILED,
    SMSG_CHAR_RENAME,
    SMSG_CHAR_CUSTOMIZE,
    SMSG_CHAR_FACTION_CHANGE,
    SMSG_CHARACTER_PROFILE,
    SMSG_CHARACTER_PROFILE_REALM_CONNECTED,

    /***********************************************************/
    /**********************CHATOPCODES***********************/
    /***********************************************************/
    SMSG_MESSAGECHAT,
    SMSG_CHAT_WRONG_FACTION,
    SMSG_CHAT_PLAYER_NOT_FOUND,
    SMSG_CHAT_RESTRICTED,
    SMSG_CHAT_PLAYER_AMBIGUOUS,
    SMSG_EXPECTED_SPAM_RECORDS,
    SMSG_DEFENSE_MESSAGE,
    SMSG_MOTD,
    SMSG_SERVER_INFO_RESPONSE,

    //Channel
    SMSG_CHANNEL_NOTIFY,
    SMSG_CHANNEL_LIST,
    SMSG_CHANNEL_MEMBER_COUNT,
    SMSG_AVAILABLE_VOICE_CHANNEL,

    /***********************************************************/
    /*********************COMBATOPCODES**********************/
    /***********************************************************/
    SMSG_CANCEL_COMBAT,

    //CombatLog
    SMSG_SPELLBREAKLOG,
    SMSG_SPELLHEALLOG,
    SMSG_SPELLENERGIZELOG,
    SMSG_BREAK_TARGET,
    SMSG_SPELLLOGMISS,
    SMSG_SPELLLOGEXECUTE,
    SMSG_DEBUGAURAPROC,
    SMSG_PERIODICAURALOG,
    SMSG_SPELLDAMAGESHIELD,
    SMSG_SPELLNONMELEEDAMAGELOG,
    SMSG_SPELLDISPELLOG,
    SMSG_DAMAGE_CALC_LOG,
    SMSG_SPELLINSTAKILLLOG,
    SMSG_SPELLSTEALLOG,
    SMSG_SPELL_CHANCE_PROC_LOG,
    SMSG_AURACASTLOG,
    SMSG_RESISTLOG,
    SMSG_ENCHANTMENTLOG,
    SMSG_PARTYKILLLOG,
    SMSG_ENVIRONMENTALDAMAGELOG,

    /***********************************************************/
    /**********************DUELOPCODES***********************/
    /***********************************************************/
    SMSG_DUEL_REQUESTED,
    SMSG_DUEL_OUTOFBOUNDS,
    SMSG_DUEL_INBOUNDS,
    SMSG_DUEL_COMPLETE,
    SMSG_DUEL_WINNER,
    SMSG_DUEL_COUNTDOWN,

    /***********************************************************/
    /********************FACTIONOPCODES**********************/
    /***********************************************************/
    SMSG_INITIALIZE_FACTIONS,
    SMSG_SET_FACTION_VISIBLE,
    SMSG_SET_FACTION_STANDING,
    SMSG_SET_FACTION_ATWAR,

    /***********************************************************/
    /*******************GAMEMASTEROPCODES********************/
    /***********************************************************/
    SMSG_GM_PLAYER_INFO,
    SMSG_GM_MESSAGECHAT,
    SMSG_GMRESPONSE_DB_ERROR,
    SMSG_GMRESPONSE_RECEIVED,
    SMSG_GMRESPONSE_STATUS_UPDATE,

    //Ticket
    SMSG_GMTICKET_CREATE,
    SMSG_GMTICKET_UPDATETEXT,
    SMSG_GMTICKET_GETTICKET,
    SMSG_GMTICKET_SYSTEMSTATUS,
    SMSG_GM_TICKET_STATUS_UPDATE,
    SMSG_GMTICKET_DELETETICKET,

    /***********************************************************/
    /******************(GAME)OBJECTOPCODES*******************/
    /***********************************************************/
    SMSG_GAMEOBJECT_CUSTOM_ANIM,
    SMSG_GAMEOBJECT_PAGETEXT,
    SMSG_GAMEOBJECT_DESPAWN_ANIM,
    SMSG_GAMEOBJECT_RESET_STATE,
    SMSG_DUMP_OBJECTS_DATA,

    /***********************************************************/
    /**********************GOSSIPOPCODES*********************/
    /***********************************************************/
    //GossipGeneral
    SMSG_GOSSIP_MESSAGE,
    SMSG_GOSSIP_COMPLETE,
    SMSG_NPC_WONT_TALK,
    SMSG_GOSSIP_POI,

    //GossipQuestgiver
    SMSG_QUESTGIVER_STATUS,
    SMSG_QUESTGIVER_QUEST_LIST,
    SMSG_QUESTGIVER_QUEST_DETAILS,
    SMSG_QUESTGIVER_REQUEST_ITEMS,
    SMSG_QUESTGIVER_OFFER_REWARD,
    SMSG_QUESTGIVER_QUEST_INVALID,
    SMSG_QUESTGIVER_QUEST_COMPLETE,
    SMSG_QUESTGIVER_QUEST_FAILED,
    SMSG_QUESTGIVER_STATUS_MULTIPLE,

    /***********************************************************/
    /**********************GROUPOPCODES**********************/
    /***********************************************************/
    SMSG_GROUP_INVITE,
    SMSG_GROUP_CANCEL,
    SMSG_GROUP_DECLINE,
    SMSG_GROUP_UNINVITE,
    SMSG_GROUP_SET_LEADER,
    SMSG_GROUP_DESTROYED,
    SMSG_GROUP_LIST,
    SMSG_REAL_GROUP_UPDATE,
    SMSG_GROUPACTION_THROTTLED,

    /***********************************************************/
    /**********************GUILDOPCODES**********************/
    /***********************************************************/
    SMSG_GUILD_INVITE,
    SMSG_GUILD_DECLINE,
    SMSG_GUILD_INFO,
    SMSG_GUILD_ROSTER,
    SMSG_GUILD_EVENT,
    SMSG_GUILD_UPDATE_ROSTER,
    SMSG_GUILD_RANK,

    SMSG_GUILD_REWARDS_LIST,
    SMSG_GUILD_TRADESKILL_UPDATE,
    SMSG_GUILD_MAX_DAILY_XP,
    SMSG_GUILD_NEWS_UPDATE,
    SMSG_GUILD_XP_UPDATE,
    SMSG_GUILD_COMMAND_RESULT,
    SMSG_GUILD_BANK_LIST,

    //Party
    SMSG_PARTY_MEMBER_STATS,
    SMSG_PARTY_COMMAND_RESULT,
    SMSG_PARTY_MEMBER_STATS_FULL,
    SMSG_ECHO_PARTY_SQUELCH,

    //Petition
    SMSG_BUY_BANK_SLOT_RESULT,
    SMSG_PETITION_SHOWLIST,
    SMSG_PETITION_SHOW_SIGNATURES,
    SMSG_PETITION_SIGN_RESULTS,
    SMSG_TURN_IN_PETITION_RESULTS,
    SMSG_OFFER_PETITION_ERROR,

    /***********************************************************/
    /********************INSTANCEOPCODES*********************/
    /***********************************************************/
    SMSG_INSTANCE_LOCK_WARNING_QUERY,
    SMSG_UPDATE_INSTANCE_ENCOUNTER_UNIT,
    SMSG_RAID_GROUP_ONLY,
    SMSG_INSTANCE_SAVE_CREATED,
    SMSG_RAID_INSTANCE_INFO,
    SMSG_RAID_INSTANCE_MESSAGE,
    SMSG_UPDATE_INSTANCE_OWNERSHIP,
    SMSG_INSTANCE_DIFFICULTY,
    SMSG_RESET_FAILED_NOTIFY,
    SMSG_RAID_READY_CHECK_ERROR,

    //Lfg
    SMSG_LFG_PLAYER_REWARD,
    SMSG_LFG_TELEPORT_DENIED,
    SMSG_LFG_OFFER_CONTINUE,
    SMSG_LFG_ROLE_CHOSEN,
    SMSG_UPDATE_LFG_LIST,
    SMSG_LFG_PROPOSAL_UPDATE,
    SMSG_LFG_ROLE_CHECK_UPDATE,
    SMSG_LFG_JOIN_RESULT,
    SMSG_LFG_QUEUE_STATUS,
    SMSG_LFG_UPDATE_PLAYER,
    SMSG_LFG_UPDATE_PARTY,
    SMSG_LFG_UPDATE_SEARCH,
    SMSG_LFG_BOOT_PLAYER,
    SMSG_LFG_PLAYER_INFO,
    SMSG_LFG_PARTY_INFO,
    SMSG_LFG_DISABLED,

    //Meetingstone
    SMSG_MEETINGSTONE_SETQUEUE,
    SMSG_MEETINGSTONE_COMPLETE,
    SMSG_MEETINGSTONE_IN_PROGRESS,
    SMSG_MEETINGSTONE_MEMBER_ADDED,

    //Battleground
    SMSG_GROUP_JOINED_BATTLEGROUND,
    SMSG_BATTLEGROUND_PLAYER_JOINED,
    SMSG_BATTLEGROUND_PLAYER_LEFT,
    SMSG_INSTANCE_RESET,
    SMSG_INSTANCE_RESET_FAILED,
    SMSG_UPDATE_LAST_INSTANCE,
    SMSG_JOINED_BATTLEGROUND_QUEUE,
    SMSG_BATTLEGROUND_INFO_THROTTLED,

    /***********************************************************/
    /**********************ITEMOPCODES***********************/
    /***********************************************************/
    SMSG_READ_ITEM_OK,
    SMSG_READ_ITEM_FAILED,
    SMSG_ITEM_COOLDOWN,
    SMSG_ITEM_PUSH_RESULT,
    SMSG_ITEM_REFUND_INFO_RESPONSE,
    SMSG_ITEM_REFUND_RESULT,
    SMSG_UPDATE_ITEM_ENCHANTMENTS,
    SMSG_ITEM_QUERY_SINGLE_RESPONSE,

    //Inventory/Trade
    SMSG_INVENTORY_CHANGE_FAILURE,
    SMSG_OPEN_CONTAINER,
    SMSG_INSPECT,
    SMSG_TRADE_STATUS,
    SMSG_TRADE_STATUS_EXTENDED,
    SMSG_VENDOR_INVENTORY,
    SMSG_EQUIPMENT_SET_LIST,

    //Equipment
    SMSG_EQUIPMENT_SET_SAVED,
    SMSG_EQUIPMENT_SET_USE_RESULT,

    //ItemBuy/Sell
    SMSG_SELL_ITEM,
    SMSG_BUY_ITEM,
    SMSG_BUY_FAILED,

    /***********************************************************/
    /*******************LOGIN/OUTOPCODES*******************/
    /***********************************************************/
    //Logout
    SMSG_LOGOUT_RESPONSE,
    SMSG_LOGOUT_COMPLETE,
    SMSG_LOGOUT_CANCEL_ACK,

    /***********************************************************/
    /**********************LOOTOPCODES***********************/
    /***********************************************************/
    SMSG_LOOT_RESPONSE,
    SMSG_LOOT_RELEASE_RESPONSE,
    SMSG_LOOT_REMOVED,
    SMSG_LOOT_MONEY_NOTIFY,
    SMSG_LOOT_ITEM_NOTIFY,
    SMSG_LOOT_CLEAR_MONEY,
    SMSG_LOOT_LIST,
    SMSG_LOOT_SLOT_CHANGED,

    //LootGroup
    SMSG_LOOT_ALL_PASSED,
    SMSG_LOOT_ROLL_WON,
    SMSG_LOOT_START_ROLL,
    SMSG_LOOT_ROLL,
    SMSG_LOOT_MASTER_LIST,
    SMSG_DYNAMIC_DROP_ROLL_RESULT,

    /***********************************************************/
    /**********************MAILOPCODES***********************/
    /***********************************************************/
    SMSG_SEND_MAIL_RESULT,
    SMSG_MAIL_LIST_RESULT,
    SMSG_RECEIVED_MAIL,

    /***********************************************************/
    /********************MOVEMENTOPCODES*********************/
    /***********************************************************/
    SMSG_PLAYER_MOVE,
    SMSG_MOVE_CHARACTER_CHEAT,
    SMSG_MOVE_WATER_WALK,
    SMSG_MOVE_LAND_WALK,
    SMSG_FORCE_SWIM_SPEED_CHANGE,
    SMSG_MOVE_KNOCK_BACK,
    SMSG_COMPRESSED_MOVES,
    SMSG_MOVE_ABANDON_TRANSPORT,
    SMSG_UNKNOWN_1302,
    SMSG_UNKNOWN_1304,

    //MovementForce
    SMSG_FORCE_RUN_SPEED_CHANGE,
    SMSG_FORCE_RUN_BACK_SPEED_CHANGE,
    SMSG_FORCE_MOVE_ROOT,
    SMSG_FORCE_MOVE_UNROOT,
    SMSG_FORCE_WALK_SPEED_CHANGE,
    SMSG_FORCE_SWIM_BACK_SPEED_CHANGE,
    SMSG_FORCE_TURN_RATE_CHANGE,
    SMSG_FORCE_FLIGHT_SPEED_CHANGE,
    SMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE,
    SMSG_FORCE_UNK1_SPEED_CHANGE,
    SMSG_FORCE_UNK2_SPEED_CHANGE,
    SMSG_FORCE_PITCH_RATE_CHANGE,

    //MovementTeleport/Fall/Fly/Water
    SMSG_MOVE_FEATHER_FALL,
    SMSG_MOVE_NORMAL_FALL,
    SMSG_MOVE_SET_WALK_IN_AIR,
    SMSG_MOVE_UNSET_WALK_IN_AIR,

    //MovementSet/Unset
    SMSG_MOVE_SET_HOVER,
    SMSG_MOVE_UNSET_HOVER,
    SMSG_MOVE_SET_FLIGHT,
    SMSG_MOVE_UNSET_FLIGHT,
    SMSG_MOVE_SET_CAN_FLY,
    SMSG_MOVE_UNSET_CAN_FLY,

    //Spline
    SMSG_SPLINE_MOVE_UNROOT,
    SMSG_SPLINE_MOVE_FEATHER_FALL,
    SMSG_SPLINE_MOVE_NORMAL_FALL,
    SMSG_SPLINE_MOVE_SET_HOVER,
    SMSG_SPLINE_MOVE_UNSET_HOVER,
    SMSG_SPLINE_MOVE_WATER_WALK,
    SMSG_SPLINE_MOVE_LAND_WALK,
    SMSG_SPLINE_MOVE_START_SWIM,
    SMSG_SPLINE_MOVE_STOP_SWIM,
    SMSG_SPLINE_MOVE_SET_RUN_MODE,
    SMSG_SPLINE_MOVE_SET_WALK_MODE,
    SMSG_SPLINE_MOVE_ROOT,
    SMSG_SPLINE_MOVE_UNKNOWN_1235,
    SMSG_SPLINE_MOVE_UNKNOWN_1236,
    SMSG_SPLINE_SET_PITCH_RATE,

    //SplineSet/Unset
    SMSG_SPLINE_SET_RUN_SPEED,
    SMSG_SPLINE_SET_RUN_BACK_SPEED,
    SMSG_SPLINE_SET_SWIM_SPEED,
    SMSG_SPLINE_SET_WALK_SPEED,
    SMSG_SPLINE_SET_SWIM_BACK_SPEED,
    SMSG_SPLINE_SET_TURN_RATE,
    SMSG_SPLINE_SET_FLIGHT_SPEED,
    SMSG_SPLINE_SET_FLIGHT_BACK_SPEED,
    SMSG_SPLINE_MOVE_SET_FLYING,
    SMSG_SPLINE_MOVE_UNSET_FLYING,

    /***********************************************************/
    /*********************MOVIEOPCODES***********************/
    /***********************************************************/
    //Cinematic
    SMSG_TRIGGER_CINEMATIC,

    //Movie
    SMSG_TRIGGER_MOVIE,

    /***********************************************************/
    /******************MOUNT/PETOPCODES********************/
    /***********************************************************/
    //Mount
    SMSG_MOUNTRESULT,
    SMSG_DISMOUNTRESULT,
    SMSG_PUREMOUNT_CANCELLED_OBSOLETE,
    SMSG_MOUNTSPECIAL_ANIM,
    SMSG_DISMOUNT,

    //Pet
    SMSG_PET_TAME_FAILURE,
    SMSG_PET_NAME_INVALID,
    SMSG_PET_SPELLS,
    SMSG_PET_MODE,
    SMSG_PET_UPDATE_COMBO_POINTS,

    /***********************************************************/
    /**********************MULTIOPCODES**********************/
    /***********************************************************/
    SMSG_MULTIPLE_PACKETS,

    /***********************************************************/
    /*********************PLAYEROPCODES**********************/
    /***********************************************************/
    SMSG_PLAYER_DIFFICULTY_CHANGE,
    SMSG_PLAYER_SKINNED,
    SMSG_ADDON_INFO,
    SMSG_GHOSTEE_GONE,
    SMSG_TITLE_EARNED,
    SMSG_UPDATE_COMBO_POINTS,
    SMSG_CHEAT_PLAYER_LOOKUP,
    SMSG_KICK_REASON,
    SMSG_SET_PLAYER_DECLINED_NAMES_RESULT,
    SMSG_HIGHEST_THREAT_UPDATE,
    SMSG_THREAT_UPDATE,
    SMSG_THREAT_REMOVE,
    SMSG_THREAT_CLEAR,

    //PlayerDance
    SMSG_NOTIFY_DANCE,
    SMSG_PLAY_DANCE,
    SMSG_STOP_DANCE,
    SMSG_LEARNED_DANCE_MOVES,

    //PlayerAchievement
    SMSG_ACHIEVEMENT_EARNED,
    SMSG_CRITERIA_UPDATE,
    SMSG_RESPOND_INSPECT_ACHIEVEMENTS,
    SMSG_ALL_ACHIEVEMENT_DATA,
    SMSG_SERVER_FIRST_ACHIEVEMENT,
    SMSG_CRITERIA_DELETED,
    SMSG_ACHIEVEMENT_DELETED,

    //PlayerExploration
    SMSG_EXPLORATION_EXPERIENCE,

    //PlayerCorpse/Resurrect/Death
    SMSG_RESURRECT_REQUEST,
    SMSG_RESURRECT_FAILED,
    SMSG_CORPSE_RECLAIM_DELAY,
    SMSG_FEIGN_DEATH_RESISTED,
    SMSG_DEATH_RELEASE_LOC,
    SMSG_FORCED_DEATH_UPDATE,
    SMSG_PRE_RESURRECT,
    SMSG_CORPSE_NOT_IN_INSTANCE,
    SMSG_CORPSE_MAP_POSITION_QUERY_RESPONSE,

    //PlayerPet
    SMSG_STABLE_RESULT,
    SMSG_SUMMON_REQUEST,
    SMSG_PET_BROKEN,
    SMSG_PET_ACTION_FEEDBACK,
    SMSG_PET_UNLEARN_CONFIRM,
    SMSG_PET_RENAMEABLE,
    SMSG_PET_GUIDS,
    SMSG_PET_ACTION_SOUND,
    SMSG_PET_DISMISS_SOUND,

    //PlayerPVP/Honor/Arena
    SMSG_PVP_CREDIT,
    SMSG_ARENA_TEAM_COMMAND_RESULT,
    SMSG_ARENA_TEAM_ROSTER,
    SMSG_ARENA_TEAM_INVITE,
    SMSG_ARENA_TEAM_EVENT,
    SMSG_ARENA_TEAM_STATS,
    SMSG_ARENA_ERROR,
    SMSG_REPORT_PVP_AFK_RESULT,
    SMSG_ARENA_OPPONENT_UPDATE,
    SMSG_ARENA_TEAM_CHANGE_FAILED_QUEUED,

    //PlayerCurrency
    SMSG_INIT_CURRENCY,
    SMSG_UPDATE_CURRENCY,
    SMSG_UPDATE_CURRENCY_WEEK_LIMIT,

    //PlayerMinigame
    SMSG_MINIGAME_SETUP,
    SMSG_MINIGAME_STATE,
    SMSG_MINIGAME_MOVE_FAILED,

    //Friends/Contacts/...
    SMSG_USERLIST_ADD,
    SMSG_USERLIST_REMOVE,
    SMSG_USERLIST_UPDATE,
    SMSG_REFER_A_FRIEND_FAILURE,

    //Talents
    SMSG_INSPECT_TALENT,
    SMSG_TALENTS_INFO,
    SMSG_TALENTS_INVOLUNTARILY_RESET,

    //Totem
    SMSG_TOTEM_CREATED,

    //Barber
    SMSG_ENABLE_BARBER_SHOP,
    SMSG_BARBER_SHOP_RESULT,

    //PlayerHealth/Power/Mana/...
    SMSG_HEALTH_UPDATE,
    SMSG_POWER_UPDATE,
    SMSG_CONVERT_RUNE,
    SMSG_RESYNC_RUNES,
    SMSG_ADD_RUNE_POWER,

    //PlayerVehicle
    SMSG_PLAYER_VEHICLE_DATA,

    /***********************************************************/
    /*********************QUERYOPCODES***********************/
    /***********************************************************/
    SMSG_CREATURE_QUERY_RESPONSE,
    SMSG_GAMEOBJECT_QUERY_RESPONSE,
    SMSG_NPC_TEXT_UPDATE,
    SMSG_NAME_QUERY_RESPONSE,
    SMSG_GUILD_QUERY_RESPONSE,
    SMSG_QUEST_QUERY_RESPONSE,
    SMSG_PAGE_TEXT_QUERY_RESPONSE,
    SMSG_PET_NAME_QUERY_RESPONSE,
    SMSG_PETITION_QUERY_RESPONSE,
    SMSG_ITEM_TEXT_QUERY_RESPONSE,
    SMSG_INVALIDATE_PLAYER,
    SMSG_ARENA_TEAM_QUERY_RESPONSE,
    SMSG_INVALIDATE_DANCE,
    SMSG_DANCE_QUERY_RESPONSE,

    /***********************************************************/
    /*********************QUESTOPCODES***********************/
    /***********************************************************/
    SMSG_QUESTLOG_FULL,
    SMSG_QUEST_FORCE_REMOVED,
    SMSG_QUEST_CONFIRM_ACCEPT,
    SMSG_QUEST_POI_QUERY_RESPONSE,
    SMSG_QUERY_QUESTS_COMPLETED_RESPONSE,

    //QuestUpdate
    SMSG_QUESTUPDATE_FAILED,
    SMSG_QUESTUPDATE_FAILEDTIMER,
    SMSG_QUESTUPDATE_COMPLETE,
    SMSG_QUESTUPDATE_ADD_KILL,
    SMSG_QUESTUPDATE_ADD_ITEM,
    SMSG_QUESTUPDATE_ADD_PVP_KILL,

    /***********************************************************/
    /*********************SPELLOPCODES***********************/
    /***********************************************************/
    SMSG_INITIAL_SPELLS,
    SMSG_LEARNED_SPELL,
    SMSG_SUPERCEDED_SPELL,
    SMSG_CAST_FAILED,
    SMSG_SPELL_START,
    SMSG_SPELL_GO,
    SMSG_SPELL_FAILURE,
    SMSG_DAMAGE_DONE_OBSOLETE,
    SMSG_UNIT_SPELLCAST_START,
    SMSG_SPELL_DELAYED,
    SMSG_PLAY_SPELL_VISUAL,
    SMSG_PLAY_SPELL_IMPACT,
    SMSG_REMOVED_SPELL,
    SMSG_DISPEL_FAILED,
    SMSG_SPELLORDAMAGE_IMMUNE,
    SMSG_SET_FLAT_SPELL_MODIFIER,
    SMSG_SET_PCT_SPELL_MODIFIER,
    SMSG_CANCEL_AUTO_REPEAT,
    SMSG_SPELL_FAILED_OTHER,
    SMSG_SPELL_UPDATE_CHAIN_TARGETS,
    SMSG_SPELL_CHANCE_RESIST_PUSHBACK,
    SMSG_SUMMON_CANCEL,
    SMSG_NOTIFY_DEST_LOC_SPELL_CAST,
    SMSG_CAMERA_SHAKE,

    //Cooldown
    SMSG_SPELL_COOLDOWN,
    SMSG_COOLDOWN_EVENT,
    SMSG_CLEAR_COOLDOWN,
    SMSG_COOLDOWN_CHEAT,
    SMSG_MODIFY_COOLDOWN,

    //Pet
    SMSG_PET_CAST_FAILED,
    SMSG_PET_LEARNED_SPELL,
    SMSG_PET_REMOVED_SPELL,

    //Trainer
    SMSG_TRAINER_LIST,
    SMSG_TRAINER_BUY_RESULT,
    SMSG_SEND_UNLEARN_SPELLS,

    //Auras
    SMSG_INIT_EXTRA_AURA_INFO_OBSOLETE,
    SMSG_SET_EXTRA_AURA_INFO_OBSOLETE,
    SMSG_SET_EXTRA_AURA_INFO_NEED_UPDATE_OBSOLETE,
    SMSG_CLEAR_EXTRA_AURA_INFO_OBSOLETE,
    SMSG_AURA_UPDATE_ALL,
    SMSG_AURA_UPDATE,
    SMSG_ON_CANCEL_EXPECTED_RIDE_VEHICLE_AURA,

    /***********************************************************/
    /*******************TRANSPORTOPCODES*********************/
    /***********************************************************/
    //TransportTaxi
    SMSG_SHOWTAXINODES,
    SMSG_TAXINODE_STATUS,
    SMSG_ACTIVATETAXIREPLY,
    SMSG_NEW_TAXI_PATH,
    SMSG_MONSTER_MOVE_TRANSPORT,

    /***********************************************************/
    /******************TIME/SPEEDOPCODES*******************/
    /***********************************************************/
    //Time
    SMSG_LOGIN_SETTIMESPEED,
    SMSG_GAMETIME_UPDATE,
    SMSG_GAMETIME_SET,
    SMSG_SERVERTIME,
    SMSG_PLAYED_TIME,
    SMSG_QUERY_TIME_RESPONSE,
    SMSG_TIME_SYNC_REQ,
    SMSG_ITEM_TIME_UPDATE,
    SMSG_ITEM_ENCHANT_TIME_UPDATE,
    SMSG_ACCOUNT_DATA_TIMES,
    SMSG_PLAY_TIME_WARNING,
    SMSG_GAMETIMEBIAS_SET,

    //Speed
    SMSG_GAMESPEED_SET,

    /***********************************************************/
    /******************UNCATEGORZIEDOPCODES******************/
    /***********************************************************/
    SMSG_CHECK_FOR_BOTS,
    SMSG_FORCEACTIONSHOW,
    SMSG_PETGODMODE,
    SMSG_REFER_A_FRIEND_EXPIRED,
    SMSG_GODMODE,
    SMSG_DEBUG_AISTATE,
    SMSG_DESTRUCTIBLE_BUILDING_DAMAGE,
    SMSG_TRANSFER_PENDING,
    SMSG_TRANSFER_ABORTED,
    SMSG_WHO,
    SMSG_WHOIS,
    SMSG_CONTACT_LIST,
    SMSG_FRIEND_STATUS,
    SMSG_MONSTER_MOVE,
    SMSG_TUTORIAL_FLAGS,
    SMSG_EMOTE,
    SMSG_TEXT_EMOTE,
    SMSG_SET_PROFICIENCY,
    SMSG_ACTION_BUTTONS,
    SMSG_AI_REACTION,
    SMSG_CLIENT_CONTROL_UPDATE,
    SMSG_FLIGHT_SPLINE_SYNC,
    SMSG_SHOW_BANK,
    SMSG_NOTIFICATION,
    SMSG_LOG_XPGAIN,
    SMSG_LEVELUP_INFO,
    SMSG_START_MIRROR_TIMER,
    SMSG_PAUSE_MIRROR_TIMER,
    SMSG_STOP_MIRROR_TIMER,
    SMSG_PONG,
    SMSG_INVALID_PROMOTION_CODE,
    SMSG_RWHOIS,
    SMSG_UPDATE_ACCOUNT_DATA,
    SMSG_CLEAR_FAR_SIGHT_IMMEDIATE,
    SMSG_SPIRIT_HEALER_CONFIRM,
    SMSG_ZONE_UNDER_ATTACK,
    SMSG_PROCRESIST,
    SMSG_STANDSTATE_CHANGE_FAILURE_OBSOLETE,
    SMSG_PLAY_MUSIC,
    SMSG_PLAY_OBJECT_SOUND,
    SMSG_SERVER_MESSAGE,
    SMSG_STANDSTATE_UPDATE,
    SMSG_SET_FORCED_REACTIONS,
    SMSG_SCRIPT_MESSAGE,
    SMSG_AREA_TRIGGER_MESSAGE,
    SMSG_DURABILITY_DAMAGE_DEATH,
    SMSG_PLAY_SOUND,
    SMSG_AREA_SPIRIT_HEALER_TIME,
    SMSG_WARDEN_DATA,
    SMSG_LOTTERY_QUERY_RESULT_OBSOLETE,
    SMSG_LOTTERY_RESULT_OBSOLETE,
    SMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY_RESPONSE,
    SMSG_CHEAT_DUMP_ITEMS_DEBUG_ONLY_RESPONSE_WRITE_FILE,
    SMSG_IGNORE_REQUIREMENTS_CHEAT,
    SMSG_CLEAR_TARGET,
    SMSG_CROSSED_INEBRIATION_THRESHOLD,
    SMSG_COMPLAIN_RESULT,
    SMSG_FEATURE_SYSTEM_STATUS,
    SMSG_DEBUG_LIST_TARGETS,
    SMSG_GOGOGO_OBSOLETE,
    SMSG_MIRRORIMAGE_DATA,
    SMSG_FORCE_DISPLAY_UPDATE,
    SMSG_IGNORE_DIMINISHING_RETURNS_CHEAT,
    SMSG_OVERRIDE_LIGHT,
    SMSG_SERVER_BUCK_DATA,
    SMSG_PROPOSE_LEVEL_GRANT,
    SMSG_UPDATE_ACCOUNT_DATA_COMPLETE,
    SMSG_SERVER_BUCK_DATA_START,
    SMSG_CLIENTCACHE_VERSION,
    SMSG_SET_PROJECTILE_POSITION,
    SMSG_UNKNOWN_1240,
    SMSG_TOGGLE_XP_GAIN,
    SMSG_UNKNOWN_1276,
    SMSG_UNKNOWN_1295,
    SMSG_FORCE_SEND_QUEUED_PACKETS,
    SMSG_UNKNOWN_1300,
    SMSG_UNKNOWN_1301,
    SMSG_UNKNOWN_1310,

    //Fishing
    SMSG_FISH_NOT_HOOKED,
    SMSG_FISH_ESCAPED,

    //Voice
    SMSG_VOICE_SESSION_ROSTER_UPDATE,
    SMSG_VOICE_SESSION_LEAVE,
    SMSG_VOICE_SESSION_ADJUST_PRIORITY,
    SMSG_VOICE_SET_TALKER_MUTED,
    SMSG_VOICE_SESSION_ENABLE,
    SMSG_VOICE_PARENTAL_CONTROLS,
    SMSG_VOICE_CHAT_STATUS,
    SMSG_VOICESESSION_FULL,

    //Commentator
    SMSG_COMMENTATOR_STATE_CHANGED,
    SMSG_COMMENTATOR_MAP_INFO,
    SMSG_COMMENTATOR_GET_PLAYER_INFO,
    SMSG_COMMENTATOR_PLAYER_INFO,
    SMSG_UNKNOWN_1308,
    SMSG_UNKNOWN_1309,

    //Comsat
    SMSG_COMSAT_RECONNECT_TRY,
    SMSG_COMSAT_DISCONNECT,
    SMSG_COMSAT_CONNECT_FAIL,

    /***********************************************************/
    /**********************WORLDOPCODES**********************/
    /***********************************************************/
    SMSG_NEW_WORLD,
    SMSG_UPDATE_OBJECT,
    SMSG_DESTROY_OBJECT,
    SMSG_COMPRESSED_UPDATE_OBJECT,
    SMSG_LOGIN_VERIFY_WORLD,
    SMSG_INIT_WORLD_STATES,
    SMSG_UPDATE_WORLD_STATE,
    SMSG_WEATHER,
    SMSG_SET_PHASE_SHIFT,
    SMSG_WORLD_STATE_UI_TIMER_UPDATE,
    NUM_OPCODES
};

#define NUM_MSG_TYPES 0xFFFF

extern void InitOpcodeTable();

/// Player state
enum SessionStatus
{
    STATUS_AUTHED = 0,                                      // Player authenticated (_player == NULL, m_playerRecentlyLogout = false or will be reset before handler call, m_GUID have garbage)
    STATUS_LOGGEDIN,                                        // Player in game (_player != NULL, m_GUID == _player->GetGUID(), inWorld())
    STATUS_TRANSFER,                                        // Player transferring to another map (_player != NULL, m_GUID == _player->GetGUID(), !inWorld())
    STATUS_LOGGEDIN_OR_RECENTLY_LOGGOUT,                    // _player!= NULL or _player == NULL && m_playerRecentlyLogout, m_GUID store last _player guid)
    STATUS_NEVER,                                           // Opcode not accepted from client (deprecated or server side only)
    STATUS_UNHANDLED,                                       // Opcode not handled yet
};

enum PacketProcessing
{
    PROCESS_INPLACE      = 0,                               //process packet whenever we receive it - mostly for non-handled or non-implemented packets
    PROCESS_THREADUNSAFE = 2,                               //packet is not thread-safe - process it in World::UpdateSessions()
    PROCESS_THREADSAFE   = 3                                //packet is thread-safe - process it in Map::Update()
};

class WorldPacket;

struct OpcodeHandler
{
    char const* name;
    SessionStatus status;
    PacketProcessing packetProcessing;
    void (WorldSession::*handler)(WorldPacket& recvPacket);
    Opcodes opcodeEnum;
};

extern OpcodeHandler opcodeTable[NUM_MSG_TYPES];
extern uint16 opcodesEnumToNumber[NUM_OPCODES];

// Lookup opcode name for human understandable logging
inline const char* LookupOpcodeName(uint16 id)
{
    if (id >= NUM_MSG_TYPES)
        return "Received unknown opcode, it's more than max!";

    return opcodeTable[id].name;
}

inline Opcodes LookupOpcodeEnum(uint16 OpcodeValue)
{
    return opcodeTable[OpcodeValue].opcodeEnum;
}

inline uint16 LookupOpcodeNumber(Opcodes enumValue)
{
    return opcodesEnumToNumber[enumValue];
}

#endif
