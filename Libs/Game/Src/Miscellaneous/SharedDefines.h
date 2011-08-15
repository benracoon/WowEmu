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

#ifndef STRAWBERRY_SHAREDDEFINES_H
#define STRAWBERRY_SHAREDDEFINES_H

#include "Define.h"
#include <cassert>

enum SpellEffIndex
{
    EFFECT_0 = 0,
    EFFECT_1 = 1,
    EFFECT_2 = 2,
};

// used in script definitions
#define EFFECT_FIRST_FOUND 254
#define EFFECT_ALL 255

// loot modes for creatures and gameobjects, bitmask!
enum LootModes
{
    LOOT_MODE_DEFAULT                  = 1,
    LOOT_MODE_HARD_MODE_1              = 2,
    LOOT_MODE_HARD_MODE_2              = 4,
    LOOT_MODE_HARD_MODE_3              = 8,
    LOOT_MODE_HARD_MODE_4              = 16
};

enum Gender
{
    GENDER_MALE                        = 0,
    GENDER_FEMALE                      = 1,
    GENDER_NONE                        = 2
};

// Race value is index in ChrRaces.dbc
enum Races
{
    RACE_HUMAN          = 1,
    RACE_ORC            = 2,
    RACE_DWARF          = 3,
    RACE_NIGHTELF       = 4,
    RACE_UNDEAD_PLAYER  = 5,
    RACE_TAUREN         = 6,
    RACE_GNOME          = 7,
    RACE_TROLL          = 8,
    RACE_GOBLIN         = 9,
    RACE_BLOODELF       = 10,
    RACE_DRAENEI        = 11,
    //RACE_FEL_ORC        = 12,
    //RACE_NAGA           = 13,
    //RACE_BROKEN         = 14,
    //RACE_SKELETON       = 15,
    //RACE_VRYKUL         = 16,
    //RACE_TUSKARR        = 17,
    //RACE_FOREST_TROLL   = 18,
    //RACE_TAUNKA         = 19,
    //RACE_NORTHREND_SKELETON = 20,
    //RACE_ICE_TROLL      = 21
    RACE_WORGEN         = 22,
    //RACE_GILNEAN      = 23  // Human
};

// max+1 for player race
#define MAX_RACES         32

#define RACEMASK_ALL_PLAYABLE \
    ((1<<(RACE_HUMAN-1))  |(1<<(RACE_ORC-1))          |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))|(1<<(RACE_UNDEAD_PLAYER-1))|(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))   |(1<<(RACE_TROLL-1))        |(1<<(RACE_GOBLIN-1))  | \
    ((1<<(RACE_BLOODELF-1)) | 1<<(RACE_DRAENEI-1))    |(1<<(RACE_WORGEN-1)))

#define RACEMASK_ALLIANCE \
    ((1<<(RACE_HUMAN-1)) | (1<<(RACE_DWARF-1)) | (1<<(RACE_NIGHTELF-1)) | \
    (1<<(RACE_GNOME-1)) | (1<<(RACE_DRAENEI-1)))

#define RACEMASK_HORDE RACEMASK_ALL_PLAYABLE & ~RACEMASK_ALLIANCE

// Class value is index in ChrClasses.dbc
enum Classes
{
    CLASS_WARRIOR       = 1,
    CLASS_PALADIN       = 2,
    CLASS_HUNTER        = 3,
    CLASS_ROGUE         = 4,
    CLASS_PRIEST        = 5,
    CLASS_DEATH_KNIGHT  = 6,
    CLASS_SHAMAN        = 7,
    CLASS_MAGE          = 8,
    CLASS_WARLOCK       = 9,
    CLASS_DRUID         = 11
};

// max+1 for player class
#define MAX_CLASSES       12

#define CLASSMASK_ALL_PLAYABLE \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1)) | \
    (1<<(CLASS_DEATH_KNIGHT-1)))

// valid classes for creature_template.unit_class
enum UnitClass
{
    UNIT_CLASS_WARRIOR                  = 1,
    UNIT_CLASS_PALADIN                  = 2,
    UNIT_CLASS_ROGUE                    = 4,
    UNIT_CLASS_MAGE                     = 8,
};

#define CLASSMASK_ALL_CREATURES ((1<<(UNIT_CLASS_WARRIOR-1)) | (1<<(UNIT_CLASS_PALADIN-1)) | (1<<(UNIT_CLASS_ROGUE-1)) | (1<<(UNIT_CLASS_MAGE-1)))

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))

#define PLAYER_MAX_BATTLEGROUND_QUEUES 2

enum ReputationRank
{
    REP_HATED       = 0,
    REP_HOSTILE     = 1,
    REP_UNFRIENDLY  = 2,
    REP_NEUTRAL     = 3,
    REP_FRIENDLY    = 4,
    REP_HONORED     = 5,
    REP_REVERED     = 6,
    REP_EXALTED     = 7
};

#define MIN_REPUTATION_RANK (REP_HATED)
#define MAX_REPUTATION_RANK 8

#define MAX_SPILLOVER_FACTIONS 4

enum MoneyConstants
{
    COPPER = 1,
    SILVER = COPPER*100,
    GOLD   = SILVER*100
};

enum Stats
{
    STAT_STRENGTH                      = 0,
    STAT_AGILITY                       = 1,
    STAT_STAMINA                       = 2,
    STAT_INTELLECT                     = 3,
    STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

enum Powers
{
    MANA                          = 0,
    RAGE                          = 1,
    FOCUS                         = 2,
    ENERGY                        = 3,
    HAPPINESS                     = 4,
    RUNES                         = 5,
    RUNIC_POWER                   = 6,
    SOUL_SHARDS                   = 7,
    ECLIPSE                       = 8,
    HOLY_POWER                    = 9,
    ALTERNATE_POWER               = 10,
    POWER_ALL                     = 127,    // default for class?
    POWER_HEALTH                  = 0xFFFFFFFE    // (-2 as signed value)
};

#define MAX_POWERS                       5

enum SpellSchools
{
    SPELL_SCHOOL_NORMAL                 = 0,
    SPELL_SCHOOL_HOLY                   = 1,
    SPELL_SCHOOL_FIRE                   = 2,
    SPELL_SCHOOL_NATURE                 = 3,
    SPELL_SCHOOL_FROST                  = 4,
    SPELL_SCHOOL_SHADOW                 = 5,
    SPELL_SCHOOL_ARCANE                 = 6
};

#define MAX_SPELL_SCHOOL                  7

enum SpellSchoolMask
{
    SPELL_SCHOOL_MASK_NONE    = 0x00,                       // not exist
    SPELL_SCHOOL_MASK_NORMAL  = (1 << SPELL_SCHOOL_NORMAL), // PHYSICAL (Armor)
    SPELL_SCHOOL_MASK_HOLY    = (1 << SPELL_SCHOOL_HOLY),
    SPELL_SCHOOL_MASK_FIRE    = (1 << SPELL_SCHOOL_FIRE),
    SPELL_SCHOOL_MASK_NATURE  = (1 << SPELL_SCHOOL_NATURE),
    SPELL_SCHOOL_MASK_FROST   = (1 << SPELL_SCHOOL_FROST),
    SPELL_SCHOOL_MASK_SHADOW  = (1 << SPELL_SCHOOL_SHADOW),
    SPELL_SCHOOL_MASK_ARCANE  = (1 << SPELL_SCHOOL_ARCANE),

    // unions

    // 124, not include normal and holy damage
    SPELL_SCHOOL_MASK_SPELL   = (SPELL_SCHOOL_MASK_FIRE   |
                                  SPELL_SCHOOL_MASK_NATURE | SPELL_SCHOOL_MASK_FROST  |
                                  SPELL_SCHOOL_MASK_SHADOW | SPELL_SCHOOL_MASK_ARCANE),
    // 126
    SPELL_SCHOOL_MASK_MAGIC   = (SPELL_SCHOOL_MASK_HOLY | SPELL_SCHOOL_MASK_SPELL),

