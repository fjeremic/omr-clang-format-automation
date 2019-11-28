/*******************************************************************************
 * Copyright (c) 2019, 2019 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#if !defined(OMRSOCK_H_)
#define OMRSOCK_H_

#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>

#include "omrportsock.h"

/* Common data types required for using the omr socket API */

typedef int32_t OMRSocket;
typedef struct sockaddr OMRSockAddr;
typedef struct sockaddr_in OMRSockAddrIn; /* for IPv4 addresses*/
typedef struct sockaddr_in6 OMRSockAddrIn6; /* for IPv6 addresses*/
typedef struct sockaddr_storage OMRSockAddrStorage; /* For IPv4 or IPv6 addresses */
typedef struct addrinfo OMRAddrInfo; /* addrinfo structure for IPv4 or IPv6*/

/* Filled in using @ref omr_getaddrinfo. */

typedef struct OMRAddrInfoNode {
    /* Defined differently depending on the operating system.
     * Pointer to the first addrinfo node in listed list.
     */
    OMRAddrInfo* addrInfo;
    /* Number of addrinfo nodes in linked list */
    uint32_t length;
} OMRAddrInfoNode;

/* Per-thread buffer for socket information */
typedef struct OMRSocketPTB {
    OMRAddrInfoNode addrInfoHints;
} OMRSocketPTB;

#endif /* !defined(OMRSOCK_H_) */
