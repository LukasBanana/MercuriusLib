/*
 * TCPSocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_TCP_SOCKET_H
#define MC_TCP_SOCKET_H


#include <Merc/Socket.h>


namespace Mc
{


class MC_EXPORT TCPSocket : public Socket
{
    
    public:
        
        virtual void Bind(/*...*/) = 0;
        virtual void Listen(/*...*/) = 0;
        virtual void Accept(/*...*/) = 0;
        virtual void Connect(/*...*/) = 0;

        virtual void Send(/*...*/) = 0;
        virtual void Recv(/*...*/) = 0;
        
};


} // /namespace Mc


#endif



// ================================================================================
