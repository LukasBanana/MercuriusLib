/*
 * BerkeleyUDPSocket.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "BerkeleyUDPSocket.h"
#include "Platform/SocketSystem.h"


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

void BerkeleyUDPSocket::SetBroadcasting(bool enable)
{
    sock_.SetBroadcasting(enable);
}

void BerkeleyUDPSocket::SetReuseAddress(bool enable)
{
    sock_.SetReuseAddress(enable);
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
    /* Send network message to specified destination address */
    return ::sendto(
        sock_.GetNativeHandle(),
        data,
        dataSize,
        0,
        reinterpret_cast<const sockaddr*>(address.GetNativeHandle()),
        address.GetNativeHandleSize()
    );
}

int BerkeleyUDPSocket::Recv(char* data, int dataSize, IPAddress& address)
{
    /* Receive network message from unknown source address */
    sockaddr_storage addr;
    socklen_t addrSize = sizeof(addr);

    auto result = ::recvfrom(
        sock_.GetNativeHandle(),
        data,
        dataSize,
        0,
        reinterpret_cast<sockaddr*>(&addr),
        &addrSize
    );

    /* Copy source address to output parameter */
    if (result > 0)
    {
        if (addrSize == address.GetNativeHandleSize())
            memcpy(address.GetNativeHandle(), &addr, static_cast<std::size_t>(addrSize));
        else
            throw std::runtime_error("socket address size mismatch when receiving data from UDP/IP socket");
    }

    return result;
}


} // /namespace Mc



// ================================================================================
