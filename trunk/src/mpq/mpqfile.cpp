#include "mpq/mpqfile.h"

namespace SC2Replay
{
	MPQFile::MPQFile(FilePtr file)
	{
		FileSize dataRead;
		_File = file;

#ifdef BUILD_LIBMPQ
		libmpq__file_unpacked_size(_File->archive, _File->fileNumber, &_FileSize);
#else // StormLib
		_FileSize = SFileGetFileSize(_File, 0);
#endif

		_Contents = new BufferType[_FileSize];

#ifdef BUILD_LIBMPQ
		libmpq__file_read(_File->archive, _File->fileNumber, _Contents, size, &dataRead);
#else // StormLib
		SFileReadFile(_File, _Contents, _FileSize, &dataRead, 0);
#endif

		if(_FileSize == dataRead)
		{
			//Success
		}else
		{
			//Fail?
		}
	}

	MPQFile::~MPQFile()
	{
#ifdef BUILD_LIBMPQ
		libmpq__file_unpacked_size(_File->archive, _File->fileNumber, &_FileSize);
#else // StormLib
		SFileCloseFile(_File);
#endif
		
		delete[] _Contents;
	}

	FileSize MPQFile::getFileSize() const
	{
		return _FileSize;
	}

	const BufferType *MPQFile::getContents() const
	{
		return _Contents;
	}
}