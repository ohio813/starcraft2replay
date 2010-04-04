#include <iostream>
#include <cstdlib>

#include "sc2replay/replay.h"
#include "sc2replay/syncevents.h"

namespace sc = sc2replay;

int main( int argc, char** argv )
{
  if ( argc != 3 )
  {
    std::cerr << "Usage: extract_syncevents_dump <replay file> <dump file>" << std::endl;
    return EXIT_FAILURE;
  }
  
  sc::Replay replay( argv[1] );
  
  if ( !replay.isValid() )
  {
    std::cerr << "Replay file does not exists or is invalid." << std::endl;
    std::cerr << "If you are using libmpq (default) this may randomly happen. ";
    std::cerr << "Try to install StormLib (http://www.zezula.net/en/mpq/stormlib.html) ";
    std::cerr << "and use the CMake option -DBUILD_LIBMPQ=OFF" << std::endl;
    return EXIT_FAILURE;
  }
  
  replay.getSyncEvents().exportDump( argv[2] );
  
  std::cout << "Replay sync events successfully extracted to \"" << argv[2] << "\"." << std::endl;
  
  return EXIT_SUCCESS;
}