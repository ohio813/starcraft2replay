## Purpose ##

This page explains how to extract the build number from a replay file (i.e. the game client version)

## Why would we need that ? ##

Because the replay format evolves over time :
  * Patch 1 (or patch 2) introduced a change in ability codes
  * Patch 6 introduced a change in the "hotkey action" event format (event code = 0x1C)

More changes in the future are very likely. Therefore our replay parser has to take different versions into account.

## How do we get this build number ? ##

Open the replay file as a stream (open the .SC2Replay file directly, don't try to extract its content with stormlib/mpqlib).

Major version number is an int8 at offset 0x28.

Build number is an int16 starting at offset 0x2C.