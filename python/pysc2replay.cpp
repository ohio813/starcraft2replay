#include "sc2replay/replay.h"
#include "sc2replay/gameevents.h"
#include "sc2replay/info.h"
#include "sc2replay/messageevents.h"
#include "sc2replay/syncevents.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;
using namespace sc2replay;

BOOST_PYTHON_MODULE(pysc2replay)
{
  /*
   * Containers
   */
  class_<std::vector<std::string> >("std_vector_string")
    .def( vector_indexing_suite<std::vector<std::string> >() )
  ;
  
  /*
   * Replay.GameEvents
   */
  class_<GameEvents>( "GameEvents" )
  ;
  
  /*
   * Replay.GameEvents
   */
  class_<MessageEvents>( "MessageEvents" )
  ;
  
  /*
   * Replay.GameEvents
   */
  class_<SyncEvents>( "SyncEvents" )
  ;
  
  /*
   * Replay.Info
   */
  class_<PlayerDisplay>("PlayerDisplay")
    .def_readonly( "name",  &PlayerDisplay::name  )
    .def_readonly( "race",  &PlayerDisplay::race  )
    .def_readonly( "color", &PlayerDisplay::color )
  ;
   
  class_<std::vector<PlayerDisplay> >("std_vector_player_display")
    .def( vector_indexing_suite<std::vector<PlayerDisplay> >() )
  ;
  
  class_<Info>( "Info" )
    .def( "getPlayerNames",            &Info::getPlayerNames            , return_value_policy<copy_const_reference>() )
    .def( "getNumberOfPlayers",        &Info::getNumberOfPlayers        )
    .def( "getNumberOfSlots",          &Info::getNumberOfSlots          )
    .def( "getMapFilename",            &Info::getMapFilename            , return_value_policy<copy_const_reference>() )
    .def( "getMapName",                &Info::getMapName                , return_value_policy<copy_const_reference>() )
    .def( "getSpeed",                  &Info::getSpeed                  )
    .def( "getAllianceLocked",         &Info::getAllianceLocked         )
    .def( "getNumberOfPlayerDisplays", &Info::getNumberOfPlayerDisplays )
    .def( "getPlayerDisplays",         &Info::getPlayerDisplays         , return_value_policy<copy_const_reference>() )
  ;
  
  /*
   * Replay Binding
   */
  class_<Replay>( "Replay", init<std::string>() )
    .def( "load",             &Replay::load             )
    .def( "getInfo",          &Replay::getInfo          , return_value_policy<copy_const_reference>() )
    .def( "getGameEvents",    &Replay::getGameEvents    , return_value_policy<copy_const_reference>() )
    .def( "getMessageEvents", &Replay::getMessageEvents , return_value_policy<copy_const_reference>() )
    .def( "getSyncEvents",    &Replay::getSyncEvents    , return_value_policy<copy_const_reference>() )
    .def( "getFilename",      &Replay::getFilename      , return_value_policy<copy_const_reference>() )
    .def( "exportImage",      &Replay::exportImage      )
  ;
}