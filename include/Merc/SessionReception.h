/*
 * SessionReception.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SESSION_RECEPTION_H
#define MC_SESSION_RECEPTION_H


#include <Merc/Service.h>
#include <Merc/UDPSocket.h>
#include <Merc/IPAddress.h>
#include <mutex>


namespace Mc
{


//! Base class for all thread based services.
class MC_EXPORT SessionReception final : private Service
{

    public:

        SessionReception(const Service&) = delete;
        SessionReception& operator = (const SessionReception&) = delete;

        SessionReception(const IPAddress& address, const std::string& sessionDesc, const std::string& sessionKey);

        void SetSessionKey(const std::string& s);
        std::string SessionKey() const;

        void SetSessionDesc(const std::string& s);
        std::string SessionDesc() const;

    private:

        void RecvLogins(long long interval);

        std::unique_ptr<UDPSocket>  sock_;
        std::unique_ptr<IPAddress>  address_;

        // thread shared {
        std::string                 sessionDesc_;
        std::string                 sessionKey_;
        mutable std::mutex          sessionMutex_;
        // }

};


} // /namespace Mc


#endif



// ================================================================================
