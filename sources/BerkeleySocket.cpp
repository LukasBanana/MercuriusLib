/*
 * BerkeleySocket.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "BerkeleySocket.h"
#include <stdexcept>


namespace Mc
{


int AddressFamilyToNative(const AddressFamily family)
{
    switch (family)
    {
        case AddressFamily::IPv4:
            return AF_INET;
        case AddressFamily::IPv6:
            return AF_INET6;
    }
    return 0;
}

BerkeleySocket::BerkeleySocket(SOCKET sock) :
    sock_ { sock }
{
    if (sock_ == INVALID_SOCKET)
        throw std::runtime_error("invalid socket");
}

BerkeleySocket::BerkeleySocket(int domain, int type, int protocol) :
    BerkeleySocket { ::socket(domain, type, protocol) }
{
}

BerkeleySocket::BerkeleySocket(BerkeleySocket&& rhs) :
    BerkeleySocket { rhs.sock_ }
{
    rhs.sock_ = INVALID_SOCKET;
}

BerkeleySocket::~BerkeleySocket()
{
    if (sock_ != INVALID_SOCKET)
    {
        #if defined(_WIN32)
        ::closesocket(sock_);
        #elif defined(__linux__)
        ::close(sock_);
        #endif
    }
}

static void SetSocketCtrlOrThrow(SOCKET sock, unsigned long cmd, unsigned long* arg)
{
    #ifdef _WIN32
    if (::ioctlsocket(sock, static_cast<long>(cmd), arg) != 0)
    {
        throw std::runtime_error("<ioctrlsocket> failed");
    }
    #else
    if (::ioctl(sock, cmd, arg) != 0)
    {
        throw std::runtime_error("<ioctrl> failed");
    }
    #endif
}

static void SetSocketOptOrThrow(SOCKET sock, int level, int param, const void* value, std::size_t valueSize)
{
    #ifdef _WIN32
    if (::setsockopt(sock, level, param, reinterpret_cast<const char*>(value), static_cast<int>(valueSize)) != 0)
    {
        throw std::runtime_error("<setsockopt> failed");
    }
    #else
    if (::setsockopt(sock, level, param, value, static_cast<socklen_t>(valueSize)) != 0)
    {
        throw std::runtime_error("<setsockopt> failed");
    }
    #endif
}

void BerkeleySocket::SetNonBlocking(bool enable)
{
    unsigned long flags = (enable ? 1 : 0);
    SetSocketCtrlOrThrow(sock_, FIONBIO, &flags);
}

void BerkeleySocket::SetBroadcasting(bool enable)
{
    int flags = (enable ? 1 : 0);
    SetSocketOptOrThrow(sock_, SOL_SOCKET, SO_BROADCAST, &flags, sizeof(flags));
}

void BerkeleySocket::SetReuseAddress(bool enable)
{
    int flags = (enable ? 1 : 0);
    SetSocketOptOrThrow(sock_, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));
}


} // /namespace Mc



// ================================================================================
