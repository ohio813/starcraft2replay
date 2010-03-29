############################## Minimum CMake version to run ###################
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

############################## Checks #########################################
IF ( NOT CMAKE_BUILD_TYPE )
  SET( CMAKE_BUILD_TYPE Debug CACHE STRING "Available build types: Debug | Release" FORCE )
ENDIF ( NOT CMAKE_BUILD_TYPE )

############################## Project name ###################################
PROJECT( SC2Replay )

MESSAGE( "--------------------------------------------------" )
MESSAGE( STATUS "Configuring MonsterEngine" )

SET( SC2Replay_MAJOR_VERSION 0 )
SET( SC2Replay_MINOR_VERSION 1 )
SET( SC2Replay_PATCH_LEVEL   0 )

############################## Modules configuration ##########################
OPTION( BUILD_DOC    "Build the doxygen documentation"         ON )
OPTION( BUILD_STATIC "Build as a static library"               ON )
OPTION( BUILD_TOOLS  "Build the tools"                         ON )
OPTION( BUILD_TESTS  "Build the unit tests"                    ON )
OPTION( BUILD_PYTHON "Build the python bindings"               ON )
OPTION( BUILD_LIBMPQ "Build using libmpq (StormLib otherwise)" ON )

MESSAGE( STATUS "Building documentation:   " ${BUILD_DOC}    )
MESSAGE( STATUS "Building static:          " ${BUILD_STATIC} )
MESSAGE( STATUS "Building tools:           " ${BUILD_TOOLS}  )
MESSAGE( STATUS "Building tests:           " ${BUILD_TESTS}  ) 
MESSAGE( STATUS "Building python bindings: " ${BUILD_PYTHON} ) 
MESSAGE( STATUS "Building using libmpq:    " ${BUILD_LIBMPQ} )

############################## Sources ########################################
FILE( GLOB_RECURSE Sources        src/*.cpp              )       # Scan all source files
FILE( GLOB_RECURSE PublicHeaders  inc/sc2replay/*.h  )       # Scan all public  header files
FILE( GLOB_RECURSE PrivateHeaders inc/private/*.h        )       # Scan all private header files

# Group files in virtual folders under Visual Studio
SOURCE_GROUP( "Private Headers"   FILES ${PrivateHeaders} )
SOURCE_GROUP( "Public Headers"    FILES ${PublicHeaders}  )
SOURCE_GROUP( "Sources"           FILES ${Sources}        )

############################## External libraries #############################
# Not used yet
#INCLUDE( FindBoost )
#SET( Boost_USE_MULTITHREADED ON )
#SET( Boost_USE_STATIC_LIBS   ON )
#FIND_PACKAGE( Boost REQUIRED COMPONENTS serialization filesystem graph thread date_time program_options unit_test_framework )

IF ( BUILD_LIBMPQ )
  FIND_LIBRARY( MPQLib NAMES mpq )
ELSE( BUILD_LIBMPQ )
  FIND_LIBRARY( MPQLib NAMES StormLib )
ENDIF( BUILD_LIBMPQ )

############################## Includes #######################################
INCLUDE_DIRECTORIES( ./inc ) # Headers

############################## Project generation #############################
IF ( BUILD_STATIC )
  ADD_LIBRARY( SC2Replay STATIC ${Sources} ${PublicHeaders} ${PrivateHeaders} )
ELSE ( BUILD_STATIC )
  ADD_LIBRARY( SC2Replay SHARED ${Sources} ${PublicHeaders} ${PrivateHeaders} )
ENDIF ( BUILD_STATIC )

TARGET_LINK_LIBRARIES( SC2Replay ${Boost_LIBRARIES} ${MPQLib} )

################################### Options ###################################
IF ( BUILD_STATIC )
  ADD_DEFINITIONS( -DBUILD_STATIC )
ENDIF( BUILD_STATIC )

IF ( BUILD_DOC )
  #TODO build documentation using Doxygen
ENDIF( BUILD_DOC )

IF ( BUILD_TOOLS )
  ADD_SUBDIRECTORY( tools )
ENDIF( BUILD_TOOLS )

IF ( BUILD_TESTS )
  ADD_SUBDIRECTORY( tests )
ENDIF( BUILD_TESTS )

IF ( BUILD_PYTHON )
  ADD_SUBDIRECTORY( python )
ENDIF( BUILD_PYTHON )

IF ( BUILD_LIBMPQ )
  ADD_DEFINITIONS( -DBUILD_LIBMPQ )
ENDIF( BUILD_LIBMPQ )


MESSAGE( "--------------------------------------------------" )

############################## Target Properties ##############################
SET_TARGET_PROPERTIES( SC2Replay PROPERTIES LINKER_LANGUAGE CXX ) # Language forced to C++

SET_TARGET_PROPERTIES( SC2Replay PROPERTIES DEBUG_POSTFIX "d" ) # Debug mode: a trailing "d"

SET_TARGET_PROPERTIES( SC2Replay PROPERTIES RELEASE_POSTFIX "" ) # Release mode: no postfix

SET_TARGET_PROPERTIES( SC2Replay PROPERTIES PREFIX  ""  ) # Remove the "lib" prefix

SET_TARGET_PROPERTIES( SC2Replay PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE} ) # Path for shared libraries
SET_TARGET_PROPERTIES( SC2Replay PROPERTIES LIBRARY_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE} ) # Path for module libraries
SET_TARGET_PROPERTIES( SC2Replay PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE} ) # Path for import libraries

SET_TARGET_PROPERTIES( SC2Replay PROPERTIES OUTPUT_NAME "sc2replay" ) # Output name

