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

        //! Binds this socket to the specified address.
        virtual void Bind(const IPAddress& address) = 0;

        //! Listen on this socket channel with the specified queue size.
        virtual void Listen(int queueSize) = 0;

        //! Accepts a new socket connection and retrieves the TCP socket and IP address.
        virtual bool Accept(std::unique_ptr<TCPSocket>& socket, std::unique_ptr<IPAddress>& address) = 0;

        //! Connects this socket with the specified host address.
        virtual void Connect(const IPAddress& address) = 0;

        //! Sends the specified byte buffer over this socket and returns the number of bytes actually send.
        virtual int Send(const void* data, std::size_t dataSize) = 0;

        //! Receives a byte buffer with the specified maximal bytes and returns the number of actually received bytes.
        virtual int Recv(void* data, std::size_t dataSize) = 0;

        //! Sends the specified string over this socket and returns the number of bytes actually send.
        int Send(const std::string& s);

        //! Receives a string with a maximal size of the specified stirng (must be pre-allocated) and returns the number of actually received bytes.
        int Recv(std::string& s);

};


} // /namespace Mc


#endif



// ================================================================================
