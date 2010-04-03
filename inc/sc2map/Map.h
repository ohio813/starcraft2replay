#pragma once

#include "mpq/mpqarchive.h"

namespace SC2Replay
{
	class Map :
		public MPQArchive
	{
	public:
		Map(const std::string &archiveFilename);
		~Map(void);
	};
}