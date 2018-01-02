/*
 * UDPSocket.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/UDPSocket.h>
#include "BerkeleyUDPSocket.h"


namespace Mc
{


std::unique_ptr<UDPSocket> UDPSocket::Make(const AddressFamily family)
{
    return std::unique_ptr<UDPSocket>(new BerkeleyUDPSocket(family));
}

SocketType UDPSocket::Type() const
{
    return SocketType::Datagram;
}

SocketProtocol UDPSocket::Protocol() const
{
    return SocketProtocol::UDP;
}

int UDPSocket::Send(const std::string& s, const IPAddress& address)
{
    return Send(s.c_str(), s.size(), address);
}

int UDPSocket::Recv(std::string& s, IPAddress& address)
{
    auto result = Recv(&s[0], s.capacity(), address);
    if (result >= 0)
        s.resize(static_cast<std::size_t>(result));
    return result;
}


} // /namespace Mc



// ================================================================================
