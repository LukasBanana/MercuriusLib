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

void BerkeleyUDPSocket::Bind(const IPAddress& address)
{
    /* Bind socket to address */
    auto result = ::bind(
        sock_.GetNativeHandle(),
        reinterpret_cast<const sockaddr*>(address.GetNativeHandle()),
        address.GetNativeHandleSize()
    );
    if (result == SOCKET_ERROR)
        throw std::runtime_error("failed to bind UDP/IP socket to address: " + address.ToString());
}

int BerkeleyUDPSocket::Send(const char* data, int dataSize, const IPAddress& address)
{

    return 0;
}

int BerkeleyUDPSocket::Recv(char* data, int dataSize, IPAddress& address)
{
    return 0;
}


} // /namespace Mc



// ================================================================================
