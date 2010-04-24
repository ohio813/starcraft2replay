#include "Util.h"

namespace SC2ReplayNet {

	void MarshalString( String ^ s, std::string& os ) {
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	template <class S, class T> void MarshalListToVector( List<S>^ v, std::vector<T>& ov )
	{
	}

	template <class S, class T> void MarshalVectorToList( std::vector<S>& ov, List<T>^ v )
	{
		for(std::vector<S>::iterator it = ov.begin(); it < ov.end(); it++)
		{
			v->Add(gcnew S(it));
		}
	}

	void MarshalVectorToList<std::string, String^>( std::vector<std::string> ov, List<String^>^ v )
	{
		{
			v->Add(gcnew String(it->c_str()));
		}
	}
}