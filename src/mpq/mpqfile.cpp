#include "mpq/mpqfile.h"

MPQFile::MPQFile(FilePtr file)
{
	_File = file;
	Open();
}

MPQFile::~MPQFile()
{
	delete[] _Contents;
}

FileSize MPQFile::getFileSize() const
{
	return _FileSize;
}

BufferType *MPQFile::getContents() const
{
	return _Contents;
}

void MPQFile::Open()
{
	FileSize dataRead;

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