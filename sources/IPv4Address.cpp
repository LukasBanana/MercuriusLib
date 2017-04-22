/*
 * IPv4Address.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "IPv4Address.h"
#include <cstring>


namespace Mc
{


IPv4Address::IPv4Address(unsigned short port) :
    addr_ { }
{
    addr_.sin_family        = AF_INET;
    addr_.sin_port          = ::htons(port);
    addr_.sin_addr.s_addr   = ::htonl(INADDR_ANY);
}

IPv4Address::IPv4Address(unsigned short port, unsigned long address) :
    addr_ { }
{
    addr_.sin_family        = AF_INET;
    addr_.sin_port          = ::htons(port);
    addr_.sin_addr.s_addr   = address;
}

IPv4Address::IPv4Address(unsigned short port, const std::string& addressName) :
    addr_ { }
{
    addr_.sin_family    = AF_INET;
    addr_.sin_port      = ::htons(port);

    if (::inet_pton(AF_INET, addressName.c_str(), &(addr_.sin_addr.s_addr)) != 1)
        throw std::runtime_error("failed to convert IPv4 address from text to binary form: " + addressName);
}

IPv4Address::IPv4Address(const sockaddr_in& nativeHandle) :
    addr_ { }
{
    memcpy(&addr_, &nativeHandle, sizeof(addr_));
}

std::string IPv4Address::ToString() const
{
    std::string s;

    auto addr = reinterpret_cast<const unsigned char*>(&addr_.sin_addr.s_addr);

    s += std::to_string(static_cast<int>(addr[0])) + ".";
    s += std::to_string(static_cast<int>(addr[1])) + ".";
    s += std::to_string(static_cast<int>(addr[2])) + ".";
    s += std::to_string(static_cast<int>(addr[3]));

    auto port = Port();
    if (port > 0)
    {
        s += ':';
        s += std::to_string(port);
    }

    return s;
}

unsigned short IPv4Address::Port() const
{
    return ::ntohs(addr_.sin_port);
}

void IPv4Address::GetNativeHandle(void* nativeHandle, std::size_t* nativeHandleSize) const
{
    if (nativeHandle)
        memcpy(nativeHandle, &addr_, sizeof(addr_));
    if (nativeHandleSize)
        *nativeHandleSize = sizeof(addr_);
}


} // /namespace Mc



// ================================================================================
