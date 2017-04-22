/*
 * Test1.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/Merc.h>
#include <iostream>
#include <cstdlib>


static void PrintHostAddresses(const std::string& hostName)
{
    try
    {
        auto addresses = Mc::IPAddress::QueryAddressesFromHost(hostName);

        std::cout << "addresses of host \"" << hostName << "\":" << std::endl;

        if (!addresses.empty())
        {
            for (const auto& addr : addresses)
                std::cout << "  " << addr->ToString() << std::endl;
        }
        else
            std::cout << "  <none>" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        Mc::NetworkSystem net;

        auto addrLocalhost = Mc::IPAddress::MakeIPv4Localhost();
        std::cout << "localhost = " << addrLocalhost->ToString() << std::endl;

        //PrintHostAddresses("www.google.com");
        PrintHostAddresses("www.google.de");
        PrintHostAddresses("www.google.ch");
        PrintHostAddresses("localhost");
        PrintHostAddresses("www.facebook.com");
        PrintHostAddresses("www.facebook.de");

        // Send HTTP GET request to server
        auto addrGoogle = Mc::IPAddress::QueryAddressesFromHost("www.google.com");
        if (!addrGoogle.empty())
        {
            auto& addr = addrGoogle.front();
            addr->Port(80);

            auto sock = Mc::TCPSocket::Make(Mc::AddressFamily::IPv4);

            sock->Connect(*addr);

            std::string getRequest = "GET /index.html HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
            sock->Send(getRequest.c_str(), static_cast<int>(getRequest.size() + 1));
            
            char getResponse[513];
            while (true)
            {
                auto len = sock->Recv(getResponse, 512);
                if (len > 0)
                {
                    getResponse[len] = 0;
                    std::cout << getResponse;
                }
                else
                    break;
            }
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