    // 127
    SPELL_SCHOOL_MASK_ALL     = (SPELL_SCHOOL_MASK_NORMAL | SPELL_SCHOOL_MASK_MAGIC)
};

inline SpellSchools GetFirstSchoolInMask(SpellSchoolMask mask)
{
    for (int i = 0; i < MAX_SPELL_SCHOOL; ++i)
        if (mask & (1 << i))
            return SpellSchools(i);

    return SPELL_SCHOOL_NORMAL;
}

enum ItemQualities
{
    ITEM_QUALITY_POOR                  = 0,                 //GREY
    ITEM_QUALITY_NORMAL                = 1,                 //WHITE
    ITEM_QUALITY_UNCOMMON              = 2,                 //GREEN
    ITEM_QUALITY_RARE                  = 3,                 //BLUE
    ITEM_QUALITY_EPIC                  = 4,                 //PURPLE
    ITEM_QUALITY_LEGENDARY             = 5,                 //ORANGE
    ITEM_QUALITY_ARTIFACT              = 6,                 //LIGHT YELLOW
    ITEM_QUALITY_HEIRLOOM              = 7
};

#define MAX_ITEM_QUALITY                 8

enum SpellCategory
{
    SPELL_CATEGORY_FOOD             = 11,
    SPELL_CATEGORY_DRINK            = 59,
};

const uint32 ItemQualityColors[MAX_ITEM_QUALITY] = {
    0xff9d9d9d,        //GREY
    0xffffffff,        //WHITE
    0xff1eff00,        //GREEN
    0xff0070dd,        //BLUE
    0xffa335ee,        //PURPLE
    0xffff8000,        //ORANGE
    0xffe6cc80,        //LIGHT YELLOW
    0xffe6cc80         //LIGHT YELLOW
};

// ***********************************
// Spell Attributes definitions
// ***********************************

enum SpellAttr0
{
    SPELL_ATTR0_UNK0                             = 0x00000001, //  0
    SPELL_ATTR0_REQ_AMMO                         = 0x00000002, //  1 on next ranged
    SPELL_ATTR0_ON_NEXT_SWING                    = 0x00000004, //  2
    SPELL_ATTR0_UNK3                             = 0x00000008, //  3 not set in 3.0.3
    SPELL_ATTR0_ABILITY                          = 0x00000010, //  4 client puts 'ability' instead of 'spell' in game strings for these spells
    SPELL_ATTR0_TRADESPELL                       = 0x00000020, //  5 trade spells (recipes), will be added by client to a sublist of profession spell
    SPELL_ATTR0_PASSIVE                          = 0x00000040, //  6 Passive spell
    SPELL_ATTR0_HIDDEN_CLIENTSIDE                = 0x00000080, //  7 Spells with this attribute are not visible in spellbook or aura bar
    SPELL_ATTR0_HIDE_IN_COMBAT_LOG               = 0x00000100, //  8 This attribite controls whether spell appears in combat logs
    SPELL_ATTR0_TARGET_MAINHAND_ITEM             = 0x00000200, //  9 Client automatically selects item from mainhand slot as a cast target
    SPELL_ATTR0_ON_NEXT_SWING_2                  = 0x00000400, // 10
    SPELL_ATTR0_UNK11                            = 0x00000800, // 11
    SPELL_ATTR0_DAYTIME_ONLY                     = 0x00001000, // 12 only useable at daytime, not set in 2.4.2
    SPELL_ATTR0_NIGHT_ONLY                       = 0x00002000, // 13 only useable at night, not set in 2.4.2
    SPELL_ATTR0_INDOORS_ONLY                     = 0x00004000, // 14 only useable indoors, not set in 2.4.2
    SPELL_ATTR0_OUTDOORS_ONLY                    = 0x00008000, // 15 Only useable outdoors.
    SPELL_ATTR0_NOT_SHAPESHIFT                   = 0x00010000, // 16 Not while shapeshifted
    SPELL_ATTR0_ONLY_STEALTHED                   = 0x00020000, // 17 Must be in stealth
    SPELL_ATTR0_DONT_AFFECT_SHEATH_STATE         = 0x00040000, // 18 client won't hide unit weapons in sheath on cast/channel
    SPELL_ATTR0_LEVEL_DAMAGE_CALCULATION         = 0x00080000, // 19 spelldamage depends on caster level
    SPELL_ATTR0_STOP_ATTACK_TARGET               = 0x00100000, // 20 Stop attack after use this spell (and not begin attack if use)
    SPELL_ATTR0_IMPOSSIBLE_DODGE_PARRY_BLOCK     = 0x00200000, // 21 Cannot be dodged/parried/blocked
    SPELL_ATTR0_CAST_TRACK_TARGET                = 0x00400000, // 22 Client automatically forces player to face target when casting
    SPELL_ATTR0_CASTABLE_WHILE_DEAD              = 0x00800000, // 23 castable while dead?
    SPELL_ATTR0_CASTABLE_WHILE_MOUNTED           = 0x01000000, // 24 castable while mounted
    SPELL_ATTR0_DISABLED_WHILE_ACTIVE            = 0x02000000, // 25 Activate and start cooldown after aura fade or remove summoned creature or go
    SPELL_ATTR0_NEGATIVE_1                       = 0x04000000, // 26 Many negative spells have this attr
    SPELL_ATTR0_CASTABLE_WHILE_SITTING           = 0x08000000, // 27 castable while sitting
    SPELL_ATTR0_CANT_USED_IN_COMBAT              = 0x10000000, // 28 Cannot be used in combat
    SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY    = 0x20000000, // 29 unaffected by invulnerability (hmm possible not...)
    SPELL_ATTR0_BREAKABLE_BY_DAMAGE              = 0x40000000, // 30
    SPELL_ATTR0_CANT_CANCEL                      = 0x80000000  // 31 positive aura can't be canceled
};

enum SpellAttr1
{
    SPELL_ATTR1_DISMISS_PET                      = 0x00000001, //  0 for spells without this flag client doesn't allow to summon pet if caster has a pet
    SPELL_ATTR1_DRAIN_ALL_POWER                  = 0x00000002, //  1 use all power (Only paladin Lay of Hands and Bunyanize)
    SPELL_ATTR1_CHANNELED_1                      = 0x00000004, //  2 clientside checked? cancelable?
    SPELL_ATTR1_CANT_BE_REDIRECTED               = 0x00000008, //  3
    SPELL_ATTR1_UNK4                             = 0x00000010, //  4 stealth and whirlwind
    SPELL_ATTR1_NOT_BREAK_STEALTH                = 0x00000020, //  5 Not break stealth
    SPELL_ATTR1_CHANNELED_2                      = 0x00000040, //  6
    SPELL_ATTR1_CANT_BE_REFLECTED                = 0x00000080, //  7
    SPELL_ATTR1_NOT_IN_COMBAT_TARGET             = 0x00000100, //  8 Spell req target not to be in combat state
    SPELL_ATTR1_MELEE_COMBAT_START               = 0x00000200, //  9 player starts melee combat after this spell is cast
    SPELL_ATTR1_NO_THREAT                        = 0x00000400, // 10 no generates threat on cast 100% (old NO_INITIAL_AGGRO)
    SPELL_ATTR1_UNK11                            = 0x00000800, // 11 aura
    SPELL_ATTR1_UNK12                            = 0x00001000, // 12
    SPELL_ATTR1_FARSIGHT                         = 0x00002000, // 13 Client removes farsight on aura loss
    SPELL_ATTR1_CHANNEL_TRACK_TARGET             = 0x00004000, // 14 Client automatically forces player to face target when channeling
    SPELL_ATTR1_DISPEL_AURAS_ON_IMMUNITY         = 0x00008000, // 15 remove auras on immunity
    SPELL_ATTR1_UNAFFECTED_BY_SCHOOL_IMMUNE      = 0x00010000, // 16 on immuniy
    SPELL_ATTR1_UNAUTOCASTABLE_BY_PET            = 0x00020000, // 17
    SPELL_ATTR1_UNK18                            = 0x00040000, // 18
    SPELL_ATTR1_CANT_TARGET_SELF                 = 0x00080000, // 19 Applies only to unit target - for example Divine Intervention (19752)
    SPELL_ATTR1_REQ_COMBO_POINTS1                = 0x00100000, // 20 Req combo points on target
    SPELL_ATTR1_UNK21                            = 0x00200000, // 21
    SPELL_ATTR1_REQ_COMBO_POINTS2                = 0x00400000, // 22 Req combo points on target
    SPELL_ATTR1_UNK23                            = 0x00800000, // 23
    SPELL_ATTR1_UNK24                            = 0x01000000, // 24 only fishing spells
    SPELL_ATTR1_UNK25                            = 0x02000000, // 25
    SPELL_ATTR1_UNK26                            = 0x04000000, // 26 works correctly with [target=focus] and [target=mouseover] macros?
    SPELL_ATTR1_UNK27                            = 0x08000000, // 27
    SPELL_ATTR1_DONT_DISPLAY_IN_AURA_BAR         = 0x10000000, // 28 client doesn't display these spells in aura bar
    SPELL_ATTR1_CHANNEL_DISPLAY_SPELL_NAME       = 0x20000000, // 29 spell name is displayed in cast bar instead of 'channeling' text
    SPELL_ATTR1_ENABLE_AT_DODGE                  = 0x40000000, // 30 Overpower, Wolverine Bite
    SPELL_ATTR1_UNK31                            = 0x80000000  // 31
};

enum SpellAttr2
{
    SPELL_ATTR2_ALLOW_DEAD_TARGET                = 0x00000001, //  0
    SPELL_ATTR2_UNK1                             = 0x00000002, //  1 ? many triggered spells have this flag
    SPELL_ATTR2_UNK2                             = 0x00000004, //  2
    SPELL_ATTR2_UNK3                             = 0x00000008, //  3
    SPELL_ATTR2_ALWAYS_APPLY_MODIFIERS           = 0x00000010, //  4 ? spell modifiers are applied dynamically (even if aura is not passive)
    SPELL_ATTR2_AUTOREPEAT_FLAG                  = 0x00000020, //  5
    SPELL_ATTR2_CANT_TARGET_TAPPED               = 0x00000040, //  6 target must be tapped by caster
    SPELL_ATTR2_UNK7                             = 0x00000080, //  7
    SPELL_ATTR2_UNK8                             = 0x00000100, //  8 not set in 3.0.3
    SPELL_ATTR2_UNK9                             = 0x00000200, //  9
    SPELL_ATTR2_UNK10                            = 0x00000400, // 10
    SPELL_ATTR2_HEALTH_FUNNEL                    = 0x00000800, // 11
    SPELL_ATTR2_UNK12                            = 0x00001000, // 12
    SPELL_ATTR2_UNK13                            = 0x00002000, // 13 Items enchanted by spells with this flag preserve the enchant to arenas
    SPELL_ATTR2_UNK14                            = 0x00004000, // 14
    SPELL_ATTR2_UNK15                            = 0x00008000, // 15 not set in 3.0.3
    SPELL_ATTR2_TAME_BEAST                       = 0x00010000, // 16
    SPELL_ATTR2_NOT_RESET_AUTO_ACTIONS           = 0x00020000, // 17 don't reset timers for melee autoattacks (swings) or ranged autoattacks (autoshoots)
    SPELL_ATTR2_UNK18                            = 0x00040000, // 18 Only Revive pet - possible req dead pet
    SPELL_ATTR2_NOT_NEED_SHAPESHIFT              = 0x00080000, // 19 does not necessarly need shapeshift
    SPELL_ATTR2_UNK20                            = 0x00100000, // 20
    SPELL_ATTR2_DAMAGE_REDUCED_SHIELD            = 0x00200000, // 21 for ice blocks, pala immunity buffs, priest absorb shields, but used also for other spells -> not sure!
    SPELL_ATTR2_UNK22                            = 0x00400000, // 22
    SPELL_ATTR2_UNK23                            = 0x00800000, // 23 Only mage Arcane Concentration have this flag
    SPELL_ATTR2_UNK24                            = 0x01000000, // 24
    SPELL_ATTR2_UNK25                            = 0x02000000, // 25
    SPELL_ATTR2_UNK26                            = 0x04000000, // 26 unaffected by school immunity
    SPELL_ATTR2_UNK27                            = 0x08000000, // 27
    SPELL_ATTR2_UNK28                            = 0x10000000, // 28 no breaks stealth if it fails??
    SPELL_ATTR2_CANT_CRIT                        = 0x20000000, // 29 Spell can't crit
    SPELL_ATTR2_TRIGGERED_CAN_TRIGGER_PROC       = 0x40000000, // 30 spell can trigger even if triggered
    SPELL_ATTR2_FOOD_BUFF                        = 0x80000000  // 31 Food or Drink Buff (like Well Fed)
};

enum SpellAttr3
{
    SPELL_ATTR3_UNK0                             = 0x00000001, //  0
    SPELL_ATTR3_UNK1                             = 0x00000002, //  1
    SPELL_ATTR3_UNK2                             = 0x00000004, //  2
    SPELL_ATTR3_BLOCKABLE_SPELL                  = 0x00000008, //  3 Only dmg class melee in 3.1.3
    SPELL_ATTR3_IGNORE_RESURRECTION_TIMER        = 0x00000010, //  4 you don't have to wait to be resurrected with these spells
    SPELL_ATTR3_UNK5                             = 0x00000020, //  5
    SPELL_ATTR3_UNK6                             = 0x00000040, //  6
    SPELL_ATTR3_STACK_FOR_DIFF_CASTERS           = 0x00000080, //  7 separate stack for every caster
    SPELL_ATTR3_PLAYERS_ONLY                     = 0x00000100, //  8 Player only?
    SPELL_ATTR3_TRIGGERED_CAN_TRIGGER_PROC_2     = 0x00000200, //  9 triggered from effect?
    SPELL_ATTR3_MAIN_HAND                        = 0x00000400, // 10 Main hand weapon required
    SPELL_ATTR3_BATTLEGROUND                     = 0x00000800, // 11 Can casted only on battleground
    SPELL_ATTR3_REQUIRE_DEAD_TARGET              = 0x00001000, // 12
    SPELL_ATTR3_UNK13                            = 0x00002000, // 13
    SPELL_ATTR3_UNK14                            = 0x00004000, // 14 "Honorless Target" only this spells have this flag
    SPELL_ATTR3_UNK15                            = 0x00008000, // 15 Auto Shoot, Shoot, Throw,  - this is autoshot flag
    SPELL_ATTR3_CANT_TRIGGER_PROC                = 0x00010000, // 16 confirmed with many patchnotes
    SPELL_ATTR3_NO_INITIAL_AGGRO                 = 0x00020000, // 17 Soothe Animal, 39758, Mind Soothe
    SPELL_ATTR3_IGNORE_HIT_RESULT                = 0x00040000, // 18 Spell should always hit its target
    SPELL_ATTR3_DISABLE_PROC                     = 0x00080000, // 19 during aura proc no spells can trigger (20178, 20375)
    SPELL_ATTR3_DEATH_PERSISTENT                 = 0x00100000, // 20 Death persistent spells
    SPELL_ATTR3_UNK21                            = 0x00200000, // 21
    SPELL_ATTR3_REQ_WAND                         = 0x00400000, // 22 Req wand
    SPELL_ATTR3_UNK23                            = 0x00800000, // 23
    SPELL_ATTR3_REQ_OFFHAND                      = 0x01000000, // 24 Req offhand weapon
    SPELL_ATTR3_UNK25                            = 0x02000000, // 25 no cause spell pushback ?
    SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED          = 0x04000000, // 26 auras with this attribute can proc from triggered spell casts with SPELL_ATTR3_TRIGGERED_CAN_TRIGGER_PROC_2 (67736 + 52999)
    SPELL_ATTR3_DRAIN_SOUL                       = 0x08000000, // 27 only drain soul has this flag
    SPELL_ATTR3_UNK28                            = 0x10000000, // 28
    SPELL_ATTR3_NO_DONE_BONUS                    = 0x20000000, // 29 Ignore caster spellpower and done damage mods?
    SPELL_ATTR3_UNK30                            = 0x40000000, // 30 Shaman's Fire Nova 3.3.0, Sweeping Strikes 3.3.0
    SPELL_ATTR3_UNK31                            = 0x80000000  // 31
};

enum SpellAttr4
{
    SPELL_ATTR4_UNK0                             = 0x00000001, //  0
    SPELL_ATTR4_UNK1                             = 0x00000002, //  1 proc on finishing move?
    SPELL_ATTR4_UNK2                             = 0x00000004, //  2
    SPELL_ATTR4_UNK3                             = 0x00000008, //  3
    SPELL_ATTR4_UNK4                             = 0x00000010, //  4 This will no longer cause guards to attack on use??
    SPELL_ATTR4_UNK5                             = 0x00000020, //  5
    SPELL_ATTR4_NOT_STEALABLE                    = 0x00000040, //  6 although such auras might be dispellable, they cannot be stolen
    SPELL_ATTR4_TRIGGERED                        = 0x00000080, //  7 spells forced to be triggered
    SPELL_ATTR4_UNK8                             = 0x00000100, //  8 ignores taken percent damage mods?
    SPELL_ATTR4_UNK9                             = 0x00000200, //  9
    SPELL_ATTR4_SPELL_VS_EXTEND_COST             = 0x00000400, // 10 Rogue Shiv have this flag
    SPELL_ATTR4_UNK11                            = 0x00000800, // 11
    SPELL_ATTR4_UNK12                            = 0x00001000, // 12
    SPELL_ATTR4_UNK13                            = 0x00002000, // 13
    SPELL_ATTR4_DAMAGE_DOESNT_BREAK_AURAS        = 0x00004000, // 14 doesn't break auras by damage from these spells
    SPELL_ATTR4_UNK15                            = 0x00008000, // 15
    SPELL_ATTR4_NOT_USABLE_IN_ARENA              = 0x00010000, // 16
    SPELL_ATTR4_USABLE_IN_ARENA                  = 0x00020000, // 17
    SPELL_ATTR4_UNK18                            = 0x00040000, // 18
    SPELL_ATTR4_UNK19                            = 0x00080000, // 19
    SPELL_ATTR4_NOT_CHECK_SELFCAST_POWER         = 0x00100000, // 20 supersedes message "More powerful spell applied" for self casts.
    SPELL_ATTR4_UNK21                            = 0x00200000, // 21
    SPELL_ATTR4_UNK22                            = 0x00400000, // 22
    SPELL_ATTR4_UNK23                            = 0x00800000, // 23
    SPELL_ATTR4_UNK24                            = 0x01000000, // 24
    SPELL_ATTR4_UNK25                            = 0x02000000, // 25 pet scaling auras
    SPELL_ATTR4_CAST_ONLY_IN_OUTLAND             = 0x04000000, // 26 Can only be used in Outland.
    SPELL_ATTR4_UNK27                            = 0x08000000, // 27
    SPELL_ATTR4_UNK28                            = 0x10000000, // 28
    SPELL_ATTR4_UNK29                            = 0x20000000, // 29
    SPELL_ATTR4_UNK30                            = 0x40000000, // 30
    SPELL_ATTR4_UNK31                            = 0x80000000  // 31
};

enum SpellAttr5
{
    SPELL_ATTR5_UNK0                             = 0x00000001, //  0
    SPELL_ATTR5_NO_REAGENT_WHILE_PREP            = 0x00000002, //  1 not need reagents if UNIT_FLAG_PREPARATION
    SPELL_ATTR5_UNK2                             = 0x00000004, //  2
    SPELL_ATTR5_USABLE_WHILE_STUNNED             = 0x00000008, //  3 usable while stunned
    SPELL_ATTR5_UNK4                             = 0x00000010, //  4
    SPELL_ATTR5_SINGLE_TARGET_SPELL              = 0x00000020, //  5 Only one target can be apply at a time
    SPELL_ATTR5_UNK6                             = 0x00000040, //  6
    SPELL_ATTR5_UNK7                             = 0x00000080, //  7
    SPELL_ATTR5_UNK8                             = 0x00000100, //  8
    SPELL_ATTR5_START_PERIODIC_AT_APPLY          = 0x00000200, //  9 begin periodic tick at aura apply
    SPELL_ATTR5_HIDE_DURATION                    = 0x00000400, // 10 do not send duration to client
    SPELL_ATTR5_UNK11                            = 0x00000800, // 11
    SPELL_ATTR5_UNK12                            = 0x00001000, // 12
    SPELL_ATTR5_HASTE_AFFECT_DURATION            = 0x00002000, // 13 haste effects decrease duration of this
    SPELL_ATTR5_UNK14                            = 0x00004000, // 14
    SPELL_ATTR5_UNK15                            = 0x00008000, // 15
    SPELL_ATTR5_SPECIAL_ITEM_CLASS_CHECK         = 0x00010000, // 16 this allows spells with EquippedItemClass to affect spells from other items if the required item is equipped
    SPELL_ATTR5_USABLE_WHILE_FEARED              = 0x00020000, // 17 usable while feared
    SPELL_ATTR5_USABLE_WHILE_CONFUSED            = 0x00040000, // 18 usable while confused
    SPELL_ATTR5_UNK19                            = 0x00080000, // 19
    SPELL_ATTR5_UNK20                            = 0x00100000, // 20
    SPELL_ATTR5_UNK21                            = 0x00200000, // 21
    SPELL_ATTR5_UNK22                            = 0x00400000, // 22
    SPELL_ATTR5_UNK23                            = 0x00800000, // 23
    SPELL_ATTR5_UNK24                            = 0x01000000, // 24
    SPELL_ATTR5_UNK25                            = 0x02000000, // 25
    SPELL_ATTR5_UNK26                            = 0x04000000, // 26
    SPELL_ATTR5_UNK27                            = 0x08000000, // 27
    SPELL_ATTR5_UNK28                            = 0x10000000, // 28
    SPELL_ATTR5_UNK29                            = 0x20000000, // 29
    SPELL_ATTR5_UNK30                            = 0x40000000, // 30
    SPELL_ATTR5_UNK31                            = 0x80000000  // 31 Forces all nearby enemies to focus attacks caster
};

enum SpellAttr6
{
    SPELL_ATTR6_UNK0                             = 0x00000001, //  0 Only Move spell have this flag
    SPELL_ATTR6_ONLY_IN_ARENA                    = 0x00000002, //  1 only usable in arena
    SPELL_ATTR6_IGNORE_CASTER_AURAS              = 0x00000004, //  2
    SPELL_ATTR6_UNK3                             = 0x00000008, //  3
    SPELL_ATTR6_UNK4                             = 0x00000010, //  4
    SPELL_ATTR6_UNK5                             = 0x00000020, //  5
    SPELL_ATTR6_UNK6                             = 0x00000040, //  6
    SPELL_ATTR6_UNK7                             = 0x00000080, //  7
    SPELL_ATTR6_IGNORE_CROWD_CONTROL_TARGETS     = 0x00000100, //  8
    SPELL_ATTR6_UNK9                             = 0x00000200, //  9
    SPELL_ATTR6_CAN_TARGET_POSSESSED_FRIENDS     = 0x00000400, // 10 NYI!
    SPELL_ATTR6_NOT_IN_RAID_INSTANCE             = 0x00000800, // 11 not usable in raid instance
    SPELL_ATTR6_CASTABLE_WHILE_ON_VEHICLE        = 0x00001000, // 12 castable while caster is on vehicle
    SPELL_ATTR6_UNK13                            = 0x00002000, // 13
    SPELL_ATTR6_UNK14                            = 0x00004000, // 14
    SPELL_ATTR6_UNK15                            = 0x00008000, // 15 not set in 3.0.3
    SPELL_ATTR6_UNK16                            = 0x00010000, // 16
    SPELL_ATTR6_UNK17                            = 0x00020000, // 17
    SPELL_ATTR6_UNK18                            = 0x00040000, // 18
    SPELL_ATTR6_UNK19                            = 0x00080000, // 19
    SPELL_ATTR6_UNK20                            = 0x00100000, // 20
    SPELL_ATTR6_CLIENT_UI_TARGET_EFFECTS         = 0x00200000, // 21 it's only client-side attribute
    SPELL_ATTR6_UNK22                            = 0x00400000, // 22
    SPELL_ATTR6_UNK23                            = 0x00800000, // 23
    SPELL_ATTR6_CAN_TARGET_UNTARGETABLE          = 0x01000000, // 24 NYI!
    SPELL_ATTR6_UNK25                            = 0x02000000, // 25
    SPELL_ATTR6_UNK26                            = 0x04000000, // 26
    SPELL_ATTR6_UNK27                            = 0x08000000, // 27
    SPELL_ATTR6_UNK28                            = 0x10000000, // 28
    SPELL_ATTR6_NO_DONE_PCT_DAMAGE_MODS          = 0x20000000, // 29 ignores done percent damage mods?
    SPELL_ATTR6_UNK30                            = 0x40000000, // 30
    SPELL_ATTR6_UNK31                            = 0x80000000  // 31
};

enum SpellAttr7
{
    SPELL_ATTR7_UNK0                             = 0x00000001, //  0 Shaman's new spells (Call of the ...), Feign Death.
    SPELL_ATTR7_UNK1                             = 0x00000002, //  1 Not set in 3.2.2a.
    SPELL_ATTR7_REACTIVATE_AT_RESURRECT          = 0x00000004, //  2 Paladin's auras and 65607 only.
    SPELL_ATTR7_IS_CHEAT_SPELL                   = 0x00000008, //  3 Cannot cast if caster doesn't have UnitFlag2 & UNIT_FLAG2_ALLOW_CHEAT_SPELLS
    SPELL_ATTR7_UNK4                             = 0x00000010, //  4 Only 66109 test spell.
    SPELL_ATTR7_SUMMON_PLAYER_TOTEM              = 0x00000020, //  5 Only Shaman player totems.
    SPELL_ATTR7_UNK6                             = 0x00000040, //  6 Dark Surge, Surge of Light, Burning Breath triggers (boss spells).
    SPELL_ATTR7_UNK7                             = 0x00000080, //  7 66218 (Launch) spell.
    SPELL_ATTR7_HORDE_ONLY                       = 0x00000100, //  8 Teleports, mounts and other spells.
    SPELL_ATTR7_ALLIANCE_ONLY                    = 0x00000200, //  9 Teleports, mounts and other spells.
    SPELL_ATTR7_DISPEL_CHARGES                   = 0x00000400, // 10 Dispel and Spellsteal individual charges instead of whole aura.
    SPELL_ATTR7_INTERRUPT_ONLY_NONPLAYER         = 0x00000800, // 11 Only non-player casts interrupt, though Feral Charge - Bear has it.
    SPELL_ATTR7_UNK12                            = 0x00001000, // 12 Not set in 3.2.2a.
    SPELL_ATTR7_UNK13                            = 0x00002000, // 13 Not set in 3.2.2a.
    SPELL_ATTR7_UNK14                            = 0x00004000, // 14 Only 52150 (Raise Dead - Pet) spell.
    SPELL_ATTR7_UNK15                            = 0x00008000, // 15 Exorcism. Usable on players? 100% crit chance on undead and demons?
    SPELL_ATTR7_UNK16                            = 0x00010000, // 16 Druid spells (29166, 54833, 64372, 68285).
    SPELL_ATTR7_UNK17                            = 0x00020000, // 17 Only 27965 (Suicide) spell.
    SPELL_ATTR7_HAS_CHARGE_EFFECT                = 0x00040000, // 18 Only spells that have Charge among effects.
    SPELL_ATTR7_ZONE_TELEPORT                    = 0x00080000, // 19 Teleports to specific zones.
    SPELL_ATTR7_UNK20                            = 0x00100000, // 20
    SPELL_ATTR7_UNK21                            = 0x00200000, // 21
    SPELL_ATTR7_UNK22                            = 0x00400000, // 22
    SPELL_ATTR7_UNK23                            = 0x00800000, // 23
    SPELL_ATTR7_UNK24                            = 0x01000000, // 24
    SPELL_ATTR7_UNK25                            = 0x02000000, // 25
    SPELL_ATTR7_UNK26                            = 0x04000000, // 26
    SPELL_ATTR7_UNK27                            = 0x08000000, // 27
    SPELL_ATTR7_UNK28                            = 0x10000000, // 28
    SPELL_ATTR7_UNK29                            = 0x20000000, // 29
    SPELL_ATTR7_UNK30                            = 0x40000000, // 30
    SPELL_ATTR7_UNK31                            = 0x80000000  // 31
};

enum SpellAttr8
{
    SPELL_ATTR_EX8_TAUNT                      = 0x00000001,            // 0
    SPELL_ATTR_EX8_WORGEN_TRANSFORMATION      = 0x00000002,            // 1
    SPELL_ATTR_EX8_UNK2                       = 0x00000004,            // 2 3 spells : 72221, 90960, 90961
    SPELL_ATTR_EX8_UNK3                       = 0x00000008,            // 3 summoning and unsummoning spells?
    SPELL_ATTR_EX8_UNK4                       = 0x00000010,            // 4 
    SPELL_ATTR_EX8_UNK5                       = 0x00000020,            // 5
    SPELL_ATTR_EX8_UNK6                       = 0x00000040,            // 6 2 spells: 56817 and 83569
    SPELL_ATTR_EX8_UNK7                       = 0x00000080,            // 7 
    SPELL_ATTR_EX8_UNK8                       = 0x00000100,            // 8 +stats.
    SPELL_ATTR_EX8_UNK9                       = 0x00000200,            // 9 
    SPELL_ATTR_EX8_CHANGE_MODEL               = 0x00000400,            // 10
    SPELL_ATTR_EX8_UNK11                      = 0x00000800,            // 11 one spell: 80224
    SPELL_ATTR_EX8_UNK12                      = 0x00001000,            // 12 
    SPELL_ATTR_EX8_UNK13                      = 0x00002000,            // 13
    SPELL_ATTR_EX8_UNK14                      = 0x00004000,            // 14
    SPELL_ATTR_EX8_UNK15                      = 0x00008000,            // 15 one spell: 76203
    SPELL_ATTR_EX8_UNK16                      = 0x00010000,            // 16
    SPELL_ATTR_EX8_UNK17                      = 0x00020000,            // 17
    SPELL_ATTR_EX8_UNK18                      = 0x00040000,            // 18 spell with interactions?
    SPELL_ATTR_EX8_UNK19                      = 0x00080000,            // 19 requires combo points?
    SPELL_ATTR_EX8_ARMOR_SPECIALIZATION       = 0x00100000,            // 20 
    SPELL_ATTR_EX8_UNK21                      = 0x00200000,            // 21
    SPELL_ATTR_EX8_UNK22                      = 0x00400000,            // 22
    SPELL_ATTR_EX8_UNK23                      = 0x00800000,            // 23 resurrection? soulstone?
    SPELL_ATTR_EX8_UNK24                      = 0x01000000,            // 24 
    SPELL_ATTR_EX8_UNK25                      = 0x02000000,            // 25
    SPELL_ATTR_EX8_RAID_MARKER                = 0x04000000,            // 26 raid marker. 6 spells in 4.0.3a
    SPELL_ATTR_EX8_UNK27                      = 0x08000000,            // 27 throw?
    SPELL_ATTR_EX8_GUILD_PERKS                = 0x10000000,            // 28
    SPELL_ATTR_EX8_MASTERY                    = 0x20000000,            // 29
    SPELL_ATTR_EX8_UNK30                      = 0x40000000,            // 30 Not set in 4.0.3a
    SPELL_ATTR_EX8_UNK31                      = 0x80000000             // 31
};

#define MIN_TALENT_SPEC         0
#define MAX_TALENT_SPEC         1
#define MIN_TALENT_SPECS        1
#define MAX_TALENT_SPECS        2
#define MAX_GLYPH_SLOT_INDEX    9

// Custom values
enum SpellClickUserTypes
{
    SPELL_CLICK_USER_ANY = 0,
    SPELL_CLICK_USER_FRIEND = 1,
    SPELL_CLICK_USER_RAID = 2,
    SPELL_CLICK_USER_PARTY = 3,
    SPELL_CLICK_USER_MAX = 4
};

enum SpellClickCastFlags
{
    NPC_CLICK_CAST_CASTER_CLICKER       = 0x01,
    NPC_CLICK_CAST_TARGET_CLICKER       = 0x02,
    NPC_CLICK_CAST_ORIG_CASTER_OWNER    = 0x04,
};

enum SheathTypes
{
    SHEATHETYPE_NONE                   = 0,
    SHEATHETYPE_MAINHAND               = 1,
    SHEATHETYPE_OFFHAND                = 2,
    SHEATHETYPE_LARGEWEAPONLEFT        = 3,
    SHEATHETYPE_LARGEWEAPONRIGHT       = 4,
    SHEATHETYPE_HIPWEAPONLEFT          = 5,
    SHEATHETYPE_HIPWEAPONRIGHT         = 6,
    SHEATHETYPE_SHIELD                 = 7
};

#define MAX_SHEATHETYPE                  8

enum CharacterSlot
{
    SLOT_HEAD                          = 0,
    SLOT_NECK                          = 1,
    SLOT_SHOULDERS                     = 2,
    SLOT_SHIRT                         = 3,
    SLOT_CHEST                         = 4,
    SLOT_WAIST                         = 5,
    SLOT_LEGS                          = 6,
    SLOT_FEET                          = 7,
    SLOT_WRISTS                        = 8,
    SLOT_HANDS                         = 9,
    SLOT_FINGER1                       = 10,
    SLOT_FINGER2                       = 11,
    SLOT_TRINKET1                      = 12,
    SLOT_TRINKET2                      = 13,
    SLOT_BACK                          = 14,
    SLOT_MAIN_HAND                     = 15,
    SLOT_OFF_HAND                      = 16,
    SLOT_RANGED                        = 17,
    SLOT_TABARD                        = 18,
    SLOT_EMPTY                         = 19
};

enum Language
{
    LANG_UNIVERSAL      = 0,
    LANG_ORCISH         = 1,
    LANG_DARNASSIAN     = 2,
    LANG_TAURAHE        = 3,
    LANG_DWARVISH       = 6,
    LANG_COMMON         = 7,
    LANG_DEMONIC        = 8,
    LANG_TITAN          = 9,
    LANG_THALASSIAN     = 10,
    LANG_DRACONIC       = 11,
    LANG_KALIMAG        = 12,
    LANG_GNOMISH        = 13,
    LANG_TROLL          = 14,
    LANG_GUTTERSPEAK    = 33,
    LANG_DRAENEI        = 35,
    LANG_ZOMBIE         = 36,
    LANG_GNOMISH_BINARY = 37,
    LANG_GOBLIN_BINARY  = 38,
    LANG_WORGEN         = 39,
    LANG_GOBLIN         = 40,
    LANG_ADDON          = 0xFFFFFFFF                        // used by addons, in 2.4.0 not exist, replaced by messagetype?
};

#define LANGUAGES_COUNT   21

enum TeamId
{
    TEAM_ALLIANCE = 0,
    TEAM_HORDE,
    TEAM_NEUTRAL,
};

enum Team
{
    HORDE               = 67,
    ALLIANCE            = 469,
    //TEAM_STEAMWHEEDLE_CARTEL = 169,                       // not used in code
    //TEAM_ALLIANCE_FORCES     = 891,
    //TEAM_HORDE_FORCES        = 892,
    //TEAM_SANCTUARY           = 936,
    //TEAM_OUTLAND             = 980,
    TEAM_OTHER               = 0,                         // if ReputationListId > 0 && Flags != FACTION_FLAG_TEAM_HEADER
};

enum SpellEffects
{
    SPELL_EFFECT_INSTAKILL                          = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE                      = 2,
    SPELL_EFFECT_DUMMY                              = 3,
    SPELL_EFFECT_PORTAL_TELEPORT                    = 4,
    SPELL_EFFECT_TELEPORT_UNITS                     = 5,
    SPELL_EFFECT_APPLY_AURA                         = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE               = 7,
    SPELL_EFFECT_POWER_DRAIN                        = 8,
    SPELL_EFFECT_HEALTH_LEECH                       = 9,
    SPELL_EFFECT_HEAL                               = 10,
    SPELL_EFFECT_BIND                               = 11,
    SPELL_EFFECT_PORTAL                             = 12,
    SPELL_EFFECT_RITUAL_BASE                        = 13,
    SPELL_EFFECT_RITUAL_SPECIALIZE                  = 14,
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL             = 15,
    SPELL_EFFECT_QUEST_COMPLETE                     = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL             = 17,
    SPELL_EFFECT_RESURRECT                          = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS                  = 19,
    SPELL_EFFECT_DODGE                              = 20,
    SPELL_EFFECT_EVADE                              = 21,
    SPELL_EFFECT_PARRY                              = 22,
    SPELL_EFFECT_BLOCK                              = 23,
    SPELL_EFFECT_CREATE_ITEM                        = 24,
    SPELL_EFFECT_WEAPON                             = 25,
    SPELL_EFFECT_DEFENSE                            = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA               = 27,
    SPELL_EFFECT_SUMMON                             = 28,
    SPELL_EFFECT_LEAP                               = 29,
    SPELL_EFFECT_ENERGIZE                           = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE              = 31,
    SPELL_EFFECT_TRIGGER_MISSILE                    = 32,
    SPELL_EFFECT_OPEN_LOCK                          = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM                 = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY              = 35,
    SPELL_EFFECT_LEARN_SPELL                        = 36,
    SPELL_EFFECT_SPELL_DEFENSE                      = 37,
    SPELL_EFFECT_DISPEL                             = 38,
    SPELL_EFFECT_LANGUAGE                           = 39,
    SPELL_EFFECT_DUAL_WIELD                         = 40,
    SPELL_EFFECT_JUMP                               = 41,
    SPELL_EFFECT_JUMP_DEST                          = 42,
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER         = 43,
    SPELL_EFFECT_SKILL_STEP                         = 44,
    SPELL_EFFECT_ADD_HONOR                          = 45,
    SPELL_EFFECT_SPAWN                              = 46,
    SPELL_EFFECT_TRADE_SKILL                        = 47,
    SPELL_EFFECT_STEALTH                            = 48,
    SPELL_EFFECT_DETECT                             = 49,
    SPELL_EFFECT_TRANS_DOOR                         = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT                 = 51,
    SPELL_EFFECT_GUARANTEE_HIT                      = 52,
    SPELL_EFFECT_ENCHANT_ITEM                       = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY             = 54,
    SPELL_EFFECT_TAMECREATURE                       = 55,
    SPELL_EFFECT_SUMMON_PET                         = 56,
    SPELL_EFFECT_LEARN_PET_SPELL                    = 57,
    SPELL_EFFECT_WEAPON_DAMAGE                      = 58,
    SPELL_EFFECT_CREATE_RANDOM_ITEM                 = 59,
    SPELL_EFFECT_PROFICIENCY                        = 60,
    SPELL_EFFECT_SEND_EVENT                         = 61,
    SPELL_EFFECT_POWER_BURN                         = 62,
    SPELL_EFFECT_THREAT                             = 63,
    SPELL_EFFECT_TRIGGER_SPELL                      = 64,
    SPELL_EFFECT_APPLY_AREA_AURA_RAID               = 65,
    SPELL_EFFECT_CREATE_MANA_GEM                    = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH                    = 67,
    SPELL_EFFECT_INTERRUPT_CAST                     = 68,
    SPELL_EFFECT_DISTRACT                           = 69,
    SPELL_EFFECT_PULL                               = 70,
    SPELL_EFFECT_PICKPOCKET                         = 71,
    SPELL_EFFECT_ADD_FARSIGHT                       = 72,
    SPELL_EFFECT_UNTRAIN_TALENTS                    = 73,
    SPELL_EFFECT_APPLY_GLYPH                        = 74,
    SPELL_EFFECT_HEAL_MECHANICAL                    = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD                 = 76,
    SPELL_EFFECT_SCRIPT_EFFECT                      = 77,
    SPELL_EFFECT_ATTACK                             = 78,
    SPELL_EFFECT_SANCTUARY                          = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS                   = 80,
    SPELL_EFFECT_CREATE_HOUSE                       = 81,
    SPELL_EFFECT_BIND_SIGHT                         = 82,
    SPELL_EFFECT_DUEL                               = 83,
    SPELL_EFFECT_STUCK                              = 84,
    SPELL_EFFECT_SUMMON_PLAYER                      = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT                    = 86,
    SPELL_EFFECT_GAMEOBJECT_DAMAGE                  = 87,
    SPELL_EFFECT_GAMEOBJECT_REPAIR                  = 88,
    SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE   = 89,
    SPELL_EFFECT_KILL_CREDIT                        = 90,
    SPELL_EFFECT_THREAT_ALL                         = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM                  = 92,
    SPELL_EFFECT_FORCE_DESELECT                     = 93,
    SPELL_EFFECT_SELF_RESURRECT                     = 94,
    SPELL_EFFECT_SKINNING                           = 95,
    SPELL_EFFECT_CHARGE                             = 96,
    SPELL_EFFECT_CAST_BUTTON                        = 97,
    SPELL_EFFECT_KNOCK_BACK                         = 98,
    SPELL_EFFECT_DISENCHANT                         = 99,
    SPELL_EFFECT_INEBRIATE                          = 100,
    SPELL_EFFECT_FEED_PET                           = 101,
    SPELL_EFFECT_DISMISS_PET                        = 102,
    SPELL_EFFECT_REPUTATION                         = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1                = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2                = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3                = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4                = 107,
    SPELL_EFFECT_DISPEL_MECHANIC                    = 108,
    SPELL_EFFECT_SUMMON_DEAD_PET                    = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS                 = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE                  = 111,
    SPELL_EFFECT_112                                = 112,
    SPELL_EFFECT_RESURRECT_NEW                      = 113,
    SPELL_EFFECT_ATTACK_ME                          = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT              = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE                 = 116,
    SPELL_EFFECT_SPIRIT_HEAL                        = 117,
    SPELL_EFFECT_SKILL                              = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET                = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD                 = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG              = 121,
    SPELL_EFFECT_122                                = 122,
    SPELL_EFFECT_SEND_TAXI                          = 123,
    SPELL_EFFECT_PULL_TOWARDS                       = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT              = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF              = 126,
    SPELL_EFFECT_PROSPECTING                        = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND             = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY              = 129,
    SPELL_EFFECT_REDIRECT_THREAT                    = 130,
    SPELL_EFFECT_131                                = 131,
    SPELL_EFFECT_PLAY_MUSIC                         = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION             = 133,
    SPELL_EFFECT_KILL_CREDIT2                       = 134,
    SPELL_EFFECT_CALL_PET                           = 135,
    SPELL_EFFECT_HEAL_PCT                           = 136,
    SPELL_EFFECT_ENERGIZE_PCT                       = 137,
    SPELL_EFFECT_LEAP_BACK                          = 138,
    SPELL_EFFECT_CLEAR_QUEST                        = 139,
    SPELL_EFFECT_FORCE_CAST                         = 140,
    SPELL_EFFECT_FORCE_CAST_WITH_VALUE              = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE           = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER              = 143,
    SPELL_EFFECT_KNOCK_BACK_DEST                    = 144,
    SPELL_EFFECT_PULL_TOWARDS_DEST                  = 145,
    SPELL_EFFECT_ACTIVATE_RUNE                      = 146,
    SPELL_EFFECT_QUEST_FAIL                         = 147,
    SPELL_EFFECT_148                                = 148,
    SPELL_EFFECT_CHARGE_DEST                        = 149,
    SPELL_EFFECT_QUEST_START                        = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2                    = 151,
    SPELL_EFFECT_SUMMON_RAF_FRIEND                  = 152,
    SPELL_EFFECT_CREATE_TAMED_PET                   = 153,
    SPELL_EFFECT_DISCOVER_TAXI                      = 154,
    SPELL_EFFECT_TITAN_GRIP                         = 155,
    SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC             = 156,
    SPELL_EFFECT_CREATE_ITEM_2                      = 157,
    SPELL_EFFECT_MILLING                            = 158,
    SPELL_EFFECT_ALLOW_RENAME_PET                   = 159,
    SPELL_EFFECT_160                                = 160,
    SPELL_EFFECT_TALENT_SPEC_COUNT                  = 161,
    SPELL_EFFECT_TALENT_SPEC_SELECT                 = 162,
    SPELL_EFFECT_163                                = 163,
    SPELL_EFFECT_REMOVE_AURA               = 164,
    SPELL_EFFECT_165                       = 165,
    SPELL_EFFECT_166                       = 166,
    SPELL_EFFECT_167                       = 167,
    SPELL_EFFECT_168                       = 168,
    SPELL_EFFECT_169                       = 169,
    SPELL_EFFECT_170                       = 170,
    SPELL_EFFECT_171                       = 171,
    SPELL_EFFECT_172                       = 172,
    SPELL_EFFECT_173                       = 173,
    SPELL_EFFECT_174                       = 174,
    TOTAL_SPELL_EFFECTS                    = 175
};

enum SpellCastResult
{
    SPELL_FAILED_SUCCESS = 0,
    SPELL_FAILED_AFFECTING_COMBAT = 1,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH = 2,
    SPELL_FAILED_ALREADY_AT_FULL_MANA = 3,
    SPELL_FAILED_ALREADY_AT_FULL_POWER = 4,
    SPELL_FAILED_ALREADY_BEING_TAMED = 5,
    SPELL_FAILED_ALREADY_HAVE_CHARM = 6,
    SPELL_FAILED_ALREADY_HAVE_SUMMON = 7,
    SPELL_FAILED_ALREADY_HAVE_PET = 8,
    SPELL_FAILED_ALREADY_OPEN = 9,
    SPELL_FAILED_AURA_BOUNCED = 10,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED = 11,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS = 12,
    SPELL_FAILED_BAD_TARGETS = 13,
    SPELL_FAILED_CANT_BE_CHARMED = 14,
    SPELL_FAILED_CANT_BE_DISENCHANTED = 15,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL = 16,
    SPELL_FAILED_CANT_BE_MILLED = 17,
    SPELL_FAILED_CANT_BE_PROSPECTED = 18,
    SPELL_FAILED_CANT_CAST_ON_TAPPED = 19,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE = 20,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED = 21,
    SPELL_FAILED_CANT_STEALTH = 22,
    SPELL_FAILED_CASTER_AURASTATE = 23,
    SPELL_FAILED_CASTER_DEAD = 24,
    SPELL_FAILED_CHARMED = 25,
    SPELL_FAILED_CHEST_IN_USE = 26,
    SPELL_FAILED_CONFUSED = 27,
    SPELL_FAILED_DONT_REPORT = 28,
    SPELL_FAILED_EQUIPPED_ITEM = 29,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS = 30,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND = 31,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND = 32,
    SPELL_FAILED_ERROR = 33,
    SPELL_FAILED_FALLING = 34,
    SPELL_FAILED_FIZZLE = 35,
    SPELL_FAILED_FLEEING = 36,
    SPELL_FAILED_FOOD_LOWLEVEL = 37,
    SPELL_FAILED_HIGHLEVEL = 38,
    SPELL_FAILED_HUNGER_SATIATED = 39,
    SPELL_FAILED_IMMUNE = 40,
    SPELL_FAILED_INCORRECT_AREA = 41,
    SPELL_FAILED_INTERRUPTED = 42,
    SPELL_FAILED_INTERRUPTED_COMBAT = 43,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED = 44,
    SPELL_FAILED_ITEM_GONE = 45,
    SPELL_FAILED_ITEM_NOT_FOUND = 46,
    SPELL_FAILED_ITEM_NOT_READY = 47,
    SPELL_FAILED_LEVEL_REQUIREMENT = 48,
    SPELL_FAILED_LINE_OF_SIGHT = 49,
    SPELL_FAILED_LOWLEVEL = 50,
    SPELL_FAILED_LOW_CASTLEVEL = 51,
    SPELL_FAILED_MAINHAND_EMPTY = 52,
    SPELL_FAILED_MOVING = 53,
    SPELL_FAILED_NEED_AMMO = 54,
    SPELL_FAILED_NEED_AMMO_POUCH = 55,
    SPELL_FAILED_NEED_EXOTIC_AMMO = 56,
    SPELL_FAILED_NEED_MORE_ITEMS = 57,
    SPELL_FAILED_NOPATH = 58,
    SPELL_FAILED_NOT_BEHIND = 59,
    SPELL_FAILED_NOT_FISHABLE = 60,
    SPELL_FAILED_NOT_FLYING = 61,
    SPELL_FAILED_NOT_HERE = 62,
    SPELL_FAILED_NOT_INFRONT = 63,
    SPELL_FAILED_NOT_IN_CONTROL = 64,
    SPELL_FAILED_NOT_KNOWN = 65,
    SPELL_FAILED_NOT_MOUNTED = 66,
    SPELL_FAILED_NOT_ON_TAXI = 67,
    SPELL_FAILED_NOT_ON_TRANSPORT = 68,
    SPELL_FAILED_NOT_READY = 69,
    SPELL_FAILED_NOT_SHAPESHIFT = 70,
    SPELL_FAILED_NOT_STANDING = 71,
    SPELL_FAILED_NOT_TRADEABLE = 72,
    SPELL_FAILED_NOT_TRADING = 73,
    SPELL_FAILED_NOT_UNSHEATHED = 74,
    SPELL_FAILED_NOT_WHILE_GHOST = 75,
    SPELL_FAILED_NOT_WHILE_LOOTING = 76,
    SPELL_FAILED_NO_AMMO = 77,
    SPELL_FAILED_NO_CHARGES_REMAIN = 78,
    SPELL_FAILED_NO_CHAMPION = 79,
    SPELL_FAILED_NO_COMBO_POINTS = 80,
    SPELL_FAILED_NO_DUELING = 81,
    SPELL_FAILED_NO_ENDURANCE = 82,
    SPELL_FAILED_NO_FISH = 83,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED = 84,
    SPELL_FAILED_NO_MOUNTS_ALLOWED = 85,
    SPELL_FAILED_NO_PET = 86,
    SPELL_FAILED_NO_POWER = 87,
    SPELL_FAILED_NOTHING_TO_DISPEL = 88,
    SPELL_FAILED_NOTHING_TO_STEAL = 89,
    SPELL_FAILED_ONLY_ABOVEWATER = 90,
    SPELL_FAILED_ONLY_DAYTIME = 91,
    SPELL_FAILED_ONLY_INDOORS = 92,
    SPELL_FAILED_ONLY_MOUNTED = 93,
    SPELL_FAILED_ONLY_NIGHTTIME = 94,
    SPELL_FAILED_ONLY_OUTDOORS = 95,
    SPELL_FAILED_ONLY_SHAPESHIFT = 96,
    SPELL_FAILED_ONLY_STEALTHED = 97,
    SPELL_FAILED_ONLY_UNDERWATER = 98,
    SPELL_FAILED_OUT_OF_RANGE = 99,
    SPELL_FAILED_PACIFIED = 100,
    SPELL_FAILED_POSSESSED = 101,
    SPELL_FAILED_REAGENTS = 102,
    SPELL_FAILED_REQUIRES_AREA = 103,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS = 104,
    SPELL_FAILED_ROOTED = 105,
    SPELL_FAILED_SILENCED = 106,
    SPELL_FAILED_SPELL_IN_PROGRESS = 107,
    SPELL_FAILED_SPELL_LEARNED = 108,
    SPELL_FAILED_SPELL_UNAVAILABLE = 109,
    SPELL_FAILED_STUNNED = 110,
    SPELL_FAILED_TARGETS_DEAD = 111,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT = 112,
    SPELL_FAILED_TARGET_AURASTATE = 113,
    SPELL_FAILED_TARGET_DUELING = 114,
    SPELL_FAILED_TARGET_ENEMY = 115,
    SPELL_FAILED_TARGET_ENRAGED = 116,
    SPELL_FAILED_TARGET_FRIENDLY = 117,
    SPELL_FAILED_TARGET_IN_COMBAT = 118,
    SPELL_FAILED_TARGET_IS_PLAYER = 119,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED = 120,
    SPELL_FAILED_TARGET_NOT_DEAD = 121,
    SPELL_FAILED_TARGET_NOT_IN_PARTY = 122,
    SPELL_FAILED_TARGET_NOT_LOOTED = 123,
    SPELL_FAILED_TARGET_NOT_PLAYER = 124,
    SPELL_FAILED_TARGET_NO_POCKETS = 125,
    SPELL_FAILED_TARGET_NO_WEAPONS = 126,
    SPELL_FAILED_TARGET_NO_RANGED_WEAPONS = 127,
    SPELL_FAILED_TARGET_UNSKINNABLE = 128,
    SPELL_FAILED_THIRST_SATIATED = 129,
    SPELL_FAILED_TOO_CLOSE = 130,
    SPELL_FAILED_TOO_MANY_OF_ITEM = 131,
    SPELL_FAILED_TOTEM_CATEGORY = 132,
    SPELL_FAILED_TOTEMS = 133,
    SPELL_FAILED_TRY_AGAIN = 134,
    SPELL_FAILED_UNIT_NOT_BEHIND = 135,
    SPELL_FAILED_UNIT_NOT_INFRONT = 136,
    SPELL_FAILED_VISION_OBSCURED = 137,
    SPELL_FAILED_WRONG_PET_FOOD = 138,
    SPELL_FAILED_NOT_WHILE_FATIGUED = 139,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE = 140,
    SPELL_FAILED_NOT_WHILE_TRADING = 141,
    SPELL_FAILED_TARGET_NOT_IN_RAID = 142,
    SPELL_FAILED_TARGET_FREEFORALL = 143,
    SPELL_FAILED_NO_EDIBLE_CORPSES = 144,
    SPELL_FAILED_ONLY_BATTLEGROUNDS = 145,
    SPELL_FAILED_TARGET_NOT_GHOST = 146,
    SPELL_FAILED_TRANSFORM_UNUSABLE = 147,
    SPELL_FAILED_WRONG_WEATHER = 148,
    SPELL_FAILED_DAMAGE_IMMUNE = 149,
    SPELL_FAILED_PREVENTED_BY_MECHANIC = 150,
    SPELL_FAILED_PLAY_TIME = 151,
    SPELL_FAILED_REPUTATION = 152,
    SPELL_FAILED_MIN_SKILL = 153,
    SPELL_FAILED_NOT_IN_RATED_BATTLEGROUND = 154,
    SPELL_FAILED_NOT_ON_SHAPESHIFT = 155,
    SPELL_FAILED_NOT_ON_STEALTHED = 156,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE = 157,
    SPELL_FAILED_NOT_ON_MOUNTED = 158,
    SPELL_FAILED_TOO_SHALLOW = 159,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY = 160,
    SPELL_FAILED_TARGET_IS_TRIVIAL = 161,
    SPELL_FAILED_BM_OR_INVISGOD = 162,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT = 163,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT = 164,
    SPELL_FAILED_NOT_IDLE = 165,
    SPELL_FAILED_NOT_INACTIVE = 166,
    SPELL_FAILED_PARTIAL_PLAYTIME = 167,
    SPELL_FAILED_NO_PLAYTIME = 168,
    SPELL_FAILED_NOT_IN_BATTLEGROUND = 169,
    SPELL_FAILED_NOT_IN_RAID_INSTANCE = 170,
    SPELL_FAILED_ONLY_IN_ARENA = 171,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 172,
    SPELL_FAILED_ON_USE_ENCHANT = 173,
    SPELL_FAILED_NOT_ON_GROUND = 174,
    SPELL_FAILED_CUSTOM_ERROR = 175,
    SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW = 176,
    SPELL_FAILED_TOO_MANY_SOCKETS = 177,
    SPELL_FAILED_INVALID_GLYPH = 178,
    SPELL_FAILED_UNIQUE_GLYPH = 179,
    SPELL_FAILED_GLYPH_SOCKET_LOCKED = 180,
    SPELL_FAILED_NO_VALID_TARGETS = 181,
    SPELL_FAILED_ITEM_AT_MAX_CHARGES = 182,
    SPELL_FAILED_NOT_IN_BARBERSHOP = 183,
    SPELL_FAILED_FISHING_TOO_LOW = 184,
    SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW = 185,
    SPELL_FAILED_SUMMON_PENDING = 186,
    SPELL_FAILED_MAX_SOCKETS = 187,
    SPELL_FAILED_PET_CAN_RENAME = 188,
    SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED = 189,
    SPELL_FAILED_NO_ACTIONS = 190,
    SPELL_FAILED_CURRENCY_WEIGHT_MISMATCH = 191,
    SPELL_FAILED_CURRENCY_WEIGHT_NOT_ENOUGH = 192,
    SPELL_FAILED_CURRENCY_WEIGHT_TOO_MUCH = 193,
    SPELL_FAILED_NO_VACANT_SEAT = 194,
    SPELL_FAILED_NO_LIQUID = 195,
    SPELL_FAILED_ONLY_NOT_SWIMMING = 196,
    SPELL_FAILED_BY_NOT_MOVING = 197,
    SPELL_FAILED_IN_COMBAT_RES_LIMIT_REACHED = 198,
    SPELL_FAILED_NOT_IN_ARENA = 199,
    SPELL_FAILED_TARGET_NOT_GROUNDED = 200,
    SPELL_FAILED_EXCEEDED_WEEKLY_USAGE = 201,
    SPELL_FAILED_NOT_IN_LFG_DUNGEON = 202,
    SPELL_FAILED_UNKNOWN = 203,                             // default

