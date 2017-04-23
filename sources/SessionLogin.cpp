/*
 * SessionLogin.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/SessionLogin.h>
#include "SocketUtil.h"


namespace Mc
{


SessionLogin::SessionLogin(const AddressFamily family) :
    sock_    { UDPSocket::Make(family) },
    address_ { IPAddress::Make(family) }
{
    sock_->SetNonBlocking(true);
}

SessionLogin::~SessionLogin()
{
    // dummy
}

void SessionLogin::SendLogin(const IPAddress& address, const std::string& sessionKey)
{
    sock_->Send(g_msgPrefix + sessionKey, address);
}

void SessionLogin::RecvResponse()
{
    /* Receive response from session reception host */
    std::string msg;
    msg.resize(static_cast<std::size_t>(g_msgMaxSize));

    if (sock_->Recv(msg, *address_) > 0)
        OnResponse(*address_, msg);
}


/*
 * ======= Protected: =======
 */

void SessionLogin::OnResponse(const IPAddress& address, const std::string& sessionDesc)
{
    // dummy
}


} // /namespace Mc



// ================================================================================
