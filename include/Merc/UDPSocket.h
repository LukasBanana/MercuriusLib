/*
 * UDPSocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_UDP_SOCKET_H
#define MC_UDP_SOCKET_H


#include <Merc/Socket.h>


namespace Mc
{


class MC_EXPORT UDPSocket : public Socket
{
    
    public:
        
        virtual void Bind(/*...*/) = 0;

        virtual void Send(/*...*/) = 0;
        virtual void Recv(/*...*/) = 0;
        
};


} // /namespace Mc


#endif



// ================================================================================
