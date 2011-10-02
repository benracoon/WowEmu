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

#include "zlib.h"
#include "AddonHandler.h"
#include "OpcodeHandler.h"
#include "DatabaseEnv.h"
#include "Log.h"

AddonHandler::AddonHandler()
{
}

AddonHandler::~AddonHandler()
{
}

bool AddonHandler::BuildAddonPacket(WorldPacket *Source, WorldPacket *Target)
{
    WorldPacket data(SMSG_ADDON_INFO);
    data << uint8(0x0C);
    data << uint8(0xC7);
    data << uint8(0x34);
    data << uint8(0xC6);
    
    for(int i = 0; i < 6; i++)
        data << uint8(0x00);
    data << uint8(0x02);
    data << uint8(0x02);

    return true;
}
