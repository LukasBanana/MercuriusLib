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

static void PrintNetworkAdapter(const Mc::NetworkAdapter& adapter, std::size_t idx)
{
    std::cout << "network adapter " << (idx++) << ':' << std::endl;
    std::cout << "  type        = " << Mc::ToString(adapter.type) << std::endl;
    std::cout << "  description = " << adapter.description << std::endl;
    std::cout << "  addressName = " << adapter.addressName << std::endl;
    std::cout << "  subnetMask  = " << adapter.subnetMask << std::endl;
    std::cout << "  active      = " << std::boolalpha << adapter.active << std::endl;
    std::cout << "  broadcast   = " << adapter.BroadcastAddress()->ToString() << std::endl;
}

int main()
{
    try
    {
        Mc::NetworkSystem net;

        // Print network adapters
        auto adapters = net.QueryAdapters();

        std::size_t adaptersIdx = 0;
        for (const auto& adapter : adapters)
            PrintNetworkAdapter(adapter, adaptersIdx);

        // Print some IP addresses
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
                {
                    std::cout << "\n\n";
                    break;
                }
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
