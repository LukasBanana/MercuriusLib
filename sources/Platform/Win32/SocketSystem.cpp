/*
 * SocketInterface.cpp (Win32)
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "../SocketSystem.h"
#include "SocketAPI.h"
#include <iphlpapi.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>


namespace Mc
{


/*
 * Internal functions
 */

template <typename T>
std::string ToHexString(T i)
{
    std::stringstream s;
    s << "0x" << std::setfill('0') << std::setw(sizeof(T)*2) << std::hex << i;
    return s.str();
}

// -> WSAGetLastError()
// see also: https://msdn.microsoft.com/en-us/library/windows/desktop/ms740120(v=vs.85).aspx
static std::string WSAErrorToString(int errorCode)
{
    switch (errorCode)
    {
        case WSANOTINITIALISED:     return "network subsystem not initialised";
        case WSAENETDOWN:           return "network subsystem failed";
        case WSAEFAULT:             return "bad memory address";
        case WSAEINTR:              return "blocking call was canceled";
        case WSAEINPROGRESS:        return "blocking operation in progress";
        case WSAEINVAL:             return "socket not bound or unknown flag";
        case WSAEISCONN:            return "function not permitted with connected socket";
        case WSAENETRESET:          return "time to live expired";
        case WSAENOTSOCK:           return "invalid socket descriptor";
        case WSAEOPNOTSUPP:         return "invalid stream socket";
        case WSAESHUTDOWN:          return "socket has been shutdown";
        case WSAEWOULDBLOCK:        return "blocking operation in non-blocking socket";
        case WSAEMSGSIZE:           return "message size overflow";
        case WSAETIMEDOUT:          return "connection droped";
        case WSAECONNRESET:         return "virtual circuit reset";
        case WSASYSNOTREADY:        return "network subsystem is unavailable";
        case WSAVERNOTSUPPORTED:    return "Winsock.dll version out of range";
        case WSAEPROCLIM:           return "maximum tasks reached";
        default:                    return "unknown error code (" + ToHexString(errorCode) + ")";
    }
}

static std::string AdaptersInfoErrorToString(DWORD errorCode)
{
    switch (errorCode)
    {
        case ERROR_BUFFER_OVERFLOW:     return "buffer overflow";
        case ERROR_INVALID_DATA:        return "invalid data";
        case ERROR_INVALID_PARAMETER:   return "invalid parameter";
        case ERROR_NO_DATA:             return "no data";
        case ERROR_NOT_SUPPORTED:       return "not supported";
        default:                        return "unknown error code (" + ToHexString(errorCode) + ")";
    }
}

static NetworkAdapterType ToNetworkAdapterType(UINT t)
{
    switch (t)
    {
        case MIB_IF_TYPE_ETHERNET:  return NetworkAdapterType::Ethernet;
        case MIB_IF_TYPE_TOKENRING: return NetworkAdapterType::TokenRing;
        case MIB_IF_TYPE_FDDI:      return NetworkAdapterType::FDDI;
        case MIB_IF_TYPE_PPP:       return NetworkAdapterType::PPP;
        case MIB_IF_TYPE_LOOPBACK:  return NetworkAdapterType::LoopBack;
        case MIB_IF_TYPE_SLIP:      return NetworkAdapterType::SLIP;
        default:                    return NetworkAdapterType::Undefined;
    }
}


/*
 * Global functions
 */

void StartUp(StartUpInfo* info)
{
    /* Windows socket startup */
    const WORD versionRequest = MAKEWORD(2, 2);

    WSADATA winSockData;
    const int err = WSAStartup(versionRequest, &winSockData);

    if (err)
        throw std::runtime_error("WinSock startup error: " + WSAErrorToString(err));

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

std::vector<NetworkAdapter> QueryAdapters()
{
    std::vector<NetworkAdapter> adapters;

    /* Get first network adapter */
    ULONG bufferSize = sizeof(IP_ADAPTER_INFO);

    std::vector<char> adapterInfoBuffer(bufferSize);
    auto adapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(adapterInfoBuffer.data());

    if (GetAdaptersInfo(adapterInfo, &bufferSize) != ERROR_SUCCESS)
    {
        /* Resize adapter info buffer */
        adapterInfoBuffer.resize(bufferSize);
        adapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(adapterInfoBuffer.data());
    }

    /* Final call to receive adapter info */
    auto result = GetAdaptersInfo(adapterInfo, &bufferSize);

    if (result != ERROR_SUCCESS)
        throw std::runtime_error("failed to enumerate network adapters: " + AdaptersInfoErrorToString(result));

    /* Iterate over all network adapters */
    for (; adapterInfo != nullptr; adapterInfo = adapterInfo->Next)
    {
        NetworkAdapter adapter;
        {
            adapter.type        = ToNetworkAdapterType(adapterInfo->Type);
            adapter.description = std::string(adapterInfo->Description);
            adapter.addressName = std::string(adapterInfo->IpAddressList.IpAddress.String);
            adapter.subnetMask  = std::string(adapterInfo->IpAddressList.IpMask.String);
            adapter.active      = (adapterInfo->DhcpEnabled != 0);
        }
        adapters.push_back(adapter);
    }

    return adapters;
}

std::string LastErrorToString()
{
    auto err = WSAGetLastError();
    return (err != 0 ? WSAErrorToString(err) : "");
}


} // /namespace Mc



// ================================================================================
