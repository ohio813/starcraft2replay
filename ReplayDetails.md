# General structure #

| **Field name** | **Type** | **Count** | **Comments** |
|:---------------|:---------|:----------|:-------------|
| unknownHeader | uint8 | x 6 | No magic word. Is it version? |
| doublePlayerCount | uint8 | x 1 | All counts are doubled in this file.<br />No idea why. |
| playerInfo | playerDetailStruct | x (doublePlayerCount / 2) | Always x16 ?<br />See below for struct. |
| unknown1 | uint8 | x 2 |  |
| doubleMapNameLength | uint8 | x 1 |  |
| mapName | char | x (doubleMapNameLength / 2) |  |
| unknown2 | uint16 | x 1 | Always "04 02" ? |
| doubleUnknown3Length | uint8 | x 1 |  |
| unknown3 | char | x (doubleUnknown3Length / 2) |  |
| unknown4 | uint8 | x 3 | Always "06 05 02" ? |
| unknown5 | uint16 | x 1 | Always "00 02" ? |
| doubleMinimapFilenameLength | uint8 | x 1 |  |
| minimapFilename | char | x (doubleMinimapFilenameLength / 2) |  |
| crap | char | x 28 | Might be variable length as everything in there is unknown.<br />Starts with "08 06 01", ends with "10 02 00" |
| param1 | keyValueStruct | x 1 | See below for type keyValueStruct.<br />Key is always "12 02" ? |
| mapPath | char | x (param1.doubleValue / 2) |  |
| usualCrap | char | ? | till the end |

<br /><br />
# playerDetailStruct #

| **Field name** | **Type** | **Count** | **Comments** |
|:---------------|:---------|:----------|:-------------|
| playerHeader | uint32 | x 1 | Always "05 12 00 02" ? |
| doubleShortNameLength | uint8 | x 1 |  |
| shortName | char | x (doubleShortNameLength / 2) |  |
| unknown1 | uint8 | x 3 | Always "02 05 08" ? |
| param1 | keyValueStruct | x 1 | See below for type keyValueStruct.<br />Key is always "00 09" ? |
| unknown2 | uint8 | x 6 |  |
| param2 | keyValueStruct | x 1 | See below for type keyValueStruct.<br />Key is always "04 09" ? |
| unknown3 | uint16 | x 1 | Always "06 02" ? |
| doubleFullNameLength | uint8 | x 1 |  |
| fullName | char | x (doubleFullNameLength / 2) | Separator between name and realID is "#" |
| unknown4 | uint16 | x 1 | Always "04 02" ? |
| doubleRaceLength | uint8 | x 1 |  |
| race | char | x (doubleRaceLength / 2) |  |
| unknown5 | uint8 | x 3 | Always "06 05 08" ? |
| paramList | keyValueStruct | x 9 | See below for keyValueStruct.<br />Key values are successively<br />"00 09"<br />"02 09"<br />"04 09"<br />"06 09"<br />"08 09"<br />"0A 09"<br />"0C 09"<br />"0E 09"<br />"10 09" |

<br /><br />
# keyValueStruct #

| **Field name** | **Type** | **Count** | **Comments** |
|:---------------|:---------|:----------|:-------------|
| key | uint16 | x 1 | Always "xx 09" ? |
| doubleValue | paramValue | x 1 | See below for type "paramValue" |

<br /><br />
# paramValue #

paramValue is a special type that can be 1 or 2 bytes, depending on the contained value. To parse it, you have to use the same algorithm as for timestamps in event files. See GameEventsOverview for more details.

The only difference between paramValues and timestamps is that the "follow up" bit is on the left for paramValues whereas it's on the right for timestamps. So, instead of using a 0x03 mask, use 0x80.

tldr: If (firstByte & 0x80 > 0) Then (read second byte)

Remember that in a keyValueStruct, the encoded value is doubled.

<br /><br />
# known params in paramList #

| **key** | **Meaning** | **Comments** |
|:--------|:------------|:-------------|
| "00 09" | Player Color Transparency (A) | Always "FE 03" = 255 (decimal) once decoded |
| "02 09" | Player Color Red (R) |  |
| "04 09" | Player Color Green (G) |  |
| "06 09" | Player Color Blue (B) |  |

Note 1: "0C 09" might be Handicap, needs to be checked.

Note 2: Instead of uint8, all "length" fields in this file might actually be paramValues from a keyValueStruct. This needs to be checked too.