#include "Util.h"

namespace SC2ReplayNet {

	void MarshalString( String ^ s, std::string& os ) {
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
}