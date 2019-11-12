/*******************************************************************************
 * Copyright (c) 1998, 2016 IBM Corp. and others
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

/**
 * @file
 * @ingroup Port
 * @brief Port Library Error Codes
 *
 * When an error is reported by the operating system the port library must translate this OS specific error code to a
 * portable error code.  All portable error codes are negative numbers.  Not every module of the port library will have
 * error codes dedicated to it's own use, some will use the generic portable error code values.
 *
 * Errors reported by the OS may be recorded by calling the port library functions @ref omrerror.c::omrerror_set_last_error "omrerror_set_last_error()"
 * or @ref omrerror.c::omrerror_set_last_error_with_message "omrerror_set_last_error_with_message()"
 * or @ref omrerror.c::omrerror_set_last_error_with_message_format "omrerror_set_last_error_with_message_format()".
 * The mapping of the OS specific error code to a portable error code is the responsibility of the calling module.
 */
#ifndef omrporterror_h
#define omrporterror_h


/**
 * @name Generic Errors
 * Generic error codes for modules that do not have their own specific errors.  Where possible it is recommended that all
 * modules that return error codes have their own set
 *
 * @internal OMRPORT_ERROR* range from -1 to -49 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_BASE -1
#define OMRPORT_ERROR_OPFAILED OMRPORT_ERROR_BASE
#define OMRPORT_ERROR_EOF (OMRPORT_ERROR_BASE-1)
#define OMRPORT_ERROR_NOPERMISSION (OMRPORT_ERROR_BASE-2)
#define OMRPORT_ERROR_NOTFOUND (OMRPORT_ERROR_BASE-3)
#define OMRPORT_ERROR_NAMETOOLONG (OMRPORT_ERROR_BASE-4)
#define OMRPORT_ERROR_DISKFULL (OMRPORT_ERROR_BASE-5)
#define OMRPORT_ERROR_EXIST (OMRPORT_ERROR_BASE-6)
#define OMRPORT_ERROR_NOTEXIST (OMRPORT_ERROR_BASE-7)
#define OMRPORT_ERROR_SYSTEMFULL (OMRPORT_ERROR_BASE-8)
#define OMRPORT_ERROR_NOENT (OMRPORT_ERROR_BASE-9)
#define OMRPORT_ERROR_DIRECTORY (OMRPORT_ERROR_BASE-10)
#define OMRPORT_ERROR_NOTDIRECTORY (OMRPORT_ERROR_BASE-11)
#define OMRPORT_ERROR_LOOP (OMRPORT_ERROR_BASE-12)
#define OMRPORT_ERROR_BADF (OMRPORT_ERROR_BASE-13)
#define OMRPORT_ERROR_WOULDBLOCK (OMRPORT_ERROR_BASE-14)
#define OMRPORT_ERROR_INVALID (OMRPORT_ERROR_BASE-15)
#define OMRPORT_ERROR_FILE_LOCK_VIOLATION (OMRPORT_ERROR_BASE-16)
#define OMRPORT_ERROR_INVALID_HANDLE (OMRPORT_ERROR_BASE-17)
#define OMRPORT_ERROR_NOT_SUPPORTED_ON_THIS_PLATFORM (OMRPORT_ERROR_BASE-18)
#define OMRPORT_ERROR_INVALID_ARGUMENTS (OMRPORT_ERROR_BASE-19)
/** @} */

/**
 * @name Port Library startup failure code
 * Failures related to the initialization and startup of the port library.
 *
 * @internal OMRPORT_ERROR_STARTUP* range from -50 to -99 to avoid overlap
 * @{
 */
