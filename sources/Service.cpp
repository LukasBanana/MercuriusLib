/*
 * Service.cpp
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <Merc/Service.h>


namespace Mc
{


Service::~Service()
{
    Halt();
}

void Service::Halt()
{
    if (thread_.joinable())
    {
        running_ = false;
        thread_.join();
    }
}


} // /namespace Mc



// ================================================================================
