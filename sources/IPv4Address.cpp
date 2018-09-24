/*
 * IPv4Address.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "IPv4Address.h"
#include "SocketUtil.h"
#include <cstring>


namespace Mc
{


IPv4Address::IPv4Address(unsigned short port) :
    addr_ { }
{
    addr_.sin_family        = AF_INET;
    addr_.sin_port          = htons(port);
    addr_.sin_addr.s_addr   = htonl(INADDR_ANY);
}

IPv4Address::IPv4Address(unsigned short port, unsigned long address) :
    addr_ { }
{
    addr_.sin_family        = AF_INET;
    addr_.sin_port          = htons(port);
    #if defined __linux__ || defined __APPLE__
    addr_.sin_addr.s_addr   = static_cast<in_addr_t>(address);
    #else
    addr_.sin_addr.s_addr   = address;
    #endif
}

IPv4Address::IPv4Address(unsigned short port, const std::string& addressName) :
    addr_ { }
{
    addr_.sin_family    = AF_INET;
    addr_.sin_port      = htons(port);
    addr_.sin_addr      = AddressNameToBinary(addressName);
}

IPv4Address::IPv4Address(const sockaddr_in& nativeHandle) :
    addr_ { }
{
    memcpy(&addr_, &nativeHandle, sizeof(addr_));
}

AddressFamily IPv4Address::Family() const
{
    return AddressFamily::IPv4;
}

std::string IPv4Address::ToString(long flags) const
{
    std::string s;
    char buf[16];

    if (auto ptr = ::inet_ntop(AF_INET, &addr_.sin_addr, buf, 16))
    {
        s = ptr;

        if ((flags & AppendPort) != 0)
        {
            auto port = Port();
            if (port > 0)
            {
                s += ':';
                s += std::to_string(port);
            }
        }
    }

    return s;
}

unsigned short IPv4Address::Port() const
{
    return ntohs(addr_.sin_port);
}

void IPv4Address::Port(unsigned short port)
{
    addr_.sin_port = htons(port);
}

const void* IPv4Address::GetNativeHandle() const
{
    return reinterpret_cast<const void*>(&addr_);
}

void* IPv4Address::GetNativeHandle()
{
    return reinterpret_cast<void*>(&addr_);
}

int IPv4Address::GetNativeHandleSize() const
{
    return static_cast<int>(sizeof(addr_));
}

std::unique_ptr<IPAddress> IPv4Address::Copy() const
{
    return std::unique_ptr<IPAddress> { new IPv4Address { addr_ } };
}

static int Sign(int x)
{
    if (x < 0) return -1;
    if (x > 0) return +1;
               return  0;
}

int IPv4Address::CompareSWO(const IPAddress& rhs) const
{
    switch (rhs.Family())
    {
        case AddressFamily::IPv4:
        {
            const auto& rhsIPv4 = static_cast<const IPv4Address&>(rhs);
            auto s0 = reinterpret_cast<const char*>(&(addr_.sin_addr));
            auto s1 = reinterpret_cast<const char*>(&(rhsIPv4.addr_.sin_addr));
            return Sign(std::strncmp(s0, s1, 4));
        }
        break;

        case AddressFamily::IPv6:
        {
            //TODO...
        }
        break;
    }
    return 0;
}


} // /namespace Mc



// ================================================================================
