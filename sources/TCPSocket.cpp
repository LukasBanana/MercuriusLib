/*
 * TCPSocket.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/TCPSocket.h>
#include "BerkeleyTCPSocket.h"


namespace Mc
{


std::unique_ptr<TCPSocket> TCPSocket::Make(const AddressFamily family)
{
    return std::unique_ptr<TCPSocket>(new BerkeleyTCPSocket(family));
}

SocketType TCPSocket::Type() const
{
    return SocketType::Stream;
}

SocketProtocol TCPSocket::Protocol() const
{
    return SocketProtocol::TCP;
}

int TCPSocket::Send(const std::string& s)
{
    return Send(s.c_str(), static_cast<int>(s.size()));
}

int TCPSocket::Recv(std::string& s)
{
    auto result = Recv(&s[0], static_cast<int>(s.size()));
    if (result >= 0)
        s.resize(static_cast<std::size_t>(result));
    return result;
}


} // /namespace Mc



// ================================================================================
