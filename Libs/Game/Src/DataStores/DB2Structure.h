/*
 * Copyright (C) 2010-2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
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

#ifndef STRAWBERRY_DB2STRUCTURE_H
#define STRAWBERRY_DB2STRUCTURE_H

#include "Common.h"
#include "DBCEnums.h"
#include "Define.h"
#include "Path.h"
#include "Util.h"
#include "Vehicle.h"

#include <map>
#include <set>
#include <vector>
#include "SharedDefines.h"

// Structures using to access raw DB2 data and required packing to portability
struct ItemEntry
{
   uint32   ID;                                             // 0
   uint32   Class;                                          // 1
   uint32   SubClass;                                       // 2 some items have strange subclasses
   int32    Unk0;                                           // 3
   int32    Material;                                       // 4
   uint32   DisplayId;                                      // 5
   uint32   InventoryType;                                  // 6
   uint32   Sheath;                                         // 7
};

struct ItemCurrencyCostEntry
{
    //uint32 id;                                            // 0
    uint32 itemid;                                          // 1
};

#define MAX_ITEM_EXT_COST_ITEMS         5
#define MAX_ITEM_EXT_COST_CURRENCIES    5

struct ItemExtendedCostEntry
{
    uint32      ID;                                                  // 0 extended-cost entry id
    uint32      RequiredHonorPoints;                                 // 1 required honor points
    uint32      RequiredArenaPoints;                                 // 2 required arena points
    uint32      RequiredArenaSlot;                                   // 4 arena slot restrictions (min slot value)
    uint32      RequiredItem[MAX_ITEM_EXT_COST_ITEMS];               // 5-8 required item id
    uint32      RequiredItemCount[MAX_ITEM_EXT_COST_ITEMS];          // 9-13 required count of 1st item
    uint32      RequiredPersonalArenaRating;                         // 14 required personal arena rating
    //uint32                                                         // 15
    uint32      RequiredCurrency[MAX_ITEM_EXT_COST_CURRENCIES];      // 16-20
    uint32      RequiredCurrencyCount[MAX_ITEM_EXT_COST_CURRENCIES]; // 21-25
    //uint32    something[5];                                        // 26-30
};

struct ItemSparseEntry
{
};

#endif
