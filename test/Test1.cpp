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

        auto addrLocalhost = Mc::IPAddress::MakeIPv4AddressLocalhost();

        std::cout << "localhost = " << addrLocalhost->ToString() << std::endl;

        //PrintHostAddresses("www.google.com");
        PrintHostAddresses("www.google.de");
        PrintHostAddresses("www.google.ch");
        PrintHostAddresses("localhost");
        PrintHostAddresses("www.facebook.com");
        PrintHostAddresses("www.facebook.de");


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
