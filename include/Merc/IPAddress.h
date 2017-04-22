/*
 * IPAddress.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_IPADDRESS_H
#define MC_IPADDRESS_H


#include <Merc/Export.h>
#include <string>
#include <memory>
#include <vector>


namespace Mc
{


//! Address family enumeration.
enum class AddressFamily
{
    IPv4, //!< IPv4 Internet protocols.
    IPv6, //!< IPv6 Internet protocols.
};

class MC_EXPORT IPAddress
{

    public:

        static std::unique_ptr<IPAddress> MakeIPv4(unsigned short port);
        static std::unique_ptr<IPAddress> MakeIPv4(unsigned short port, unsigned long address);
        static std::unique_ptr<IPAddress> MakeIPv4(unsigned short port, const std::string& addressName);
        static std::unique_ptr<IPAddress> MakeIPv4Localhost();

        static std::vector<std::unique_ptr<IPAddress>> QueryAddressesFromHost(const std::string& hostName);

        virtual ~IPAddress();

        //! Returns the address family.
        virtual AddressFamily Family() const = 0;

        //! Returns this address as human readable string.
        virtual std::string ToString() const = 0;

        //! Returns the port number.
        virtual unsigned short Port() const = 0;

        //! Sets the new port number.
        virtual void Port(unsigned short port) = 0;

        //! Returns a constant raw pointer to the native socket address handle, i.e. either from type 'const sockaddr_in*' or 'const sockaddr_in6*'.
        virtual const void* GetNativeHandle() const = 0;

        //! Returns a raw pointer to the native socket address handle, i.e. either from type 'sockaddr_in*' or 'sockaddr_in6*'.
        virtual void* GetNativeHandle() = 0;

        //! Returns the size of the native socket address handle, i.e. either 'sizeof(sockaddr_in)' or 'sizeof(sockaddr_in6)'.
        virtual int GetNativeHandleSize() const = 0;

};


} // /namespace Mc


#endif



// ================================================================================
