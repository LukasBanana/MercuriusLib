/*
 * TCPSocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_TCP_SOCKET_H
#define MC_TCP_SOCKET_H


#include <Merc/Socket.h>
#include <Merc/IPAddress.h>
#include <memory>


namespace Mc
{


class MC_EXPORT TCPSocket : public Socket
{
    
    public:
        
        static std::unique_ptr<TCPSocket> Make(const AddressFamily family);

        SocketType Type() const override;
        SocketProtocol Protocol() const override; 

        virtual void Bind(const IPAddress& address) = 0;

        virtual void Listen(int queueSize) = 0;

        virtual bool Accept(std::unique_ptr<TCPSocket>& socket, std::unique_ptr<IPAddress>& address) = 0;

        //! Connects this socket with the specified host address.
        virtual void Connect(const IPAddress& address) = 0;

        virtual int Send(const char* data, int dataSize) = 0;

        virtual int Recv(char* data, int dataSize) = 0;
        
};


} // /namespace Mc


#endif



// ================================================================================
