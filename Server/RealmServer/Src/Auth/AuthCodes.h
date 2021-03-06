/*
 * Copyright (C) 2010-2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com>
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

#ifndef AUTHCODES
#define AUTHCODES

enum AuthResult
{
    WOW_SUCCESS                                  = 0x00,
    WOW_FAIL_BANNED                              = 0x03,
    WOW_FAIL_UNKNOWN_ACCOUNT                     = 0x04,
    WOW_FAIL_INCORRECT_PASSWORD                  = 0x05,
    WOW_FAIL_ALREADY_ONLINE                      = 0x06,
    WOW_FAIL_NO_TIME                             = 0x07,
    WOW_FAIL_DB_BUSY                             = 0x08,
    WOW_FAIL_VERSION_INVALID                     = 0x09,
    WOW_FAIL_VERSION_UPDATE                      = 0x0A,
    WOW_FAIL_SUSPENDED                           = 0x0C,
    WOW_SUCCESS_SURVEY                           = 0x0E,
    WOW_FAIL_PARENTCONTROL                       = 0x0F,
    WOW_FAIL_LOCKED_ENFORCED                     = 0x10,
    WOW_FAIL_TRIAL_ENDED                         = 0x11,
    WOW_FAIL_USE_BATTLENET                       = 0x12,
    WOW_FAIL_TOO_FAST                            = 0x16,
    WOW_FAIL_CHARGEBACK                          = 0x17,
    WOW_FAIL_GAME_ACCOUNT_LOCKED                 = 0x18,
    WOW_FAIL_INTERNET_GAME_ROOM_WITHOUT_BNET     = 0x19,
    WOW_FAIL_UNLOCKABLE_LOCK                     = 0x20,
    WOW_FAIL_DISCONNECTED                        = 0xFF,
};

enum LoginResult
{
    LOGIN_OK                                     = 0x00,
    LOGIN_FAILED                                 = 0x01,
    LOGIN_FAILED2                                = 0x02,
    LOGIN_BANNED                                 = 0x03,
    LOGIN_UNKNOWN_ACCOUNT                        = 0x04,
    LOGIN_UNKNOWN_ACCOUNT3                       = 0x05,
    LOGIN_ALREADYONLINE                          = 0x06,
    LOGIN_NOTIME                                 = 0x07,
    LOGIN_DBBUSY                                 = 0x08,
    LOGIN_BADVERSION                             = 0x09,
    LOGIN_DOWNLOAD_FILE                          = 0x0A,
    LOGIN_FAILED3                                = 0x0B,
    LOGIN_SUSPENDED                              = 0x0C,
    LOGIN_FAILED4                                = 0x0D,
    LOGIN_CONNECTED                              = 0x0E,
    LOGIN_PARENTALCONTROL                        = 0x0F,
    LOGIN_LOCKED_ENFORCED                        = 0x10,
};

enum AcceptedClientBuilds
{
    CL_ACCEPTED_CLIENT_BUILD = 0x1775,    // 1.12.2 (6005),  Classic
    BC_ACCEPTED_CLIENT_BUILD = 0x219E,    // 2.4.3  (8606),  The Burning Crusade
    LK_ACCEPTED_CLIENT_BUILD = 0x3034,    // 3.3.5a (12340), Wrath of the Lich King
    CT_ACCEPTED_CLIENT_BUILD = 0x37FD,    // 4.2.0  (14333), Cataclysm
    LT_ACCEPTED_CLIENT_BUILD = 0x3890,    // 4.2.0a (14480), Cataclysm[Latest]
};

enum ExpansionFlags
{
    CL_EXPANSION_FLAG = 0x0,    // No Expansion     - Classic
    BC_EXPANSION_FLAG = 0x1,    // First Expansion  - The Burning Crusade
    LK_EXPANSION_FLAG = 0x2,    // Second Expansion - Wrath of the Lich King
    CT_EXPANSION_FLAG = 0x3,    // Third Expansion  - Cataclysm
};

namespace AuthHelper
{
    bool GetAcceptedClientBuilds(uint32 build);
    bool IsAcceptedClientBuild(uint32 build);
};

#endif
