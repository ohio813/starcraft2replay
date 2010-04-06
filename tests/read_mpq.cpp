#include <iostream>
#include <cstdlib>

#include "sc2replay/replay.h"
#include "sc2replay/info.h"
#include "sc2replay/messageevents.h"
#include "sc2replay/gameevents.h"
#include "sc2replay/util.h"

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
  std::cout << std::hex;
  for (; it != gameEvents.end(); ++it )
  {
    switch ( (*it)->code )
    {
      case sc::INITIALIZATION_SPAWN:
      {
        const sc::InitializationSpawn* event = dynamic_cast<const sc::InitializationSpawn*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[INITIALIZATION_SPAWN player:" << (int)event->player << "]" << std::endl;
      } break;
      
      case sc::INITIALIZATION_START:
      {
        sc::InitializationStart* event = dynamic_cast<sc::InitializationStart*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[INITIALIZATION_START]" << std::endl;
      } break;
      
      case sc::ACTION_QUIT:
      {
        sc::ActionQuit* event = dynamic_cast<sc::ActionQuit*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[ACTION_QUIT]" << std::endl;
      } break;
      
      case sc::ACTION_ABILITY:
      {
        sc::ActionAbility* event = dynamic_cast<sc::ActionAbility*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[ACTION_ABILITY]" << std::endl;
      } break;
      
      case sc::ACTION_SEND_RESOURCE:
      {
        sc::ActionSendResource* event = dynamic_cast<sc::ActionSendResource*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[ACTION_SEND_RESOURCE]" << std::endl;
      } break;
      
      case sc::ACTION_SELECTION:
      {
        sc::ActionSelection* event = dynamic_cast<sc::ActionSelection*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[ACTION_SELECTION]" << std::endl;
      } break;
      
      case sc::ACTION_USE_HOTKEY0:
      case sc::ACTION_USE_HOTKEY1:
      case sc::ACTION_USE_HOTKEY2:
      case sc::ACTION_USE_HOTKEY3:
      case sc::ACTION_USE_HOTKEY4:
      case sc::ACTION_USE_HOTKEY5:
      case sc::ACTION_USE_HOTKEY6:
      case sc::ACTION_USE_HOTKEY7:
      case sc::ACTION_USE_HOTKEY8:
      case sc::ACTION_USE_HOTKEY9:
      {
        sc::ActionUseHotkey* event = dynamic_cast<sc::ActionUseHotkey*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[ACTION_USE_HOTKEY]" << std::endl;
      } break;
      
      case sc::ACTION_UPDATE_HOTKEY0:
      case sc::ACTION_UPDATE_HOTKEY1:
      case sc::ACTION_UPDATE_HOTKEY2:
      case sc::ACTION_UPDATE_HOTKEY3:
      case sc::ACTION_UPDATE_HOTKEY4:
      case sc::ACTION_UPDATE_HOTKEY5:
      case sc::ACTION_UPDATE_HOTKEY6:
      case sc::ACTION_UPDATE_HOTKEY7:
      case sc::ACTION_UPDATE_HOTKEY8:
      case sc::ACTION_UPDATE_HOTKEY9:
      {
        sc::ActionUpdateHotkey* event = dynamic_cast<sc::ActionUpdateHotkey*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[ACTION_UPDATE_HOTKEY]" << std::endl;
      } break;
      
      case sc::REPLAY_MOVE_CAMERA:
      {
        sc::ReplayMoveCamera* event = dynamic_cast<sc::ReplayMoveCamera*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[REPLAY_MOVE_CAMERA"
                << " p:" << (int)event->player
                << " x:" << event->x
                << " y:" << event->y
                << " h:" << event->horizontal
                << " v:" << event->vertical
                << "]" << std::endl;
      } break;
      
      case sc::INACTION_SYNCHRONIZATION:
      {
        sc::InactionSynchronization* event = dynamic_cast<sc::InactionSynchronization*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[INACTION_SYNCHRONIZATION]" << std::endl;
      } break;
      
      case sc::INACTION_SEND_REQUEST:
      {
        sc::InactionSendRequest* event = dynamic_cast<sc::InactionSendRequest*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[INACTION_SEND_REQUEST]" << std::endl;
      } break;
      
      case sc::INACTION_CANCEL_REQUEST:
      {
        sc::InactionCancelRequest* event = dynamic_cast<sc::InactionCancelRequest*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[INACTION_CANCEL_REQUEST]" << std::endl;
      } break;
      
      case sc::SYSTEM_SYNCHRONIZATION:
      {
        sc::SystemSynchronization* event = dynamic_cast<sc::SystemSynchronization*>(*it);
        std::cout << sc::timestampToString(event->timestamp) << " ";
        std::cout << "[SYSTEM_SYNCHRONIZATION]" << std::endl;
      } break;
    }
  }
  
  return EXIT_SUCCESS;
}