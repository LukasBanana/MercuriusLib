/*
 * NetworkAdapter.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/NetworkAdapter.h>
#include "SocketUtil.h"


namespace Mc
{


MC_EXPORT std::string ToString(const NetworkAdapterType t)
{
    switch (t)
    {
        case NetworkAdapterType::Ethernet:  return "Ethernet";
        case NetworkAdapterType::TokenRing: return "Token Ring (IEEE 802.5)";
        case NetworkAdapterType::FDDI:      return "Fiber Distributed Data Interface (FDDI)";
        case NetworkAdapterType::PPP:       return "Point-to-Point Protocol (PPP)";
        case NetworkAdapterType::LoopBack:  return "Loop Back Protocol";
        case NetworkAdapterType::SLIP:      return "Serial Line Internet Protocol (SLIP)";
        default:                            return "";
    }
}

NetworkAdapter::NetworkAdapter(
    const NetworkAdapterType type,
    const std::string& description,
    const std::string& addressName,
    const std::string& subnetMask,
    bool active
) :
    type        { type        },
    description { description },
    addressName { addressName },
    subnetMask  { subnetMask  },
    active      { active      }
{
}

static void AppendBroadcast(std::string& s, unsigned char maskPart, unsigned char addrPart)
{
    if (maskPart > 0)
        s += std::to_string(static_cast<int>(addrPart));
    else
        s += "255";
}

std::unique_ptr<IPAddress> NetworkAdapter::BroadcastAddress(unsigned short port) const
{
    /* Get address and mask from strings */
    auto addr = AddressNameToBinary(addressName);
    auto mask = AddressNameToBinary(subnetMask);

    /* Get broad cast IP address */
    std::string broadcastAddr;

    AppendBroadcast(broadcastAddr, mask.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b1);
    broadcastAddr += ".";
    AppendBroadcast(broadcastAddr, mask.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b2);
    broadcastAddr += ".";
    AppendBroadcast(broadcastAddr, mask.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b3);
    broadcastAddr += ".";
    AppendBroadcast(broadcastAddr, mask.S_un.S_un_b.s_b4, addr.S_un.S_un_b.s_b4);

    return IPAddress::MakeIPv4(port, broadcastAddr);
}


} // /namespace Mc



// ================================================================================
