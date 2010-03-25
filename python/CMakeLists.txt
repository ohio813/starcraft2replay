############################## External libraries #############################
INCLUDE( FindBoost )
SET( Boost_USE_MULTITHREADED ON )
SET( Boost_USE_STATIC_LIBS   ON )
FIND_PACKAGE( Boost REQUIRED COMPONENTS python )
FIND_PACKAGE( PythonLibs )

############################## Includes #######################################
INCLUDE_DIRECTORIES( ../inc ./inc ${PYTHON_INCLUDE_PATH} ${Boost_INCLUDE_DIRS} )

### Build & Link
ADD_LIBRARY( pysc2replay SHARED pysc2replay.cpp )
TARGET_LINK_LIBRARIES( pysc2replay SC2Replay ${PYTHON_LIBRARY} ${Boost_LIBRARIES} )

SET_TARGET_PROPERTIES( pysc2replay PROPERTIES PREFIX  ""  ) # Remove the "lib" prefix
