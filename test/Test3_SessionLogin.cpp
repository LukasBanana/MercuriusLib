/*
 * Test3_SessionLogin.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/Merc.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <thread>


std::string GetInputLine()
{
    std::string s;
    std::getline(std::cin, s);
    return s;
}

template <typename T>
T GetInputLineAs()
{
    std::stringstream s;
    s << GetInputLine();
    T value = T(0);
    s >> value;
    return value;
}

class Login : public Mc::SessionLogin
{

public:
        
    Login() :
        Mc::SessionLogin { Mc::AddressFamily::IPv4 }
    {
    }

private:

    void OnResponse(const Mc::IPAddress& address, const std::string& sessionDesc) override
    {
        std::cout << "Received login response from:" << std::endl;
        std::cout << "  Host                = " << address.ToString() << std::endl;
        std::cout << "  Session Description = \"" << sessionDesc << '\"' << std::endl;
    }

};

int main()
{
    try
    {
        Mc::NetworkSystem net;

        // Get port number
        std::cout << "Enter session port: ";
        auto port = GetInputLineAs<unsigned short>();

        // Start session login
        Login login;

        // Send broadcast requests all network adapters
        for (const auto& adapter : net.QueryAdapters())
        {
            auto broadcastAddr = adapter.BroadcastAddress(port);
            std::cout << "Send login request to broadcast address: " << broadcastAddr->ToString() << std::endl;
            login.SendLogin(*broadcastAddr, "");
        }

        // Send request to localhost
        auto localhostAddr = Mc::IPAddress::MakeIPv4Localhost(port);
        std::cout << "Send login request to localhost address: " << localhostAddr->ToString() << std::endl;
        login.SendLogin(*localhostAddr, "");

        // Wait for responses
        const float duration = 5.0f;
        auto timePoint = std::chrono::system_clock::now();

        while (std::chrono::duration<float>(std::chrono::system_clock::now() - timePoint).count() < duration)
        {
            // Receive login responses
            std::cout << "Waiting for response ..." << std::endl;
            login.RecvResponse();

            // Wait a moment
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    #ifdef _WIN32
    system("pause");
    #endif

    return 0;
}



// ================================================================================