    SPELL_CAST_OK = 255 // custom value, don't must be send to client
};

enum SpellCustomErrors
{
    SPELL_CUSTOM_ERROR_NONE                             =  0,
    SPELL_CUSTOM_ERROR_CUSTOM_MSG                       =  1, // Something bad happened, and we want to display a custom message!
    SPELL_CUSTOM_ERROR_ALEX_BROKE_QUEST                 =  2, // Alex broke your quest! Thank him later!
    SPELL_CUSTOM_ERROR_NEED_HELPLESS_VILLAGER           =  3, // This spell may only be used on Helpless Wintergarde Villagers that have not been rescued.
    SPELL_CUSTOM_ERROR_NEED_WARSONG_DISGUISE            =  4, // Requires that you be wearing the Warsong Orc Disguise.
    SPELL_CUSTOM_ERROR_REQUIRES_PLAGUE_WAGON            =  5, // You must be closer to a plague wagon in order to drop off your 7th Legion Siege Engineer.
    SPELL_CUSTOM_ERROR_CANT_TARGET_FRIENDLY_NONPARTY    =  6, // You cannot target friendly units outside your party.
    SPELL_CUSTOM_ERROR_NEED_CHILL_NYMPH                 =  7, // You must target a weakened chill nymph.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_ENKILAH               =  8, // The Imbued Scourge Shroud will only work when equipped in the Temple City of En'kilah.
    SPELL_CUSTOM_ERROR_REQUIRES_CORPSE_DUST             =  9, // Requires Corpse Dust
    SPELL_CUSTOM_ERROR_CANT_SUMMON_GARGOYLE             = 10, // You cannot summon another gargoyle yet.
    SPELL_CUSTOM_ERROR_NEED_CORPSE_DUST_IF_NO_TARGET    = 11, // Requires Corpse Dust if the target is not dead and humanoid.
    SPELL_CUSTOM_ERROR_MUST_BE_AT_SHATTERHORN           = 12, // Can only be placed near Shatterhorn
    SPELL_CUSTOM_ERROR_MUST_TARGET_PROTO_DRAKE_EGG      = 13, // You must first select a Proto-Drake Egg.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_TREE            = 14, // You must be close to a marked tree.
    SPELL_CUSTOM_ERROR_MUST_TARGET_TURKEY               = 15, // You must target a Fjord Turkey.
    SPELL_CUSTOM_ERROR_MUST_TARGET_HAWK                 = 16, // You must target a Fjord Hawk.
    SPELL_CUSTOM_ERROR_TOO_FAR_FROM_BOUY                = 17, // You are too far from the bouy.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_OIL_SLICK       = 18, // Must be used near an oil slick.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_BOUY            = 19, // You must be closer to the buoy!
    SPELL_CUSTOM_ERROR_WYRMREST_VANQUISHER              = 20, // You may only call for the aid of a Wyrmrest Vanquisher in Wyrmrest Temple, The Dragon Wastes, Galakrond's Rest or The Wicked Coil.
    SPELL_CUSTOM_ERROR_MUST_TARGET_ICE_HEART_JORMUNGAR  = 21, // That can only be used on a Ice Heart Jormungar Spawn.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_SINKHOLE        = 22, // You must be closer to a sinkhole to use your map.
    SPELL_CUSTOM_ERROR_REQUIRES_HAROLD_LANE             = 23, // You may only call down a stampede on Harold Lane.
    SPELL_CUSTOM_ERROR_REQUIRES_GAMMOTH_MAGNATAUR       = 24, // You may only use the Pouch of Crushed Bloodspore on Gammothra or other magnataur in the Bloodspore Plains and Gammoth.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_RESURRECTION_CHAMBER  = 25, // Requires the magmawyrm resurrection chamber in the back of the Maw of Neltharion.
    SPELL_CUSTOM_ERROR_CANT_CALL_WINTERGARDE_HERE       = 26, // You may only call down a Wintergarde Gryphon in Wintergarde Keep or the Carrion Fields.
    SPELL_CUSTOM_ERROR_MUST_TARGET_WILHELM              = 27, // What are you doing? Only aim that thing at Wilhelm!
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH                = 28, // Not enough health!
    SPELL_CUSTOM_ERROR_NO_NEARBY_CORPSES                = 29, // There are no nearby corpses to use
    SPELL_CUSTOM_ERROR_TOO_MANY_GHOULS                  = 30, // You've created enough ghouls. Return to Gothik the Harvester at Death's Breach.
    SPELL_CUSTOM_ERROR_GO_FURTHER_FROM_SUNDERED_SHARD   = 31, // Your companion does not want to come here.  Go further from the Sundered Shard.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_CAT_FORM              = 32, // Must be in Cat Form
    SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT             = 33, // Only Death Knights may enter Ebon Hold.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_FERAL_FORM            = 34, // Must be in Cat Form, Bear Form, or Dire Bear Form
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_HELPLESS_VILLAGER   = 35, // You must be within range of a Helpless Wintergarde Villager.
    SPELL_CUSTOM_ERROR_CANT_TARGET_ELEMENTAL_MECHANICAL = 36, // You cannot target an elemental or mechanical corpse.
    SPELL_CUSTOM_ERROR_MUST_HAVE_USED_DALARAN_CRYSTAL   = 37, // This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once.
    SPELL_CUSTOM_ERROR_YOU_ALREADY_HOLD_SOMETHING       = 38, // You are already holding something in your hand. You must throw the creature in your hand before picking up another.
    SPELL_CUSTOM_ERROR_YOU_DONT_HOLD_ANYTHING           = 39, // You don't have anything to throw! Find a Vargul and use Gymer Grab to pick one up!
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_VALDURAN        = 40, // Bouldercrag's War Horn can only be used within 10 yards of Valduran the Stormborn.
    SPELL_CUSTOM_ERROR_NO_PASSENGER                     = 41, // You are not carrying a passenger. There is nobody to drop off.
    SPELL_CUSTOM_ERROR_CANT_BUILD_MORE_VEHICLES         = 42, // You cannot build any more siege vehicles.
    SPELL_CUSTOM_ERROR_ALREADY_CARRYING_CRUSADER        = 43, // You are already carrying a captured Argent Crusader. You must return to the Argent Vanguard infirmary and drop off your passenger before you may pick up another.
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_ROOTED             = 44, // You can't do that while rooted.
    SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_TARGET           = 45, // Requires a nearby target.
    SPELL_CUSTOM_ERROR_NOTHING_TO_DISCOVER              = 46, // Nothing left to discover.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_TARGETS               = 47, // No targets close enough to bluff.
    SPELL_CUSTOM_ERROR_CONSTRUCT_TOO_FAR                = 48, // Your Iron Rune Construct is out of range.
    SPELL_CUSTOM_ERROR_REQUIRES_GRAND_MASTER_ENGINEER   = 49, // Requires Grand Master Engineer
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_MOUNT              = 50, // You can't use that mount.
    SPELL_CUSTOM_ERROR_NOONE_TO_EJECT                   = 51, // There is nobody to eject!
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_BOUND             = 52, // The target must be bound to you.
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_UNDEAD            = 53, // Target must be undead.
    SPELL_CUSTOM_ERROR_TARGET_TOO_FAR                   = 54, // You have no target or your target is too far away.
    SPELL_CUSTOM_ERROR_MISSING_DARK_MATTER              = 55, // Missing Reagents: Dark Matter
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_ITEM               = 56, // You can't use that item
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_CYCYLONED          = 57, // You can't do that while Cycloned
    SPELL_CUSTOM_ERROR_TARGET_HAS_SCROLL                = 58, // Target is already affected by a scroll
    SPELL_CUSTOM_ERROR_POISON_TOO_STRONG                = 59, // That anti-venom is not strong enough to dispel that poison
    SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED         = 60, // You must have a lance equipped.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_MAIDEN          = 61, // You must be near the Maiden of Winter's Breath Lake.
    SPELL_CUSTOM_ERROR_LEARNED_EVERYTHING               = 62, // You have learned everything from that book
    SPELL_CUSTOM_ERROR_PET_IS_DEAD                      = 63, // Your pet is dead
    SPELL_CUSTOM_ERROR_NO_VALID_TARGETS                 = 64, // There are no valid targets within range.
    SPELL_CUSTOM_ERROR_GM_ONLY                          = 65, // Only GMs may use that. Your account has been reported for investigation.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_58                = 66, // You must reach level 58 to use this portal.
    SPELL_CUSTOM_ERROR_AT_HONOR_CAP                     = 67, // You already have the maximum amount of honor.
    SPELL_CUSTOM_ERROR_68                               = 68, // ""
    SPELL_CUSTOM_ERROR_69                               = 69, // ""
    SPELL_CUSTOM_ERROR_70                               = 70, // ""
    SPELL_CUSTOM_ERROR_71                               = 71, // ""
    SPELL_CUSTOM_ERROR_72                               = 72, // ""
    SPELL_CUSTOM_ERROR_73                               = 73, // ""
    SPELL_CUSTOM_ERROR_74                               = 74, // ""
    SPELL_CUSTOM_ERROR_MUST_HAVE_DEMONIC_CIRCLE         = 75, // You must have a demonic circle active.
    SPELL_CUSTOM_ERROR_AT_MAX_RAGE                      = 76, // You already have maximum rage
    SPELL_CUSTOM_ERROR_REQUIRES_350_ENGINEERING         = 77, // Requires Engineering (350)
    SPELL_CUSTOM_ERROR_SOUL_BELONGS_TO_LICH_KING        = 78, // Your soul belongs to the Lich King
    SPELL_CUSTOM_ERROR_ATTENDANT_HAS_PONY               = 79, // Your attendant already has an Argent Pony
    SPELL_CUSTOM_ERROR_80                               = 80, // ""
    SPELL_CUSTOM_ERROR_81                               = 81, // ""
    SPELL_CUSTOM_ERROR_82                               = 82, // ""
    SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM             = 83, // You must have a Fire Totem active.
    SPELL_CUSTOM_ERROR_CANT_TARGET_VAMPIRES             = 84, // You may not bite other vampires.
    SPELL_CUSTOM_ERROR_PET_ALREADY_AT_YOUR_LEVEL        = 85, // Your pet is already at your level.
    SPELL_CUSTOM_ERROR_MISSING_ITEM_REQUIREMENS         = 86, // You do not meet the level requirements for this item.
    SPELL_CUSTOM_ERROR_TOO_MANY_ABOMINATIONS            = 87, // There are too many Mutated Abominations.
    SPELL_CUSTOM_ERROR_ALL_POTIONS_USED                 = 88, // The potions have all been depleted by Professor Putricide.
    SPELL_CUSTOM_ERROR_89                               = 89, // ""
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_65                = 90, // Requires level 65
    SPELL_CUSTOM_ERROR_91                               = 91, // ""
    SPELL_CUSTOM_ERROR_92                               = 92, // ""
    SPELL_CUSTOM_ERROR_93                               = 93, // ""
    SPELL_CUSTOM_ERROR_94                               = 94, // ""
    SPELL_CUSTOM_ERROR_95                               = 95, // ""
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_RECRUITS           = 96, // You already have the max number of recruits.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_VOLUNTEERS         = 97, // You already have the max number of volunteers.
    SPELL_CUSTOM_ERROR_FROSTMOURNE_RENDERED_RESSURECT   = 98, // Frostmourne has rendered you unable to ressurect.
    SPELL_CUSTOM_ERROR_CANT_MOUNT_WITH_SHAPESHIFT       = 99, // You can't mount while affected by that shapeshift.
};

enum StealthType
{
    STEALTH_GENERAL     = 0,
    STEALTH_TRAP        = 1,

    TOTAL_STEALTH_TYPES = 2
};

enum InvisibilityType
{
    INVISIBILITY_GENERAL     =  0,
    INVISIBILITY_UNK1        =  1,
    INVISIBILITY_UNK2        =  2,
    INVISIBILITY_TRAP        =  3,
    INVISIBILITY_UNK4        =  4,
    INVISIBILITY_UNK5        =  5,
    INVISIBILITY_DRUNK       =  6,
    INVISIBILITY_UNK7        =  7,
    INVISIBILITY_UNK8        =  8,
    INVISIBILITY_UNK9        =  9,
    INVISIBILITY_UNK10       = 10,
    INVISIBILITY_UNK11       = 11,

    TOTAL_INVISIBILITY_TYPES = 12
};

enum ServerSideVisibilityType
{
    SERVERSIDE_VISIBILITY_GM          = 0,
    SERVERSIDE_VISIBILITY_GHOST       = 1,

    TOTAL_SERVERSIDE_VISIBILITY_TYPES = 2
};

enum GhostVisibilityType
{
    GHOST_VISIBILITY_ALIVE = 0x1,
    GHOST_VISIBILITY_GHOST = 0x2
};

// Spell aura states
enum AuraStateType
{   // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_NONE                         = 0,            // C   |
    AURA_STATE_DEFENSE                      = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT        = 2,            // CcT |
    AURA_STATE_BERSERKING                   = 3,            // C T |
    AURA_STATE_FROZEN                       = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT                    = 5,            // C   |
    //AURA_STATE_UNKNOWN6                   = 6,            //     | not used
    AURA_STATE_HUNTER_PARRY                 = 7,            // C   |
    //AURA_STATE_UNKNOWN7                   = 7,            //  c  | creature cheap shot / focused bursts spells
    //AURA_STATE_UNKNOWN8                   = 8,            //    t| test spells
    //AURA_STATE_UNKNOWN9                   = 9,            //     |
    AURA_STATE_WARRIOR_VICTORY_RUSH         = 10,           // C   | warrior victory rush
    //AURA_STATE_UNKNOWN11                  = 11,           // C  t| 60348 - Maelstrom Ready!, test spells
    AURA_STATE_FAERIE_FIRE                  = 12,           //  c t|
    AURA_STATE_HEALTHLESS_35_PERCENT        = 13,           // C T |
    AURA_STATE_CONFLAGRATE                  = 14,           //   T |
    AURA_STATE_SWIFTMEND                    = 15,           //   T |
    AURA_STATE_DEADLY_POISON                = 16,           //   T |
    AURA_STATE_ENRAGE                       = 17,           // C   |
    AURA_STATE_BLEEDING                     = 18,           //    T|
    AURA_STATE_UNKNOWN19                    = 19,           //     |
    //AURA_STATE_UNKNOWN20                  = 20,           //  c  | only (45317 Suicide)
    //AURA_STATE_UNKNOWN21                  = 21,           //     | not used
    AURA_STATE_UNKNOWN22                    = 22,           // C  t| varius spells (63884, 50240)
    AURA_STATE_HEALTH_ABOVE_75_PERCENT      = 23,           // C   |
};

#define PER_CASTER_AURA_STATE_MASK (\
    (1<<(AURA_STATE_CONFLAGRATE-1))|(1<<(AURA_STATE_DEADLY_POISON-1)))

