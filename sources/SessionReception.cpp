/*
 * SessionReception.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/SessionReception.h>
#include "SocketUtil.h"

#include <iostream>//!!!


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
    sock_->SetReuseAddress(true);
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

std::unique_ptr<IPAddress> SessionReception::PollLoginAddress()
{
    std::lock_guard<std::mutex> guard { sessionMutex_ };
    if (!loginAddresses_.empty())
    {
        auto address = std::move(loginAddresses_.back());
        loginAddresses_.pop();
        return address;
    }
    return nullptr;
}


/*
 * ======= Private: =======
 */

void SessionReception::RecvLogins(long long interval)
{
    try
    {
        char msg[g_msgMaxSize];

        while (Running())
        {
            /* Receive next login request */
            auto len = sock_->Recv(msg, g_msgMaxSize, *address_);

            if (len >= 0 && len < g_msgMaxSize)
                msg[len] = '\0';

            /* Compare message with session */
            const auto key = g_msgPrefix + SessionKey();
            if (key.compare(msg) == 0)
            {
                /* Send login response and add copy of address to list */
                std::lock_guard<std::mutex> guard { sessionMutex_ };
                sock_->Send(sessionDesc_, *address_);
                loginAddresses_.push(address_->Copy());
            }

            /* Wait a moment (100ms) to give the other threads time to run */
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
    catch (const std::exception& e)
    {
        #if 1//!!!
        std::cerr << "SessionReception::RecvLogins: " << e.what() << std::endl;
        #endif
    }
}


} // /namespace Mc



// ================================================================================
