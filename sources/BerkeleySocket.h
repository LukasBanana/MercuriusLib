/*
 * BerkeleySocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_BERKELEY_SOCKET_H
#define MC_BERKELEY_SOCKET_H


#include "Platform/Platform.h"


namespace Mc
{


class BerkeleySocket
{

    public:

        // Opens a new socket with the specified parameters.
        BerkeleySocket(int domain, int type, int protocol);

        // Takes the ownership of the specified socket.
        BerkeleySocket(SOCKET sock);
        
        // Takes the ownership of the socket of the specified object.
        BerkeleySocket(BerkeleySocket&& rhs);

        ~BerkeleySocket();

        BerkeleySocket(const BerkeleySocket&) = delete;
        BerkeleySocket& operator = (const BerkeleySocket&) = delete;
        
        void SetNonBlocking(bool enable);

    private:

        SOCKET sock_;

};


} // /namespace Mc


#endif



// ================================================================================
