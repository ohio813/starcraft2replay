#ifndef SC2REPLAY_SYNCEVENTS_H
#define SC2REPLAY_SYNCEVENTS_H

#include <string>

#include "mpq/mpqlib.h"

namespace sc2replay
{

/**
 * NOT IMPLEMENTED YET
 */

class SyncEvents
{
public:
  SyncEvents();
  ~SyncEvents();
  
public:
  void load( const uint8_t* data, unsigned long size );
  
public:
  off_t    getBufferSize() const;
  uint8_t* getBuffer    () const;
  
public:
  void exportDump( const std::string& filename ) const;
  
private:
  uint8_t* buffer_;
  off_t    bufferSize_;
};

} // namespace sc2replay

#endif // SC2REPLAY_SYNCEVENTS_H