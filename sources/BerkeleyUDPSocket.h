/*
 * BerkeleyUDPSocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_BERKELEY_UDP_SOCKET_H
#define MC_BERKELEY_UDP_SOCKET_H


#include <Merc/UDPSocket.h>
#include "BerkeleySocket.h"


namespace Mc
{


class BerkeleyUDPSocket : public UDPSocket
{
    
    public:
        
        BerkeleyUDPSocket(const AddressFamily family);
        BerkeleyUDPSocket(SOCKET sock);

        void SetNonBlocking(bool enable) override;
        void SetBroadcasting(bool enable) override;
        void SetReuseAddress(bool enable) override;

        void Bind(const IPAddress& address) override;

        int Send(const void* data, std::size_t dataSize, const IPAddress& address) override;
        int Recv(void* data, std::size_t dataSize, IPAddress& address) override;

    private:

        BerkeleySocket sock_;
        
};


} // /namespace Mc


#endif



// ================================================================================
