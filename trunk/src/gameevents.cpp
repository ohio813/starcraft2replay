#include "sc2replay/gameevents.h"

#include <fstream>

namespace sc2replay
{

GameEvents::GameEvents()
  : buffer_    ( 0 ),
    bufferSize_( 0 )
{
}

GameEvents::~GameEvents()
{
  delete [] buffer_;
}

void GameEvents::load( const uint8_t* buffer, unsigned long size )
{
  buffer_ = new uint8_t[size];
  std::copy( buffer, buffer+size, buffer_ );
  bufferSize_ = size;
  
  parse();
}

off_t GameEvents::getBufferSize() const
{
  return bufferSize_;
}

uint8_t* GameEvents::getBuffer() const
{
  return buffer_;
}

void GameEvents::exportDump( const std::string& filename ) const
{
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (const char*)buffer_, bufferSize_ );
  file.close();
}

GameEvents::EventList::const_iterator GameEvents::begin() const
{
  return events_.begin();
}

GameEvents::EventList::const_iterator GameEvents::end() const
{
  return events_.end();
}

size_t GameEvents::size() const
{
  return events_.size();
}

//
// PARSER INTERFACE
//

void GameEvents::parse()
{
  off_t offset = 0;
  
  while ( offset < bufferSize_ )
  {
    GameEvent e;
    parseHeader( offset, e );
    
    switch ( e.code )
    {
      case INITIALIZATION_SPAWN:
      {
        parseSpawnEvent( offset, e );
        events_.push_back( new InitializationSpawn(e) );
      } break;
      case INITIALIZATION_START:
      {
        parseStartEvent( offset, e );
        events_.push_back( new InitializationStart(e) );
      } break;
      case ACTION_QUIT:
      {
        return; // Not implemented at the moment
      } break;
      case ACTION_ABILITY:
      {
        return; // Not implemented at the moment
      } break;
      case ACTION_SEND_RESOURCE:
      {
        return; // Not implemented at the moment
      } break;
      case ACTION_SELECTION:
      {
        return; // Not implemented at the moment
      } break;
      case ACTION_USE_HOTKEY:
      {
        return; // Not implemented at the moment
      } break;
      case ACTION_UPDATE_HOTKEY:
      {
        return; // Not implemented at the moment
      } break;
      case REPLAY_MOVE_CAMERA:
      {
        return; // Not implemented at the moment
      } break;
      case INACTION_SYNCHRONIZATION:
      {
        return; // Not implemented at the moment
      } break;
      case INACTION_SEND_REQUEST:
      {
        return; // Not implemented at the moment
      } break;
      case INACTION_CANCEL_REQUEST:
      {
        return; // Not implemented at the moment
      } break;
      case SYSTEM_SYNCHRONIZATION:
      {
        return; // Not implemented at the moment
      } break;
    }
  }
}

void GameEvents::parseHeader( off_t& offset, GameEvent& event )
{
  // --- Timestamp
  timestamp_t timestamp = 0;
  if ( buffer_[offset] & 0x03 ) // 2 bytes timestamp
  {
    timestamp = (buffer_[offset] >> 2) << 8 + buffer_[offset];
    offset += 2;
  }
  else  // 1 byte timestamp
  {
    timestamp = buffer_[offset] >> 2;
    offset += 1;
  }
  event.timestamp = timestamp;
  
  // --- Type
  event.type = static_cast<EventType>((buffer_[offset] & 0xE0) >> 5);
  
  // --- Flag
  event.flag = static_cast<EventFlag>((buffer_[offset] & 0x10) >> 4);
  
  // --- Player
  event.player = static_cast<player_t>(buffer_[offset] & 0x0F);
  
  offset += 1;
  
  // --- Code
  event.code = static_cast<EventCode>(buffer_[offset]);
  offset += 1;
}

void GameEvents::parseSpawnEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseStartEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseQuitEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseAbilityEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseSendResourceEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseSelectionEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseUseHotkey( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseUpdateHotkey( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseCameraHotkey( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseSyncEvent( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseSendRequest( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseCancelRequest( off_t& offset, GameEvent& event )
{
}

void GameEvents::parseSystemSync( off_t& offset, GameEvent& event )
{
}

}