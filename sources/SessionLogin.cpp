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


SessionLogin::SessionLogin(const IPAddress& portAddress) :
    sock_    { UDPSocket::Make(portAddress.Family()) },
    address_ { IPAddress::Make(portAddress.Family()) }
{
    /* Bind socket to address */
    sock_->SetNonBlocking(true);
    sock_->SetReuseAddress(true);
    sock_->SetBroadcasting(true);
    sock_->Bind(portAddress);
}

SessionLogin::~SessionLogin()
{
    // dummy
}

void SessionLogin::SendLogin(const IPAddress& address, const std::string& sessionKey)
{
    /* Build actual login message */
    std::string msg = g_msgPrefix;
    msg += sessionKey;

    /* Send and check for completion */
    if (sock_->Send(msg, address) != static_cast<int>(msg.size()))
    {
        throw std::runtime_error("failed to send session login");
    }
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