#define OMRPORT_ERROR_STARTUP_BASE -50
#define OMRPORT_ERROR_STARTUP_THREAD (OMRPORT_ERROR_STARTUP_BASE)
#define OMRPORT_ERROR_STARTUP_MEM (OMRPORT_ERROR_STARTUP_BASE -1)
#define OMRPORT_ERROR_STARTUP_TLS (OMRPORT_ERROR_STARTUP_BASE -2)
#define OMRPORT_ERROR_STARTUP_TLS_ALLOC (OMRPORT_ERROR_STARTUP_BASE -3)
#define OMRPORT_ERROR_STARTUP_TLS_MUTEX (OMRPORT_ERROR_STARTUP_BASE -4)
#define OMRPORT_ERROR_STARTUP_CPU (OMRPORT_ERROR_STARTUP_BASE -5)
#define OMRPORT_ERROR_STARTUP_VMEM (OMRPORT_ERROR_STARTUP_BASE -6)
#define OMRPORT_ERROR_STARTUP_FILE (OMRPORT_ERROR_STARTUP_BASE -7)
#define OMRPORT_ERROR_STARTUP_TTY (OMRPORT_ERROR_STARTUP_BASE -8)
#define OMRPORT_ERROR_STARTUP_TTY_HANDLE (OMRPORT_ERROR_STARTUP_BASE -9)
#define OMRPORT_ERROR_STARTUP_TTY_CONSOLE (OMRPORT_ERROR_STARTUP_BASE -10)
#define OMRPORT_ERROR_STARTUP_MMAP (OMRPORT_ERROR_STARTUP_BASE -11)
#define OMRPORT_ERROR_STARTUP_NLS (OMRPORT_ERROR_STARTUP_BASE -12)
#define OMRPORT_ERROR_STARTUP_TIME (OMRPORT_ERROR_STARTUP_BASE -13)
#define OMRPORT_ERROR_STARTUP_EXIT (OMRPORT_ERROR_STARTUP_BASE -14)
#define OMRPORT_ERROR_STARTUP_SYSINFO (OMRPORT_ERROR_STARTUP_BASE -15)
#define OMRPORT_ERROR_STARTUP_SL (OMRPORT_ERROR_STARTUP_BASE -16)
#define OMRPORT_ERROR_STARTUP_STR (OMRPORT_ERROR_STARTUP_BASE -17)
#define OMRPORT_ERROR_STARTUP_ERROR (OMRPORT_ERROR_STARTUP_BASE -18)
#define OMRPORT_ERROR_STARTUP_SIGNAL (OMRPORT_ERROR_STARTUP_BASE -19)
#define OMRPORT_ERROR_STARTUP_AIX_PROC_ATTR (OMRPORT_ERROR_STARTUP_BASE -20)
#define OMRPORT_ERROR_STARTUP_DUMP (OMRPORT_ERROR_STARTUP_BASE -21)
#define OMRPORT_ERROR_STARTUP_CUDA (OMRPORT_ERROR_STARTUP_BASE -22)

/** @} */

/**
 * File operations system function call errno mappings
 * @internal
 * Errno for following system call functions:
 *  fstat
 * 	fstatfs (on Linux)
 * 	fstatvfs (on AIX)
 *
 * The errors are meant to be a 32 bit integer.
 * The most significant 16 bits will identify the failing function
 * The least significant 16 bits will identify the errno that occured while calling the function
 *
 */
#define OMRPORT_ERROR_FILE_FSTAT_ERROR (-(2<<16))
#define OMRPORT_ERROR_FILE_FSTATFS_ERROR (-(3<<16))
#define OMRPORT_ERROR_FILE_FSTATVFS_ERROR (-(3<<16))

