# Header #

| **Field name** | **Type** | **Count** | **Comments** |
|:---------------|:---------|:----------|:-------------|
| header | uint32 | x 1 | Always "00 00 00 00"? |
| attributeCount | uint32 | x 1 | Little endian |
| attributeList | attributeStruct (13 bytes) | x attributeCount | See below |

<br /><br />
# attributeStruct #

| **Field name** | **Type** | **Count** | **Comments** |
|:---------------|:---------|:----------|:-------------|
| attributeHeader | uint16 | 1 | Always "E7 03"? (= 999 decimal) |
| null1 | uint16 | 1 | Always "00 00"? |
| attributeId | uint16 | 1 | See below |
| null2 | uint16 | 1 | Always "00 00"? |
| playerId | uint8 | 1 | Player to which attribute applies.<br />"10" = All players |
| attributeValue | char | 4 | This is a string with the attribute value,<br />written from right to left,<br />with padding on the right (00)<br />if the value is smaller than 4 bytes |

<br /><br />
# known attributes #

| **attributeId** | **Meaning** | **Comments** |
|:----------------|:------------|:-------------|
| "F4 01" | Player Type | Might be "Humn" for Human or "Comp" for AI |
| "B9 0B" | Race | "Prot", "Terr", "Zerg" or "RAND"<br />When race is RAND, use replay.details to find out the final race. |
| "D1 07" | Game Format | "1v1" or "2v2" |
| "BB 0B" | Handicap? | ? |
| "D3 07" | Team? | "T1" for Team1, "T2" for Team2, ... |
| "B8 0B" | Game Speed? | ? |