/*
 * SocketAPI.h (Unix)
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SOCKET_API_H
#define MC_SOCKET_API_H


// see http://man7.org/linux/man-pages/man2/socket.2.html

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef int SOCKET;

#ifndef SOCKET_SUCCESS
#define SOCKET_SUCCESS (0)
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (~0)
#endif


#endif



// ================================================================================
