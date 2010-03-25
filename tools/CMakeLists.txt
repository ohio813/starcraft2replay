### Extractin the picture of the map
ADD_EXECUTABLE( extract_map extract_map.cpp )
TARGET_LINK_LIBRARIES( extract_map SC2Replay )

### Extract the dump of the replay info
ADD_EXECUTABLE( extract_info_dump extract_info_dump.cpp )
TARGET_LINK_LIBRARIES( extract_info_dump SC2Replay )

### Extract the dump of the replay messageevents
ADD_EXECUTABLE( extract_messageevents_dump extract_messageevents_dump.cpp )
TARGET_LINK_LIBRARIES( extract_messageevents_dump SC2Replay )

### Extract the dump of the replay gameevents
ADD_EXECUTABLE( extract_gameevents_dump extract_gameevents_dump.cpp )
TARGET_LINK_LIBRARIES( extract_gameevents_dump SC2Replay )

### Extract the dump of the replay syncevents
ADD_EXECUTABLE( extract_syncevents_dump extract_syncevents_dump.cpp )
TARGET_LINK_LIBRARIES( extract_syncevents_dump SC2Replay )

# Add your tools here