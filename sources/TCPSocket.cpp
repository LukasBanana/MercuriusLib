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


} // /namespace Mc



// ================================================================================
