/*
 * SessionReception.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/SessionReception.h>


namespace Mc
{


SessionReception::SessionReception(const IPAddress& address, const std::string& sessionDesc, const std::string& sessionKey) :
    sock_        { UDPSocket::Make(address.Family())                 },
    address_     { IPAddress::Make(address.Family(), address.Port()) },
    sessionDesc_ { sessionDesc                                       },
    sessionKey_  { sessionKey                                        }
{
    /* Bind socket to address */
    sock_->SetNonBlocking(true);
    sock_->Bind(address);

    /* Run service thread */
    Run(std::bind(&SessionReception::RecvLogins, this, std::placeholders::_1), 100);
}

void SessionReception::SetSessionKey(const std::string& s)
{
    std::lock_guard<std::mutex> guard { sessionMutex_ };
    sessionKey_ = s;
}

std::string SessionReception::SessionKey() const
{
    std::lock_guard<std::mutex> guard { sessionMutex_ };
    return sessionKey_;
}

void SessionReception::SetSessionDesc(const std::string& s)
{
    std::lock_guard<std::mutex> guard { sessionMutex_ };
    sessionDesc_ = s;
}

std::string SessionReception::SessionDesc() const
{
    std::lock_guard<std::mutex> guard { sessionMutex_ };
    return sessionDesc_;
}


/*
 * ======= Private: =======
 */

void SessionReception::RecvLogins(long long interval)
{
    static const int msgMaxLen = 4096;
    char msg[msgMaxLen];

    while (Running())
    {
        /* Receive next login request */
        auto len = sock_->Recv(msg, msgMaxLen, *address_);

        if (len >= 0 && len < msgMaxLen)
            msg[len] = '\0';

        /* Compare message with session */
        const auto key = SessionKey();
        if (key.empty() || key.compare(msg) == 0)
        {
            /* Send login response */
            const auto desc = SessionDesc();
            sock_->Send(desc.c_str(), static_cast<int>(desc.size()), *address_);
        }

        /* Wait a moment (100ms) to give the other threads time to run */
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}


} // /namespace Mc



// ================================================================================