// Spell mechanics
enum Mechanics
{
    MECHANIC_NONE             = 0,
    MECHANIC_CHARM            = 1,
    MECHANIC_DISORIENTED      = 2,
    MECHANIC_DISARM           = 3,
    MECHANIC_DISTRACT         = 4,
    MECHANIC_FEAR             = 5,
    MECHANIC_GRIP             = 6,
    MECHANIC_ROOT             = 7,
    MECHANIC_SLOW_ATTACK      = 8,
    MECHANIC_SILENCE          = 9,
    MECHANIC_SLEEP            = 10,
    MECHANIC_SNARE            = 11,
    MECHANIC_STUN             = 12,
    MECHANIC_FREEZE           = 13,
    MECHANIC_KNOCKOUT         = 14,
    MECHANIC_BLEED            = 15,
    MECHANIC_BANDAGE          = 16,
    MECHANIC_POLYMORPH        = 17,
    MECHANIC_BANISH           = 18,
    MECHANIC_SHIELD           = 19,
    MECHANIC_SHACKLE          = 20,
    MECHANIC_MOUNT            = 21,
    MECHANIC_INFECTED         = 22,
    MECHANIC_TURN             = 23,
    MECHANIC_HORROR           = 24,
    MECHANIC_INVULNERABILITY  = 25,
    MECHANIC_INTERRUPT        = 26,
    MECHANIC_DAZE             = 27,
    MECHANIC_DISCOVERY        = 28,
    MECHANIC_IMMUNE_SHIELD    = 29,                         // Divine (Blessing) Shield/Protection and Ice Block
    MECHANIC_SAPPED           = 30,
    MECHANIC_ENRAGED          = 31
};

// Used for spell 42292 Immune Movement Impairment and Loss of Control (0x49967ca6)
#define IMMUNE_TO_MOVEMENT_IMPAIRMENT_AND_LOSS_CONTROL_MASK (\
    (1<<MECHANIC_CHARM)|(1<<MECHANIC_DISORIENTED)|(1<<MECHANIC_FEAR)| \
    (1<<MECHANIC_ROOT)|(1<<MECHANIC_SLEEP)|(1<<MECHANIC_SNARE)| \
    (1<<MECHANIC_STUN)|(1<<MECHANIC_FREEZE)|(1<<MECHANIC_KNOCKOUT)| \
    (1<<MECHANIC_POLYMORPH)|(1<<MECHANIC_BANISH)|(1<<MECHANIC_SHACKLE)| \
    (1<<MECHANIC_TURN)|(1<<MECHANIC_HORROR)|(1<<MECHANIC_DAZE)| \
    (1<<MECHANIC_SAPPED))

// Spell dispell type
enum DispelType
{
    DISPEL_NONE         = 0,
    DISPEL_MAGIC        = 1,
    DISPEL_CURSE        = 2,
    DISPEL_DISEASE      = 3,
    DISPEL_POISON       = 4,
    DISPEL_STEALTH      = 5,
    DISPEL_INVISIBILITY = 6,
    DISPEL_ALL          = 7,
    DISPEL_SPE_NPC_ONLY = 8,
    DISPEL_ENRAGE       = 9,
    DISPEL_ZG_TICKET    = 10,
    DESPEL_OLD_UNUSED   = 11
};

#define DISPEL_ALL_MASK ((1<<DISPEL_MAGIC) | (1<<DISPEL_CURSE) | (1<<DISPEL_DISEASE) | (1<<DISPEL_POISON))

//To all Immune system, if target has immunes,
//some spell that related to ImmuneToDispel or ImmuneToSchool or ImmuneToDamage type can't cast to it,
//some spell_effects that related to ImmuneToEffect<effect>(only this effect in the spell) can't cast to it,
//some aura(related to Mechanics or ImmuneToState<aura>) can't apply to it.
enum SpellImmunity
{
    IMMUNITY_EFFECT                = 0,                     // enum SpellEffects
    IMMUNITY_STATE                 = 1,                     // enum AuraType
    IMMUNITY_SCHOOL                = 2,                     // enum SpellSchoolMask
    IMMUNITY_DAMAGE                = 3,                     // enum SpellSchoolMask
    IMMUNITY_DISPEL                = 4,                     // enum DispelType
    IMMUNITY_MECHANIC              = 5,                     // enum Mechanics
    IMMUNITY_ID                    = 6
};

#define MAX_SPELL_IMMUNITY           7

enum Targets
{
    TARGET_UNIT_CASTER                 = 1,
    TARGET_UNIT_NEARBY_ENEMY           = 2,
    TARGET_UNIT_NEARBY_PARTY           = 3,
    TARGET_UNIT_NEARBY_ALLY            = 4,
    TARGET_UNIT_PET                    = 5,
    TARGET_UNIT_TARGET_ENEMY           = 6,
    TARGET_UNIT_AREA_ENTRY_SRC         = 7,
    TARGET_UNIT_AREA_ENTRY_DST         = 8,
    TARGET_DST_HOME                    = 9,
    TARGET_UNIT_TARGET_DEST_CASTER     = 11, // teleport target to caster
    TARGET_UNIT_AREA_ENEMY_SRC         = 15,
    TARGET_UNIT_AREA_ENEMY_DST         = 16,
    TARGET_DST_DB                      = 17,
    TARGET_DST_CASTER                  = 18,
    TARGET_UNIT_PARTY_CASTER           = 20,
    TARGET_UNIT_TARGET_ALLY            = 21,
    TARGET_SRC_CASTER                  = 22,
    TARGET_GAMEOBJECT                  = 23,
    TARGET_UNIT_CONE_ENEMY             = 24,
    TARGET_UNIT_TARGET_ANY             = 25,
    TARGET_GAMEOBJECT_ITEM             = 26,
    TARGET_UNIT_MASTER                 = 27,
    TARGET_DEST_DYNOBJ_ENEMY           = 28,
    TARGET_DEST_DYNOBJ_ALLY            = 29,
    TARGET_UNIT_AREA_ALLY_SRC          = 30,
    TARGET_UNIT_AREA_ALLY_DST          = 31,
    TARGET_MINION                      = 32,
    //TARGET_DEST_SUMMON
    TARGET_UNIT_AREA_PARTY_SRC         = 33,
    TARGET_UNIT_AREA_PARTY_DST         = 34,
    TARGET_UNIT_TARGET_PARTY           = 35,
    TARGET_DEST_CASTER_RANDOM_UNKNOWN  = 36, //unknown
    TARGET_UNIT_TARGET_ALLY_PARTY      = 37,
    TARGET_UNIT_NEARBY_ENTRY           = 38,
    TARGET_UNIT_CASTER_FISHING         = 39,
    TARGET_GAMEOBJECT_NEARBY_ENTRY     = 40,
    TARGET_DEST_CASTER_FRONT_LEFT      = 41,
    TARGET_DEST_CASTER_BACK_LEFT       = 42,
    TARGET_DEST_CASTER_BACK_RIGHT      = 43,
    TARGET_DEST_CASTER_FRONT_RIGHT     = 44,
    TARGET_UNIT_CHAINHEAL              = 45,
    TARGET_DST_NEARBY_ENTRY            = 46,
    TARGET_DEST_CASTER_FRONT           = 47,
    TARGET_DEST_CASTER_BACK            = 48,
    TARGET_DEST_CASTER_RIGHT           = 49,
    TARGET_DEST_CASTER_LEFT            = 50,
    TARGET_GAMEOBJECT_AREA_SRC         = 51,
    TARGET_GAMEOBJECT_AREA_DST         = 52,
    TARGET_DST_TARGET_ENEMY            = 53, // set unit coordinates as dest, only 16 target B imlemented
    TARGET_UNIT_CONE_ENEMY_UNKNOWN     = 54, // 180 degree, or different angle
    TARGET_DEST_CASTER_FRONT_LEAP      = 55, // for a leap spell
    TARGET_UNIT_RAID_CASTER            = 56,
    TARGET_UNIT_TARGET_RAID            = 57,
    TARGET_UNIT_NEARBY_RAID            = 58,
    TARGET_UNIT_CONE_ALLY              = 59,
    TARGET_UNIT_CONE_ENTRY             = 60,
    TARGET_UNIT_TARGET_CLASS_RAID      = 61,
    TARGET_TEST                        = 62, // for a test spell
    TARGET_DEST_TARGET_ANY             = 63,
    TARGET_DEST_TARGET_FRONT           = 64,
    TARGET_DEST_TARGET_BACK            = 65,
    TARGET_DEST_TARGET_RIGHT           = 66,
    TARGET_DEST_TARGET_LEFT            = 67,
    TARGET_DEST_TARGET_FRONT_LEFT      = 68,
    TARGET_DEST_TARGET_BACK_LEFT       = 69,
    TARGET_DEST_TARGET_BACK_RIGHT      = 70,
    TARGET_DEST_TARGET_FRONT_RIGHT     = 71,
    TARGET_DEST_CASTER_RANDOM          = 72,
    TARGET_DEST_CASTER_RADIUS          = 73,
    TARGET_DEST_TARGET_RANDOM          = 74,
    TARGET_DEST_TARGET_RADIUS          = 75,
    TARGET_DEST_CHANNEL_TARGET         = 76,
    TARGET_UNIT_CHANNEL_TARGET         = 77,
    TARGET_DEST_DEST_FRONT             = 78,
    TARGET_DEST_DEST_BACK              = 79,
    TARGET_DEST_DEST_RIGHT             = 80,
    TARGET_DEST_DEST_LEFT              = 81,
    TARGET_DEST_DEST_FRONT_LEFT        = 82,
    TARGET_DEST_DEST_BACK_LEFT         = 83,
    TARGET_DEST_DEST_BACK_RIGHT        = 84,
    TARGET_DEST_DEST_FRONT_RIGHT       = 85,
    TARGET_DEST_DEST_RANDOM            = 86,
    TARGET_DEST_DEST                   = 87,
    TARGET_DEST_DYNOBJ_NONE            = 88,
    TARGET_DEST_TRAJ                   = 89,
    TARGET_UNIT_TARGET_MINIPET         = 90,
    TARGET_DEST_DEST_RANDOM_DIR_DIST   = 91,
    TARGET_UNIT_SUMMONER               = 92,
    TARGET_CORPSE_AREA_ENEMY_PLAYER_SRC= 93, // TODO
    TARGET_UNIT_VEHICLE                = 94,
    TARGET_UNIT_TARGET_PASSENGER       = 95,
    TARGET_UNIT_PASSENGER_0            = 96,
    TARGET_UNIT_PASSENGER_1            = 97,
    TARGET_UNIT_PASSENGER_2            = 98,
    TARGET_UNIT_PASSENGER_3            = 99,
    TARGET_UNIT_PASSENGER_4            = 100,
    TARGET_UNIT_PASSENGER_5            = 101,
    TARGET_UNIT_PASSENGER_6            = 102,
    TARGET_UNIT_PASSENGER_7            = 103,
    TARGET_UNIT_AREA_PATH              = 104,
    TARGET_UNIT_UNK_105                = 105, // 1 spell
    TARGET_DEST_CHANNEL_CASTER         = 106,
    TARGET_UNK_AREA_UNK_DST_107        = 107, // not enough info - only generic spells avalible
    TARGET_GAMEOBJECT_AREA_PATH        = 108,
    TARGET_DEST_UNK_110                = 110, // some kind of traj?
    TOTAL_SPELL_TARGETS
};

enum SpellMissInfo
{
    SPELL_MISS_NONE                    = 0,
    SPELL_MISS_MISS                    = 1,
    SPELL_MISS_RESIST                  = 2,
    SPELL_MISS_DODGE                   = 3,
    SPELL_MISS_PARRY                   = 4,
    SPELL_MISS_BLOCK                   = 5,
    SPELL_MISS_EVADE                   = 6,
    SPELL_MISS_IMMUNE                  = 7,
    SPELL_MISS_IMMUNE2                 = 8, // one of these 2 is MISS_TEMPIMMUNE
    SPELL_MISS_DEFLECT                 = 9,
    SPELL_MISS_ABSORB                  = 10,
    SPELL_MISS_REFLECT                 = 11
};

enum SpellHitType
{
    SPELL_HIT_TYPE_UNK1 = 0x00001,
    SPELL_HIT_TYPE_CRIT = 0x00002,
    SPELL_HIT_TYPE_UNK3 = 0x00004,
    SPELL_HIT_TYPE_UNK4 = 0x00008,
    SPELL_HIT_TYPE_UNK5 = 0x00010,                          // replace caster?
    SPELL_HIT_TYPE_UNK6 = 0x00020
};

enum SpellDmgClass
{
    SPELL_DAMAGE_CLASS_NONE     = 0,
    SPELL_DAMAGE_CLASS_MAGIC    = 1,
    SPELL_DAMAGE_CLASS_MELEE    = 2,
    SPELL_DAMAGE_CLASS_RANGED   = 3
};

enum SpellPreventionType
{
    SPELL_PREVENTION_TYPE_NONE      = 0,
    SPELL_PREVENTION_TYPE_SILENCE   = 1,
    SPELL_PREVENTION_TYPE_PACIFY    = 2
};

enum GameobjectTypes
{
    GAMEOBJECT_TYPE_DOOR                   = 0,
    GAMEOBJECT_TYPE_BUTTON                 = 1,
    GAMEOBJECT_TYPE_QUESTGIVER             = 2,
    GAMEOBJECT_TYPE_CHEST                  = 3,
    GAMEOBJECT_TYPE_BINDER                 = 4,
    GAMEOBJECT_TYPE_GENERIC                = 5,
    GAMEOBJECT_TYPE_TRAP                   = 6,
    GAMEOBJECT_TYPE_CHAIR                  = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
    GAMEOBJECT_TYPE_TEXT                   = 9,
    GAMEOBJECT_TYPE_GOOBER                 = 10,
    GAMEOBJECT_TYPE_TRANSPORT              = 11,
    GAMEOBJECT_TYPE_AREADAMAGE             = 12,
    GAMEOBJECT_TYPE_CAMERA                 = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
    GAMEOBJECT_TYPE_FISHINGNODE            = 17,
    GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
    GAMEOBJECT_TYPE_MAILBOX                = 19,
    GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
    GAMEOBJECT_TYPE_GUARDPOST              = 21,
    GAMEOBJECT_TYPE_SPELLCASTER            = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
    GAMEOBJECT_TYPE_FLAGSTAND              = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
    GAMEOBJECT_TYPE_FLAGDROP               = 26,
    GAMEOBJECT_TYPE_MINI_GAME              = 27,
    GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
    GAMEOBJECT_TYPE_GUILD_BANK             = 34,
    GAMEOBJECT_TYPE_TRAPDOOR               = 35
};

#define MAX_GAMEOBJECT_TYPE                  36             // sending to client this or greater value can crash client.
#define MAX_GAMEOBJECT_DATA                  32             // Max number of uint32 vars in gameobject_template data field

enum GameObjectFlags
{
    GO_FLAG_IN_USE          = 0x00000001,                   //disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   //require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   //cannot interact (condition to interact)
    GO_FLAG_TRANSPORT       = 0x00000008,                   //any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_UNK1            = 0x00000010,                   //
    GO_FLAG_NODESPAWN       = 0x00000020,                   //never despawn, typically for doors, they just change state
    GO_FLAG_TRIGGERED       = 0x00000040,                   //typically, summoned objects. Triggered by spell or other events
    GO_FLAG_DAMAGED         = 0x00000200,
    GO_FLAG_DESTROYED       = 0x00000400,
};

enum GameObjectDynamicLowFlags
{
    GO_DYNFLAG_LO_ACTIVATE          = 0x01,                 // enables interaction with GO
    GO_DYNFLAG_LO_ANIMATE           = 0x02,                 // possibly more distinct animation of GO
    GO_DYNFLAG_LO_NO_INTERACT       = 0x04,                 // appears to disable interaction (not fully verified)
    GO_DYNFLAG_LO_SPARKLE           = 0x08,                 // makes GO sparkle
};

enum GameObjectDestructibleState
{
    GO_DESTRUCTIBLE_INTACT      = 0,
    GO_DESTRUCTIBLE_DAMAGED     = 1,
    GO_DESTRUCTIBLE_DESTROYED   = 2,
    GO_DESTRUCTIBLE_REBUILDING  = 3,
};

enum TextEmotes
{
    TEXTEMOTE_AGREE                = 1,
    TEXTEMOTE_AMAZE                = 2,
    TEXTEMOTE_ANGRY                = 3,
    TEXTEMOTE_APOLOGIZE            = 4,
    TEXTEMOTE_APPLAUD              = 5,
    TEXTEMOTE_BASHFUL              = 6,
    TEXTEMOTE_BECKON               = 7,
    TEXTEMOTE_BEG                  = 8,
    TEXTEMOTE_BITE                 = 9,
    TEXTEMOTE_BLEED                = 10,
    TEXTEMOTE_BLINK                = 11,
    TEXTEMOTE_BLUSH                = 12,
    TEXTEMOTE_BONK                 = 13,
    TEXTEMOTE_BORED                = 14,
    TEXTEMOTE_BOUNCE               = 15,
    TEXTEMOTE_BRB                  = 16,
    TEXTEMOTE_BOW                  = 17,
    TEXTEMOTE_BURP                 = 18,
    TEXTEMOTE_BYE                  = 19,
    TEXTEMOTE_CACKLE               = 20,
    TEXTEMOTE_CHEER                = 21,
    TEXTEMOTE_CHICKEN              = 22,
    TEXTEMOTE_CHUCKLE              = 23,
    TEXTEMOTE_CLAP                 = 24,
    TEXTEMOTE_CONFUSED             = 25,
    TEXTEMOTE_CONGRATULATE         = 26,
    TEXTEMOTE_COUGH                = 27,
    TEXTEMOTE_COWER                = 28,
    TEXTEMOTE_CRACK                = 29,
    TEXTEMOTE_CRINGE               = 30,
    TEXTEMOTE_CRY                  = 31,
    TEXTEMOTE_CURIOUS              = 32,
    TEXTEMOTE_CURTSEY              = 33,
    TEXTEMOTE_DANCE                = 34,
    TEXTEMOTE_DRINK                = 35,
    TEXTEMOTE_DROOL                = 36,
    TEXTEMOTE_EAT                  = 37,
    TEXTEMOTE_EYE                  = 38,
    TEXTEMOTE_FART                 = 39,
    TEXTEMOTE_FIDGET               = 40,
    TEXTEMOTE_FLEX                 = 41,
    TEXTEMOTE_FROWN                = 42,
    TEXTEMOTE_GASP                 = 43,
    TEXTEMOTE_GAZE                 = 44,
    TEXTEMOTE_GIGGLE               = 45,
    TEXTEMOTE_GLARE                = 46,
    TEXTEMOTE_GLOAT                = 47,
    TEXTEMOTE_GREET                = 48,
    TEXTEMOTE_GRIN                 = 49,
    TEXTEMOTE_GROAN                = 50,
    TEXTEMOTE_GROVEL               = 51,
    TEXTEMOTE_GUFFAW               = 52,
    TEXTEMOTE_HAIL                 = 53,
    TEXTEMOTE_HAPPY                = 54,
    TEXTEMOTE_HELLO                = 55,
    TEXTEMOTE_HUG                  = 56,
    TEXTEMOTE_HUNGRY               = 57,
    TEXTEMOTE_KISS                 = 58,
    TEXTEMOTE_KNEEL                = 59,
    TEXTEMOTE_LAUGH                = 60,
    TEXTEMOTE_LAYDOWN              = 61,
    TEXTEMOTE_MESSAGE              = 62,
    TEXTEMOTE_MOAN                 = 63,
    TEXTEMOTE_MOON                 = 64,
    TEXTEMOTE_MOURN                = 65,
    TEXTEMOTE_NO                   = 66,
    TEXTEMOTE_NOD                  = 67,
    TEXTEMOTE_NOSEPICK             = 68,
    TEXTEMOTE_PANIC                = 69,
    TEXTEMOTE_PEER                 = 70,
    TEXTEMOTE_PLEAD                = 71,
    TEXTEMOTE_POINT                = 72,
    TEXTEMOTE_POKE                 = 73,
    TEXTEMOTE_PRAY                 = 74,
    TEXTEMOTE_ROAR                 = 75,
    TEXTEMOTE_ROFL                 = 76,
    TEXTEMOTE_RUDE                 = 77,
    TEXTEMOTE_SALUTE               = 78,
    TEXTEMOTE_SCRATCH              = 79,
    TEXTEMOTE_SEXY                 = 80,
    TEXTEMOTE_SHAKE                = 81,
    TEXTEMOTE_SHOUT                = 82,
    TEXTEMOTE_SHRUG                = 83,
    TEXTEMOTE_SHY                  = 84,
    TEXTEMOTE_SIGH                 = 85,
    TEXTEMOTE_SIT                  = 86,
    TEXTEMOTE_SLEEP                = 87,
    TEXTEMOTE_SNARL                = 88,
    TEXTEMOTE_SPIT                 = 89,
    TEXTEMOTE_STARE                = 90,
    TEXTEMOTE_SURPRISED            = 91,
    TEXTEMOTE_SURRENDER            = 92,
    TEXTEMOTE_TALK                 = 93,
    TEXTEMOTE_TALKEX               = 94,
    TEXTEMOTE_TALKQ                = 95,
    TEXTEMOTE_TAP                  = 96,
    TEXTEMOTE_THANK                = 97,
    TEXTEMOTE_THREATEN             = 98,
    TEXTEMOTE_TIRED                = 99,
    TEXTEMOTE_VICTORY              = 100,
    TEXTEMOTE_WAVE                 = 101,
    TEXTEMOTE_WELCOME              = 102,
    TEXTEMOTE_WHINE                = 103,
    TEXTEMOTE_WHISTLE              = 104,
    TEXTEMOTE_WORK                 = 105,
    TEXTEMOTE_YAWN                 = 106,
    TEXTEMOTE_BOGGLE               = 107,
    TEXTEMOTE_CALM                 = 108,
    TEXTEMOTE_COLD                 = 109,
    TEXTEMOTE_COMFORT              = 110,
    TEXTEMOTE_CUDDLE               = 111,
    TEXTEMOTE_DUCK                 = 112,
    TEXTEMOTE_INSULT               = 113,
    TEXTEMOTE_INTRODUCE            = 114,
    TEXTEMOTE_JK                   = 115,
    TEXTEMOTE_LICK                 = 116,
    TEXTEMOTE_LISTEN               = 117,
    TEXTEMOTE_LOST                 = 118,
    TEXTEMOTE_MOCK                 = 119,
    TEXTEMOTE_PONDER               = 120,
    TEXTEMOTE_POUNCE               = 121,
    TEXTEMOTE_PRAISE               = 122,
    TEXTEMOTE_PURR                 = 123,
    TEXTEMOTE_PUZZLE               = 124,
    TEXTEMOTE_RAISE                = 125,
    TEXTEMOTE_READY                = 126,
    TEXTEMOTE_SHIMMY               = 127,
    TEXTEMOTE_SHIVER               = 128,
    TEXTEMOTE_SHOO                 = 129,
    TEXTEMOTE_SLAP                 = 130,
    TEXTEMOTE_SMIRK                = 131,
    TEXTEMOTE_SNIFF                = 132,
    TEXTEMOTE_SNUB                 = 133,
    TEXTEMOTE_SOOTHE               = 134,
    TEXTEMOTE_STINK                = 135,
    TEXTEMOTE_TAUNT                = 136,
    TEXTEMOTE_TEASE                = 137,
    TEXTEMOTE_THIRSTY              = 138,
    TEXTEMOTE_VETO                 = 139,
    TEXTEMOTE_SNICKER              = 140,
    TEXTEMOTE_STAND                = 141,
    TEXTEMOTE_TICKLE               = 142,
    TEXTEMOTE_VIOLIN               = 143,
    TEXTEMOTE_SMILE                = 163,
    TEXTEMOTE_RASP                 = 183,
    TEXTEMOTE_PITY                 = 203,
    TEXTEMOTE_GROWL                = 204,
    TEXTEMOTE_BARK                 = 205,
    TEXTEMOTE_SCARED               = 223,
    TEXTEMOTE_FLOP                 = 224,
    TEXTEMOTE_LOVE                 = 225,
    TEXTEMOTE_MOO                  = 226,
    TEXTEMOTE_OPENFIRE             = 327,
    TEXTEMOTE_FLIRT                = 328,
    TEXTEMOTE_JOKE                 = 329,
    TEXTEMOTE_COMMEND              = 243,
    TEXTEMOTE_WINK                 = 363,
    TEXTEMOTE_PAT                  = 364,
    TEXTEMOTE_SERIOUS              = 365,
    TEXTEMOTE_MOUNTSPECIAL         = 366,
    TEXTEMOTE_GOODLUCK             = 367,
    TEXTEMOTE_BLAME                = 368,
    TEXTEMOTE_BLANK                = 369,
    TEXTEMOTE_BRANDISH             = 370,
    TEXTEMOTE_BREATH               = 371,
    TEXTEMOTE_DISAGREE             = 372,
    TEXTEMOTE_DOUBT                = 373,
    TEXTEMOTE_EMBARRASS            = 374,
    TEXTEMOTE_ENCOURAGE            = 375,
    TEXTEMOTE_ENEMY                = 376,
    TEXTEMOTE_EYEBROW              = 377,
    TEXTEMOTE_TOAST                = 378,
    TEXTEMOTE_FAIL                 = 379,
    TEXTEMOTE_HIGHFIVE             = 380,
    TEXTEMOTE_ABSENT               = 381,
    TEXTEMOTE_ARM                  = 382,
    TEXTEMOTE_AWE                  = 383,
    TEXTEMOTE_BACKPACK             = 384,
    TEXTEMOTE_BADFEELING           = 385,
    TEXTEMOTE_CHALLENGE            = 386,
    TEXTEMOTE_CHUG                 = 387,
    TEXTEMOTE_DING                 = 389,
    TEXTEMOTE_FACEPALM             = 390,
    TEXTEMOTE_FAINT                = 391,
    TEXTEMOTE_GO                   = 392,
    TEXTEMOTE_GOING                = 393,
    TEXTEMOTE_GLOWER               = 394,
    TEXTEMOTE_HEADACHE             = 395,
    TEXTEMOTE_HICCUP               = 396,
    TEXTEMOTE_HISS                 = 398,
    TEXTEMOTE_HOLDHAND             = 399,
    TEXTEMOTE_HURRY                = 401,
    TEXTEMOTE_IDEA                 = 402,
    TEXTEMOTE_JEALOUS              = 403,
    TEXTEMOTE_LUCK                 = 404,
    TEXTEMOTE_MAP                  = 405,
    TEXTEMOTE_MERCY                = 406,
    TEXTEMOTE_MUTTER               = 407,
    TEXTEMOTE_NERVOUS              = 408,
    TEXTEMOTE_OFFER                = 409,
    TEXTEMOTE_PET                  = 410,
    TEXTEMOTE_PINCH                = 411,
    TEXTEMOTE_PROUD                = 413,
    TEXTEMOTE_PROMISE              = 414,
    TEXTEMOTE_PULSE                = 415,
    TEXTEMOTE_PUNCH                = 416,
    TEXTEMOTE_POUT                 = 417,
    TEXTEMOTE_REGRET               = 418,
    TEXTEMOTE_REVENGE              = 420,
    TEXTEMOTE_ROLLEYES             = 421,
    TEXTEMOTE_RUFFLE               = 422,
    TEXTEMOTE_SAD                  = 423,
    TEXTEMOTE_SCOFF                = 424,
    TEXTEMOTE_SCOLD                = 425,
    TEXTEMOTE_SCOWL                = 426,
    TEXTEMOTE_SEARCH               = 427,
    TEXTEMOTE_SHAKEFIST            = 428,
    TEXTEMOTE_SHIFTY               = 429,
    TEXTEMOTE_SHUDDER              = 430,
    TEXTEMOTE_SIGNAL               = 431,
    TEXTEMOTE_SILENCE              = 432,
    TEXTEMOTE_SING                 = 433,
    TEXTEMOTE_SMACK                = 434,
    TEXTEMOTE_SNEAK                = 435,
    TEXTEMOTE_SNEEZE               = 436,
    TEXTEMOTE_SNORT                = 437,
    TEXTEMOTE_SQUEAL               = 438,
    TEXTEMOTE_STOPATTACK           = 439,
    TEXTEMOTE_SUSPICIOUS           = 440,
    TEXTEMOTE_THINK                = 441,
    TEXTEMOTE_TRUCE                = 442,
    TEXTEMOTE_TWIDDLE              = 443,
    TEXTEMOTE_WARN                 = 444,
    TEXTEMOTE_SNAP                 = 445,
    TEXTEMOTE_CHARM                = 446,
    TEXTEMOTE_COVEREARS            = 447,
    TEXTEMOTE_CROSSARMS            = 448,
    TEXTEMOTE_LOOK                 = 449,
    TEXTEMOTE_OBJECT               = 450,
    TEXTEMOTE_SWEAT                = 451,
    TEXTEMOTE_YW                   = 453,
    TEXTEMOTE_READ                 = 456
};

