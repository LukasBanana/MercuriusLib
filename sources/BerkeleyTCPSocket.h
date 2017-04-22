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
        
        void Bind(/*...*/) override;
        void Listen(/*...*/) override;
        void Accept(/*...*/) override;
        void Connect(/*...*/) override;

        void Send(/*...*/) override;
        void Recv(/*...*/) override;

    private:

        BerkeleySocket sock_;
        
};


} // /namespace Mc


#endif



// ================================================================================
