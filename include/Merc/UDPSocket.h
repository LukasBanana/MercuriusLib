/*
 * UDPSocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_UDP_SOCKET_H
#define MC_UDP_SOCKET_H


#include <Merc/Socket.h>
#include <Merc/IPAddress.h>
#include <memory>


namespace Mc
{


class MC_EXPORT UDPSocket : public Socket
{
    
    public:
        
        static std::unique_ptr<UDPSocket> Make(const AddressFamily family);

        SocketType Type() const override;
        SocketProtocol Protocol() const override; 

        //! Binds this socket to the specified address.
        virtual void Bind(const IPAddress& address) = 0;

        //! Sends the specified byte buffer over this socket and returns the number of bytes actually send.
        virtual int Send(const char* data, int dataSize, const IPAddress& address) = 0;

        //! Receives a byte buffer with the specified maximal bytes and returns the number of actually received bytes.
        virtual int Recv(char* data, int dataSize, IPAddress& address) = 0;
        
};


} // /namespace Mc


#endif



// ================================================================================
