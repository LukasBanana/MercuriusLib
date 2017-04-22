/*
 * IPAddress.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/IPAddress.h>
#include "IPv4Address.h"


namespace Mc
{


std::unique_ptr<IPAddress> IPAddress::MakeIPv4Address(unsigned short port)
{
    return std::unique_ptr<IPAddress>(new IPv4Address(port));
}

std::unique_ptr<IPAddress> IPAddress::MakeIPv4Address(unsigned short port, unsigned long address)
{
    return std::unique_ptr<IPAddress>(new IPv4Address(port, address));
}

std::unique_ptr<IPAddress> IPAddress::MakeIPv4Address(unsigned short port, const std::string& addressName)
{
    return std::unique_ptr<IPAddress>(new IPv4Address(port, addressName));
}

std::unique_ptr<IPAddress> IPAddress::MakeIPv4AddressLocalhost()
{
    return MakeIPv4Address(0, "127.0.0.1");
}

std::vector<std::unique_ptr<IPAddress>> IPAddress::QueryAddressesFromHost(const std::string& hostName)
{
    /* Query addresses from host name */
    addrinfo* results;
    if (::getaddrinfo(hostName.c_str(), nullptr, nullptr, &results) != 0)
        throw std::runtime_error("failed to query addresses from host name: " + hostName);

    /* Enumerate addresses */
    std::vector<std::unique_ptr<IPAddress>> addresses;

    for (auto ptr = results; ptr != nullptr; ptr = ptr->ai_next)
    {
        switch (ptr->ai_family)
        {
            case AF_INET:
            {
                if (ptr->ai_addr)
                {
                    addresses.emplace_back(
                        std::unique_ptr<IPv4Address>(
                            new IPv4Address(*reinterpret_cast<const sockaddr_in*>(ptr->ai_addr))
                        )
                    );
                }
            }
            break;

            case AF_INET6:
            {
                //TODO...
            }
            break;

            default:
            break;
        }
    }

    return addresses;
}

IPAddress::~IPAddress()
{
}


} // /namespace Mc



// ================================================================================
