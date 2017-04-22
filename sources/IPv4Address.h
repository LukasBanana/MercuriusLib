/*
 * IPv4Address.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_IPV4ADDRESS_H
#define MC_IPV4ADDRESS_H


#include <Merc/IPAddress.h>
#include "Platform/Platform.h"


namespace Mc
{


class IPv4Address : public IPAddress
{

    public:

        IPv4Address(unsigned short port);
        IPv4Address(unsigned short port, unsigned long address);
        IPv4Address(unsigned short port, const std::string& addressName);
        IPv4Address(const sockaddr_in& nativeHandle);

        AddressFamily Family() const override;

        std::string ToString() const override;

        unsigned short Port() const override;
        void Port(unsigned short port) override;
        
        void GetNativeHandle(void* nativeHandle, int* nativeHandleSize) const override;

    private:

        sockaddr_in addr_;

};


} // /namespace Mc


#endif



// ================================================================================