/**
 * @name File Errors
 * Error codes for file operations.
 *
 * @internal OMRPORT_ERROR_FILE* range from -100 to -149 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_FILE_BASE -100
#define OMRPORT_ERROR_FILE_OPFAILED (OMRPORT_ERROR_FILE_BASE)
#define OMRPORT_ERROR_FILE_EOF (OMRPORT_ERROR_FILE_BASE-1)
#define OMRPORT_ERROR_FILE_NOPERMISSION (OMRPORT_ERROR_FILE_BASE-2)
#define OMRPORT_ERROR_FILE_NOTFOUND (OMRPORT_ERROR_FILE_BASE-3)
#define OMRPORT_ERROR_FILE_NAMETOOLONG (OMRPORT_ERROR_FILE_BASE-4)
#define OMRPORT_ERROR_FILE_DISKFULL (OMRPORT_ERROR_FILE_BASE-5)
#define OMRPORT_ERROR_FILE_EXIST (OMRPORT_ERROR_FILE_BASE-6)
#define OMRPORT_ERROR_FILE_SYSTEMFULL (OMRPORT_ERROR_FILE_BASE-7)
#define OMRPORT_ERROR_FILE_NOENT (OMRPORT_ERROR_FILE_BASE-8)
#define OMRPORT_ERROR_FILE_NOTDIR (OMRPORT_ERROR_FILE_BASE-9)
#define OMRPORT_ERROR_FILE_LOOP (OMRPORT_ERROR_FILE_BASE-10)
#define OMRPORT_ERROR_FILE_BADF (OMRPORT_ERROR_FILE_BASE-11)
#define OMRPORT_ERROR_FILE_WOULDBLOCK (OMRPORT_ERROR_FILE_BASE-12)
#define OMRPORT_ERROR_FILE_INVAL (OMRPORT_ERROR_FILE_BASE-13)
#define OMRPORT_ERROR_FILE_LOCK_NOREADWRITE (OMRPORT_ERROR_FILE_BASE-14)
#define OMRPORT_ERROR_FILE_LOCK_NOWAITNOWAIT (OMRPORT_ERROR_FILE_BASE-15)
#define OMRPORT_ERROR_FILE_LOCK_BADLOCK (OMRPORT_ERROR_FILE_BASE-16)
#define OMRPORT_ERROR_FILE_UNLOCK_BADUNLOCK (OMRPORT_ERROR_FILE_BASE-17)
#define OMRPORT_ERROR_FILE_INTERRUPTED (OMRPORT_ERROR_FILE_BASE-18)
#define OMRPORT_ERROR_FILE_ISDIR (OMRPORT_ERROR_FILE_BASE-19)
#define OMRPORT_ERROR_FILE_PROCESS_MAX_OPEN (OMRPORT_ERROR_FILE_BASE-20)
#define OMRPORT_ERROR_FILE_XIO (OMRPORT_ERROR_FILE_BASE-21)
#define OMRPORT_ERROR_FILE_ROFS (OMRPORT_ERROR_FILE_BASE-22)
#define OMRPORT_ERROR_FILE_LOCK_EDEADLK (OMRPORT_ERROR_FILE_BASE-23)
#define OMRPORT_ERROR_FILE_EAGAIN (OMRPORT_ERROR_FILE_BASE-24)
#define OMRPORT_ERROR_FILE_EFAULT (OMRPORT_ERROR_FILE_BASE-25)
#define OMRPORT_ERROR_FILE_EINTR (OMRPORT_ERROR_FILE_BASE-26)
#define OMRPORT_ERROR_FILE_IO (OMRPORT_ERROR_FILE_BASE-27)
#define OMRPORT_ERROR_FILE_OVERFLOW (OMRPORT_ERROR_FILE_BASE-28)
#define OMRPORT_ERROR_FILE_SPIPE (OMRPORT_ERROR_FILE_BASE-29)
#define OMRPORT_ERROR_FILE_FSTAT_FAILED (OMRPORT_ERROR_FILE_BASE-30)
#define OMRPORT_ERROR_FILE_OPERATION_ABORTED (OMRPORT_ERROR_FILE_BASE-31)
#define OMRPORT_ERROR_FILE_NOT_ENOUGH_QUOTA (OMRPORT_ERROR_FILE_BASE-32)
#define OMRPORT_ERROR_FILE_INSUFFICIENT_BUFFER (OMRPORT_ERROR_FILE_BASE-33)
#define OMRPORT_ERROR_FILE_HANDLE_EOF (OMRPORT_ERROR_FILE_BASE-34)
#define OMRPORT_ERROR_FILE_BROKEN_PIPE (OMRPORT_ERROR_FILE_BASE-35)
#define OMRPORT_ERROR_FILE_MORE_DATA (OMRPORT_ERROR_FILE_BASE-36)
#define OMRPORT_ERROR_FILE_INVALID_PARAMETER (OMRPORT_ERROR_FILE_BASE-37)
#define OMRPORT_ERROR_FILE_IO_PENDING (OMRPORT_ERROR_FILE_BASE-38)
#define OMRPORT_ERROR_FILE_READ_NO_BYTES_READ (OMRPORT_ERROR_FILE_BASE-39)
#define OMRPORT_ERROR_FILE_FAILED_TO_ALLOCATE_TLS (OMRPORT_ERROR_FILE_BASE-40)
#define OMRPORT_ERROR_FILE_TOO_MANY_OPEN_FILES (OMRPORT_ERROR_FILE_BASE-41)


/** @} */

