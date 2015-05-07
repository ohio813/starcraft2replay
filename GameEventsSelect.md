This event is by far the hardest to read.

The general structure is as follow:

| **Flags** | 1 byte |
|:----------|:-------|
| **Deselected units count** | 1 byte |
| **Deselected units map** | n bits (see below) |
| **Number of different unit types ( = X )** | 1 byte after bit-shift (see below) |
| **Type 1 ID** | 3 bytes after bit-shift (see below) |
| **Type 1 count** | 1 byte after bit-shift (see below) |
| **Type 2 ID** | 3 bytes after bit-shift (see below) |
| **Type 2 count** | 1 byte after bit-shift (see below) |
| **...** |  |
| **Type X ID** | 3 bytes after bit-shift (see below) |
| **Type X count** | 1 byte after bit-shift (see below) |
| **Total number of units ( = Y )** | 1 byte after bit-shift (see below) |
| **Unit 1 ID** | 4 bytes after bit-shift (see below) |
| **Unit 2 ID** | 4 bytes after bit-shift (see below) |
| **...** |  |
| **Unit Y ID** | 4 bytes after bit-shift (see below) |

where :

Y = Type 1 count + Type 2 count + ... + Type X count

<br /><br />
# Easy example #
When no unit is deselected, the parsing is easy:
| 22 | Player 2 |
|:---|:---------|
| AC | Selection event |
| 00 | Flags |
| 00 | No deselected unit, in this case the **Deselected units map** is omited |
| 02 | 2 different unit types |
| 00 69 01 | Type 1 ID = 0x006901 = Sentry |
| 04 | Type 1 count = 4 |
| 00 65 01 | Type 2 ID = 0x006501 = Zealot |
| 05 | Type 2 count = 5 |
| 09 | Total number of units = 4 + 5 = 9 |
| 02 08 00 03 | Sentry 1 ID |
| 02 88 00 03 | Sentry 2 ID |
| 03 80 00 01 | Sentry 3 ID |
| 03 C0 00 02 | Sentry 4 ID |
| 02 74 00 02 | Zealot 1 ID |
| 02 F8 00 01 | Zealot 2 ID |
| 04 50 00 03 | Zealot 3 ID |
| 04 5C 00 03 | Zealot 4 ID |
| 04 70 00 02 | Zealot 5 ID |

Final interpretation: "Player 2 adds 4 sentries and 5 zealots to current selection".

<br /><br />
# Deselected units #
Let's call "D" the **Deselected units count** field.

When this field is not null, it's followed by a **Deselected units map** that indicates where the units are deselected inside the current selection. This supplementary field is D bits long (yes, _bits_, not bytes).

For example, if D is 5 and the **Deselected units map** is (0 0 1 0 0), it means that the middle unit is deselected from the current selection.

Now this creates a serious problem: because of this field, the rest of the event is not byte-aligned anymore and has to be read bits by bits.

<br />
### How to start ###
The **Deselected units map** field might be several bytes long, if D is greater than 8. Whatever its length, if D cannot be divided by 8, the last byte is partial: the bits from the map don't cover the byte entirely.

Now the hard part: the final bits of the **map**, those that do not fill a complete byte, are not immediately after the complete bytes: they are right-aligned on the final byte. This creates a shift that propagates to all bytes after that.

For example, if D is 0x13, the **map** is 2 bytes and 3 bits long. The 2 bytes are right after the **Deselected units count** field but the 3 remaining bits are right-aligned on the next byte. So, there is a "gap" of 5 bits in the middle of the field. And the bits inside this gap are not lost: they are part of the next field.

Illustration:

| 00010011 | aaaaaaaa | bbbbbbbb | dddddccc |
|:---------|:---------|:---------|:---------|

  * D = 0x13
  * aaaaaaaa is the first part of the **map**
  * bbbbbbbb is the second part
  * ccc is the third part (notice the position)
  * ddddd are the 5 first bits of the field after the **map**

