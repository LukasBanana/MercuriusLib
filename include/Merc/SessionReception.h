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
#include <queue>


namespace Mc
{


class MC_EXPORT SessionReception final : private Service
{

    public:

        SessionReception(const SessionReception&) = delete;
        SessionReception& operator = (const SessionReception&) = delete;

        SessionReception(const IPAddress& address, const std::string& sessionDesc, const std::string& sessionKey);

        void SetSessionKey(const std::string& s);
        std::string SessionKey() const;

        void SetSessionDesc(const std::string& s);
        std::string SessionDesc() const;

        //! Returns the next address of a previous login attempt or null if there are no further login addresses.
        std::unique_ptr<IPAddress> PollLoginAddress();

    private:

        void RecvLogins(long long interval);

        std::unique_ptr<UDPSocket>              sock_;
        std::unique_ptr<IPAddress>              address_;

        // thread shared {
        mutable std::mutex                      sessionMutex_;
        std::string                             sessionDesc_;
        std::string                             sessionKey_;
        std::queue<std::unique_ptr<IPAddress>>  loginAddresses_;
        // }

};


} // /namespace Mc


#endif



// ================================================================================