enum Emote
{
    EMOTE_ONESHOT_NONE                 = 0,
    EMOTE_ONESHOT_TALK                 = 1,
    EMOTE_ONESHOT_BOW                  = 2,
    EMOTE_ONESHOT_WAVE                 = 3,
    EMOTE_ONESHOT_CHEER                = 4,
    EMOTE_ONESHOT_EXCLAMATION          = 5,
    EMOTE_ONESHOT_QUESTION             = 6,
    EMOTE_ONESHOT_EAT                  = 7,
    EMOTE_STATE_DANCE                  = 10,
    EMOTE_ONESHOT_LAUGH                = 11,
    EMOTE_STATE_SLEEP                  = 12,
    EMOTE_STATE_SIT                    = 13,
    EMOTE_ONESHOT_RUDE                 = 14,
    EMOTE_ONESHOT_ROAR                 = 15,
    EMOTE_ONESHOT_KNEEL                = 16,
    EMOTE_ONESHOT_KISS                 = 17,
    EMOTE_ONESHOT_CRY                  = 18,
    EMOTE_ONESHOT_CHICKEN              = 19,
    EMOTE_ONESHOT_BEG                  = 20,
    EMOTE_ONESHOT_APPLAUD              = 21,
    EMOTE_ONESHOT_SHOUT                = 22,
    EMOTE_ONESHOT_FLEX                 = 23,
    EMOTE_ONESHOT_SHY                  = 24,
    EMOTE_ONESHOT_POINT                = 25,
    EMOTE_STATE_STAND                  = 26,
    EMOTE_STATE_READYUNARMED           = 27,
    EMOTE_STATE_WORK_SHEATHED          = 28,
    EMOTE_STATE_POINT                  = 29,
    EMOTE_STATE_NONE                   = 30,
    EMOTE_ONESHOT_WOUND                = 33,
    EMOTE_ONESHOT_WOUNDCRITICAL        = 34,
    EMOTE_ONESHOT_ATTACKUNARMED        = 35,
    EMOTE_ONESHOT_ATTACK1H             = 36,
    EMOTE_ONESHOT_ATTACK2HTIGHT        = 37,
    EMOTE_ONESHOT_ATTACK2HLOOSE        = 38,
    EMOTE_ONESHOT_PARRYUNARMED         = 39,
    EMOTE_ONESHOT_PARRYSHIELD          = 43,
    EMOTE_ONESHOT_READYUNARMED         = 44,
    EMOTE_ONESHOT_READY1H              = 45,
    EMOTE_ONESHOT_READYBOW             = 48,
    EMOTE_ONESHOT_SPELLPRECAST         = 50,
    EMOTE_ONESHOT_SPELLCAST            = 51,
    EMOTE_ONESHOT_BATTLEROAR           = 53,
    EMOTE_ONESHOT_SPECIALATTACK1H      = 54,
    EMOTE_ONESHOT_KICK                 = 60,
    EMOTE_ONESHOT_ATTACKTHROWN         = 61,
    EMOTE_STATE_STUN                   = 64,
    EMOTE_STATE_DEAD                   = 65,
    EMOTE_ONESHOT_SALUTE               = 66,
    EMOTE_STATE_KNEEL                  = 68,
    EMOTE_STATE_USESTANDING            = 69,
    EMOTE_ONESHOT_WAVE_NOSHEATHE       = 70,
    EMOTE_ONESHOT_CHEER_NOSHEATHE      = 71,
    EMOTE_ONESHOT_EAT_NOSHEATHE        = 92,
    EMOTE_STATE_STUN_NOSHEATHE         = 93,
    EMOTE_ONESHOT_DANCE                = 94,
    EMOTE_ONESHOT_SALUTE_NOSHEATH      = 113,
    EMOTE_STATE_USESTANDING_NOSHEATHE  = 133,
    EMOTE_ONESHOT_LAUGH_NOSHEATHE      = 153,
    EMOTE_STATE_WORK                   = 173,
    EMOTE_STATE_SPELLPRECAST           = 193,
    EMOTE_ONESHOT_READYRIFLE           = 213,
    EMOTE_STATE_READYRIFLE             = 214,
    EMOTE_STATE_WORK_MINING            = 233,
    EMOTE_STATE_WORK_CHOPWOOD          = 234,
    EMOTE_STATE_APPLAUD                = 253,
    EMOTE_ONESHOT_LIFTOFF              = 254,
    EMOTE_ONESHOT_YES                  = 273,
    EMOTE_ONESHOT_NO                   = 274,
    EMOTE_ONESHOT_TRAIN                = 275,
    EMOTE_ONESHOT_LAND                 = 293,
    EMOTE_STATE_AT_EASE                = 313,
    EMOTE_STATE_READY1H                = 333,
    EMOTE_STATE_SPELLKNEELSTART        = 353,
    EMOTE_STATE_SUBMERGED              = 373,
    EMOTE_ONESHOT_SUBMERGE             = 374,
    EMOTE_STATE_READY2H                = 375,
    EMOTE_STATE_READYBOW               = 376,
    EMOTE_ONESHOT_MOUNTSPECIAL         = 377,
    EMOTE_STATE_TALK                   = 378,
    EMOTE_STATE_FISHING                = 379,
    EMOTE_ONESHOT_FISHING              = 380,
    EMOTE_ONESHOT_LOOT                 = 381,
    EMOTE_STATE_WHIRLWIND              = 382,
    EMOTE_STATE_DROWNED                = 383,
    EMOTE_STATE_HOLD_BOW               = 384,
    EMOTE_STATE_HOLD_RIFLE             = 385,
    EMOTE_STATE_HOLD_THROWN            = 386,
    EMOTE_ONESHOT_DROWN                = 387,
    EMOTE_ONESHOT_STOMP                = 388,
    EMOTE_ONESHOT_ATTACKOFF            = 389,
    EMOTE_ONESHOT_ATTACKOFFPIERCE      = 390,
    EMOTE_STATE_ROAR                   = 391,
    EMOTE_STATE_LAUGH                  = 392,
    EMOTE_ONESHOT_CREATURE_SPECIAL     = 393,
    EMOTE_ONESHOT_JUMPLANDRUN          = 394,
    EMOTE_ONESHOT_JUMPEND              = 395,
    EMOTE_ONESHOT_TALK_NOSHEATHE       = 396,
    EMOTE_ONESHOT_POINT_NOSHEATHE      = 397,
    EMOTE_STATE_CANNIBALIZE            = 398,
    EMOTE_ONESHOT_JUMPSTART            = 399,
    EMOTE_STATE_DANCESPECIAL           = 400,
    EMOTE_ONESHOT_DANCESPECIAL         = 401,
    EMOTE_ONESHOT_CUSTOMSPELL01        = 402,
    EMOTE_ONESHOT_CUSTOMSPELL02        = 403,
    EMOTE_ONESHOT_CUSTOMSPELL03        = 404,
    EMOTE_ONESHOT_CUSTOMSPELL04        = 405,
    EMOTE_ONESHOT_CUSTOMSPELL05        = 406,
    EMOTE_ONESHOT_CUSTOMSPELL06        = 407,
    EMOTE_ONESHOT_CUSTOMSPELL07        = 408,
    EMOTE_ONESHOT_CUSTOMSPELL08        = 409,
    EMOTE_ONESHOT_CUSTOMSPELL09        = 410,
    EMOTE_ONESHOT_CUSTOMSPELL10        = 411,
    EMOTE_STATE_EXCLAIM                = 412,
    EMOTE_STATE_DANCE_CUSTOM           = 413,
    EMOTE_STATE_SIT_CHAIR_MED          = 415,
    EMOTE_STATE_CUSTOM_SPELL_01        = 416,
    EMOTE_STATE_CUSTOM_SPELL_02        = 417,
    EMOTE_STATE_EAT                    = 418,
    EMOTE_STATE_CUSTOM_SPELL_04        = 419,
    EMOTE_STATE_CUSTOM_SPELL_03        = 420,
    EMOTE_STATE_CUSTOM_SPELL_05        = 421,
    EMOTE_STATE_SPELLEFFECT_HOLD       = 422,
    EMOTE_STATE_EAT_NO_SHEATHE         = 423,
    EMOTE_STATE_MOUNT                  = 424,
    EMOTE_STATE_READY2HL               = 425,
    EMOTE_STATE_SIT_CHAIR_HIGH         = 426,
    EMOTE_STATE_FALL                   = 427,
    EMOTE_STATE_LOOT                   = 428,
    EMOTE_STATE_SUBMERGED_NEW          = 429,
    EMOTE_ONESHOT_COWER                = 430,
    EMOTE_STATE_COWER                  = 431,
    EMOTE_ONESHOT_USESTANDING          = 432,
    EMOTE_STATE_STEALTH_STAND          = 433,
    EMOTE_ONESHOT_OMNICAST_GHOUL       = 434,
    EMOTE_ONESHOT_ATTACKBOW            = 435,
    EMOTE_ONESHOT_ATTACKRIFLE          = 436,
    EMOTE_STATE_SWIM_IDLE              = 437,
    EMOTE_STATE_ATTACK_UNARMED         = 438,
    EMOTE_ONESHOT_SPELLCAST_W_SOUND    = 439,
    EMOTE_ONESHOT_DODGE                = 440,
    EMOTE_ONESHOT_PARRY1H              = 441,
    EMOTE_ONESHOT_PARRY2H              = 442,
    EMOTE_ONESHOT_PARRY2HL             = 443,
    EMOTE_STATE_FLYFALL                = 444,
    EMOTE_ONESHOT_FLYDEATH             = 445,
    EMOTE_STATE_FLY_FALL               = 446,
    EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN  = 447,
    EMOTE_ONESHOT_FLY_SIT_GROUND_UP    = 448,
    EMOTE_ONESHOT_EMERGE               = 449,
    EMOTE_ONESHOT_DRAGONSPIT           = 450,
    EMOTE_STATE_SPECIALUNARMED         = 451,
    EMOTE_ONESHOT_FLYGRAB              = 452,
    EMOTE_STATE_FLYGRABCLOSED          = 453,
    EMOTE_ONESHOT_FLYGRABTHROWN        = 454,
    EMOTE_STATE_FLY_SIT_GROUND         = 455,
    EMOTE_STATE_WALKBACKWARDS          = 456,
    EMOTE_ONESHOT_FLYTALK              = 457,
    EMOTE_ONESHOT_FLYATTACK1H          = 458,
    EMOTE_STATE_CUSTOMSPELL08          = 459,
    EMOTE_ONESHOT_FLY_DRAGONSPIT       = 460,
    EMOTE_STATE_SIT_CHAIR_LOW          = 461,
    EMOTE_ONE_SHOT_STUN                = 462,
    EMOTE_ONESHOT_SPELLCAST_OMNI       = 463,
    EMOTE_STATE_READYTHROWN            = 465,
    EMOTE_ONESHOT_WORK_CHOPWOOD        = 466,
    EMOTE_ONESHOT_WORK_MINING          = 467,
    EMOTE_STATE_SPELL_CHANNEL_OMNI     = 468,
    EMOTE_STATE_SPELL_CHANNEL_DIRECTED = 469,
    EMOTE_STAND_STATE_NONE             = 470,
    EMOTE_STATE_READYJOUST             = 471,
    EMOTE_STATE_STRANGULATE            = 472,
    EMOTE_STATE_STRANGULATE2           = 473,
    EMOTE_STATE_READYSPELLOMNI         = 474,
    EMOTE_STATE_HOLD_JOUST             = 475,
    EMOTE_ONESHOT_CRY_JP               = 476,                // Only Jaina Proudmoore
    EMOTE_ONESHOT_SPECIALUNARMED       = 477,
    EMOTE_STATE_DANCE_NOSHEATHE        = 478,
    EMOTE_ONESHOT_SNIFF                = 479,
    EMOTE_ONESHOT_DRAGONSTOMP          = 480,
    EMOTE_ONESHOT_KNOCKDOWN            = 482,
    EMOTE_STATE_READ                   = 483,
    EMOTE_ONESHOT_FLYEMOTETALK         = 485
};