<br />
### How to continue ###
Now, you already have the first bits of the following field. To complete this read, some bits are missing. How many exactly? This is quite easy to estimate. Consider this:
  * each time D increases by 8, the **map** field gains 1 byte but this doesn't create a bit-shift
  * what creates the shift are the remaining bits, those that "do not fill a complete byte" as I said before: D modulo 8.
  * take the example above: we read 5 bits (ddddd) from the next field. 3 more bits have to be read. And 3 is (0x13 & 0x07)
  * ( the 0x07 mask is a modulo 8, check it :) )

We know how many bits we have to read. Where do we read them? As you probably guessed, they are at the end (right side) of the following byte, just like the **map** was.

<br />
### How to end ###
With this advices, you should be able to repeat the procedure to read all the bytes of the event.

Remember that the stream is re-aligned when the event ends, so there is a small padding in the last byte to achieve that.

<br /><br />
# Working code #
Here's a sample in C# that parses correctly select events:
```
        public override void ReadEventData(ref BinaryReader br)
        {
            eventData = new List<byte>();

            byte flags01 = br.ReadByte();
            eventData.Add(flags01);

            byte totalShift = br.ReadByte();
            eventData.Add(totalShift);
            byte unitaryShift = (byte)(totalShift & 0x07); // "unitary" means "shift on a single byte"
            byte complementaryShift = (byte)(0x08 - (int)unitaryShift);

            // how to read an int16 after shift byte:
            //
            // |    first byte   |  |   second byte  |  |    third byte   |
            // | 2 2 2 2 2 2| 1 1|  | 3 3 3 3 3 3 3 3|  | 5 5 5 5 5 5| 4 4|  
            // |  comple    |uni |  |      all       |  |  comple    |uni |  
            // |  mentary   |tary|  |                |  |  mentary   |tary|  
            //
            // correct read order is: 1 1  2 2 2 2 2 2  3 3 3 3 3 3 3 3  4 4  5 5 5 5 5 5 
            //
            // value of int16 is: 2 2 2 2 2 2 3 3 3 3 3 3 3 3 4 4
            //  1 1 is end of previous value
            //  5 5 5 5 5 5 is start of next value


            //reading bytes full of "deselectMap" data
            if (totalShift > (byte)0x00)
            {
                for (int readingDeselectField = 0; readingDeselectField < (totalShift >> 3); ++readingDeselectField)
                {
                    //deselectMap is ignored for now
                    eventData.Add(br.ReadByte());
                }
            }

            //reading 1 byte:
            //first bits (size: complementary) are part of the typeCount field
            //last bits (size: shift) are part of the deselectMap

            byte typeCountStartAndDeselectMapEnd = br.ReadByte();
            eventData.Add(typeCountStartAndDeselectMapEnd);
            byte typeCountStart = (byte)((typeCountStartAndDeselectMapEnd >> unitaryShift) << unitaryShift);
            //deselectMapEnd is ignored for now

            byte typeStartAndTypeCountEnd = br.ReadByte();
            eventData.Add(typeStartAndTypeCountEnd);
            byte typeCountEnd = (byte)(((typeStartAndTypeCountEnd << complementaryShift) & 0xFF) >> complementaryShift);
            byte typeCount = (byte)(typeCountStart | typeCountEnd);

            if (typeCount == 0)
            {
                //event was a deselect only
                if (unitaryShift > 0)
                {
                    //shift correction (cf. end of this function)
                    eventData.Add(br.ReadByte());
                }
                return;
            }
            int remainingTypes = typeCount;
            byte typeStart = (byte)((typeStartAndTypeCountEnd >> unitaryShift) << unitaryShift);
            byte totalCountStart = 0;

            do
            {
                //                                                           ---------------------------------------------------------
                //         flags01  totalShift typeCountStart    typeStart  | typeMiddle  alwaysOneStart unitCountStart nextTypeStart | unitIdStart   unitIdMiddle1 unitIdMiddle2 unitIdEnd shiftCorrection
                //                             DeselectMapEnd  TypeCountEnd |                TypeEnd     AlwaysOneEnd   UnitCountEnd  | TotalCountEnd
                //21 AC        00        00           01             00     |     2A           01              01            01       |      01             78          00            01                    //select command center from scratch
                //                                 00000001       00000000  |  00101010     00000001        00000001      00000001    |   00000001       01111000    00000000                      
                //21 AC        00        01           01             01     |     15           00              01            01       |      01             BC          00            00          01        //select command center after deselect 1 scv
                //                                 00000001       00000001  |  00010101     00000000        00000001      00000001    |   00000001       10111100    00000000           
                //22 AC        00        02           03             02     |     1A           01              11            00       |      06 02 05 16 02 
                //                                                           ---------------------------------------------------------
                //                                                                             Repeat for each type
                
                byte typeMiddle = br.ReadByte();
                eventData.Add(typeMiddle);

                byte alwaysOneStartAndTypeEnd = br.ReadByte();
                eventData.Add(alwaysOneStartAndTypeEnd);

                byte unitCountStartAndAlwaysOneEnd = br.ReadByte();
                eventData.Add(unitCountStartAndAlwaysOneEnd);

                byte nextTypeStartAndUnitCountEnd = br.ReadByte();
                eventData.Add(nextTypeStartAndUnitCountEnd);
                byte nextTypeStart = (byte)((nextTypeStartAndUnitCountEnd >> unitaryShift) << unitaryShift);
                totalCountStart = nextTypeStart;

                --remainingTypes;
            }
            while (remainingTypes > 0);

            int remainingUnits = 0;
            bool remainingCountIsKnown = false;

            do
            {
                //                                                                                                                    -----------------------------------------------------
                //         flags01  totalShift typeCountStart    typeStart   typeMiddle  alwaysOneStart unitCountStart nextTypeStart | unitIdStart   unitIdMiddle1 unitIdMiddle2 unitIdEnd | shiftCorrection
                //                             DeselectMapEnd  TypeCountEnd                 TypeEnd     AlwaysOneEnd   UnitCountEnd  | TotalCountEnd                                       |
                //21 AC        00        00           01             00          2A           01              01            01       |      01             78          00            01    |                 //select command center from scratch
                //                                 00000001       00000000    00101010     00000001        00000001      00000001    |   00000001       01111000    00000000               |        
                //21 AC        00        01           01             01          15           00              01            01       |      01             BC          00            00    |       01        //select command center after deselect 1 scv
                //                                 00000001       00000001    00010101     00000000        00000001      00000001    |   00000001       10111100    00000000               |
                //22 AC        00        02           03             02          1A           01              11            00       |      06 02 05 16 02                                 |
                //                                                                                                                    -----------------------------------------------------
                //                                                                                                                                   Repeat for each unit
                byte unitIdStartAndTotalCountEnd = br.ReadByte();
                eventData.Add(unitIdStartAndTotalCountEnd);
                byte totalCountEnd = (byte)(((unitIdStartAndTotalCountEnd << complementaryShift) & 0xFF) >> complementaryShift);
                byte totalCount = (byte)(totalCountStart | totalCountEnd);
                if (!remainingCountIsKnown)
                {
                    remainingUnits = totalCount;
                    remainingCountIsKnown = true;
                }

                byte unitIdMiddle1 = br.ReadByte();
                eventData.Add(unitIdMiddle1);

                byte unitIdMiddle2 = br.ReadByte();
                eventData.Add(unitIdMiddle2);

                byte unitIdEnd = br.ReadByte();
                eventData.Add(unitIdEnd);

                --remainingUnits;
            }
            while (remainingUnits > 0);

            if (unitaryShift > 0)
            {
                //padding for shift correction
                eventData.Add(br.ReadByte());
            }
        }

```