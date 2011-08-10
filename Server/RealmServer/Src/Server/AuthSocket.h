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

#ifndef _AUTHSOCKET_H
#define _AUTHSOCKET_H

#include "Common.h"
#include "BigNumber.h"
#include "RealmSocket.h"

enum eAuthCmd
{
    AUTH_LOGON_CHALLENGE                         = 0x00,
    AUTH_LOGON_PROOF                             = 0x01,
    AUTH_RECONNECT_CHALLENGE                     = 0x02,
    AUTH_RECONNECT_PROOF                         = 0x03,
    REALM_LIST                                   = 0x10,
    // NOT USED!!!
    XFER_INITIATE                                = 0x30,
    XFER_DATA                                    = 0x31,
    XFER_ACCEPT                                  = 0x32,
    XFER_RESUME                                  = 0x33,
    XFER_CANCEL                                  = 0x34
};

enum RealmFlags
{
    REALM_FLAG_NONE                              = 0x00,
    REALM_FLAG_INVALID                           = 0x01,
    REALM_FLAG_OFFLINE                           = 0x02,
    REALM_FLAG_SPECIFYBUILD                      = 0x04,
    REALM_FLAG_UNK1                              = 0x08,
    REALM_FLAG_UNK2                              = 0x10,
    REALM_FLAG_RECOMMENDED                       = 0x20,
    REALM_FLAG_NEW                               = 0x40,
    REALM_FLAG_FULL                              = 0x80
};

// Handle login commands
class AuthSocket: public RealmSocket::Session
{
public:
    const static int s_BYTE_SIZE = 32;

    AuthSocket(RealmSocket& socket);
    virtual ~AuthSocket(void);

    virtual void OnRead(void);
    virtual void OnAccept(void);
    virtual void OnClose(void);

    bool _HandleLogonChallenge();
    bool _HandleLogonProof();
    bool _HandleReconnectChallenge();
    bool _HandleReconnectProof();
    bool _HandleRealmList();

    void _SetVSFields(const std::string& rI);

private:
    RealmSocket& socket_;
    RealmSocket& socket(void) { return socket_; }

    BigNumber N, s, g, v;
    BigNumber b, B;
    BigNumber K;
    BigNumber _reconnectProof;

    bool _authed;
    std::string _login;

    // Since GetLocaleByName() is _NOT_ bijective, we have to store the locale as a string. Otherwise we can't differ
    // between enUS and enGB, which is important for the patch system
    std::string _localizationName;
    uint16 _build;
    uint8 _expversion;
    AccountTypes _accountSecurityLevel;
};

#endif
