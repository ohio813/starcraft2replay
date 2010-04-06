#include <iostream>
#include <cstdlib>

#include "sc2replay/replay.h"
#include "sc2replay/info.h"
#include "sc2replay/messageevents.h"

namespace sc = sc2replay;

int main( int argc, char** argv )
{
  if ( argc != 2 )
    return EXIT_SUCCESS;
  
  std::string replayName = argv[1];
  sc::Replay replay( replayName );
  
  if ( !replay.isValid() )
  {
    std::cerr << "Replay file does not exists or is invalid." << std::endl;
    std::cerr << "If you are using libmpq (default) this may randomly happen. ";
    std::cerr << "Try to install StormLib (http://www.zezula.net/en/mpq/stormlib.html) ";
    std::cerr << "and use the CMake option -DBUILD_LIBMPQ=OFF" << std::endl;
    return EXIT_FAILURE;
  }
  
  const sc::Info&          info = replay.getInfo();
  const sc::MessageEvents& mess = replay.getMessageEvents();
  
  std::cout << "Number of slots:           " << (unsigned int)info.getNumberOfSlots() << std::endl;
  std::cout << "Number of players:         " << (unsigned int)info.getNumberOfPlayers() << std::endl;
  
  std::cout << "Player names:              ";
  const sc::Info::PlayerNames& playerNames = info.getPlayerNames();
  for (sc::Info::PlayerNames::const_iterator it = playerNames.begin(); it!=playerNames.end(); ++it )
  {
    if ( it!=playerNames.begin() )
      std::cout << ", ";
    std::cout << *it;
  }
  std::cout << std::endl;
  
  std::cout << "Map filename:              " << info.getMapFilename() << std::endl;
  std::cout << "Map name:                  " << info.getMapName() << std::endl;
  std::cout << "Game speed:                " << info.getSpeed() << std::endl;
  std::cout << "Alliance locked:           " << info.getAllianceLocked() << std::endl;
  std::cout << "Number of player displays: " << (unsigned int)info.getNumberOfPlayerDisplays() << std::endl;
  std::cout << "Player display:            ";
  const sc::Info::PlayerDisplays& playerDisplays = info.getPlayerDisplays();
  for (sc::Info::PlayerDisplays::const_iterator it = playerDisplays.begin(); it!=playerDisplays.end(); ++it )
  {
    if ( it!=playerDisplays.begin() )
      std::cout << ", ";
    std::cout << "[ " << it->name << " " << it->race << " " << it->color << " ]";
  }
  std::cout << std::endl;
  
  std::cout << "Blinks:" << std::endl;
  const sc::MessageEvents::Blinks& blinks = mess.getBlinks();
  for ( sc::MessageEvents::Blinks::const_iterator it = blinks.begin(); it!=blinks.end(); ++it )
    std::cout << "  [ " << it->timestamp << " " << (unsigned int)it->player << " " << it->x << " " << it->y << " ]" << std::endl;
  std::cout << std::endl;
  
  std::cout << "Messages:" << std::endl;
  const sc::MessageEvents::Messages& messages = mess.getMessages();
  for ( sc::MessageEvents::Messages::const_iterator it = messages.begin(); it!=messages.end(); ++it )
    std::cout << "  [ " << it->timestamp << " " << (unsigned int)it->player << " " << it->type << " " << it->text << " ]" << std::endl;
  std::cout << std::endl;
  
  std::cout << std::endl << "--- Game events ---" << std::endl;
  const sc::GameEvents& gameEvents = replay.getGameEvents();
  sc::GameEvents::const_iterator it = gameEvents.begin();
  for (; it != gameEvents.end(); ++it )
  {
     switch ( (*it)->code )
      {
        case sc::INITIALIZATION_SPAWN:
        {
          std::cout << "[INITIALIZATION_SPAWN player:" << (int)(*it)->player << "]" << std::endl;
        } break;
        
        case sc::INITIALIZATION_START:
        {
          std::cout << "[INITIALIZATION_START]" << std::endl;
        } break;
        
        case sc::ACTION_QUIT:
        {
          std::cout << "[ACTION_QUIT]" << std::endl;
        } break;
        
        case sc::ACTION_ABILITY:
        {
          std::cout << "[ACTION_ABILITY]" << std::endl;
        } break;
        
        case sc::ACTION_SEND_RESOURCE:
        {
          std::cout << "[ACTION_SEND_RESOURCE]" << std::endl;
        } break;
        
        case sc::ACTION_SELECTION:
        {
          std::cout << "[ACTION_SELECTION]" << std::endl;
        } break;
        
        case sc::ACTION_USE_HOTKEY:
        {
          std::cout << "[ACTION_USE_HOTKEY]" << std::endl;
        } break;
        
        case sc::ACTION_UPDATE_HOTKEY:
        {
          std::cout << "[ACTION_UPDATE_HOTKEY]" << std::endl;
        } break;
        
        case sc::REPLAY_MOVE_CAMERA:
        {
          std::cout << "[REPLAY_MOVE_CAMERA]" << std::endl;
        } break;
        
        case sc::INACTION_SYNCHRONIZATION:
        {
          std::cout << "[INACTION_SYNCHRONIZATION]" << std::endl;
        } break;
        
        case sc::INACTION_SEND_REQUEST:
        {
          std::cout << "[INACTION_SEND_REQUEST]" << std::endl;
        } break;
        
        case sc::INACTION_CANCEL_REQUEST:
        {
          std::cout << "[INACTION_CANCEL_REQUEST]" << std::endl;
        } break;
        
        case sc::SYSTEM_SYNCHRONIZATION:
        {
          std::cout << "[SYSTEM_SYNCHRONIZATION]" << std::endl;
        } break;
      }
  }
  
  return EXIT_SUCCESS;
}