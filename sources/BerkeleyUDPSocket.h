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
        
        void Bind(/*...*/) override;

        void Send(/*...*/) override;
        void Recv(/*...*/) override;

    private:

        BerkeleySocket sock_;
        
};


} // /namespace Mc


#endif



// ================================================================================
