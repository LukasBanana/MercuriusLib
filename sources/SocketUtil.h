/*
 * SocketUtil.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SOCKET_UTIL_H
#define MC_SOCKET_UTIL_H


#include "Platform/Platform.h"
#include <string>


namespace Mc
{


// Uses ::inet_pton to convert the address name from text to binary form and throws an std::runtime_error exception on failure.
in_addr AddressNameToBinary(const std::string& addressName);


} // /namespace Mc


#endif



// ================================================================================
