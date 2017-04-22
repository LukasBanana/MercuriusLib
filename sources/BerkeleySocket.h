/*
 * BerkeleySocket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_BERKELEY_SOCKET_H
#define MC_BERKELEY_SOCKET_H


#include <Merc/IPAddress.h>
#include "Platform/Platform.h"


namespace Mc
{


// Returns the native value for the specified address family.
int AddressFamilyToNative(const AddressFamily family);

class BerkeleySocket
{

    public:

        // Takes the ownership of the specified socket.
        BerkeleySocket(SOCKET sock);
        
        // Opens a new socket with the specified parameters.
        BerkeleySocket(int domain, int type, int protocol);

        // Takes the ownership of the socket of the specified object.
        BerkeleySocket(BerkeleySocket&& rhs);

        ~BerkeleySocket();

        BerkeleySocket(const BerkeleySocket&) = delete;
        BerkeleySocket& operator = (const BerkeleySocket&) = delete;
        
        void SetNonBlocking(bool enable);

        // Returns the native socket handle.
        inline SOCKET GetNativeHandle() const
        {
            return sock_;
        }

    private:

        SOCKET sock_ = INVALID_SOCKET;

};


} // /namespace Mc


#endif



// ================================================================================
