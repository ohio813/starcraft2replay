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

}