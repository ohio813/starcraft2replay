#ifndef MPQ_FILE_H
#define MPQ_FILE_H

#include "mpqlib.h"

namespace SC2Replay
{
	class MPQFile
	{
	public:
		MPQFile(FilePtr file);
		~MPQFile();

		FileSize getFileSize() const;
		const BufferType *getContents() const;
	private:
		MPQFile();

		FilePtr _File;
		FileSize _FileSize;
		BufferType *_Contents;
	};
}

#endif