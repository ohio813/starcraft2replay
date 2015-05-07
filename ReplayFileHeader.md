# Replay File Header #

As you may have noticed the Starcraft 2 Replay file is a MPQ file, but it's not a plain MPQ file since the actual MPQ data starts at offset 0x400. The first first 1024 bytes contain some extra data.

| **Location**           | **Meaning**                                                  |
|:-----------------------|:-------------------------------------------------------------|
| 0x00-0x03            | 458313805, "MPQ\x1B"                                       |
| 0x04-0x07            | Maximum size of the user data, 512                         |
| 0x04-0x07            | Offset of the MPQ header, 1024                             |
| 0x0C-0x0F            | Size of user data header, 39                               |
| 0x10                 | Length of the following string (Incorrect?)                |
| 0x11-0x23            | "StarCraft II replay"                                      |
| 0x24-0x27            | 0x1B 0x32 0x01 0x00                                        |
| 0x28-0x2B            | Major version (Initial release = 2, patch 8 = 10)          |
| 0x2C-0x2F            | Build number (corresponds to the folders versions)         |
| 0x30-0x36            | Unknown (first two seem to be build number again           |
| 0x36                 | End of user data                                           |