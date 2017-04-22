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
        #ifdef _WIN32
        ::closesocket(sock_);
        #else
        ::close(sock_);
        #endif
    }
}

void BerkeleySocket::SetNonBlocking(bool enable)
{
    unsigned long flags = (enable ? 1 : 0);
    ::ioctlsocket(sock_, FIONBIO, &flags);
}


} // /namespace Mc



// ================================================================================
