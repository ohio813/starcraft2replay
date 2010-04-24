#pragma once

using namespace System;
using namespace System::Collections::Generic;

#include <string>
#include <vector>

namespace SC2ReplayNet {
	void MarshalString( String^ s, std::string& os );

	template <class S, class T> void MarshalListToVector( List<S>^ v, std::vector<T>& ov );
	template <class S, class T> void MarshalVectorToList( std::vector<S>& ov, List<T>^ v );
};