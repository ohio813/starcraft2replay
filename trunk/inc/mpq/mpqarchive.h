#ifndef MPQ_ARCHIVE_H
#define MPQ_ARCHIVE_H

#include "mpqlib.h"
#include "mpqfile.h"

class MPQArchive
{
public:
	MPQArchive(const std::string &archiveFilename);
	~MPQArchive();

	MPQFile *openFile(const std::string &filename);

private:
	void Load(const std::string &archive);
	void Unload();

	ArchivePtr _Archive;
};

#endif