/**
 * @name Memory Mapping Errors
 * Error codes for file operations.
 *
 * @internal OMRPORT_ERROR_MMAP* range from -150 to -199 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_MMAP_BASE -150
#define OMRPORT_ERROR_MMAP_MAP_FILE_INVALIDFILE (OMRPORT_ERROR_MMAP_BASE)
#define OMRPORT_ERROR_MMAP_MAP_FILE_UNSUPPORTEDWRITE (OMRPORT_ERROR_MMAP_BASE-1)
#define OMRPORT_ERROR_MMAP_MAP_FILE_INVALIDFLAGS (OMRPORT_ERROR_MMAP_BASE-2)
#define OMRPORT_ERROR_MMAP_MAP_FILE_MALLOCFAILED (OMRPORT_ERROR_MMAP_BASE-3)
#define OMRPORT_ERROR_MMAP_MAP_FILE_CREATEMAPPINGOBJECTFAILED (OMRPORT_ERROR_MMAP_BASE-4)
#define OMRPORT_ERROR_MMAP_MAP_FILE_MAPPINGFAILED (OMRPORT_ERROR_MMAP_BASE-5)
#define OMRPORT_ERROR_MMAP_MSYNC_INVALIDFLAGS (OMRPORT_ERROR_MMAP_BASE-6)
#define OMRPORT_ERROR_MMAP_MSYNC_FAILED (OMRPORT_ERROR_MMAP_BASE-7)
#define OMRPORT_ERROR_MMAP_MAP_FILE_STATFAILED (OMRPORT_ERROR_MMAP_BASE-8)
/** @} */

/**
 * @name memory protection errors
 * Error codes for file operations.
 *
 * @internal OMRPORT_ERROR_MMAP* range from -200 to -249 avoid overlap
 * @{
 */
#define OMRPORT_PAGE_PROTECT_BASE -200
#define OMRPORT_PAGE_PROTECT_FAILED (OMRPORT_PAGE_PROTECT_BASE)
/** @} */

/**
 * @name vmem Errors
 * Error codes for virtual memory operations.
 *
 * @internal OMRPORT_ERROR_VMEM* range from -250 to -299 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_VMEM_BASE -250
#define OMRPORT_ERROR_VMEM_OPFAILED (OMRPORT_ERROR_VMEM_BASE)
#define OMRPORT_ERROR_VMEM_INSUFFICENT_RESOURCES (OMRPORT_ERROR_VMEM_BASE -1)
#define OMRPORT_ERROR_VMEM_INVALID_PARAMS (OMRPORT_ERROR_VMEM_BASE -2)
#define OMRPORT_ERROR_VMEM_NOT_SUPPORTED (OMRPORT_ERROR_VMEM_BASE -3)

/** @} */

