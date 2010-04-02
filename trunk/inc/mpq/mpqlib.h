#ifndef MPQ_LIB_H
#define MPQ_LIB_H

#include <string>
#include "pstdint.h"

#ifdef BUILD_LIBMPQ
#  include <libmpq/mpq.h>
typedef mpq_archive_s * ArchivePtr;
typedef *struct {
	ArchivePtr archive;
	uint32_t fileNumber;
} FilePtr;
typedef uint8_t BufferType;
typedef libmpq__off_t FileSize;

#else // StormLib
#  include <StormLib/StormLib.h>
typedef HANDLE ArchivePtr;
typedef HANDLE FilePtr;
typedef uint8_t BufferType;
typedef DWORD FileSize;
#endif

#endif