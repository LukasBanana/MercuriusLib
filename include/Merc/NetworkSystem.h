/*
 * NetworkSystem.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_NETWORK_SYSTEM_H
#define MC_NETWORK_SYSTEM_H


#include <Merc/Export.h>
#include <Merc/NetworkAdapter.h>


namespace Mc
{


class MC_EXPORT NetworkSystem
{

    public:

        NetworkSystem();
        ~NetworkSystem();

        //! Returns the list of all network adapters.
        std::vector<NetworkAdapter> QueryAdapters() const;

};


} // /namespace Mc


#endif



// ================================================================================
