# Readme #

## Getting the source code ##

```
svn checkout https://starcraft2replay.googlecode.com/svn/trunk/ starcraft2replay
```

## Building ##

### Materials ###

In order to build starcraft2replay parser, you will need:
  * An library to uncompress MPQ files:
    * libmpq : https://libmpq.org/
    * StormLib : http://www.zezula.net/en/mpq/download.html#StormLib
  * CMake : http://www.cmake.org/
  * Boost Python (if you want the bindings) : http://www.boost.org/doc/libs/1_42_0/libs/python/doc/index.html

### Building on linux ###

Head to the root directory of the project, and create a subdirectory name "build".

```
mkdir build
cd build
```

Call CMake on the root directory

```
cmake ..
```

You can feed CMake with the following options:
  * `-DBUILD_PYTHON=[ON|OFF]` : enable/disable building python bindings
  * `-DLIBMPQ=[ON|OFF]` : use libmpq (ON) or stormlib (OFF)
  * `-DBUILD_TESTS=[ON|OFF]` : build the tests. Useful to quickly check is the library is working properly
  * `-DBUILD_TOOLS=[ON|OFF]` : build the developper tools (i.e. to extract parts of the MPQ)

All these options are set to `ON` by default.

Call make to build the library
```
make -j
```

That's it.
You can quickly try the library with a replay file (checkout nibbits.com to download some replays).

```
cd tests
./read_mpq myreplay.SC2Replay
```

### Building on Windows ###

Use CMake-GUI to generate a Visual Studio project or MinGW Makefile. Minor tweaks may be required.
Tested with VS2008 & 2010