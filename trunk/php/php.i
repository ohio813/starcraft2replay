%include "typemaps.i"
%include "stl.i"
%include "phppointers.i"

%rename(__compare) sc2replay::PlayerDisplay::operator==;
%rename(__compare) sc2replay::Message::operator==;
%rename(__compare) sc2replay::Blink::operator==;

/*Typemap: off_t*/
%typemap(in) sc2replay::off_t {
    $1 = (sc2replay::off_t)($input);
}
%typemap(out) sc2replay::off_t {
    /*$result = */RETVAL_LONG($1);
}

/*Typemap: uint8_t*/
%typemap(in) sc2replay::uint8_t {
    $1 = (sc2replay::uint8_t)($input);
}
%typemap(out) sc2replay::uint8_t {
    /*$result = */RETVAL_LONG($1);
}

%module sc2replay
%{
	#include "D:/programming/starcraft2replay/inc/sc2replay/types.h"
	#include "D:/programming/starcraft2replay/inc/sc2replay/gameevents.h"
	#include "D:/programming/starcraft2replay/inc/sc2replay/info.h"
	#include "D:/programming/starcraft2replay/inc/sc2replay/messageevents.h"
	#include "D:/programming/starcraft2replay/inc/sc2replay/syncevents.h"
	#include "D:/programming/starcraft2replay/inc/sc2replay/replay.h"
	
	using namespace sc2replay;
%}

%template(StringVector) std::vector<std::string>;
%template(PlayerDisplayVector) std::vector<sc2replay::PlayerDisplay>;
%template(MessagesVector) std::vector<sc2replay::Message>;
%template(BlinksVector) std::vector<sc2replay::Blink>;

/*NOT WORKING*/
%template(GameEventVector) std::vector<sc2replay::GameEvent*>;
%template(GameEventList) std::list<sc2replay::GameEvent*>;

/*%ignore sc2replay::Replay::exportImage;

%ignore sc2replay::GameEvents::exportDump;
%ignore sc2replay::GameEvents::parseSpawnEvent;
%ignore sc2replay::GameEvents::parseStartEvent;
%ignore sc2replay::GameEvents::parseQuitEvent;
%ignore sc2replay::GameEvents::parseAbilityEvent;
%ignore sc2replay::GameEvents::parseSendResourceEvent;
%ignore sc2replay::GameEvents::parseSelectionEvent;
%ignore sc2replay::GameEvents::parseUseHotkey;
%ignore sc2replay::GameEvents::parseUpdateHotkey;
%ignore sc2replay::GameEvents::parseCameraEvent;
%ignore sc2replay::GameEvents::parseSyncEvent;
%ignore sc2replay::GameEvents::parseSendRequest;
%ignore sc2replay::GameEvents::parseCancelRequest;
%ignore sc2replay::GameEvents::parseSystemSync;*/

%include "D:/programming/starcraft2replay/inc/sc2replay/types.h"
%include "D:/programming/starcraft2replay/inc/sc2replay/gameevents.h"
%include "D:/programming/starcraft2replay/inc/sc2replay/info.h"
%include "D:/programming/starcraft2replay/inc/sc2replay/messageevents.h"
%include "D:/programming/starcraft2replay/inc/sc2replay/syncevents.h"
%include "D:/programming/starcraft2replay/inc/sc2replay/replay.h"