enum Anim
{
    ANIM_STAND                        = 0x0,
    ANIM_DEATH                        = 0x1,
    ANIM_SPELL                        = 0x2,
    ANIM_STOP                         = 0x3,
    ANIM_WALK                         = 0x4,
    ANIM_RUN                          = 0x5,
    ANIM_DEAD                         = 0x6,
    ANIM_RISE                         = 0x7,
    ANIM_STANDWOUND                   = 0x8,
    ANIM_COMBATWOUND                  = 0x9,
    ANIM_COMBATCRITICAL               = 0xA,
    ANIM_SHUFFLELEFT                  = 0xB,
    ANIM_SHUFFLERIGHT                 = 0xC,
    ANIM_WALKBACKWARDS                = 0xD,
    ANIM_STUN                         = 0xE,
    ANIM_HANDSCLOSED                  = 0xF,
    ANIM_ATTACKUNARMED                = 0x10,
    ANIM_ATTACK1H                     = 0x11,
    ANIM_ATTACK2H                     = 0x12,
    ANIM_ATTACK2HL                    = 0x13,
    ANIM_PARRYUNARMED                 = 0x14,
    ANIM_PARRY1H                      = 0x15,
    ANIM_PARRY2H                      = 0x16,
    ANIM_PARRY2HL                     = 0x17,
    ANIM_SHIELDBLOCK                  = 0x18,
    ANIM_READYUNARMED                 = 0x19,
    ANIM_READY1H                      = 0x1A,
    ANIM_READY2H                      = 0x1B,
    ANIM_READY2HL                     = 0x1C,
    ANIM_READYBOW                     = 0x1D,
    ANIM_DODGE                        = 0x1E,
    ANIM_SPELLPRECAST                 = 0x1F,
    ANIM_SPELLCAST                    = 0x20,
    ANIM_SPELLCASTAREA                = 0x21,
    ANIM_NPCWELCOME                   = 0x22,
    ANIM_NPCGOODBYE                   = 0x23,
    ANIM_BLOCK                        = 0x24,
    ANIM_JUMPSTART                    = 0x25,
    ANIM_JUMP                         = 0x26,
    ANIM_JUMPEND                      = 0x27,
    ANIM_FALL                         = 0x28,
    ANIM_SWIMIDLE                     = 0x29,
    ANIM_SWIM                         = 0x2A,
    ANIM_SWIMLEFT                     = 0x2B,
    ANIM_SWIMRIGHT                    = 0x2C,
    ANIM_SWIMBACKWARDS                = 0x2D,
    ANIM_ATTACKBOW                    = 0x2E,
    ANIM_FIREBOW                      = 0x2F,
    ANIM_READYRIFLE                   = 0x30,
    ANIM_ATTACKRIFLE                  = 0x31,
    ANIM_LOOT                         = 0x32,
    ANIM_READYSPELLDIRECTED           = 0x33,
    ANIM_READYSPELLOMNI               = 0x34,
    ANIM_SPELLCASTDIRECTED            = 0x35,
    ANIM_SPELLCASTOMNI                = 0x36,
    ANIM_BATTLEROAR                   = 0x37,
    ANIM_READYABILITY                 = 0x38,
    ANIM_SPECIAL1H                    = 0x39,
    ANIM_SPECIAL2H                    = 0x3A,
    ANIM_SHIELDBASH                   = 0x3B,
    ANIM_EMOTETALK                    = 0x3C,
    ANIM_EMOTEEAT                     = 0x3D,
    ANIM_EMOTEWORK                    = 0x3E,
    ANIM_EMOTEUSESTANDING             = 0x3F,
    ANIM_EMOTETALKEXCLAMATION         = 0x40,
    ANIM_EMOTETALKQUESTION            = 0x41,
    ANIM_EMOTEBOW                     = 0x42,
    ANIM_EMOTEWAVE                    = 0x43,
    ANIM_EMOTECHEER                   = 0x44,
    ANIM_EMOTEDANCE                   = 0x45,
    ANIM_EMOTELAUGH                   = 0x46,
    ANIM_EMOTESLEEP                   = 0x47,
    ANIM_EMOTESITGROUND               = 0x48,
    ANIM_EMOTERUDE                    = 0x49,
    ANIM_EMOTEROAR                    = 0x4A,
    ANIM_EMOTEKNEEL                   = 0x4B,
    ANIM_EMOTEKISS                    = 0x4C,
    ANIM_EMOTECRY                     = 0x4D,
    ANIM_EMOTECHICKEN                 = 0x4E,
    ANIM_EMOTEBEG                     = 0x4F,
    ANIM_EMOTEAPPLAUD                 = 0x50,
    ANIM_EMOTESHOUT                   = 0x51,
    ANIM_EMOTEFLEX                    = 0x52,
    ANIM_EMOTESHY                     = 0x53,
    ANIM_EMOTEPOINT                   = 0x54,
    ANIM_ATTACK1HPIERCE               = 0x55,
    ANIM_ATTACK2HLOOSEPIERCE          = 0x56,
    ANIM_ATTACKOFF                    = 0x57,
    ANIM_ATTACKOFFPIERCE              = 0x58,
    ANIM_SHEATH                       = 0x59,
    ANIM_HIPSHEATH                    = 0x5A,
    ANIM_MOUNT                        = 0x5B,
    ANIM_RUNRIGHT                     = 0x5C,
    ANIM_RUNLEFT                      = 0x5D,
    ANIM_MOUNTSPECIAL                 = 0x5E,
    ANIM_KICK                         = 0x5F,
    ANIM_SITGROUNDDOWN                = 0x60,
    ANIM_SITGROUND                    = 0x61,
    ANIM_SITGROUNDUP                  = 0x62,
    ANIM_SLEEPDOWN                    = 0x63,
    ANIM_SLEEP                        = 0x64,
    ANIM_SLEEPUP                      = 0x65,
    ANIM_SITCHAIRLOW                  = 0x66,
    ANIM_SITCHAIRMED                  = 0x67,
    ANIM_SITCHAIRHIGH                 = 0x68,
    ANIM_LOADBOW                      = 0x69,
    ANIM_LOADRIFLE                    = 0x6A,
    ANIM_ATTACKTHROWN                 = 0x6B,
    ANIM_READYTHROWN                  = 0x6C,
    ANIM_HOLDBOW                      = 0x6D,
    ANIM_HOLDRIFLE                    = 0x6E,
    ANIM_HOLDTHROWN                   = 0x6F,
    ANIM_LOADTHROWN                   = 0x70,
    ANIM_EMOTESALUTE                  = 0x71,
    ANIM_KNEELSTART                   = 0x72,
    ANIM_KNEELLOOP                    = 0x73,
    ANIM_KNEELEND                     = 0x74,
    ANIM_ATTACKUNARMEDOFF             = 0x75,
    ANIM_SPECIALUNARMED               = 0x76,
    ANIM_STEALTHWALK                  = 0x77,
    ANIM_STEALTHSTAND                 = 0x78,
    ANIM_KNOCKDOWN                    = 0x79,
    ANIM_EATINGLOOP                   = 0x7A,
    ANIM_USESTANDINGLOOP              = 0x7B,
    ANIM_CHANNELCASTDIRECTED          = 0x7C,
    ANIM_CHANNELCASTOMNI              = 0x7D,
    ANIM_WHIRLWIND                    = 0x7E,
    ANIM_BIRTH                        = 0x7F,
    ANIM_USESTANDINGSTART             = 0x80,
    ANIM_USESTANDINGEND               = 0x81,
    ANIM_CREATURESPECIAL              = 0x82,
    ANIM_DROWN                        = 0x83,
    ANIM_DROWNED                      = 0x84,
    ANIM_FISHINGCAST                  = 0x85,
    ANIM_FISHINGLOOP                  = 0x86,
    ANIM_FLY                          = 0x87,
    ANIM_EMOTEWORKNOSHEATHE           = 0x88,
    ANIM_EMOTESTUNNOSHEATHE           = 0x89,
    ANIM_EMOTEUSESTANDINGNOSHEATHE    = 0x8A,
    ANIM_SPELLSLEEPDOWN               = 0x8B,
    ANIM_SPELLKNEELSTART              = 0x8C,
    ANIM_SPELLKNEELLOOP               = 0x8D,
    ANIM_SPELLKNEELEND                = 0x8E,
    ANIM_SPRINT                       = 0x8F,
    ANIM_INFLIGHT                     = 0x90,
    ANIM_SPAWN                        = 0x91,
    ANIM_CLOSE                        = 0x92,
    ANIM_CLOSED                       = 0x93,
    ANIM_OPEN                         = 0x94,
    ANIM_OPENED                       = 0x95,
    ANIM_DESTROY                      = 0x96,
    ANIM_DESTROYED                    = 0x97,
    ANIM_REBUILD                      = 0x98,
    ANIM_CUSTOM0                      = 0x99,
    ANIM_CUSTOM1                      = 0x9A,
    ANIM_CUSTOM2                      = 0x9B,
    ANIM_CUSTOM3                      = 0x9C,
    ANIM_DESPAWN                      = 0x9D,
    ANIM_HOLD                         = 0x9E,
    ANIM_DECAY                        = 0x9F,
    ANIM_BOWPULL                      = 0xA0,
    ANIM_BOWRELEASE                   = 0xA1,
    ANIM_SHIPSTART                    = 0xA2,
    ANIM_SHIPMOVING                   = 0xA3,
    ANIM_SHIPSTOP                     = 0xA4,
    ANIM_GROUPARROW                   = 0xA5,
    ANIM_ARROW                        = 0xA6,
    ANIM_CORPSEARROW                  = 0xA7,
    ANIM_GUIDEARROW                   = 0xA8,
    ANIM_SWAY                         = 0xA9,
    ANIM_DRUIDCATPOUNCE               = 0xAA,
    ANIM_DRUIDCATRIP                  = 0xAB,
    ANIM_DRUIDCATRAKE                 = 0xAC,
    ANIM_DRUIDCATRAVAGE               = 0xAD,
    ANIM_DRUIDCATCLAW                 = 0xAE,
    ANIM_DRUIDCATCOWER                = 0xAF,
    ANIM_DRUIDBEARSWIPE               = 0xB0,
    ANIM_DRUIDBEARBITE                = 0xB1,
    ANIM_DRUIDBEARMAUL                = 0xB2,
    ANIM_DRUIDBEARBASH                = 0xB3,
    ANIM_DRAGONTAIL                   = 0xB4,
    ANIM_DRAGONSTOMP                  = 0xB5,
    ANIM_DRAGONSPIT                   = 0xB6,
    ANIM_DRAGONSPITHOVER              = 0xB7,
    ANIM_DRAGONSPITFLY                = 0xB8,
    ANIM_EMOTEYES                     = 0xB9,
    ANIM_EMOTENO                      = 0xBA,
    ANIM_JUMPLANDRUN                  = 0xBB,
    ANIM_LOOTHOLD                     = 0xBC,
    ANIM_LOOTUP                       = 0xBD,
    ANIM_STANDHIGH                    = 0xBE,
    ANIM_IMPACT                       = 0xBF,
    ANIM_LIFTOFF                      = 0xC0,
    ANIM_HOVER                        = 0xC1,
    ANIM_SUCCUBUSENTICE               = 0xC2,
    ANIM_EMOTETRAIN                   = 0xC3,
    ANIM_EMOTEDEAD                    = 0xC4,
    ANIM_EMOTEDANCEONCE               = 0xC5,
    ANIM_DEFLECT                      = 0xC6,
    ANIM_EMOTEEATNOSHEATHE            = 0xC7,
    ANIM_LAND                         = 0xC8,
    ANIM_SUBMERGE                     = 0xC9,
    ANIM_SUBMERGED                    = 0xCA,
    ANIM_CANNIBALIZE                  = 0xCB,
    ANIM_ARROWBIRTH                   = 0xCC,
    ANIM_GROUPARROWBIRTH              = 0xCD,
    ANIM_CORPSEARROWBIRTH             = 0xCE,
    ANIM_GUIDEARROWBIRTH              = 0xCF,
    ANIM_EMOTETALKNOSHEATHE           = 0xD0,
    ANIM_EMOTEPOINTNOSHEATHE          = 0xD1,
    ANIM_EMOTESALUTENOSHEATHE         = 0xD2,
    ANIM_EMOTEDANCESPECIAL            = 0xD3,
    ANIM_MUTILATE                     = 0xD4,
    ANIM_CUSTOMSPELL01                = 0xD5,
    ANIM_CUSTOMSPELL02                = 0xD6,
    ANIM_CUSTOMSPELL03                = 0xD7,
    ANIM_CUSTOMSPELL04                = 0xD8,
    ANIM_CUSTOMSPELL05                = 0xD9,
    ANIM_CUSTOMSPELL06                = 0xDA,
    ANIM_CUSTOMSPELL07                = 0xDB,
    ANIM_CUSTOMSPELL08                = 0xDC,
    ANIM_CUSTOMSPELL09                = 0xDD,
    ANIM_CUSTOMSPELL10                = 0xDE,
    ANIM_STEALTHRUN                   = 0xDF,
    ANIM_EMERGE                       = 0xE0,
    ANIM_COWER                        = 0xE1,
    ANIM_GRAB                         = 0xE2,
    ANIM_GRABCLOSED                   = 0xE3,
    ANIM_GRABTHROWN                   = 0xE4,
    ANIM_FLYSTAND                     = 0xE5,
    ANIM_FLYDEATH                     = 0xE6,
    ANIM_FLYSPELL                     = 0xE7,
    ANIM_FLYSTOP                      = 0xE8,
    ANIM_FLYWALK                      = 0xE9,
    ANIM_FLYRUN                       = 0xEA,
    ANIM_FLYDEAD                      = 0xEB,
    ANIM_FLYRISE                      = 0xEC,
    ANIM_FLYSTANDWOUND                = 0xED,
    ANIM_FLYCOMBATWOUND               = 0xEE,
    ANIM_FLYCOMBATCRITICAL            = 0xEF,
    ANIM_FLYSHUFFLELEFT               = 0xF0,
    ANIM_FLYSHUFFLERIGHT              = 0xF1,
    ANIM_FLYWALKBACKWARDS             = 0xF2,
    ANIM_FLYSTUN                      = 0xF3,
    ANIM_FLYHANDSCLOSED               = 0xF4,
    ANIM_FLYATTACKUNARMED             = 0xF5,
    ANIM_FLYATTACK1H                  = 0xF6,
    ANIM_FLYATTACK2H                  = 0xF7,
    ANIM_FLYATTACK2HL                 = 0xF8,
    ANIM_FLYPARRYUNARMED              = 0xF9,
    ANIM_FLYPARRY1H                   = 0xFA,
    ANIM_FLYPARRY2H                   = 0xFB,
    ANIM_FLYPARRY2HL                  = 0xFC,
    ANIM_FLYSHIELDBLOCK               = 0xFD,
    ANIM_FLYREADYUNARMED              = 0xFE,
    ANIM_FLYREADY1H                   = 0xFF,
    ANIM_FLYREADY2H                   = 0x100,
    ANIM_FLYREADY2HL                  = 0x101,
    ANIM_FLYREADYBOW                  = 0x102,
    ANIM_FLYDODGE                     = 0x103,
    ANIM_FLYSPELLPRECAST              = 0x104,
    ANIM_FLYSPELLCAST                 = 0x105,
    ANIM_FLYSPELLCASTAREA             = 0x106,
    ANIM_FLYNPCWELCOME                = 0x107,
    ANIM_FLYNPCGOODBYE                = 0x108,
    ANIM_FLYBLOCK                     = 0x109,
    ANIM_FLYJUMPSTART                 = 0x10A,
    ANIM_FLYJUMP                      = 0x10B,
    ANIM_FLYJUMPEND                   = 0x10C,
    ANIM_FLYFALL                      = 0x10D,
    ANIM_FLYSWIMIDLE                  = 0x10E,
    ANIM_FLYSWIM                      = 0x10F,
    ANIM_FLYSWIMLEFT                  = 0x110,
    ANIM_FLYSWIMRIGHT                 = 0x111,
    ANIM_FLYSWIMBACKWARDS             = 0x112,
    ANIM_FLYATTACKBOW                 = 0x113,
    ANIM_FLYFIREBOW                   = 0x114,
    ANIM_FLYREADYRIFLE                = 0x115,
    ANIM_FLYATTACKRIFLE               = 0x116,
    ANIM_FLYLOOT                      = 0x117,
    ANIM_FLYREADYSPELLDIRECTED        = 0x118,
    ANIM_FLYREADYSPELLOMNI            = 0x119,
    ANIM_FLYSPELLCASTDIRECTED         = 0x11A,
    ANIM_FLYSPELLCASTOMNI             = 0x11B,
    ANIM_FLYBATTLEROAR                = 0x11C,
    ANIM_FLYREADYABILITY              = 0x11D,
    ANIM_FLYSPECIAL1H                 = 0x11E,
    ANIM_FLYSPECIAL2H                 = 0x11F,
    ANIM_FLYSHIELDBASH                = 0x120,
    ANIM_FLYEMOTETALK                 = 0x121,
    ANIM_FLYEMOTEEAT                  = 0x122,
    ANIM_FLYEMOTEWORK                 = 0x123,
    ANIM_FLYEMOTEUSESTANDING          = 0x124,
    ANIM_FLYEMOTETALKEXCLAMATION      = 0x125,
    ANIM_FLYEMOTETALKQUESTION         = 0x126,
    ANIM_FLYEMOTEBOW                  = 0x127,
    ANIM_FLYEMOTEWAVE                 = 0x128,
    ANIM_FLYEMOTECHEER                = 0x129,
    ANIM_FLYEMOTEDANCE                = 0x12A,
    ANIM_FLYEMOTELAUGH                = 0x12B,
    ANIM_FLYEMOTESLEEP                = 0x12C,
    ANIM_FLYEMOTESITGROUND            = 0x12D,
    ANIM_FLYEMOTERUDE                 = 0x12E,
    ANIM_FLYEMOTEROAR                 = 0x12F,
    ANIM_FLYEMOTEKNEEL                = 0x130,
    ANIM_FLYEMOTEKISS                 = 0x131,
    ANIM_FLYEMOTECRY                  = 0x132,
    ANIM_FLYEMOTECHICKEN              = 0x133,
    ANIM_FLYEMOTEBEG                  = 0x134,
    ANIM_FLYEMOTEAPPLAUD              = 0x135,
    ANIM_FLYEMOTESHOUT                = 0x136,
    ANIM_FLYEMOTEFLEX                 = 0x137,
    ANIM_FLYEMOTESHY                  = 0x138,
    ANIM_FLYEMOTEPOINT                = 0x139,
    ANIM_FLYATTACK1HPIERCE            = 0x13A,
    ANIM_FLYATTACK2HLOOSEPIERCE       = 0x13B,
    ANIM_FLYATTACKOFF                 = 0x13C,
    ANIM_FLYATTACKOFFPIERCE           = 0x13D,
    ANIM_FLYSHEATH                    = 0x13E,
    ANIM_FLYHIPSHEATH                 = 0x13F,
    ANIM_FLYMOUNT                     = 0x140,
    ANIM_FLYRUNRIGHT                  = 0x141,
    ANIM_FLYRUNLEFT                   = 0x142,
    ANIM_FLYMOUNTSPECIAL              = 0x143,
    ANIM_FLYKICK                      = 0x144,
    ANIM_FLYSITGROUNDDOWN             = 0x145,
    ANIM_FLYSITGROUND                 = 0x146,
    ANIM_FLYSITGROUNDUP               = 0x147,
    ANIM_FLYSLEEPDOWN                 = 0x148,
    ANIM_FLYSLEEP                     = 0x149,
    ANIM_FLYSLEEPUP                   = 0x14A,
    ANIM_FLYSITCHAIRLOW               = 0x14B,
    ANIM_FLYSITCHAIRMED               = 0x14C,
    ANIM_FLYSITCHAIRHIGH              = 0x14D,
    ANIM_FLYLOADBOW                   = 0x14E,
    ANIM_FLYLOADRIFLE                 = 0x14F,
    ANIM_FLYATTACKTHROWN              = 0x150,
    ANIM_FLYREADYTHROWN               = 0x151,
    ANIM_FLYHOLDBOW                   = 0x152,
    ANIM_FLYHOLDRIFLE                 = 0x153,
    ANIM_FLYHOLDTHROWN                = 0x154,
    ANIM_FLYLOADTHROWN                = 0x155,
    ANIM_FLYEMOTESALUTE               = 0x156,
    ANIM_FLYKNEELSTART                = 0x157,
    ANIM_FLYKNEELLOOP                 = 0x158,
    ANIM_FLYKNEELEND                  = 0x159,
    ANIM_FLYATTACKUNARMEDOFF          = 0x15A,
    ANIM_FLYSPECIALUNARMED            = 0x15B,
    ANIM_FLYSTEALTHWALK               = 0x15C,
    ANIM_FLYSTEALTHSTAND              = 0x15D,
    ANIM_FLYKNOCKDOWN                 = 0x15E,
    ANIM_FLYEATINGLOOP                = 0x15F,
    ANIM_FLYUSESTANDINGLOOP           = 0x160,
    ANIM_FLYCHANNELCASTDIRECTED       = 0x161,
    ANIM_FLYCHANNELCASTOMNI           = 0x162,
    ANIM_FLYWHIRLWIND                 = 0x163,
    ANIM_FLYBIRTH                     = 0x164,
    ANIM_FLYUSESTANDINGSTART          = 0x165,
    ANIM_FLYUSESTANDINGEND            = 0x166,
    ANIM_FLYCREATURESPECIAL           = 0x167,
    ANIM_FLYDROWN                     = 0x168,
    ANIM_FLYDROWNED                   = 0x169,
    ANIM_FLYFISHINGCAST               = 0x16A,
    ANIM_FLYFISHINGLOOP               = 0x16B,
    ANIM_FLYFLY                       = 0x16C,
    ANIM_FLYEMOTEWORKNOSHEATHE        = 0x16D,
    ANIM_FLYEMOTESTUNNOSHEATHE        = 0x16E,
    ANIM_FLYEMOTEUSESTANDINGNOSHEATHE = 0x16F,
    ANIM_FLYSPELLSLEEPDOWN            = 0x170,
    ANIM_FLYSPELLKNEELSTART           = 0x171,
    ANIM_FLYSPELLKNEELLOOP            = 0x172,
    ANIM_FLYSPELLKNEELEND             = 0x173,
    ANIM_FLYSPRINT                    = 0x174,
    ANIM_FLYINFLIGHT                  = 0x175,
    ANIM_FLYSPAWN                     = 0x176,
    ANIM_FLYCLOSE                     = 0x177,
    ANIM_FLYCLOSED                    = 0x178,
    ANIM_FLYOPEN                      = 0x179,
    ANIM_FLYOPENED                    = 0x17A,
    ANIM_FLYDESTROY                   = 0x17B,
    ANIM_FLYDESTROYED                 = 0x17C,
    ANIM_FLYREBUILD                   = 0x17D,
    ANIM_FLYCUSTOM0                   = 0x17E,
    ANIM_FLYCUSTOM1                   = 0x17F,
    ANIM_FLYCUSTOM2                   = 0x180,
    ANIM_FLYCUSTOM3                   = 0x181,
    ANIM_FLYDESPAWN                   = 0x182,
    ANIM_FLYHOLD                      = 0x183,
    ANIM_FLYDECAY                     = 0x184,
    ANIM_FLYBOWPULL                   = 0x185,
    ANIM_FLYBOWRELEASE                = 0x186,
    ANIM_FLYSHIPSTART                 = 0x187,
    ANIM_FLYSHIPMOVING                = 0x188,
    ANIM_FLYSHIPSTOP                  = 0x189,
    ANIM_FLYGROUPARROW                = 0x18A,
    ANIM_FLYARROW                     = 0x18B,
    ANIM_FLYCORPSEARROW               = 0x18C,
    ANIM_FLYGUIDEARROW                = 0x18D,
    ANIM_FLYSWAY                      = 0x18E,
    ANIM_FLYDRUIDCATPOUNCE            = 0x18F,
    ANIM_FLYDRUIDCATRIP               = 0x190,
    ANIM_FLYDRUIDCATRAKE              = 0x191,
    ANIM_FLYDRUIDCATRAVAGE            = 0x192,
    ANIM_FLYDRUIDCATCLAW              = 0x193,
    ANIM_FLYDRUIDCATCOWER             = 0x194,
    ANIM_FLYDRUIDBEARSWIPE            = 0x195,
    ANIM_FLYDRUIDBEARBITE             = 0x196,
    ANIM_FLYDRUIDBEARMAUL             = 0x197,
    ANIM_FLYDRUIDBEARBASH             = 0x198,
    ANIM_FLYDRAGONTAIL                = 0x199,
    ANIM_FLYDRAGONSTOMP               = 0x19A,
    ANIM_FLYDRAGONSPIT                = 0x19B,
    ANIM_FLYDRAGONSPITHOVER           = 0x19C,
    ANIM_FLYDRAGONSPITFLY             = 0x19D,
    ANIM_FLYEMOTEYES                  = 0x19E,
    ANIM_FLYEMOTENO                   = 0x19F,
    ANIM_FLYJUMPLANDRUN               = 0x1A0,
    ANIM_FLYLOOTHOLD                  = 0x1A1,
    ANIM_FLYLOOTUP                    = 0x1A2,
    ANIM_FLYSTANDHIGH                 = 0x1A3,
    ANIM_FLYIMPACT                    = 0x1A4,
    ANIM_FLYLIFTOFF                   = 0x1A5,
    ANIM_FLYHOVER                     = 0x1A6,
    ANIM_FLYSUCCUBUSENTICE            = 0x1A7,
    ANIM_FLYEMOTETRAIN                = 0x1A8,
    ANIM_FLYEMOTEDEAD                 = 0x1A9,
    ANIM_FLYEMOTEDANCEONCE            = 0x1AA,
    ANIM_FLYDEFLECT                   = 0x1AB,
    ANIM_FLYEMOTEEATNOSHEATHE         = 0x1AC,
    ANIM_FLYLAND                      = 0x1AD,
    ANIM_FLYSUBMERGE                  = 0x1AE,
    ANIM_FLYSUBMERGED                 = 0x1AF,
    ANIM_FLYCANNIBALIZE               = 0x1B0,
    ANIM_FLYARROWBIRTH                = 0x1B1,
    ANIM_FLYGROUPARROWBIRTH           = 0x1B2,
    ANIM_FLYCORPSEARROWBIRTH          = 0x1B3,
    ANIM_FLYGUIDEARROWBIRTH           = 0x1B4,
    ANIM_FLYEMOTETALKNOSHEATHE        = 0x1B5,
    ANIM_FLYEMOTEPOINTNOSHEATHE       = 0x1B6,
    ANIM_FLYEMOTESALUTENOSHEATHE      = 0x1B7,
    ANIM_FLYEMOTEDANCESPECIAL         = 0x1B8,
    ANIM_FLYMUTILATE                  = 0x1B9,
    ANIM_FLYCUSTOMSPELL01             = 0x1BA,
    ANIM_FLYCUSTOMSPELL02             = 0x1BB,
    ANIM_FLYCUSTOMSPELL03             = 0x1BC,
    ANIM_FLYCUSTOMSPELL04             = 0x1BD,
    ANIM_FLYCUSTOMSPELL05             = 0x1BE,
    ANIM_FLYCUSTOMSPELL06             = 0x1BF,
    ANIM_FLYCUSTOMSPELL07             = 0x1C0,
    ANIM_FLYCUSTOMSPELL08             = 0x1C1,
    ANIM_FLYCUSTOMSPELL09             = 0x1C2,
    ANIM_FLYCUSTOMSPELL10             = 0x1C3,
    ANIM_FLYSTEALTHRUN                = 0x1C4,
    ANIM_FLYEMERGE                    = 0x1C5,
    ANIM_FLYCOWER                     = 0x1C6,
    ANIM_FLYGRAB                      = 0x1C7,
    ANIM_FLYGRABCLOSED                = 0x1C8,
    ANIM_FLYGRABTHROWN                = 0x1C9,
    ANIM_TOFLY                        = 0x1CA,
    ANIM_TOHOVER                      = 0x1CB,
    ANIM_TOGROUND                     = 0x1CC,
    ANIM_FLYTOFLY                     = 0x1CD,
    ANIM_FLYTOHOVER                   = 0x1CE,
    ANIM_FLYTOGROUND                  = 0x1CF,
    ANIM_SETTLE                       = 0x1D0,
    ANIM_FLYSETTLE                    = 0x1D1,
    ANIM_DEATHSTART                   = 0x1D2,
    ANIM_DEATHLOOP                    = 0x1D3,
    ANIM_DEATHEND                     = 0x1D4,
    ANIM_FLYDEATHSTART                = 0x1D5,
    ANIM_FLYDEATHLOOP                 = 0x1D6,
    ANIM_FLYDEATHEND                  = 0x1D7,
    ANIM_DEATHENDHOLD                 = 0x1D8,
    ANIM_FLYDEATHENDHOLD              = 0x1D9,
    ANIM_STRANGULATE                  = 0x1DA,
    ANIM_FLYSTRANGULATE               = 0x1DB,
    ANIM_READYJOUST                   = 0x1DC,
    ANIM_LOADJOUST                    = 0x1DD,
    ANIM_HOLDJOUST                    = 0x1DE,
    ANIM_FLYREADYJOUST                = 0x1DF,
    ANIM_FLYLOADJOUST                 = 0x1E0,
    ANIM_FLYHOLDJOUST                 = 0x1E1,
    ANIM_ATTACKJOUST                  = 0x1E2,
    ANIM_FLYATTACKJOUST               = 0x1E3,
    ANIM_RECLINEDMOUNT                = 0x1E4,
    ANIM_FLYRECLINEDMOUNT             = 0x1E5,
    ANIM_TOALTERED                    = 0x1E6,
    ANIM_FROMALTERED                  = 0x1E7,
    ANIM_FLYTOALTERED                 = 0x1E8,
    ANIM_FLYFROMALTERED               = 0x1E9,
    ANIM_INSTOCKS                     = 0x1EA,
    ANIM_FLYINSTOCKS                  = 0x1EB,
    ANIM_VEHICLEGRAB                  = 0x1EC,
    ANIM_VEHICLETHROW                 = 0x1ED,
    ANIM_FLYVEHICLEGRAB               = 0x1EE,
    ANIM_FLYVEHICLETHROW              = 0x1EF,
    ANIM_TOALTEREDPOSTSWAP            = 0x1F0,
    ANIM_FROMALTEREDPOSTSWAP          = 0x1F1,
    ANIM_FLYTOALTEREDPOSTSWAP         = 0x1F2,
    ANIM_FLYFROMALTEREDPOSTSWAP       = 0x1F3,
    ANIM_RECLINEDMOUNTPASSENGER       = 0x1F4,
    ANIM_FLYRECLINEDMOUNTPASSENGER    = 0x1F5,
    ANIM_CARRY2H                      = 0x1F6,
    ANIM_CARRIED2H                    = 0x1F7,
    ANIM_FLYCARRY2H                   = 0x1F8,
    ANIM_FLYCARRIED2H                 = 0x1F9,
    ANIM_EMOTESNIFF                   = 0x1FA,
    ANIM_EMOTEFLYSNIFF                = 0x1FB,
    ANIM_ATTACKFIST1H                 = 0x1FC,
    ANIM_FLYATTACKFIST1H              = 0x1FD,
    ANIM_ATTACKFIST1HOFF              = 0x1FE,
    ANIM_FLYATTACKFIST1HOFF           = 0x1FF,
    ANIM_PARRYFIST1H                  = 0x200,
    ANIM_FLYPARRYFIST1H               = 0x201,
    ANIM_READYFIST1H                  = 0x202,
    ANIM_FLYREADYFIST1H               = 0x203,
    ANIM_SPECIALFIST1H                = 0x204,
    ANIM_FLYSPECIALFIST1H             = 0x205,
    ANIM_EMOTEREADSTART               = 0x206,
    ANIM_FLYEMOTEREADSTART            = 0x207,
    ANIM_EMOTEREADLOOP                = 0x208,
    ANIM_FLYEMOTEREADLOOP             = 0x209,
    ANIM_EMOTEREADEND                 = 0x20A,
    ANIM_FLYEMOTEREADEND              = 0x20B,
    ANIM_SWIMRUN                      = 0x20C,
    ANIM_FLYSWIMRUN                   = 0x20D,
    ANIM_SWIMWALK                     = 0x20E,
    ANIM_FLYSWIMWALK                  = 0x20F,
    ANIM_SWIMWALKBACKWARDS            = 0x210,
    ANIM_FLYSWIMWALKBACKWARDS         = 0x211,
    ANIM_SWIMSPRINT                   = 0x212,
    ANIM_FLYSWIMSPRINT                = 0x213,
    ANIM_MOUNTSWIMIDLE                = 0x214,
    ANIM_FLYMOUNTSWIMIDLE             = 0x215,
    ANIM_MOUNTSWIMBACKWARDS           = 0x216,
    ANIM_FLYMOUNTSWIMBACKWARDS        = 0x217,
    ANIM_MOUNTSWIMLEFT                = 0x218,
    ANIM_FLYMOUNTSWIMLEFT             = 0x219,
    ANIM_MOUNTSWIMRIGHT               = 0x21A,
    ANIM_FLYMOUNTSWIMRIGHT            = 0x21B,
    ANIM_MOUNTSWIMRUN                 = 0x21C,
    ANIM_FLYMOUNTSWIMRUN              = 0x21D,
    ANIM_MOUNTSWIMSPRINT              = 0x21E,
    ANIM_FLYMOUNTSWIMSPRINT           = 0x21F,
    ANIM_MOUNTSWIMWALK                = 0x220,
    ANIM_FLYMOUNTSWIMWALK             = 0x221,
    ANIM_MOUNTSWIMWALKBACKWARDS       = 0x222,
    ANIM_FLYMOUNTSWIMWALKBACKWARDS    = 0x223,
    ANIM_MOUNTFLIGHTIDLE              = 0x224,
    ANIM_FLYMOUNTFLIGHTIDLE           = 0x225,
    ANIM_MOUNTFLIGHTBACKWARDS         = 0x226,
    ANIM_FLYMOUNTFLIGHTBACKWARDS      = 0x227,
    ANIM_MOUNTFLIGHTLEFT              = 0x228,
    ANIM_FLYMOUNTFLIGHTLEFT           = 0x229,
    ANIM_MOUNTFLIGHTRIGHT             = 0x22A,
    ANIM_FLYMOUNTFLIGHTRIGHT          = 0x22B,
    ANIM_MOUNTFLIGHTRUN               = 0x22C,
    ANIM_FLYMOUNTFLIGHTRUN            = 0x22D,
    ANIM_MOUNTFLIGHTSPRINT            = 0x22E,
    ANIM_FLYMOUNTFLIGHTSPRINT         = 0x22F,
    ANIM_MOUNTFLIGHTWALK              = 0x230,
    ANIM_FLYMOUNTFLIGHTWALK           = 0x231,
    ANIM_MOUNTFLIGHTWALKBACKWARDS     = 0x232,
    ANIM_FLYMOUNTFLIGHTWALKBACKWARDS  = 0x233,
    ANIM_MOUNTFLIGHTSTART             = 0x234,
    ANIM_FLYMOUNTFLIGHTSTART          = 0x235,
    ANIM_MOUNTSWIMSTART               = 0x236,
    ANIM_FLYMOUNTSWIMSTART            = 0x237,
    ANIM_MOUNTSWIMLAND                = 0x238,
    ANIM_FLYMOUNTSWIMLAND             = 0x239,
    ANIM_MOUNTSWIMLANDRUN             = 0x23A,
    ANIM_FLYMOUNTSWIMLANDRUN          = 0x23B,
    ANIM_MOUNTFLIGHTLAND              = 0x23C,
    ANIM_FLYMOUNTFLIGHTLAND           = 0x23D,
    ANIM_MOUNTFLIGHTLANDRUN           = 0x23E,
    ANIM_FLYMOUNTFLIGHTLANDRUN        = 0x23F,
    ANIM_READYBLOWDART                = 0x240,
    ANIM_FLYREADYBLOWDART             = 0x241,
    ANIM_LOADBLOWDART                 = 0x242,
    ANIM_FLYLOADBLOWDART              = 0x243,
    ANIM_HOLDBLOWDART                 = 0x244,
    ANIM_FLYHOLDBLOWDART              = 0x245,
    ANIM_ATTACKBLOWDART               = 0x246,
    ANIM_FLYATTACKBLOWDART            = 0x247,
    ANIM_CARRIAGEMOUNT                = 0x248,
    ANIM_FLYCARRIAGEMOUNT             = 0x249,
    ANIM_CARRIAGEPASSENGERMOUNT       = 0x24A,
    ANIM_FLYCARRIAGEPASSENGERMOUNT    = 0x24B,
    ANIM_CARRIAGEMOUNTATTACK          = 0x24C,
    ANIM_FLYCARRIAGEMOUNTATTACK       = 0x24D,
    ANIM_BARTENDERSTAND               = 0x24E,
    ANIM_FLYBARTENDERSTAND            = 0x24F,
    ANIM_BARTENDERWALK                = 0x250,
    ANIM_FLYBARTENDERWALK             = 0x251,
    ANIM_BARTENDERRUN                 = 0x252,
    ANIM_FLYBARTENDERRUN              = 0x253,
    ANIM_BARTENDERSHUFFLELEFT         = 0x254,
    ANIM_FLYBARTENDERSHUFFLELEFT      = 0x255,
    ANIM_BARTENDERSHUFFLERIGHT        = 0x256,
    ANIM_FLYBARTENDERSHUFFLERIGHT     = 0x257,
    ANIM_BARTENDEREMOTETALK           = 0x258,
    ANIM_FLYBARTENDEREMOTETALK        = 0x259,
    ANIM_BARTENDEREMOTEPOINT          = 0x25A,
    ANIM_FLYBARTENDEREMOTEPOINT       = 0x25B,
    ANIM_BARMAIDSTAND                 = 0x25C,
    ANIM_FLYBARMAIDSTAND              = 0x25D,
    ANIM_BARMAIDWALK                  = 0x25E,
    ANIM_FLYBARMAIDWALK               = 0x25F,
    ANIM_BARMAIDRUN                   = 0x260,
    ANIM_FLYBARMAIDRUN                = 0x261,
    ANIM_BARMAIDSHUFFLELEFT           = 0x262,
    ANIM_FLYBARMAIDSHUFFLELEFT        = 0x263,
    ANIM_BARMAIDSHUFFLERIGHT          = 0x264,
    ANIM_FLYBARMAIDSHUFFLERIGHT       = 0x265,
    ANIM_BARMAIDEMOTETALK             = 0x266,
    ANIM_FLYBARMAIDEMOTETALK          = 0x267,
    ANIM_BARMAIDEMOTEPOINT            = 0x268,
    ANIM_FLYBARMAIDEMOTEPOINT         = 0x269,
    ANIM_MOUNTSELFIDLE                = 0x26A,
    ANIM_FLYMOUNTSELFIDLE             = 0x26B,
    ANIM_MOUNTSELFWALK                = 0x26C,
    ANIM_FLYMOUNTSELFWALK             = 0x26D,
    ANIM_MOUNTSELFRUN                 = 0x26E,
    ANIM_FLYMOUNTSELFRUN              = 0x26F,
    ANIM_MOUNTSELFSPRINT              = 0x270,
    ANIM_FLYMOUNTSELFSPRINT           = 0x271,
    ANIM_MOUNTSELFRUNLEFT             = 0x272,
    ANIM_FLYMOUNTSELFRUNLEFT          = 0x273,
    ANIM_MOUNTSELFRUNRIGHT            = 0x274,
    ANIM_FLYMOUNTSELFRUNRIGHT         = 0x275,
    ANIM_MOUNTSELFSHUFFLELEFT         = 0x276,
    ANIM_FLYMOUNTSELFSHUFFLELEFT      = 0x277,
    ANIM_MOUNTSELFSHUFFLERIGHT        = 0x278,
    ANIM_FLYMOUNTSELFSHUFFLERIGHT     = 0x279,
    ANIM_MOUNTSELFWALKBACKWARDS       = 0x27A,
    ANIM_FLYMOUNTSELFWALKBACKWARDS    = 0x27B,
    ANIM_MOUNTSELFSPECIAL             = 0x27C,
    ANIM_FLYMOUNTSELFSPECIAL          = 0x27D,
    ANIM_MOUNTSELFJUMP                = 0x27E,
    ANIM_FLYMOUNTSELFJUMP             = 0x27F,
    ANIM_MOUNTSELFJUMPSTART           = 0x280,
    ANIM_FLYMOUNTSELFJUMPSTART        = 0x281,
    ANIM_MOUNTSELFJUMPEND             = 0x282,
    ANIM_FLYMOUNTSELFJUMPEND          = 0x283,
    ANIM_MOUNTSELFJUMPLANDRUN         = 0x284,
    ANIM_FLYMOUNTSELFJUMPLANDRUN      = 0x285,
    ANIM_MOUNTSELFSTART               = 0x286,
    ANIM_FLYMOUNTSELFSTART            = 0x287,
    ANIM_MOUNTSELFFALL                = 0x288,
    ANIM_FLYMOUNTSELFFALL             = 0x289,
    ANIM_STORMSTRIKE                  = 0x28A,
    ANIM_FLYSTORMSTRIKE               = 0x28B,
    ANIM_READYJOUSTNOSHEATHE          = 0x28C,
    ANIM_FLYREADYJOUSTNOSHEATHE       = 0x28D
};

