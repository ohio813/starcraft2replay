#include "mpq/mpqarchive.h"

MPQArchive::MPQArchive(const std::string &archiveFilename)
{
	Load(archiveFilename);
}

MPQArchive::~MPQArchive()
{
	Unload();
}


void MPQArchive::Load(const std::string &archiveFilename)
{
#ifdef BUILD_LIBMPQ
	libmpq__archive_open(&_Archive, archiveFilename.c_str(), -1);
#else // StormLib
	SFileOpenArchive(archiveFilename.c_str(), 0, 0, &_Archive);
#endif
}

void MPQArchive::Unload()
{
#ifdef BUILD_LIBMPQ
	libmpq__archive_close(_Archive);
#else // StormLib
	SFileCloseArchive(_Archive);
#endif
}

MPQFile *MPQArchive::openFile(const std::string &filename)
{
	FilePtr file;
	MPQFile *openedFile;

#ifdef BUILD_LIBMPQ
	libmpq__file_number(_Archive, filename.c_str(), &file->fileNumber);
	file->archive = _Archive;
#else // StormLib
	SFileOpenFileEx(_Archive, filename.c_str(), 0, &file);
#endif

	//TODO: Exception handling
	openedFile = new MPQFile(file);
	return openedFile;
}