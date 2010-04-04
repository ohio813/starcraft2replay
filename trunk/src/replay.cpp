#include "sc2replay/replay.h"

#ifdef BUILD_LIBMPQ
#  include <libmpq/mpq.h>
#else // StormLib
#  include <StormLib/StormLib.h>
#endif

#include <fstream>

namespace sc2replay
{

Replay::Replay( const std::string& filename )
  : imageBuffer_(  0    ),
    isValid_    ( false )
{
  load( filename );
}

Replay::~Replay()
{
  delete [] imageBuffer_;
}

void Replay::load( const std::string& filename )
{
  filename_ = filename;
  
#ifdef BUILD_LIBMPQ
  // Initialize libmpq
  // Comment this line if using a newer version of libmpq that removed libmpq__init & libmpq__shutdown
  libmpq__init();
  
  // Open the MPQ archive
  mpq_archive_s* archive;
  int32_t err = libmpq__archive_open( &archive, filename.c_str(), -1 );
  
  if ( err < 0 )
  {
    isValid_ = false;
    return;
  }
  
  uint32_t number;
  off_t    size;
#else // StormLib
  HANDLE archive = 0;
  HANDLE file    = 0;
  DWORD  size    = 0;
  
  bool good = SFileOpenArchive( filename.c_str(), 0, 0, &archive );
  
  if ( !good )
  {
    isValid_ = false;
    return;
  }
#endif

  
  
  uint8_t* buffer;
  
  //
  // Replay.Info
  //
  {
    // Open file and retrieve its size
#ifdef BUILD_LIBMPQ
    libmpq__file_number( archive, "replay.info", &number );
    libmpq__file_unpacked_size( archive, number, &size );
#else // StormLib
    SFileOpenFileEx( archive, "replay.info", 0, &file );
    size = SFileGetFileSize( file, NULL );
#endif

    // Allocate a buffer for file data
    buffer = new uint8_t[size];
    
    // Fill the buffer with the file content
#ifdef BUILD_LIBMPQ
    libmpq__file_read( archive, number, buffer, size, NULL );
#else // StormLib
    SFileReadFile( file, buffer, size, &size, NULL );
    SFileCloseFile( file );
#endif
    
    // Load file
    info_.load( buffer, size );
    
    // Release buffer
    delete [] buffer;
  }
  
  //
  // Replay.Game.Events
  //
  {
    // Open file and retrieve its size
#ifdef BUILD_LIBMPQ
    libmpq__file_number( archive, "replay.game.events", &number );
    libmpq__file_unpacked_size( archive, number, &size );
#else // StormLib
    SFileOpenFileEx( archive, "replay.game.events", 0, &file );
    size = SFileGetFileSize( file, NULL );
#endif

    // Allocate a buffer for file data
    buffer = new uint8_t[size];

    // Fill the buffer with the file content
#ifdef BUILD_LIBMPQ
    libmpq__file_read( archive, number, buffer, size, NULL );
#else // StormLib
    SFileReadFile( file, buffer, size, &size, NULL );
    SFileCloseFile( file );
#endif

    // Load file
    gameEvents_.load( buffer, size );
    
    // Release buffer
    delete [] buffer;
  }
  
  //
  // Replay.Message.Events
  //
  {
    // Open file and retrieve its size
#ifdef BUILD_LIBMPQ
    libmpq__file_number( archive, "replay.message.events", &number );
    libmpq__file_unpacked_size( archive, number, &size );
#else // StormLib
    SFileOpenFileEx( archive, "replay.message.events", 0, &file );
    size = SFileGetFileSize( file, NULL );
#endif

    // Allocate a buffer for file data
    buffer = new uint8_t[size];

    // Fill the buffer with the file content
#ifdef BUILD_LIBMPQ
    libmpq__file_read( archive, number, buffer, size, NULL );
#else // StormLib
    SFileReadFile( file, buffer, size, &size, NULL );
    SFileCloseFile( file );
#endif

    // Load file
    messageEvents_.load( buffer, size );

    // Release buffer
    delete [] buffer;
  }
  
  //
  // Replay.Sync.Events
  //
  {
    // Open file and retrieve its size
#ifdef BUILD_LIBMPQ
    libmpq__file_number( archive, "replay.sync.events", &number );
    libmpq__file_unpacked_size( archive, number, &size );
#else // StormLib
    SFileOpenFileEx( archive, "replay.sync.events", 0, &file );
    size = SFileGetFileSize( file, NULL );
#endif

    // Allocate a buffer for file data
    buffer = new uint8_t[size];

    // Fill the buffer with the file content
#ifdef BUILD_LIBMPQ
    libmpq__file_read( archive, number, buffer, size, NULL );
#else // StormLib
    SFileReadFile( file, buffer, size, &size, NULL );
    SFileCloseFile( file );
#endif

    // Load file
    syncEvents_.load( buffer, size );

    // Release buffer
    delete [] buffer;
  }
  
  //
  // Replay.Save
  //
  {
    // Open file and retrieve its size
#ifdef BUILD_LIBMPQ
    libmpq__file_number( archive, "save.jpg", &number );
    libmpq__file_unpacked_size( archive, number, &size );
#else // StormLib
    SFileOpenFileEx( archive, "save.jpg", 0, &file );
    size = SFileGetFileSize( file, NULL );
#endif

    // Allocate a buffer for file data
    imageSize_   = size;
    imageBuffer_ = new uint8_t[imageSize_];

    // Fill the buffer with the file content
#ifdef BUILD_LIBMPQ
    libmpq__file_read( archive, number, imageBuffer_, size, NULL );
#else // StormLib
    SFileReadFile( file, imageBuffer_, size, &size, NULL );
    SFileCloseFile( file );
#endif
  }
  
  // Close the archive
#ifdef BUILD_LIBMPQ
  libmpq__archive_close( archive );
#else // StormLib
  SFileCloseArchive( archive );
#endif
  
  isValid_ = true;
}

const Info& Replay::getInfo() const
{
  return info_;
}

const GameEvents& Replay::getGameEvents() const
{
  return gameEvents_;
}

const MessageEvents& Replay::getMessageEvents() const
{
  return messageEvents_;
}

const SyncEvents& Replay::getSyncEvents() const
{
  return syncEvents_;
}

const std::string& Replay::getFilename() const
{
  return filename_;
}

const uint8_t* Replay::getImageBuffer() const
{
  return imageBuffer_;
}

off_t Replay::getImageSize() const
{
  return imageSize_;
}

bool Replay::isValid() const
{
  return isValid_;
}

void Replay::exportImage( const std::string& filename ) const
{
  if ( imageBuffer_==0 )
    return;
  
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (char*)imageBuffer_, imageSize_ );
  file.close();
}

}