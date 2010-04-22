#pragma once

#include "Info.h"
#include "Util.h"
using namespace System;

#include "sc2replay/replay.h"

namespace SC2ReplayNet {

	public ref class Replay
	{
	public:
		explicit Replay(System::String^ file)
		{
			std::string filename;
			MarshalString(file, filename);
			replay = new sc2replay::Replay(filename);
		}

		const Info^ getInfo()
		{
			const Info^ retval = gcnew Info(&replay->getInfo());
			return retval;
		}

		sc2replay::off_t getImageSize() {
			return replay->getImageSize();
		}
	private:
		sc2replay::Replay *replay;
	};
}