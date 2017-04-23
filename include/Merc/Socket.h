/*
 * Socket.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SOCKET_H
#define MC_SOCKET_H


#include <Merc/Export.h>


namespace Mc
{


enum class SocketType
{
    Stream,     //!< Sequenced, reliable, two-way, connection-based byte streams.
    Datagram,   //!< Connection less datagrams.
    Raw,        //!< Raw network protocol access.
};

enum class SocketProtocol
{
    TCP, //!< Transmission Control Protocol (TCP).
    UDP, //!< User Datagram Protocol (UDP).
};

class MC_EXPORT Socket
{

    public:

        virtual ~Socket();

        //! Specifies whether to set the socket into non-blocking (true) or blocking (false) state.
        virtual void SetNonBlocking(bool enable) = 0;

        virtual void SetBroadcasting(bool enable) = 0;

        virtual void SetReuseAddress(bool enable) = 0;

        //! Returns the socket type.
        virtual SocketType Type() const = 0;

        //! Returns the socket protocol.
        virtual SocketProtocol Protocol() const = 0; 

};


} // /namespace Mc


#endif



// ================================================================================
