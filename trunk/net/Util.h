#pragma once

using namespace System;

#include <string>

namespace SC2ReplayNet {
	void MarshalString( String ^ s, std::string& os );
};