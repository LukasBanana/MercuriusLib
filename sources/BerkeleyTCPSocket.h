/*
 * BerkeleyTCPSocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_BERKELEY_TCP_SOCKET_H
#define MC_BERKELEY_TCP_SOCKET_H


#include <Merc/TCPSocket.h>
#include "BerkeleySocket.h"


namespace Mc
{


class BerkeleyTCPSocket : public TCPSocket
{

    public:

        BerkeleyTCPSocket(const AddressFamily family);
        BerkeleyTCPSocket(SOCKET sock);

        void SetNonBlocking(bool enable) override;
        void SetBroadcasting(bool enable) override;
        void SetReuseAddress(bool enable) override;

        void Bind(const IPAddress& address) override;
        void Listen(int queueSize) override;
        bool Accept(std::unique_ptr<TCPSocket>& socket, std::unique_ptr<IPAddress>& address) override;
        void Connect(const IPAddress& address) override;

        int Send(const void* data, std::size_t dataSize) override;
        int Recv(void* data, std::size_t dataSize) override;

    private:

        BerkeleySocket sock_;

};


} // /namespace Mc


#endif



// ================================================================================