enum LockKeyType
{
    LOCK_KEY_NONE  = 0,
    LOCK_KEY_ITEM  = 1,
    LOCK_KEY_SKILL = 2
};

enum LockType
{
    LOCKTYPE_PICKLOCK              = 1,
    LOCKTYPE_HERBALISM             = 2,
    LOCKTYPE_MINING                = 3,
    LOCKTYPE_DISARM_TRAP           = 4,
    LOCKTYPE_OPEN                  = 5,
    LOCKTYPE_TREASURE              = 6,
    LOCKTYPE_CALCIFIED_ELVEN_GEMS  = 7,
    LOCKTYPE_CLOSE                 = 8,
    LOCKTYPE_ARM_TRAP              = 9,
    LOCKTYPE_QUICK_OPEN            = 10,
    LOCKTYPE_QUICK_CLOSE           = 11,
    LOCKTYPE_OPEN_TINKERING        = 12,
    LOCKTYPE_OPEN_KNEELING         = 13,
    LOCKTYPE_OPEN_ATTACKING        = 14,
    LOCKTYPE_GAHZRIDIAN            = 15,
    LOCKTYPE_BLASTING              = 16,
    LOCKTYPE_SLOW_OPEN             = 17,
    LOCKTYPE_SLOW_CLOSE            = 18,
    LOCKTYPE_FISHING               = 19,
    LOCKTYPE_INSCRIPTION           = 20,
    LOCKTYPE_OPEN_FROM_VEHICLE     = 21,
    LOCKTYPE_ARCHAEOLOGY           = 22,
    LOCKTYPE_PVP_OPEN_FAST         = 23
};

enum TrainerType                                            // this is important type for npcs!
{
    TRAINER_TYPE_CLASS             = 0,
    TRAINER_TYPE_MOUNTS            = 1,                     // on blizz it's 2
    TRAINER_TYPE_TRADESKILLS       = 2,
    TRAINER_TYPE_PETS              = 3
};

#define MAX_TRAINER_TYPE 4

enum TrainerId
{
    TRAINER_ID_WARRIOR = 0x5B,
    TRAINER_ID_MAGE    = 0x57,
};

// CreatureType.dbc
enum CreatureType
{
    CREATURE_TYPE_BEAST            = 1,
    CREATURE_TYPE_DRAGONKIN        = 2,
    CREATURE_TYPE_DEMON            = 3,
    CREATURE_TYPE_ELEMENTAL        = 4,
    CREATURE_TYPE_GIANT            = 5,
    CREATURE_TYPE_UNDEAD           = 6,
    CREATURE_TYPE_HUMANOID         = 7,
    CREATURE_TYPE_CRITTER          = 8,
    CREATURE_TYPE_MECHANICAL       = 9,
    CREATURE_TYPE_NOT_SPECIFIED    = 10,
    CREATURE_TYPE_TOTEM            = 11,
    CREATURE_TYPE_NON_COMBAT_PET   = 12,
    CREATURE_TYPE_GAS_CLOUD        = 13
};

