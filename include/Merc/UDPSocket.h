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

        virtual void Bind(/*...*/) = 0;

        virtual int Send(/*...*/) = 0;
        virtual int Recv(/*...*/) = 0;
        
};


} // /namespace Mc


#endif



// ================================================================================
