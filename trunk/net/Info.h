#pragma once

using namespace System;

#include "sc2replay/info.h"

namespace SC2ReplayNet {
	public ref class Info
	{
	public:
		Info(const sc2replay::Info *inf) {
			info = inf;
		}

		String^ getFilename() {
			return gcnew String(info->getMapName().c_str());
		}
	private:
		const sc2replay::Info *info;
	};
}