/**
 * @name signal Errors
 * Error codes for signal memory operations.
 *
 * @internal OMRPORT_ERROR_SIG* range from -300 to -349 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_SIG_BASE -300
#define OMRPORT_ERROR_SIG_OPFAILED (OMRPORT_ERROR_VMEM_BASE)
/** @} */

#define OMRPORT_ERROR_SYSTEM_CALL_ERRNO_MASK 0xffff0000
#define OMRPORT_ERROR_SYSTEM_CALL_CODE_SHIFT 16

/**
 * Miscellaneous system function call errno mappings
 * @internal
 * Errno for following system call functions:
 * 	getgroups
 *
 * The errors are meant to be a 32 bit integer.
 * The most significant 16 bits will identify the failing function
 * The least significant 16 bits will identify the errno that occured while calling the function
 *
 */
#define OMRPORT_ERROR_SYSINFO_GETGROUPSSIZE_ERROR (-(2<<16))
#define OMRPORT_ERROR_SYSINFO_GETGROUPS_ERROR (-(3<<16))

/**
 * @name sysinfo Errors
 * Error codes for sysinfo operations.
 *
 * @internal OMRPORT_ERROR_SYSINFO* range from -350 to -399 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_SYSINFO_BASE -350
#define OMRPORT_ERROR_SYSINFO_OPFAILED (OMRPORT_ERROR_SYSINFO_BASE)
#define OMRPORT_ERROR_SYSINFO_ENV_INIT_CRASHED_COPYING_BUFFER (OMRPORT_ERROR_SYSINFO_BASE-1)
#define OMRPORT_ERROR_SYSINFO_GET_STATS_FAILED (OMRPORT_ERROR_SYSINFO_BASE-2)
#define OMRPORT_ERROR_SYSINFO_INVALID_TIME (OMRPORT_ERROR_SYSINFO_BASE-3)
#define OMRPORT_ERROR_SYSINFO_QUERY_SETUP_FAILED (OMRPORT_ERROR_SYSINFO_BASE-4)
#define OMRPORT_ERROR_SYSINFO_NOT_SUPPORTED (OMRPORT_ERROR_SYSINFO_BASE-5)
#define OMRPORT_ERROR_SYSINFO_INSUFFICIENT_PRIVILEGE (OMRPORT_ERROR_SYSINFO_BASE-6)
#define OMRPORT_ERROR_SYSINFO_NULL_OBJECT_RECEIVED (OMRPORT_ERROR_SYSINFO_BASE-7)
#define OMRPORT_ERROR_SYSINFO_ERROR_READING_MEMORY_INFO (OMRPORT_ERROR_SYSINFO_BASE-8)
#define OMRPORT_ERROR_SYSINFO_PARAM_HAS_INVALID_RANGE (OMRPORT_ERROR_SYSINFO_BASE-9)
#define OMRPORT_ERROR_SYSINFO_ERROR_READING_PROCESSOR_INFO (OMRPORT_ERROR_SYSINFO_BASE-10)
#define OMRPORT_ERROR_SYSINFO_MEMORY_ALLOC_FAILED (OMRPORT_ERROR_SYSINFO_BASE-11)
#define OMRPORT_ERROR_SYSINFO_UNEXPECTED_PROCESSOR_COUNT (OMRPORT_ERROR_SYSINFO_BASE-12)
#define OMRPORT_ERROR_SYSINFO_ERROR_EINVAL (OMRPORT_ERROR_SYSINFO_BASE-13)
#define OMRPORT_ERROR_SYSINFO_ERROR_EFAULT (OMRPORT_ERROR_SYSINFO_BASE-14)
#define OMRPORT_ERROR_SYSINFO_PROCESSOR_COUNT_UNSTABLE (OMRPORT_ERROR_SYSINFO_BASE-15)
#define OMRPORT_ERROR_SYSINFO_GET_OPEN_FILES_NOT_SUPPORTED (OMRPORT_ERROR_SYSINFO_BASE-16)
#define OMRPORT_ERROR_SYSINFO_CGROUP_UNSUPPORTED_PLATFORM (OMRPORT_ERROR_SYSINFO_BASE-17)
#define OMRPORT_ERROR_SYSINFO_PROCESS_CGROUP_FILE_FOPEN_FAILED (OMRPORT_ERROR_SYSINFO_BASE-18)
#define OMRPORT_ERROR_SYSINFO_PROCESS_CGROUP_FILE_READ_FAILED (OMRPORT_ERROR_SYSINFO_BASE-19)
#define OMRPORT_ERROR_SYSINFO_SYS_FS_CGROUP_STATFS_FAILED (OMRPORT_ERROR_SYSINFO_BASE-20)
#define OMRPORT_ERROR_SYSINFO_SYS_FS_CGROUP_TMPFS_NOT_MOUNTED (OMRPORT_ERROR_SYSINFO_BASE-21)
#define OMRPORT_ERROR_SYSINFO_CGROUP_SUBSYSTEM_UNAVAILABLE (OMRPORT_ERROR_SYSINFO_BASE-22)
#define OMRPORT_ERROR_SYSINFO_CGROUP_NAME_NOT_AVAILABLE (OMRPORT_ERROR_SYSINFO_BASE-23)
#define OMRPORT_ERROR_SYSINFO_CGROUP_SUBSYSTEM_FILE_FOPEN_FAILED (OMRPORT_ERROR_SYSINFO_BASE-24)
#define OMRPORT_ERROR_SYSINFO_CGROUP_MEMLIMIT_NOT_SET (OMRPORT_ERROR_SYSINFO_BASE-25)
#define OMRPORT_ERROR_SYSINFO_CGROUP_SUBSYSTEM_FILE_INVALID_VALUE (OMRPORT_ERROR_SYSINFO_BASE-26)
#define OMRPORT_ERROR_SYSINFO_CGROUP_SUBSYSTEM_METRIC_NOT_AVAILABLE (OMRPORT_ERROR_SYSINFO_BASE-27)

/**
 * @name Port library initialization return codes
 * Reasons for failure to initialize port library
 *
 * @internal OMRPORT_ERROR_STRING_* range from -400 to -449 avoid overlap
 */

