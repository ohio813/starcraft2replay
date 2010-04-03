#include "sc2replay/replay.h"

#include <fstream>

namespace SC2Replay
{

	Replay::Replay( const std::string& filename ) : MPQArchive(filename), imageBuffer_(0), isValid_(false)
	{
		MPQFile *replay_file;

		//
		// Replay.Info
		//
		replay_file = openFile("replay.info");
		info_.load(replay_file->getContents(), replay_file->getFileSize());
		delete replay_file;
	  
		//
		// Replay.Game.Events
		//
		replay_file = openFile("replay.game.events");
		gameEvents_.Load(replay_file->getContents(), replay_file->getFileSize());
		delete replay_file;
		
		//
		// Replay.Message.Events
		//
		replay_file = openFile("replay.message.events");
		messageEvents_.load(replay_file->getContents(), replay_file->getFileSize());
		delete replay_file;
		
		//
		// Replay.Sync.Events
		//
		replay_file = openFile("replay.sync.events");
		syncEvents_.load(replay_file->getContents(), replay_file->getFileSize());
		delete replay_file;

		//
		// Replay.Save
		//
		replay_file = openFile("save.jpg");
		imageSize_ = replay_file->getFileSize();
		imageBuffer_ = new uint8_t[imageSize_];
		std::copy(replay_file->getContents(), replay_file->getContents()+imageSize_, imageBuffer_);
		delete replay_file;
	}

	Replay::~Replay()
	{
		delete[] imageBuffer_;
	}

	const Info& Replay::getInfo() const {
		return info_;
	}

	const GameEvents& Replay::getGameEvents() const {
		return gameEvents_;
	}

	const MessageEvents& Replay::getMessageEvents() const {
		return messageEvents_;
	}

	const SyncEvents& Replay::getSyncEvents() const {
		return syncEvents_;
	}

	const std::string& Replay::getFilename() const {
		return filename_;
	}

	const uint8_t* Replay::getImageBuffer() const {
		return imageBuffer_;
	}

	off_t Replay::getImageSize() const {
		return imageSize_;
	}

	bool Replay::isValid() const {
		return isValid_;
	}

	void Replay::exportImage( const std::string& filename ) const
	{
		if(imageBuffer_ == 0)
			return;

		std::ofstream file(filename.c_str(), std::ios::binary);
		file.write((char*)imageBuffer_, imageSize_);
		file.close();
	}
}