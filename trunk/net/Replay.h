#pragma once

#include "Info.h"
#include "Util.h"
using namespace System;

#include "sc2replay/replay.h"

namespace SC2ReplayNet {

	public ref class Replay
	{
	public:
		explicit Replay(System::String^ filename)
		{
			std::string std_filename;
			MarshalString(filename, std_filename);
			replay = new sc2replay::Replay(std_filename);
		}

	public:
		// Load a starcraft 2 replay file
		//void load( const std::string& filename );
  
	public:
		bool isValid() {
			return replay->isValid();
		}
  
	public:
		// Getters
		const Info^ getInfo() {
			return gcnew Info(&replay->getInfo());
		}

		/*const GameEvents^ getGameEvents() {
			return gcnew GameEvents(&replay->getGameEvents());
		}

		const MessageEvents^ getMessageEvents() {
			return gcnew MessageEvents(&replay->getMessageEvents());
		}

		const SyncEvents^ getSyncEvents() {
			return gcnew SyncEvents(&replay->getSyncEvents());
		}*/

		const String^ getFilename() {
			return gcnew String(replay->getFilename().c_str());
		}

		//const uint8_t* getImageBuffer() const;

		sc2replay::off_t getImageSize() {
			return replay->getImageSize();
		}
  
	public:
		void exportImage(String^ filename) {
			std::string std_filename;
			MarshalString(filename, std_filename);
			replay->exportImage(std_filename);
		}

	private:
		sc2replay::Replay *replay;
	};
}