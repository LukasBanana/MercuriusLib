/*
 * Platform.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_PLATFORM_H
#define MC_PLATFORM_H


#if defined(_WIN32)

#include "Win32/SocketAPI.h"

#elif defined(__linux__) || defined(__APPLE__)

#include "Unix/SocketAPI.h"

#endif


#endif



// ================================================================================
