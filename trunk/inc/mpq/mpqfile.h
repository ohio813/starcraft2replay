#ifndef MPQ_FILE_H
#define MPQ_FILE_H

#include "mpqlib.h"

class MPQFile
{
public:
	MPQFile(FilePtr file);
	~MPQFile();

	void Open();

	FileSize getFileSize() const;
	BufferType *getContents() const;
private:
	MPQFile();

	FilePtr _File;
	FileSize _FileSize;
	BufferType *_Contents;
};

#endif