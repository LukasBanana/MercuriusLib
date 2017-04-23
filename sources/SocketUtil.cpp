/*
 * SocketUtil.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "SocketUtil.h"


namespace Mc
{


// Uses ::inet_pton to convert the address name from text to binary form and throws an std::runtime_error exception on failure.
in_addr AddressNameToBinary(const std::string& addressName)
{
    in_addr addr;
    if (::inet_pton(AF_INET, addressName.c_str(), &addr) != 1)
        throw std::runtime_error("failed to convert IPv4 address from text to binary form: " + addressName);
    return addr;
}


} // /namespace Mc



// ================================================================================
