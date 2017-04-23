/*
 * BerkeleyTCPSocket.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "BerkeleyTCPSocket.h"
#include "IPv4Address.h"
#include <stdexcept>


namespace Mc
{


BerkeleyTCPSocket::BerkeleyTCPSocket(const AddressFamily family) :
    sock_ { AddressFamilyToNative(family), SOCK_STREAM, IPPROTO_TCP }
{
}

BerkeleyTCPSocket::BerkeleyTCPSocket(SOCKET sock) :
    sock_ { sock }
{
}

void BerkeleyTCPSocket::SetNonBlocking(bool enable)
{
    sock_.SetNonBlocking(enable);
}

void BerkeleyTCPSocket::SetBroadcasting(bool enable)
{
    sock_.SetBroadcasting(enable);
}

void BerkeleyTCPSocket::SetReuseAddress(bool enable)
{
    sock_.SetReuseAddress(enable);
}

void BerkeleyTCPSocket::Bind(const IPAddress& address)
{
    /* Bind socket to address */
    auto result = ::bind(
        sock_.GetNativeHandle(),
        reinterpret_cast<const sockaddr*>(address.GetNativeHandle()),
        address.GetNativeHandleSize()
    );
    if (result == SOCKET_ERROR)
        throw std::runtime_error("failed to bind TCP/IP socket to address: " + address.ToString());
}

void BerkeleyTCPSocket::Listen(int queueSize)
{
    /* Listen on socket channel */
    if (::listen(sock_.GetNativeHandle(), queueSize) == SOCKET_ERROR)
        throw std::runtime_error("failed to listen on TCP/IP socket with queue size: " + std::to_string(queueSize));
}

bool BerkeleyTCPSocket::Accept(std::unique_ptr<TCPSocket>& socket, std::unique_ptr<IPAddress>& address)
{
    /* Accept incoming socket connection */
    sockaddr addr;
    int addrSize = 0;

    auto sock = ::accept(sock_.GetNativeHandle(), &addr, &addrSize);

    if (sock == INVALID_SOCKET)
        throw std::runtime_error("failed to accept incoming TCP/IP connection");

    /* Create output address */
    switch (addr.sa_family)
    {
        case AF_INET:
            address = std::unique_ptr<IPAddress>(new IPv4Address(reinterpret_cast<const sockaddr_in&>(addr)));
            break;

        case AF_INET6:
            //TODO...
            break;

        default:
            break;
    }

    /* Create output socket */
    socket = std::unique_ptr<TCPSocket>(new BerkeleyTCPSocket(sock));

    return true;
}

void BerkeleyTCPSocket::Connect(const IPAddress& address)
{
    /* Connect socket to address */
    auto result = ::connect(
        sock_.GetNativeHandle(),
        reinterpret_cast<const sockaddr*>(address.GetNativeHandle()),
        address.GetNativeHandleSize()
    );
    if (result == SOCKET_ERROR)
        throw std::runtime_error("failed to connect TCP/IP socket to address: " + address.ToString());
}

int BerkeleyTCPSocket::Send(const char* data, int dataSize)
{
    return ::send(sock_.GetNativeHandle(), data, dataSize, 0);
}

int BerkeleyTCPSocket::Recv(char* data, int dataSize)
{
    return ::recv(sock_.GetNativeHandle(), data, dataSize, 0);
}


} // /namespace Mc



// ================================================================================
