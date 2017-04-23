/*
 * SocketInterface.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SOCKET_INTERFACE_H
#define MC_SOCKET_INTERFACE_H


#include <Merc/NetworkAdapter.h>
#include <string>
#include <vector>


namespace Mc
{


struct StartUpInfo
{
    std::string description;
    std::string status;
};


void StartUp(StartUpInfo* info = nullptr);

void CleanUp();

std::vector<NetworkAdapter> QueryAdapters();


} // /namespace Mc


#endif



// ================================================================================
