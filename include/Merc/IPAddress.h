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


class MC_EXPORT IPAddress
{

    public:

        static std::unique_ptr<IPAddress> MakeIPv4Address(unsigned short port);
        static std::unique_ptr<IPAddress> MakeIPv4Address(unsigned short port, unsigned long address);
        static std::unique_ptr<IPAddress> MakeIPv4Address(unsigned short port, const std::string& addressName);
        static std::unique_ptr<IPAddress> MakeIPv4AddressLocalhost();

        static std::vector<std::unique_ptr<IPAddress>> QueryAddressesFromHost(const std::string& hostName);

        virtual ~IPAddress();

        virtual std::string ToString() const = 0;

        virtual unsigned short Port() const = 0;

        /**
        \brief Retrieves the native socket address handle, i.e. either from type 'sockaddr_in' or 'sockaddr_in6'.
        \param[out] nativeHandle Raw pointer to the output socket address. May also be null.
        \param[out] nativeHandleSize Raw pointer to the size of the socket address. May also be null.
        \remarks This should be called twice, first to retrieve the native handle size, and a second one to retrive the native handle itself:
        \code
        std::size_t nativeHandleSize = 0;
        addr->GetNativeHandle(nullptr, &nativeHandleSize);
        if (nativeHandleSize == sizeof(sockaddr_in))
        {
            sockaddr_in nativeHandle;
            addr->GetNativeHandle(&nativeHandle, nullptr);
            //...
        }
        else if (nativeHandleSize == sizeof(sockaddr_in6))
        {
            sockaddr_in6 nativeHandle;
            addr->GetNativeHandle(&nativeHandle, nullptr);
            //...
        }
        \endcode
        */
        virtual void GetNativeHandle(void* nativeHandle, std::size_t* nativeHandleSize) const = 0;

};


} // /namespace Mc


#endif



// ================================================================================
