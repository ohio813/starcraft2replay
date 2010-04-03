#include "sc2map/Map.h"

namespace SC2Replay
{
	Map::Map(const std::string &archiveFilename) : MPQArchive(archiveFilename)
	{
		MPQFile *map_file;

		//
		// (listfile)
		//
		map_file = openFile("(listfile)");
		//TODO: process contents
		delete map_file;

		//
		// (listfile)
		//
		map_file = openFile("Preload.xml");
		//TODO: process contents
		delete map_file;
	}

	Map::~Map(void)
	{
	}
}