uint32 const CREATURE_TYPEMASK_DEMON_OR_UNDEAD = (1 << (CREATURE_TYPE_DEMON-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD = (1 << (CREATURE_TYPE_HUMANOID-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_MECHANICAL_OR_ELEMENTAL = (1 << (CREATURE_TYPE_MECHANICAL-1)) | (1 << (CREATURE_TYPE_ELEMENTAL-1));

// CreatureFamily.dbc
enum CreatureFamily
{
    CREATURE_FAMILY_WOLF            = 1,
    CREATURE_FAMILY_CAT             = 2,
    CREATURE_FAMILY_SPIDER          = 3,
    CREATURE_FAMILY_BEAR            = 4,
    CREATURE_FAMILY_BOAR            = 5,
    CREATURE_FAMILY_CROCOLISK       = 6,
    CREATURE_FAMILY_CARRION_BIRD    = 7,
    CREATURE_FAMILY_CRAB            = 8,
    CREATURE_FAMILY_GORILLA         = 9,
    CREATURE_FAMILY_HORSE_CUSTOM    = 10,                    // not exist in DBC but used for horse like beasts in DB
    CREATURE_FAMILY_RAPTOR          = 11,
    CREATURE_FAMILY_TALLSTRIDER     = 12,
    CREATURE_FAMILY_FELHUNTER       = 15,
    CREATURE_FAMILY_VOIDWALKER      = 16,
    CREATURE_FAMILY_SUCCUBUS        = 17,
    CREATURE_FAMILY_DOOMGUARD       = 19,
    CREATURE_FAMILY_SCORPID         = 20,
    CREATURE_FAMILY_TURTLE          = 21,
    CREATURE_FAMILY_IMP             = 23,
    CREATURE_FAMILY_BAT             = 24,
    CREATURE_FAMILY_HYENA           = 25,
    CREATURE_FAMILY_BIRD_OF_PREY    = 26,
    CREATURE_FAMILY_WIND_SERPENT    = 27,
    CREATURE_FAMILY_REMOTE_CONTROL  = 28,
    CREATURE_FAMILY_FELGUARD        = 29,
    CREATURE_FAMILY_DRAGONHAWK      = 30,
    CREATURE_FAMILY_RAVAGER         = 31,
    CREATURE_FAMILY_WARP_STALKER    = 32,
    CREATURE_FAMILY_SPOREBAT        = 33,
    CREATURE_FAMILY_NETHER_RAY      = 34,
    CREATURE_FAMILY_SERPENT         = 35,
    CREATURE_FAMILY_MOTH            = 37,
    CREATURE_FAMILY_CHIMAERA        = 38,
    CREATURE_FAMILY_DEVILSAUR       = 39,
    CREATURE_FAMILY_GHOUL           = 40,
    CREATURE_FAMILY_SILITHID        = 41,
    CREATURE_FAMILY_WORM            = 42,
    CREATURE_FAMILY_RHINO           = 43,
    CREATURE_FAMILY_WASP            = 44,
    CREATURE_FAMILY_CORE_HOUND      = 45,
    CREATURE_FAMILY_SPIRIT_BEAST    = 46,
    CREATURE_FAMILY_WATER_ELEMENTAL = 49,
    CREATURE_FAMILY_FOX             = 50,
    CREATURE_FAMILY_MONKEY          = 51,
    CREATURE_FAMILY_DOG             = 52,
    CREATURE_FAMILY_BEETLE          = 53,
    CREATURE_FAMILY_SHALE_SPIDER    = 55,
    CREATURE_FAMILY_ZOMBIE          = 56,
    CREATURE_FAMILY_BEETLE_ZZOLD    = 57,
    CREATURE_FAMILY_SILITHID2       = 59,
    CREATURE_FAMILY_WASP2           = 66,
    CREATURE_FAMILY_HYDRA           = 68
};

enum CreatureTypeFlags
{
    CREATURE_TYPEFLAGS_TAMEABLE         = 0x000001,         // Tameable by any hunter
    CREATURE_TYPEFLAGS_GHOST            = 0x000002,         // Creature are also visible for not alive player. Allow gossip interaction if npcflag allow?
    CREATURE_TYPEFLAGS_UNK3             = 0x000004,
    CREATURE_TYPEFLAGS_UNK4             = 0x000008,
    CREATURE_TYPEFLAGS_UNK5             = 0x000010,
    CREATURE_TYPEFLAGS_UNK6             = 0x000020,
    CREATURE_TYPEFLAGS_UNK7             = 0x000040,
    CREATURE_TYPEFLAGS_DEAD_INTERACT    = 0x000080,         // Player can interact with the creature if its dead (not player dead)
    CREATURE_TYPEFLAGS_HERBLOOT         = 0x000100,         // Can be looted by herbalist
    CREATURE_TYPEFLAGS_MININGLOOT       = 0x000200,         // Can be looted by miner
    CREATURE_TYPEFLAGS_UNK11            = 0x000400,
    CREATURE_TYPEFLAGS_MOUNTED_COMBAT   = 0x000800,         // Creature can remain mounted when entering combat
    CREATURE_TYPEFLAGS_AID_PLAYERS      = 0x001000,         // ? Can aid any player in combat if in range?
    CREATURE_TYPEFLAGS_UNK14            = 0x002000,
    CREATURE_TYPEFLAGS_UNK15            = 0x004000,         // ? Possibly not in use
    CREATURE_TYPEFLAGS_ENGINEERLOOT     = 0x008000,         // Can be looted by engineer
    CREATURE_TYPEFLAGS_EXOTIC           = 0x010000,         // Can be tamed by hunter as exotic pet
    CREATURE_TYPEFLAGS_UNK18            = 0x020000,         // ? Related to vehicles/pvp?
    CREATURE_TYPEFLAGS_UNK19            = 0x040000,         // ? Related to vehicle/siege weapons?
    CREATURE_TYPEFLAGS_UNK20            = 0x080000,
    CREATURE_TYPEFLAGS_UNK21            = 0x100000,
    CREATURE_TYPEFLAGS_UNK22            = 0x200000,
    CREATURE_TYPEFLAGS_UNK23            = 0x400000,
    CREATURE_TYPEFLAGS_UNK24            = 0x800000,          // ? First seen in 3.2.2. Related to banner/backpack of creature/companion?
    CREATURE_TYPEFLAGS_UNK30            = 0x20000000,
    CREATURE_TYPEFLAGS_UNK31            = 0x40000000,
    CREATURE_TYPEFLAGS_QUEST_BOSS       = 0x80000000,       // Lua_UnitIsQuestBoss

};

enum CreatureEliteType
{
    CREATURE_ELITE_NORMAL          = 0,
    CREATURE_ELITE_ELITE           = 1,
    CREATURE_ELITE_RAREELITE       = 2,
    CREATURE_ELITE_WORLDBOSS       = 3,
    CREATURE_ELITE_RARE            = 4,
    CREATURE_UNKNOWN               = 5                      // found in 2.2.3 for 2 mobs
};

// values based at Holidays.dbc
enum HolidayIds
{
    HOLIDAY_NONE                     = 0,

    HOLIDAY_FIREWORKS_SPECTACULAR    = 62,
    HOLIDAY_FEAST_OF_WINTER_VEIL     = 141,
    HOLIDAY_NOBLEGARDEN              = 181,
    HOLIDAY_CHILDRENS_WEEK           = 201,
    HOLIDAY_CALL_TO_ARMS_AV          = 283,
    HOLIDAY_CALL_TO_ARMS_WS          = 284,
    HOLIDAY_CALL_TO_ARMS_AB          = 285,
    HOLIDAY_FISHING_EXTRAVAGANZA     = 301,
    HOLIDAY_HARVEST_FESTIVAL         = 321,
    HOLIDAY_HALLOWS_END              = 324,
    HOLIDAY_LUNAR_FESTIVAL           = 327,
    HOLIDAY_LOVE_IS_IN_THE_AIR       = 335,
    HOLIDAY_FIRE_FESTIVAL            = 341,
    HOLIDAY_CALL_TO_ARMS_EY          = 353,
    HOLIDAY_BREWFEST                 = 372,
    HOLIDAY_DARKMOON_FAIRE_ELWYNN    = 374,
    HOLIDAY_DARKMOON_FAIRE_THUNDER   = 375,
    HOLIDAY_DARKMOON_FAIRE_SHATTRATH = 376,
    HOLIDAY_PIRATES_DAY              = 398,
    HOLIDAY_CALL_TO_ARMS_SA          = 400,
    HOLIDAY_PILGRIMS_BOUNTY          = 404,
    HOLIDAY_WOTLK_LAUNCH             = 406,
    HOLIDAY_DAY_OF_DEAD              = 409,
    HOLIDAY_CALL_TO_ARMS_IC          = 420,
    HOLIDAY_LOVE_IN_THE_AIR          = 423,
    HOLIDAY_KALUAK_FISHIN_DERBY      = 424,
    HOLIDAY_CALL_TO_ARMS_BG          = 435,                 // Call to Arms: The Battle for Gilneas
    HOLIDAY_CALL_TO_ARMS_TP          = 436,                 // Call to Arms: Twin Peaks
    HOLIDAY_10_V_10                  = 441,                 // Rated BG: 10v10
    HOLIDAY_15_V_15                  = 442,                 // Rated BG: 15v15
    HOLIDAY_25_V_25                  = 443,                 // Rated BG: 25v25
    HOLIDAY_WOWS_7TH_ANNIVERSARY     = 467
};

// values based at QuestInfo.dbc
enum QuestTypes
{
    QUEST_TYPE_ELITE               = 1,
    QUEST_TYPE_LIFE                = 21,
    QUEST_TYPE_PVP                 = 41,
    QUEST_TYPE_RAID                = 62,
    QUEST_TYPE_DUNGEON             = 81,
    QUEST_TYPE_WORLD_EVENT         = 82,
    QUEST_TYPE_LEGENDARY           = 83,
    QUEST_TYPE_ESCORT              = 84,
    QUEST_TYPE_HEROIC              = 85,
    QUEST_TYPE_RAID_10             = 88,
    QUEST_TYPE_RAID_25             = 89
};

// values based at QuestSort.dbc
enum QuestSort
{
    QUEST_SORT_EPIC                = 1,
    QUEST_SORT_WAILING_CAVERNS_OLD = 21,
    QUEST_SORT_SEASONAL            = 22,
    QUEST_SORT_UNDERCITY_OLD       = 23,
    QUEST_SORT_HERBALISM           = 24,
    QUEST_SORT_BATTLEGROUNDS       = 25,
    QUEST_SORT_ULDAMN_OLD          = 41,
    QUEST_SORT_WARLOCK             = 61,
    QUEST_SORT_WARRIOR             = 81,
    QUEST_SORT_SHAMAN              = 82,
    QUEST_SORT_FISHING             = 101,
    QUEST_SORT_BLACKSMITHING       = 121,
    QUEST_SORT_PALADIN             = 141,
    QUEST_SORT_MAGE                = 161,
    QUEST_SORT_ROGUE               = 162,
    QUEST_SORT_ALCHEMY             = 181,
    QUEST_SORT_LEATHERWORKING      = 182,
    QUEST_SORT_ENGINERING          = 201,
    QUEST_SORT_TREASURE_MAP        = 221,
    QUEST_SORT_SUNKEN_TEMPLE_OLD   = 241,
    QUEST_SORT_HUNTER              = 261,
    QUEST_SORT_PRIEST              = 262,
    QUEST_SORT_DRUID               = 263,
    QUEST_SORT_TAILORING           = 264,
    QUEST_SORT_SPECIAL             = 284,
    QUEST_SORT_COOKING             = 304,
    QUEST_SORT_FIRST_AID           = 324,
    QUEST_SORT_LEGENDARY           = 344,
    QUEST_SORT_DARKMOON_FAIRE      = 364,
    QUEST_SORT_AHN_QIRAJ_WAR       = 365,
    QUEST_SORT_LUNAR_FESTIVAL      = 366,
    QUEST_SORT_REPUTATION          = 367,
    QUEST_SORT_INVASION            = 368,
    QUEST_SORT_MIDSUMMER           = 369,
    QUEST_SORT_BREWFEST            = 370,
    QUEST_SORT_INSCRIPTION         = 371,
    QUEST_SORT_DEATH_KNIGHT        = 372,
    QUEST_SORT_JEWELCRAFTING       = 373,
    QUEST_SORT_NOBLEGARDEN         = 374,
    QUEST_SORT_PILGRIMS_BOUNTY     = 375,
    QUEST_SORT_LOVE_IS_IN_THE_AIR  = 376,
    QUEST_SORT_ARCHAEOLOGY         = 377,
    QUEST_SORT_CHILDRENS_WEEK      = 378,
    QUEST_SORT_FIRELANDS_INVASION  = 379,
    QUEST_SORT_THE_ZANDALARI       = 380,
    QUEST_SORT_ELEMENTAL_BONDS     = 381
};

inline uint8 ClassByQuestSort(int32 QuestSort)
{
    switch(QuestSort)
    {
        case QUEST_SORT_WARLOCK:        return CLASS_WARLOCK;
        case QUEST_SORT_WARRIOR:        return CLASS_WARRIOR;
        case QUEST_SORT_SHAMAN:         return CLASS_SHAMAN;
        case QUEST_SORT_PALADIN:        return CLASS_PALADIN;
        case QUEST_SORT_MAGE:           return CLASS_MAGE;
        case QUEST_SORT_ROGUE:          return CLASS_ROGUE;
        case QUEST_SORT_HUNTER:         return CLASS_HUNTER;
        case QUEST_SORT_PRIEST:         return CLASS_PRIEST;
        case QUEST_SORT_DRUID:          return CLASS_DRUID;
        case QUEST_SORT_DEATH_KNIGHT:   return CLASS_DEATH_KNIGHT;
    }
    return 0;
}

enum SkillType
{
    SKILL_NONE                     = 0,

    SKILL_FROST                    = 6,
    SKILL_FIRE                     = 8,
    SKILL_ARMS                     = 26,
    SKILL_COMBAT                   = 38,
    SKILL_SUBTLETY                 = 39,
    SKILL_SWORDS                   = 43,
    SKILL_AXES                     = 44,
    SKILL_BOWS                     = 45,
    SKILL_GUNS                     = 46,
    SKILL_BEAST_MASTERY            = 50,
    SKILL_SURVIVAL                 = 51,
    SKILL_MACES                    = 54,
    SKILL_2H_SWORDS                = 55,
    SKILL_HOLY                     = 56,
    SKILL_SHADOW                   = 78,
    SKILL_DEFENSE                  = 95,
    SKILL_LANG_COMMON              = 98,
    SKILL_RACIAL_DWARVEN           = 101,
    SKILL_LANG_ORCISH              = 109,
    SKILL_LANG_DWARVEN             = 111,
    SKILL_LANG_DARNASSIAN          = 113,
    SKILL_LANG_TAURAHE             = 115,
    SKILL_DUAL_WIELD               = 118,
    SKILL_RACIAL_TAUREN            = 124,
    SKILL_ORC_RACIAL               = 125,
    SKILL_RACIAL_NIGHT_ELF         = 126,
    SKILL_FIRST_AID                = 129,
    SKILL_FERAL_COMBAT             = 134,
    SKILL_STAVES                   = 136,
    SKILL_LANG_THALASSIAN          = 137,
    SKILL_LANG_DRACONIC            = 138,
    SKILL_LANG_DEMON_TONGUE        = 139,
    SKILL_LANG_TITAN               = 140,
    SKILL_LANG_OLD_TONGUE          = 141,
    SKILL_SURVIVAL2                = 142,
    SKILL_RIDING_HORSE             = 148,
    SKILL_RIDING_WOLF              = 149,
    SKILL_RIDING_RAM               = 152,
    SKILL_RIDING_TIGER             = 150,
    SKILL_SWIMING                  = 155,
    SKILL_2H_MACES                 = 160,
    SKILL_UNARMED                  = 162,
    SKILL_MARKSMANSHIP             = 163,
    SKILL_BLACKSMITHING            = 164,
    SKILL_LEATHERWORKING           = 165,
    SKILL_ALCHEMY                  = 171,
    SKILL_2H_AXES                  = 172,
    SKILL_DAGGERS                  = 173,
    SKILL_THROWN                   = 176,
    SKILL_HERBALISM                = 182,
    SKILL_GENERIC_DND              = 183,
    SKILL_RETRIBUTION              = 184,
    SKILL_COOKING                  = 185,
    SKILL_MINING                   = 186,
    SKILL_PET_IMP                  = 188,
    SKILL_PET_FELHUNTER            = 189,
    SKILL_TAILORING                = 197,
    SKILL_ENGINERING               = 202,
    SKILL_PET_SPIDER               = 203,
    SKILL_PET_VOIDWALKER           = 204,
    SKILL_PET_SUCCUBUS             = 205,
    SKILL_PET_INFERNAL             = 206,
    SKILL_PET_DOOMGUARD            = 207,
    SKILL_PET_WOLF                 = 208,
    SKILL_PET_CAT                  = 209,
    SKILL_PET_BEAR                 = 210,
    SKILL_PET_BOAR                 = 211,
    SKILL_PET_CROCILISK            = 212,
    SKILL_PET_CARRION_BIRD         = 213,
    SKILL_PET_CRAB                 = 214,
    SKILL_PET_GORILLA              = 215,
    SKILL_PET_RAPTOR               = 217,
    SKILL_PET_TALLSTRIDER          = 218,
    SKILL_RACIAL_UNDED             = 220,
    SKILL_CROSSBOWS                = 226,
    SKILL_WANDS                    = 228,
    SKILL_POLEARMS                 = 229,
    SKILL_PET_SCORPID              = 236,
    SKILL_ARCANE                   = 237,
    SKILL_PET_TURTLE               = 251,
    SKILL_ASSASSINATION            = 253,
    SKILL_FURY                     = 256,
    SKILL_PROTECTION               = 257,
    SKILL_PROTECTION2              = 267,
    SKILL_PET_TALENTS              = 270,
    SKILL_PLATE_MAIL               = 293,
    SKILL_LANG_GNOMISH             = 313,
    SKILL_LANG_TROLL               = 315,
    SKILL_ENCHANTING               = 333,
    SKILL_DEMONOLOGY               = 354,
    SKILL_AFFLICTION               = 355,
    SKILL_FISHING                  = 356,
    SKILL_ENHANCEMENT              = 373,
    SKILL_RESTORATION              = 374,
    SKILL_ELEMENTAL_COMBAT         = 375,
    SKILL_SKINNING                 = 393,
    SKILL_MAIL                     = 413,
    SKILL_LEATHER                  = 414,
    SKILL_CLOTH                    = 415,
    SKILL_SHIELD                   = 433,
    SKILL_FIST_WEAPONS             = 473,
    SKILL_RIDING_RAPTOR            = 533,
    SKILL_RIDING_MECHANOSTRIDER    = 553,
    SKILL_RIDING_UNDEAD_HORSE      = 554,
    SKILL_RESTORATION2             = 573,
    SKILL_BALANCE                  = 574,
    SKILL_DESTRUCTION              = 593,
    SKILL_HOLY2                    = 594,
    SKILL_DISCIPLINE               = 613,
    SKILL_LOCKPICKING              = 633,
    SKILL_PET_BAT                  = 653,
    SKILL_PET_HYENA                = 654,
    SKILL_PET_BIRD_OF_PREY         = 655,
    SKILL_PET_WIND_SERPENT         = 656,
    SKILL_LANG_GUTTERSPEAK         = 673,
    SKILL_RIDING_KODO              = 713,
    SKILL_RACIAL_TROLL             = 733,
    SKILL_RACIAL_GNOME             = 753,
    SKILL_RACIAL_HUMAN             = 754,
    SKILL_JEWELCRAFTING            = 755,
    SKILL_RACIAL_BLOODELF          = 756,
    SKILL_PET_EVENT_RC             = 758,
    SKILL_LANG_DRAENEI             = 759,
    SKILL_RACIAL_DRAENEI           = 760,
    SKILL_PET_FELGUARD             = 761,
    SKILL_RIDING                   = 762,
    SKILL_PET_DRAGONHAWK           = 763,
    SKILL_PET_NETHER_RAY           = 764,
    SKILL_PET_SPOREBAT             = 765,
    SKILL_PET_WARP_STALKER         = 766,
    SKILL_PET_RAVAGER              = 767,
    SKILL_PET_SERPENT              = 768,
    SKILL_INTERNAL                 = 769,
    SKILL_DK_BLOOD                 = 770,
    SKILL_DK_FROST                 = 771,
    SKILL_DK_UNHOLY                = 772,
    SKILL_INSCRIPTION              = 773,
    SKILL_PET_MOTH                 = 775,
    SKILL_RUNEFORGING              = 776,
    SKILL_MOUNTS                   = 777,
    SKILL_COMPANIONS               = 778,
    SKILL_PET_EXOTIC_CHIMAERA      = 780,
    SKILL_PET_EXOTIC_DEVILSAUR     = 781,
    SKILL_PET_GHOUL                = 782,
    SKILL_PET_EXOTIC_SILITHID      = 783,
    SKILL_PET_EXOTIC_WORM          = 784,
    SKILL_PET_WASP                 = 785,
    SKILL_PET_EXOTIC_RHINO         = 786,
    SKILL_PET_EXOTIC_CORE_HOUND    = 787,
    SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788,
    SKILL_RACIAL_WORGEN            = 789,
    SKILL_RACIAL_GOBLIN            = 790,
    SKILL_LANG_WORGEN              = 791,
    SKILL_LANG_GOBLIN              = 792,
    SKILL_ARCHAEOLOGY              = 794,
    SKILL_GENERAL_HUNTER           = 795,
    SKILL_GENERAL_DEATHKNIGHT      = 796,
    SKILL_GENERAL_ROGUE            = 797,
    SKILL_GENERAL_DRUID            = 798,
    SKILL_GENERAL_MAGE             = 799,
    SKILL_GENERAL_PALADIN          = 800,
    SKILL_GENERAL_SHAMAN           = 801,
    SKILL_GENERAL_WARLOCK          = 802,
    SKILL_GENERAL_WARRIOR          = 803,
    SKILL_GENERAL_PRIEST           = 804,
    SKILL_PET_WATER_ELEMENTAL      = 805,
    SKILL_PET_FOX                  = 808,
    SKILL_GLYPHS_ALL               = 810,
    SKILL_PET_DOG                  = 811,
    SKILL_MONKEY                   = 815,
    SKILL_SHALE_SPIDER             = 817,
    SKILL_BEETLE                   = 818,
    SKILL_GUILD_PERKS_ALL          = 821,
    SKILL_HYDRA                    = 824
};

#define MAX_SKILL_TYPE               825

inline SkillType SkillByLockType(LockType locktype)
{
    switch(locktype)
    {
    case LOCKTYPE_PICKLOCK:
        return SKILL_LOCKPICKING;
    case LOCKTYPE_HERBALISM:
        return SKILL_HERBALISM;
    case LOCKTYPE_MINING:
        return SKILL_MINING;
    case LOCKTYPE_FISHING:
        return SKILL_FISHING;
    case LOCKTYPE_INSCRIPTION:
        return SKILL_INSCRIPTION;
    default: break;
    }
    return SKILL_NONE;
}

inline uint32 SkillByQuestSort(int32 QuestSort)
{
    switch(QuestSort)
    {
    case QUEST_SORT_HERBALISM:
        return SKILL_HERBALISM;
    case QUEST_SORT_FISHING:
        return SKILL_FISHING;
    case QUEST_SORT_BLACKSMITHING:
        return SKILL_BLACKSMITHING;
    case QUEST_SORT_ALCHEMY:
        return SKILL_ALCHEMY;
    case QUEST_SORT_LEATHERWORKING:
        return SKILL_LEATHERWORKING;
    case QUEST_SORT_ENGINERING:
        return SKILL_ENGINERING;
    case QUEST_SORT_TAILORING:
        return SKILL_TAILORING;
    case QUEST_SORT_COOKING:
        return SKILL_COOKING;
    case QUEST_SORT_FIRST_AID:
        return SKILL_FIRST_AID;
    case QUEST_SORT_JEWELCRAFTING:
        return SKILL_JEWELCRAFTING;
    case QUEST_SORT_INSCRIPTION:
        return SKILL_INSCRIPTION;
    }
    return 0;
}

enum SkillCategory
{
    SKILL_CATEGORY_ATTRIBUTES    = 5,
    SKILL_CATEGORY_WEAPON        = 6,
    SKILL_CATEGORY_CLASS         = 7,
    SKILL_CATEGORY_ARMOR         = 8,
    SKILL_CATEGORY_SECONDARY     = 9,                       // secondary professions
    SKILL_CATEGORY_LANGUAGES     = 10,
    SKILL_CATEGORY_PROFESSION    = 11,                      // primary professions
    SKILL_CATEGORY_GENERIC       = 12
};

enum TotemCategory
{
    TC_SKINNING_SKIFE_OLD          = 1,
    TC_EARTH_TOTEM                 = 2,
    TC_AIR_TOTEM                   = 3,
    TC_FIRE_TOTEM                  = 4,
    TC_WATER_TOTEM                 = 5,
    TC_COPPER_ROD                  = 6,
    TC_SILVER_ROD                  = 7,
    TC_GOLDEN_ROD                  = 8,
    TC_TRUESILVER_ROD              = 9,
    TC_ARCANITE_ROD                = 10,
    TC_MINING_PICK_OLD             = 11,
    TC_PHILOSOPHERS_STONE          = 12,
    TC_BLACKSMITH_HAMMER_OLD       = 13,
    TC_ARCLIGHT_SPANNER            = 14,
    TC_GYROMATIC_MA                = 15,
    TC_MASTER_TOTEM                = 21,
    TC_FEL_IRON_ROD                = 41,
    TC_ADAMANTITE_ROD              = 62,
    TC_ETERNIUM_ROD                = 63,
    TC_HOLLOW_QUILL                = 81,
    TC_RUNED_AZURITE_ROD           = 101,
    TC_VIRTUOSO_INKING_SET         = 121,
    TC_DRUMS                       = 141,
    TC_GNOMISH_ARMY_KNIFE          = 161,
    TC_BLACKSMITH_HAMMER           = 162,
    TC_MINING_PICK                 = 165,
    TC_SKINNING_KNIFE              = 166,
    TC_HAMMER_PICK                 = 167,
    TC_BLADED_PICKAXE              = 168,
    TC_FLINT_AND_TINDER            = 169,
    TC_RUNED_COBALT_ROD            = 189,
    TC_RUNED_TITANIUM_ROD          = 190,
    TC_RUNED_ELEMENTIUM_ROD        = 209,
    TC_HIGH_POWERED_BOLT_GUN       = 210
};

enum UnitDynFlags
{
    UNIT_DYNFLAG_NONE                       = 0x0000,
    UNIT_DYNFLAG_LOOTABLE                   = 0x0001,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0002,
    UNIT_DYNFLAG_TAPPED                     = 0x0004,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0008,       // Lua_UnitIsTappedByPlayer
    UNIT_DYNFLAG_SPECIALINFO                = 0x0010,
    UNIT_DYNFLAG_DEAD                       = 0x0020,
    UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0040,
    UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0080        // Lua_UnitIsTappedByAllThreatList
};

enum CorpseDynFlags
{
    CORPSE_DYNFLAG_LOOTABLE        = 0x0001
};

enum WeatherType
{
    WEATHER_TYPE_FINE       = 0,
    WEATHER_TYPE_RAIN       = 1,
    WEATHER_TYPE_SNOW       = 2,
    WEATHER_TYPE_STORM      = 3,
    WEATHER_TYPE_THUNDERS   = 86,
    WEATHER_TYPE_BLACKRAIN  = 90
};

#define MAX_WEATHER_TYPE 4

enum ChatMsg
{
    CHAT_MSG_ADDON                  = 0xFFFFFFFF,
    CHAT_MSG_SYSTEM                 = 0x00,
    CHAT_MSG_SAY                    = 0x01,
    CHAT_MSG_PARTY                  = 0x02,
    CHAT_MSG_RAID                   = 0x03,
    CHAT_MSG_GUILD                  = 0x04,
    CHAT_MSG_OFFICER                = 0x05,
    CHAT_MSG_YELL                   = 0x06,
    CHAT_MSG_WHISPER                = 0x07,
    CHAT_MSG_WHISPER_FOREIGN        = 0x08,
    CHAT_MSG_WHISPER_INFORM         = 0x09,
    CHAT_MSG_EMOTE                  = 0x0A,
    CHAT_MSG_TEXT_EMOTE             = 0x0B,
    CHAT_MSG_MONSTER_SAY            = 0x0C,
    CHAT_MSG_MONSTER_PARTY          = 0x0D,
    CHAT_MSG_MONSTER_YELL           = 0x0E,
    CHAT_MSG_MONSTER_WHISPER        = 0x0F,
    CHAT_MSG_MONSTER_EMOTE          = 0x10,
    CHAT_MSG_CHANNEL                = 0x11,
    CHAT_MSG_CHANNEL_JOIN           = 0x12,
    CHAT_MSG_CHANNEL_LEAVE          = 0x13,
    CHAT_MSG_CHANNEL_LIST           = 0x14,
    CHAT_MSG_CHANNEL_NOTICE         = 0x15,
    CHAT_MSG_CHANNEL_NOTICE_USER    = 0x16,
    CHAT_MSG_AFK                    = 0x17,
    CHAT_MSG_DND                    = 0x18,
    CHAT_MSG_IGNORED                = 0x19,
    CHAT_MSG_SKILL                  = 0x1A,
    CHAT_MSG_LOOT                   = 0x1B,
    CHAT_MSG_MONEY                  = 0x1C,
    CHAT_MSG_OPENING                = 0x1D,
    CHAT_MSG_TRADESKILLS            = 0x1E,
    CHAT_MSG_PET_INFO               = 0x1F,
    CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
    CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
    CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
    CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
    CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x24,
    CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x25,
    CHAT_MSG_BG_SYSTEM_HORDE        = 0x26,
    CHAT_MSG_RAID_LEADER            = 0x27,
    CHAT_MSG_RAID_WARNING           = 0x28,
    CHAT_MSG_RAID_BOSS_EMOTE        = 0x29,
    CHAT_MSG_RAID_BOSS_WHISPER      = 0x2A,
    CHAT_MSG_FILTERED               = 0x2B,
    CHAT_MSG_BATTLEGROUND           = 0x2C,
    CHAT_MSG_BATTLEGROUND_LEADER    = 0x2D,
    CHAT_MSG_RESTRICTED             = 0x2E,
    CHAT_MSG_BATTLENET              = 0x2F,
    CHAT_MSG_ACHIEVEMENT            = 0x30,
    CHAT_MSG_GUILD_ACHIEVEMENT      = 0x31,
    CHAT_MSG_ARENA_POINTS           = 0x32,
    CHAT_MSG_PARTY_LEADER           = 0x33,
    CHAT_MSG_UNK52                  = 0x34,     // 4.0.1
    CHAT_MSG_BN_WISPER              = 0x35,     // 4.0.1
    CHAT_MSG_BN_WISPER_INFORM       = 0x36,     // 4.0.1
    CHAT_MSG_BN_CONVERSATION        = 0x37      // 4.0.1
};

#define MAX_CHAT_MSG_TYPE 0x34

enum ChatLinkColors
{
    CHAT_LINK_COLOR_TRADE       = 0xffffd000,   // orange
    CHAT_LINK_COLOR_TALENT      = 0xff4e96f7,   // blue
    CHAT_LINK_COLOR_SPELL       = 0xff71d5ff,   // bright blue
    CHAT_LINK_COLOR_ENCHANT     = 0xffffd000,   // orange
    CHAT_LINK_COLOR_ACHIEVEMENT = 0xffffff00,
    CHAT_LINK_COLOR_GLYPH       = 0xff66bbff
};

// Values from ItemPetFood (power of (value-1) used for compare with CreatureFamilyEntry.petDietMask
enum PetDiet
{
    PET_DIET_MEAT     = 1,
    PET_DIET_FISH     = 2,
    PET_DIET_CHEESE   = 3,
    PET_DIET_BREAD    = 4,
    PET_DIET_FUNGAS   = 5,
    PET_DIET_FRUIT    = 6,
    PET_DIET_RAW_MEAT = 7,
    PET_DIET_RAW_FISH = 8
};

#define MAX_PET_DIET 9

#define CHAIN_SPELL_JUMP_RADIUS 10

#define GUILD_BANKLOG_MAX_RECORDS   25
#define GUILD_EVENTLOG_MAX_RECORDS  100

enum AiReaction
{
    AI_REACTION_ALERT    = 0,                               // pre-aggro (used in client packet handler)
    AI_REACTION_FRIENDLY = 1,                               // (NOT used in client packet handler)
    AI_REACTION_HOSTILE  = 2,                               // sent on every attack, triggers aggro sound (used in client packet handler)
    AI_REACTION_AFRAID   = 3,                               // seen for polymorph (when AI not in control of self?) (NOT used in client packet handler)
    AI_REACTION_DESTROY  = 4,                               // used on object destroy (NOT used in client packet handler)
};

// Diminishing Returns Types
enum DiminishingReturnsType
{
    DRTYPE_NONE         = 0,                                // this spell is not diminished, but may have limited it's duration to 10s
    DRTYPE_PLAYER       = 1,                                // this spell is diminished only when applied on players
    DRTYPE_ALL          = 2                                 // this spell is diminished in every case
};

// Diminishing Return Groups
enum DiminishingGroup
{
    DIMINISHING_NONE                = 0,
    DIMINISHING_BANISH              = 1,
    DIMINISHING_CHARGE              = 2,
    DIMINISHING_OPENING_STUN        = 3, // Cheap Shot and Pounce
    DIMINISHING_CONTROLLED_STUN     = 4,
    DIMINISHING_CONTROLLED_ROOT     = 5,
    DIMINISHING_CYCLONE             = 6,
    DIMINISHING_DISARM              = 7,
    DIMINISHING_DISORIENT           = 8, // Several spells where name cant be generalized.
    DIMINISHING_ENTRAPMENT          = 9,
    DIMINISHING_FEAR                = 10,
    DIMINISHING_HORROR              = 11,
    DIMINISHING_MIND_CONTROL        = 12,
    DIMINISHING_ROOT                = 13,
    DIMINISHING_STUN                = 14,
    DIMINISHING_SCATTER_SHOT        = 15,
    DIMINISHING_SILENCE             = 16,
    DIMINISHING_SLEEP               = 17,
    DIMINISHING_TAUNT               = 18,
    DIMINISHING_LIMITONLY           = 19
};

enum SummonCategory
{
    SUMMON_CATEGORY_WILD        = 0,
    SUMMON_CATEGORY_ALLY        = 1,
    SUMMON_CATEGORY_PET         = 2,
    SUMMON_CATEGORY_PUPPET      = 3,
    SUMMON_CATEGORY_VEHICLE     = 4,
    SUMMON_CATEGORY_UNK         = 5, // as of patch 3.3.5a only Bone Spike in Icecrown Citadel
                                     // uses this category
};

enum SummonType
{
    SUMMON_TYPE_NONE        = 0,
    SUMMON_TYPE_PET         = 1,
    SUMMON_TYPE_GUARDIAN    = 2,
    SUMMON_TYPE_MINION      = 3,
    SUMMON_TYPE_TOTEM       = 4,
    SUMMON_TYPE_MINIPET     = 5,
    SUMMON_TYPE_GUARDIAN2   = 6,
    SUMMON_TYPE_WILD2       = 7,
    SUMMON_TYPE_WILD3       = 8,
    SUMMON_TYPE_VEHICLE     = 9,
    SUMMON_TYPE_VEHICLE2    = 10,
    SUMMON_TYPE_OBJECT      = 11,
};

enum EventId
{
    EVENT_SPELLCLICK        = 1001,
    EVENT_FALL_GROUND       = 1002,
    EVENT_CHARGE            = 1003,
};

enum ResponseCodes
{
    RESPONSE_SUCCESS                                       = 0x00,
    RESPONSE_FAILURE                                       = 0x01,
    RESPONSE_CANCELLED                                     = 0x02,
    RESPONSE_DISCONNECTED                                  = 0x03,
    RESPONSE_FAILED_TO_CONNECT                             = 0x04,
    RESPONSE_CONNECTED                                     = 0x05,
    RESPONSE_VERSION_MISMATCH                              = 0x06,

    CSTATUS_CONNECTING                                     = 0x07,
    CSTATUS_NEGOTIATING_SECURITY                           = 0x08,
    CSTATUS_NEGOTIATION_COMPLETE                           = 0x09,
    CSTATUS_NEGOTIATION_FAILED                             = 0x0A,
    CSTATUS_AUTHENTICATING                                 = 0x0B,

    AUTH_OK                                                = 0x0C,
    AUTH_FAILED                                            = 0x0D,
    AUTH_REJECT                                            = 0x0E,
    AUTH_BAD_SERVER_PROOF                                  = 0x0F,
    AUTH_UNAVAILABLE                                       = 0x10,
    AUTH_SYSTEM_ERROR                                      = 0x11,
    AUTH_BILLING_ERROR                                     = 0x12,
    AUTH_BILLING_EXPIRED                                   = 0x13,
    AUTH_VERSION_MISMATCH                                  = 0x14,
    AUTH_UNKNOWN_ACCOUNT                                   = 0x15,
    AUTH_INCORRECT_PASSWORD                                = 0x16,
    AUTH_SESSION_EXPIRED                                   = 0x17,
    AUTH_SERVER_SHUTTING_DOWN                              = 0x18,
    AUTH_ALREADY_LOGGING_IN                                = 0x19,
    AUTH_LOGIN_SERVER_NOT_FOUND                            = 0x1A,
    AUTH_WAIT_QUEUE                                        = 0x1B,
    AUTH_BANNED                                            = 0x1C,
    AUTH_ALREADY_ONLINE                                    = 0x1D,
    AUTH_NO_TIME                                           = 0x1E,
    AUTH_DB_BUSY                                           = 0x1F,
    AUTH_SUSPENDED                                         = 0x20,
    AUTH_PARENTAL_CONTROL                                  = 0x21,
    AUTH_LOCKED_ENFORCED                                   = 0x22,

    REALM_LIST_IN_PROGRESS                                 = 0x23,
    REALM_LIST_SUCCESS                                     = 0x24,
    REALM_LIST_FAILED                                      = 0x25,
    REALM_LIST_INVALID                                     = 0x26,
    REALM_LIST_REALM_NOT_FOUND                             = 0x27,

    ACCOUNT_CREATE_IN_PROGRESS                             = 0x28,
    ACCOUNT_CREATE_SUCCESS                                 = 0x29,
    ACCOUNT_CREATE_FAILED                                  = 0x2A,

    CHAR_LIST_RETRIEVING                                   = 0x2B,
    CHAR_LIST_RETRIEVED                                    = 0x2C,
    CHAR_LIST_FAILED                                       = 0x2D,

    CHAR_CREATE_IN_PROGRESS                                = 0x2E,
    CHAR_CREATE_SUCCESS                                    = 0x2F,
    CHAR_CREATE_ERROR                                      = 0x30,
    CHAR_CREATE_FAILED                                     = 0x31,
    CHAR_CREATE_NAME_IN_USE                                = 0x32,
    CHAR_CREATE_DISABLED                                   = 0x33,
    CHAR_CREATE_PVP_TEAMS_VIOLATION                        = 0x34,
    CHAR_CREATE_SERVER_LIMIT                               = 0x35,
    CHAR_CREATE_ACCOUNT_LIMIT                              = 0x36,
    CHAR_CREATE_SERVER_QUEUE                               = 0x37,
    CHAR_CREATE_ONLY_EXISTING                              = 0x38,
    CHAR_CREATE_EXPANSION                                  = 0x39,
    CHAR_CREATE_EXPANSION_CLASS                            = 0x3A,
    CHAR_CREATE_LEVEL_REQUIREMENT                          = 0x3B,
    CHAR_CREATE_UNIQUE_CLASS_LIMIT                         = 0x3C,
    CHAR_CREATE_CHARACTER_IN_GUILD                         = 0x3D,
    CHAR_CREATE_RESTRICTED_RACECLASS                       = 0x3E,
    CHAR_CREATE_CHARACTER_CHOOSE_RACE                      = 0x3F,
    CHAR_CREATE_CHARACTER_ARENA_LEADER                     = 0x40,
    CHAR_CREATE_CHARACTER_DELETE_MAIL                      = 0x41,
    CHAR_CREATE_CHARACTER_SWAP_FACTION                     = 0x42,
    CHAR_CREATE_CHARACTER_RACE_ONLY                        = 0x43,

    CHAR_CREATE_CHARACTER_GOLD_LIMIT                       = 0x44,

    CHAR_CREATE_FORCE_LOGIN                                = 0x45,

    CHAR_DELETE_IN_PROGRESS                                = 0x46,
    CHAR_DELETE_SUCCESS                                    = 0x47,
    CHAR_DELETE_FAILED                                     = 0x48,
    CHAR_DELETE_FAILED_LOCKED_FOR_TRANSFER                 = 0x49,
    CHAR_DELETE_FAILED_GUILD_LEADER                        = 0x4A,
    CHAR_DELETE_FAILED_ARENA_CAPTAIN                       = 0x4B,

    CHAR_LOGIN_IN_PROGRESS                                 = 0x4C,
    CHAR_LOGIN_SUCCESS                                     = 0x4D,
    CHAR_LOGIN_NO_WORLD                                    = 0x4E,
    CHAR_LOGIN_DUPLICATE_CHARACTER                         = 0x4F,
    CHAR_LOGIN_NO_INSTANCES                                = 0x50,
    CHAR_LOGIN_FAILED                                      = 0x51,
    CHAR_LOGIN_DISABLED                                    = 0x52,
    CHAR_LOGIN_NO_CHARACTER                                = 0x53,
    CHAR_LOGIN_LOCKED_FOR_TRANSFER                         = 0x54,
    CHAR_LOGIN_LOCKED_BY_BILLING                           = 0x55,
    CHAR_LOGIN_LOCKED_BY_MOBILE_AH                         = 0x56,

    CHAR_NAME_SUCCESS                                      = 0x57,
    CHAR_NAME_FAILURE                                      = 0x58,
    CHAR_NAME_NO_NAME                                      = 0x59,
    CHAR_NAME_TOO_SHORT                                    = 0x5A,
    CHAR_NAME_TOO_LONG                                     = 0x5B,
    CHAR_NAME_INVALID_CHARACTER                            = 0x5C,
    CHAR_NAME_MIXED_LANGUAGES                              = 0x5D,
    CHAR_NAME_PROFANE                                      = 0x5E,
    CHAR_NAME_RESERVED                                     = 0x5F,
    CHAR_NAME_INVALID_APOSTROPHE                           = 0x60,
    CHAR_NAME_MULTIPLE_APOSTROPHES                         = 0x61,
    CHAR_NAME_THREE_CONSECUTIVE                            = 0x62,
    CHAR_NAME_INVALID_SPACE                                = 0x63,
    CHAR_NAME_CONSECUTIVE_SPACES                           = 0x64,
    CHAR_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS        = 0x65,
    CHAR_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END = 0x66,
    CHAR_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME            = 0x67
};

/// Ban function modes
enum BanMode
{
    BAN_ACCOUNT,
    BAN_CHARACTER,
    BAN_IP
};

/// Ban function return codes
enum BanReturn
{
    BAN_SUCCESS,
    BAN_SYNTAX_ERROR,
    BAN_NOTFOUND
};

// indexes of BattlemasterList.dbc
enum BattlegroundTypeId
{
    BATTLEGROUND_TYPE_NONE     = 0,
    BATTLEGROUND_AV            = 1,
    BATTLEGROUND_WS            = 2,
    BATTLEGROUND_AB            = 3,
    BATTLEGROUND_NA            = 4,
    BATTLEGROUND_BE            = 5,
    BATTLEGROUND_AA            = 6,
    BATTLEGROUND_EY            = 7,
    BATTLEGROUND_RL            = 8,
    BATTLEGROUND_SA            = 9,
    BATTLEGROUND_DS            = 10,
    BATTLEGROUND_RV            = 11,
    BATTLEGROUND_IC            = 30,
    BATTLEGROUND_RB            = 32,                        // Random Battleground
    BATTLEGROUND_RA_BG         = 100,                       // Rated Battleground
    BATTLEGROUND_RA_BG1        = 101,                       // Rated Battleground
    BATTLEGROUND_RA_BG2        = 102,                       // Rated Battleground
    BATTLEGROUND_TP            = 108,                       // Twin Peaks
    BATTLEGROUND_BG            = 120,                       // The Battle for Gilneas
    BATTLEGROUND_ICD           = 441,                       // Icecrown Citadel
    BATTLEGROUND_RS            = 443,                       // The Ruby Sanctum
    BATTLEGROUND_FL            = 522,                       // Firelands
    BATTLEGROUND_FL2           = 523,                       // Firelands Terrain 2
    BATTLEGROUND_TFW           = 530,                       // Throne of the Four Winds
    BATTLEGROUND_BD            = 531,                       // Blackwing Descent
    BATTLEGROUND_BT            = 532,                       // The Bastion of Twilight
    BATTLEGROUND_BH            = 533,                       // Baradin Hold
    BATTLEGROUND_RA_ES         = 656                        // Rated Eye of the Storm
};

#define MAX_BATTLEGROUND_TYPE_ID 657

enum MailResponseType
{
    MAIL_SEND               = 0,
    MAIL_MONEY_TAKEN        = 1,
    MAIL_ITEM_TAKEN         = 2,
    MAIL_RETURNED_TO_SENDER = 3,
    MAIL_DELETED            = 4,
    MAIL_MADE_PERMANENT     = 5
};

enum MailResponseResult
{
    MAIL_OK                            = 0,
    MAIL_ERR_EQUIP_ERROR               = 1,
    MAIL_ERR_CANNOT_SEND_TO_SELF       = 2,
    MAIL_ERR_NOT_ENOUGH_MONEY          = 3,
    MAIL_ERR_RECIPIENT_NOT_FOUND       = 4,
    MAIL_ERR_NOT_YOUR_TEAM             = 5,
    MAIL_ERR_INTERNAL_ERROR            = 6,
    MAIL_ERR_DISABLED_FOR_TRIAL_ACC    = 14,
    MAIL_ERR_RECIPIENT_CAP_REACHED     = 15,
    MAIL_ERR_CANT_SEND_WRAPPED_COD     = 16,
    MAIL_ERR_MAIL_AND_CHAT_SUSPENDED   = 17,
    MAIL_ERR_TOO_MANY_ATTACHMENTS      = 18,
    MAIL_ERR_MAIL_ATTACHMENT_INVALID   = 19,
    MAIL_ERR_ITEM_HAS_EXPIRED          = 21,
};

enum SpellFamilyNames
{
    SPELLFAMILY_GENERIC     = 0,
    SPELLFAMILY_UNK1        = 1,                            // events, holidays
    // 2 - unused
    SPELLFAMILY_MAGE        = 3,
    SPELLFAMILY_WARRIOR     = 4,
    SPELLFAMILY_WARLOCK     = 5,
    SPELLFAMILY_PRIEST      = 6,
    SPELLFAMILY_DRUID       = 7,
    SPELLFAMILY_ROGUE       = 8,
    SPELLFAMILY_HUNTER      = 9,
    SPELLFAMILY_PALADIN     = 10,
    SPELLFAMILY_SHAMAN      = 11,
    SPELLFAMILY_UNK2        = 12,                           // 2 spells (silence resistance)
    SPELLFAMILY_POTION      = 13,
    // 14 - unused
    SPELLFAMILY_DEATHKNIGHT = 15,
    // 16 - unused
    SPELLFAMILY_PET         = 17
};

enum TradeStatus
{
    TRADE_STATUS_BUSY           = 0,
    TRADE_STATUS_BEGIN_TRADE    = 1,
    TRADE_STATUS_OPEN_WINDOW    = 2,
    TRADE_STATUS_TRADE_CANCELED = 3,
    TRADE_STATUS_TRADE_ACCEPT   = 4,
    TRADE_STATUS_BUSY_2         = 5,
    TRADE_STATUS_NO_TARGET      = 6,
    TRADE_STATUS_BACK_TO_TRADE  = 7,
    TRADE_STATUS_TRADE_COMPLETE = 8,
    // 9?
    TRADE_STATUS_TARGET_TO_FAR  = 10,
    TRADE_STATUS_WRONG_FACTION  = 11,
    TRADE_STATUS_CLOSE_WINDOW   = 12,
    // 13?
    TRADE_STATUS_IGNORE_YOU     = 14,
    TRADE_STATUS_YOU_STUNNED    = 15,
    TRADE_STATUS_TARGET_STUNNED = 16,
    TRADE_STATUS_YOU_DEAD       = 17,
    TRADE_STATUS_TARGET_DEAD    = 18,
    TRADE_STATUS_YOU_LOGOUT     = 19,
    TRADE_STATUS_TARGET_LOGOUT  = 20,
    TRADE_STATUS_TRIAL_ACCOUNT  = 21,                       // Trial accounts can not perform that action
    TRADE_STATUS_ONLY_CONJURED  = 22,                       // You can only trade conjured items... (cross realm BG related).
    TRADE_STATUS_NOT_ELIGIBLE   = 23                        // Related to trading soulbound loot items
};

enum XPColorChar
{
    XP_RED,
    XP_ORANGE,
    XP_YELLOW,
    XP_GREEN,
    XP_GRAY
};

enum RemoveMethod
{
    GROUP_REMOVEMETHOD_DEFAULT = 0,
    GROUP_REMOVEMETHOD_KICK    = 1,
    GROUP_REMOVEMETHOD_LEAVE   = 2,
};

#endif
