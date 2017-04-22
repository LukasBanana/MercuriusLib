/*
 * BerkeleyUDPSocket.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "BerkeleyUDPSocket.h"


namespace Mc
{


BerkeleyUDPSocket::BerkeleyUDPSocket(const AddressFamily family) :
    sock_ { AddressFamilyToNative(family), SOCK_DGRAM, IPPROTO_UDP }
{
}

BerkeleyUDPSocket::BerkeleyUDPSocket(SOCKET sock) :
    sock_ { sock }
{
}

void BerkeleyUDPSocket::SetNonBlocking(bool enable)
{
    sock_.SetNonBlocking(enable);
}

void BerkeleyUDPSocket::Bind(/*...*/)
{
}

int BerkeleyUDPSocket::Send(/*...*/)
{
    return 0;
}

int BerkeleyUDPSocket::Recv(/*...*/)
{
    return 0;
}


} // /namespace Mc



// ================================================================================
