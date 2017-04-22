/*
 * Export.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_EXPORT_H
#define MC_EXPORT_H


#ifdef _MSC_VER
#   define MC_EXPORT __declspec(dllexport)
#else
#   define MC_EXPORT
#endif


#endif



// ================================================================================
