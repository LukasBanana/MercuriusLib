/*
 * NetworkSystem.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/NetworkSystem.h>
#include "Platform/SocketSystem.h"


namespace Mc
{


NetworkSystem::NetworkSystem()
{
    StartUp();
}

NetworkSystem::~NetworkSystem()
{
    CleanUp();
}

std::vector<NetworkAdapter> NetworkSystem::QueryAdapters() const
{
    return Mc::QueryAdapters();
}


} // /namespace Mc



// ================================================================================
