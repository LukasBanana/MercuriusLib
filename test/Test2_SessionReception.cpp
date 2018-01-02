/*
 * Test2_SessionReception.cpp
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

int main()
{
    try
    {
        Mc::NetworkSystem net;

        #if 0
        // Get port number
        std::cout << "Enter session port: ";
        auto port = GetInputLineAs<unsigned short>();

        // Get session description
        std::cout << "Enter session description: ";
        auto sessionDesc = GetInputLine();
        #else
        unsigned short port = 8888;
        std::string sessionDesc = "Hello, World";
        #endif

        // Start session reception
        auto address = Mc::IPAddress::MakeIPv4(port);
        Mc::SessionReception reception { *address, sessionDesc, "", true };

        // Wait for logins
        std::cout << "Waiting for login attempts ..." << std::endl;

        // Create socket for messages
        auto sock = Mc::UDPSocket::Make(address->Family());
        auto sockAddr = Mc::IPAddress::Make(address->Family(), port + 1);

        sock->SetNonBlocking(true);
        sock->SetReuseAddress(true);
        sock->Bind(*sockAddr);

        while (true)
        {
            // Poll login attempts
            while (auto address = reception.PollLoginAddress())
                std::cout << "Login attempt: " << address->ToString() << std::endl;

            // Receive messages
            std::string s;
            s.resize(512);
            if (sock->Recv(s, *sockAddr) > 0)
            {
                if (!s.empty())
                    std::cout << "Message received: " << s << std::endl;
            }

            // Wait a moment
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        #ifdef _WIN32
        system("pause");
        #endif
    }
    return 0;
}



// ================================================================================
