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

#define _GNU_SOURCE

#include <sys/ucontext.h>
#include <unistd.h>

#include "omrport.h"
#include "omrportasserts.h"
#include "omrsignal_context.h"

#define NGPRS 32
#define NFPRS 32

/* AArch64 Signal Context Reserved Space Size */
#define RESERVED_SPACE_SZ 4096

void fillInUnixSignalInfo(struct OMRPortLibrary* portLibrary, void* contextInfo, struct OMRUnixSignalInfo* signalInfo)
{
    signalInfo->platformSignalInfo.context = (ucontext_t*)contextInfo;
    /* module info is filled on demand */
}

uint32_t infoForSignal(
    struct OMRPortLibrary* portLibrary, struct OMRUnixSignalInfo* info, int32_t index, const char** name, void** value)
{
    *name = "";

    switch (index) {

    case OMRPORT_SIG_SIGNAL_TYPE:
    case 0:
        *name = "J9Generic_Signal_Number";
        *value = &info->portLibrarySignalType;
        return OMRPORT_SIG_VALUE_32;

    case OMRPORT_SIG_SIGNAL_PLATFORM_SIGNAL_TYPE:
    case 1:
        *name = "Signal_Number";
        if (NULL != info->sigInfo) {
            *value = &info->sigInfo->si_signo;
            return OMRPORT_SIG_VALUE_32;
        }
        break;

    case OMRPORT_SIG_SIGNAL_ERROR_VALUE:
    case 2:
        *name = "Error_Value";
        *value = &info->sigInfo->si_errno;
        return OMRPORT_SIG_VALUE_32;

    case OMRPORT_SIG_SIGNAL_CODE:
    case 3:
        *name = "Signal_Code";
        if (NULL != info->sigInfo) {
            *value = &info->sigInfo->si_code;
            return OMRPORT_SIG_VALUE_32;
        }
        break;

    case OMRPORT_SIG_SIGNAL_HANDLER:
    case 4:
        *name = "Handler1";
        *value = &info->handlerAddress;
        return OMRPORT_SIG_VALUE_ADDRESS;

    case 5:
        *name = "Handler2";
        *value = &info->handlerAddress2;
        return OMRPORT_SIG_VALUE_ADDRESS;

    case OMRPORT_SIG_SIGNAL_INACCESSIBLE_ADDRESS:
    case 6:
        /* si_code > 0 indicates that the signal was generated by the kernel */
        if (NULL != info->sigInfo && 0 < info->sigInfo->si_code) {
            if ((info->sigInfo->si_signo == SIGBUS) || (info->sigInfo->si_signo == SIGSEGV)) {
                *name = "InaccessibleAddress";
                *value = &info->sigInfo->si_addr;
                return OMRPORT_SIG_VALUE_ADDRESS;
            }
        }
        break;

        // case OMRPORT_SIG_SIGNAL_ADDRESS:
        // case 7:
        // 	*name = "fault_address";
        // 	*value = &((struct sigcontext *)&info->platformSignalInfo.context->uc_mcontext)->fault_address;
        // 	return OMRPORT_SIG_VALUE_ADDRESS;

    default:
        break;
    }

    return OMRPORT_SIG_VALUE_UNDEFINED;
}

/**
 * Walk the 4k reserve space to get the floating point registers since the layout differ
 * per-chip
 * @param	magic_to_find	input	magic number #define in the linux kernel (sigcontext.h)\
 * that defines which struct the reserved area is at a given space
 * @param	reserved_space	input	array of bytes that holds all the struct
 * @see linux/arch/riscv/include/uapi/asm/sigcontext.h for the defines and information to why we need
 * to walk the space

 */
void* walkReserveSpace(uint32_t magic_to_find, uint8_t* reserved_space)
{
    Assert_PRT_true(0 && "Not yet implemented");
    return NULL;
}

uint32_t infoForFPR(
    struct OMRPortLibrary* portLibrary, struct OMRUnixSignalInfo* info, int32_t index, const char** name, void** value)
{
    Assert_PRT_true(0 && "Not yet implemented");
    return 0;
}

uint32_t infoForGPR(
    struct OMRPortLibrary* portLibrary, struct OMRUnixSignalInfo* info, int32_t index, const char** name, void** value)
{
    Assert_PRT_true(0 && "Not yet implemented");
    return 0;
}

uint32_t infoForControl(
    struct OMRPortLibrary* portLibrary, struct OMRUnixSignalInfo* info, int32_t index, const char** name, void** value)
{
    Assert_PRT_true(0 && "Not yet implemented");
    return 0;
}

uint32_t infoForModule(
    struct OMRPortLibrary* portLibrary, struct OMRUnixSignalInfo* info, int32_t index, const char** name, void** value)
{
    Assert_PRT_true(0 && "Not yet implemented");
    return 0;
}
