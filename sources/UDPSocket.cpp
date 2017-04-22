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


} // /namespace Mc



// ================================================================================
