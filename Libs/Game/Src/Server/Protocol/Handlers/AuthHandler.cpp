/*
 * Copyright (C) 2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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

#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"

int WorldSocket::SendResumeComms()
{
    std::string ServerToClient = "RLD OF WARCRAFT CONNECTION - SERVER TO CLIENT";
    WorldPacket data(MSG_RESUME_COMMS, 45);

    data.Put(ServerToClient);

    if (SendPacket(data) == -1)
        return -1;

    return 0;
}

void WorldSession::SendAuthResponse(uint8 AuthCode, bool shortForm, uint32 queuePos)
{
    WorldPacket packet(SMSG_AUTH_RESPONSE, 1 + 4 + 1 + 4 + 1 + 1 + (shortForm ? 0 : (4 + 1)));
    packet.Put(AuthCode);
    packet.Put(0);                            // BillingTimeRemaining
    packet.Put(0);                            // BillingPlanFlags
    packet.Put(0);                            // BillingTimeRested
    packet.Put(Expansion());                  // Account expansion
    packet.Put(CONFIG_EXPANSION);             // Server expansion

    if (!shortForm)
    {
        packet.Put(queuePos);                             // Queue position
        packet.Put(0);                                    // Unk 3.3.0
    }

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}
