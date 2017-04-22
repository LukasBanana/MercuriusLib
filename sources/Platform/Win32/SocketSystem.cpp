/*
 * SocketInterface.cpp (Win32)
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "../SocketSystem.h"
#include "SocketAPI.h"
#include <sstream>
#include <iomanip>


namespace Mc
{


template <typename T>
std::string ToHexString(T i)
{
    std::stringstream s;
    s << "0x" << std::setfill('0') << std::setw(sizeof(T)*2) << std::hex << i;
    return s.str();
}

static std::string WSAStartupErrorToString(int errorCode)
{
    switch (errorCode)
    {
        case WSASYSNOTREADY:
            return "network subsystem is unavailable";
        case WSAVERNOTSUPPORTED:
            return "Winsock.dll version out of range";
        case WSAEINPROGRESS:
            return "blocking operation in progress";
        case WSAEPROCLIM:
            return "maximum tasks reached";
        case WSAEFAULT:
            return "bad memory address";
        default:
            return "unknown error code (" + ToHexString(errorCode) + ")";
    }
}

void StartUp(StartUpInfo* info)
{
    /* Windows socket startup */
    const WORD versionRequest = MAKEWORD(2, 2);
    
    WSADATA winSockData;
    const int err = WSAStartup(versionRequest, &winSockData);

    if (err)
        throw std::runtime_error("WinSock startup error: " + WSAStartupErrorToString(err));

    if (info)
    {
        /* Pass start-up information to output argument */
        info->description   = winSockData.szDescription;
        info->status        = winSockData.szSystemStatus;
    }
}

void CleanUp()
{
    WSACleanup();
}


} // /namespace Mc



// ================================================================================