/* default value */
#define OMRPORT_ERROR_INIT_OMR_FAIL_BASE -400
#define OMRPORT_ERROR_INIT_OMR_WRONG_SIZE (OMRPORT_ERROR_INIT_OMR_FAIL_BASE)

/** @} */

/**
 * @name omrstr Errors
 * Error code returned by the string processing API
 *
 * @internal OMRPORT_ERROR_STRING_* range from -450 to -499 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_STRING_BASE -450
#define OMRPORT_ERROR_STRING_ILLEGAL_STRING (OMRPORT_ERROR_STRING_BASE - 0)
#define OMRPORT_ERROR_STRING_BUFFER_TOO_SMALL (OMRPORT_ERROR_STRING_BASE - 1)
#define OMRPORT_ERROR_STRING_ICONV_OPEN_FAILED (OMRPORT_ERROR_STRING_BASE - 2)
#define OMRPORT_ERROR_STRING_UNSUPPORTED_ENCODING (OMRPORT_ERROR_STRING_BASE - 3)
#define OMRPORT_ERROR_STRING_MEM_ALLOCATE_FAILED (OMRPORT_ERROR_STRING_BASE - 4)
/**
 * @}
 */

/**
 * @name OMR Socket API Errors
 * Error code returned by the socket API
 *
 * @internal OMRPORT_ERROR_SOCK_* range from -500 to -549 avoid overlap
 * @{
 */
#define OMRPORT_ERROR_SOCK_BASE -500
#define OMRPORT_ERROR_SOCK_PTB_FAILED (OMRPORT_ERROR_SOCK_BASE - 0)
#define OMRPORT_ERROR_SOCK_SYSTEMFULL (OMRPORT_ERROR_SOCK_BASE - 1)
/**
 * @}
 */

#endif /* omrporterror_h */
