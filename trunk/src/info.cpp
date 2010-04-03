#include "sc2replay/info.h"

#include <fstream>

namespace sc2replay
{

Info::Info()
  : buffer_    ( 0 ),
    bufferSize_( 0 )
{
  
}

Info::~Info()
{
  delete [] buffer_;
}

void Info::load( const uint8_t* buffer, off_t size )
{
  buffer_  = new uint8_t[size];
  std::copy( buffer, buffer+size, buffer_ );
  bufferSize_ = size;
  
  off_t offset = 0;
  
  // Always 16 ?
  numberOfSlots_ = buffer[offset];
  offset += sizeof(uint8_t);

  for ( unsigned char i=0; i<numberOfSlots_; ++i )
  {
    uint8_t length = buffer[offset];
    offset += sizeof(uint8_t);
    
    if ( length > 0 )
      playerNames_.push_back( std::string( (const char*)(buffer+offset), length ) );
    offset += length*sizeof(uint8_t);
    
    offset += sizeof(uint8_t);  // Padding ?
    offset += sizeof(uint32_t); // Padding ?
  }
  
  // Why do we have an extra offset ? One of the slots have only 4 bytes padding ?
  offset -= sizeof(uint8_t);
  
  // What is this ?
  offset += sizeof(uint8_t);
  offset += sizeof(uint32_t);
  
  // A length and a string, storing what ?
  uint8_t unknownLength1_ = buffer[offset];
  offset += sizeof(uint8_t);
  
  offset += unknownLength1_*sizeof(uint8_t);
  
  // Alliance locked ?
  allianceLocked_ = buffer[offset] & 0x01;
  offset += sizeof(uint8_t);
  
  // A bunch of unknown bytes
  offset += 3 * sizeof(uint8_t);
  
  // Game speed
  speed_ = static_cast<GameSpeed>(buffer[offset] & 0x07);
  offset += sizeof(uint8_t);
  
  // A bunch of unknown bytes
  offset += 9 * sizeof(uint8_t);
  
  // Map filename length
  uint8_t mapFilenameLength = buffer[offset];
  offset += sizeof(uint8_t);
  
  // Map filename string
  mapFilename_ = std::string( (const char*)(buffer+offset), mapFilenameLength );
  offset += mapFilenameLength * sizeof(uint8_t);
  
  /*
  // Big bunch of unknown bytes, often equal between replays
  offset += 92 * sizeof(uint8_t);
  
  // Big bunch of unknown bytes again
  offset += 593 * sizeof(uint8_t);
  offset += sizeof(uint8_t);
  */
  // Temporary hack - skip the unknown variable length chunk
  while ( !(buffer[offset-1]==0x1F && buffer[offset]==0x28)  )
    offset += sizeof(uint8_t);
  
  offset += sizeof(uint8_t);
  
  // 5 structures starting with "s2ma" 0 "USB" ... 40 bytes long
  offset += 5 * 40 * sizeof(uint8_t);
  
  // 5 bytes always here
  offset += 5 * sizeof(uint8_t);
  
  /*
  // No idea :/ can't find the exact length, should be stored in the marker bytes
  //10 0E 02 06 08 01    64 02 06 15    80 24 2F 3F A6 AF 00                                  00 00 00 00
  //20 0C 02 06 08 03 01 64 02 06 15 01 80 24 2C 06 8F B4 00                                  00 00 00 00
  //10 0E 02 06 08 03 02 64 02 06 15 01 80 24 95 B6 1B A2 00                                  00 00 00 00
  //20 0C 02 06 08 01    64 02 06 15 01 81 24 A6 BF E3 22 00                                  00 00 00 00
  //20 2C 00 06 08 01    64 02 06 14 01 80 24 02 05 8F 00 C0 04 82 13 49 00 C0 04 94 B7 9E 32 00 00 00 00
  //               ^^ ^^          ^^ ^^                   ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^
  
  // For now, let's run until we find 4 bytes equals to 0, that sould be just before the name of the map
  uint8_t unknown1 = buffer[offset];
  offset += sizeof(uint8_t);
  
  // if 0x01, then followed by      0x64 0x02 0x06
  // if 0x03, then followed by 0x?? 0x64 0x02 0x06
  if ( unknown1==0x03 )
    offset += sizeof(uint8_t);
  
  // Always 0x64 0x02 0x06 ?
  offset += 3 * sizeof(uint8_t);
  
  uint8_t unknown2 = buffer[offset];
  offset += sizeof(uint8_t);
  
  uint8_t unknown3 = buffer[offset];
  offset += sizeof(uint8_t);
  
  // If 0x15 then short tail, if 0x14 then long tail ?
  if ( unknown2==0x15 && unknown3==0x80 )
    offset += 10 * sizeof(uint8_t);
  else if ( unknown2==0x15 && unknown3==0x01 )
    offset += 11 * sizeof(uint8_t);
  else if ( unknown2==0x14 && unknown3==0x01 )
    offset += 22 * sizeof(uint8_t);
  */
  
  // Temporary hack - skip the unknown variable length chunk
  while ( !( buffer[offset-3] == 0x00 &&
             buffer[offset-2] == 0x00 &&
             buffer[offset-1] == 0x00 &&
             buffer[offset  ] == 0x00 &&
             (buffer[offset+1]>0 || buffer[offset+2]>0) &&
             buffer[offset+3]  > 0x1F) )
    offset += sizeof(uint8_t);
  offset += sizeof(uint8_t);
  
  // Map name length
  uint16_t mapNameLength = (buffer[offset] << 2) + buffer[offset+sizeof(uint8_t)];
  offset+= sizeof(uint16_t);
  
  // Map name
  mapName_ = std::string( (const char*)buffer+offset, mapNameLength );
  offset += mapNameLength * sizeof(uint8_t);
  
  // Always 0 ?
  offset += sizeof(uint8_t);
  
  // Player display count
  numberOfPlayerDisplay_ = buffer[offset];
  offset += sizeof(uint8_t);
  
  // Players displays
  for ( uint8_t i=0; i<numberOfPlayerDisplay_; ++i )
  {
    // Name length
    uint8_t nameLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Name
    std::string name( (const char*)buffer+offset, nameLength );
    offset += nameLength * sizeof(uint8_t);
    
    // Race length
    uint8_t raceLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Race
    std::string race( (const char*)buffer+offset, raceLength );
    offset += raceLength * sizeof(uint8_t);
    
    // Color length
    uint8_t colorLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Color
    std::string color( (const char*)buffer+offset, colorLength );
    offset += colorLength * sizeof(uint8_t);
    
    playerDisplays_.push_back( PlayerDisplay( name, race, color ) );
  }
}

const Info::PlayerNames& Info::getPlayerNames() const
{
  return playerNames_;
}

const uint8_t Info::getNumberOfPlayers() const
{
  return playerNames_.size();
}

const uint8_t Info::getNumberOfSlots() const
{
  return numberOfSlots_;
}

const std::string& Info::getMapFilename() const
{
  return mapFilename_;
}

const std::string& Info::getMapName() const
{
  return mapName_;
}

Info::GameSpeed Info::getSpeed() const
{
  return speed_;
}

bool Info::getAllianceLocked() const
{
  return allianceLocked_;
}

uint8_t Info::getNumberOfPlayerDisplays() const
{
  return numberOfPlayerDisplay_;
}

const Info::PlayerDisplays& Info::getPlayerDisplays() const
{
  return playerDisplays_;
}

off_t Info::getBufferSize() const
{
  return bufferSize_;
}

uint8_t* Info::getBuffer() const
{
  return buffer_;
}

void Info::exportDump( const std::string& filename ) const
{
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (const char*)buffer_, bufferSize_ );
  file.close();
}

}