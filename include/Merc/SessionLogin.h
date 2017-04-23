/*
 * SessionLogin.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SESSION_LOGIN_H
#define MC_SESSION_LOGIN_H


#include <Merc/Export.h>
#include <Merc/UDPSocket.h>
#include <Merc/IPAddress.h>
#include <vector>
#include <string>
#include <memory>


namespace Mc
{


class MC_EXPORT SessionLogin
{

    public:

        SessionLogin(const AddressFamily family);
        virtual ~SessionLogin();

        void SendLogin(const IPAddress& address, const std::string& sessionKey);

        void RecvResponse();

    protected:

        virtual void OnResponse(const IPAddress& address, const std::string& sessionDesc);

    private:

        std::unique_ptr<UDPSocket> sock_;
        std::unique_ptr<IPAddress> address_;

};


} // /namespace Mc


#endif



// ================================================================================
