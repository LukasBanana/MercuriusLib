/*
 * NetworkAdapter.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_NETWORK_ADAPTER_H
#define MC_NETWORK_ADAPTER_H


#include <Merc/Export.h>
#include <Merc/IPAddress.h>
#include <string>


namespace Mc
{


//! Network adapter type enumeratino.
enum class NetworkAdapterType
{
    Undefined,

    Ethernet,   //!< Ethernet (e.g. for LAN connections).
    TokenRing,  //!< Token Ring (IEEE 802.5).
    FDDI,       //!< Fiber Distributed Data Interface.
    PPP,        //!< Point-to-Point Protocol.
    LoopBack,   //!< Loop Back Protocol.
    SLIP,       //!< Serial Line Internet Protocol.
};

//! Returns the specified network adapter type as string.
MC_EXPORT std::string ToString(const NetworkAdapterType t);

//! Network adapter class.
struct MC_EXPORT NetworkAdapter
{
    NetworkAdapter() = default;
    NetworkAdapter(const NetworkAdapter&) = default;
    NetworkAdapter& operator = (const NetworkAdapter&) = default;
    NetworkAdapter(NetworkAdapter&&) = default;
    NetworkAdapter& operator = (NetworkAdapter&&) = default;

    NetworkAdapter(
        const NetworkAdapterType type,
        const std::string& description,
        const std::string& addressName,
        const std::string& subnetMask,
        bool active
    );

    //! Returns a broadcast address for this adapter with an optional port number.
    std::unique_ptr<IPAddress> BroadcastAddress(unsigned short port = 0) const;

    //! Network adapter type. By default NetworkAdapterType::Undefined.
    NetworkAdapterType  type        = NetworkAdapterType::Undefined;

    //! Description of the hardware/software network adapter.
    std::string         description;

    //! IP address name (e.g. "192.168.0.1").
    std::string         addressName;

    //! Sub networking mask (e.g. "255.255.255.0").
    std::string         subnetMask;

    //! Specifies whether the network adapter is active or inactive.
    bool                active      = false;
};


} // /namespace Mc


#endif



// ================================================================================
