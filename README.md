MercuriusLib - Simple Networking Library for modern C++
=======================================================

Overview
--------

- **Version**: 1.00 Alpha
- **License**: [3-Clause BSD License](https://github.com/LukasBanana/MercuriusLib/blob/master/LICENSE.txt)


Example
-------

This is an example about the mesh generator:
```cpp
#include <Merc/Merc.h>
#include <iostream>

int main()
{
    try
    {
        Mc::NetworkSystem net;
        
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
}
```


