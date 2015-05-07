# General Information #

Events inside replay.game.events are queued one after another. As soon as an event ends, another starts.

Some events have to be read bit by bit - and not byte by byte - in order to be correctly decrypted. However, those events have some padding bits at the end so that the stream is correctly byte-aligned when the next event starts. Therefore, a byte-aligned read of the file works.

The general structure of an event is:

| **Encoded timestamp** | **Event type** | **Global event flag** | **Player id** | **Event code** | **Event data** |
|:----------------------|:---------------|:----------------------|:--------------|:---------------|:---------------|
| 8 or 16 bits | 3 bits | 1 bit | 4 bits | 8 bits | 8`*`X bits |

**Event data** field size depends on **event code** but is always a multiple of 8 bits.

<br /><br />
# Encoded timestamp #

This field contains an indication of the time elapsed since the previous event.

The 2 final bits of the 1st byte indicate whether there is a second byte to read or not.

Reading first byte:
| **Significant value** | **Follow-up** |
|:----------------------|:--------------|
| 6 bits | 2 bits |

  * If the **Follow-up** field is 00b --> the timestamp is over
  * If the **Follow-up** field is 01b --> there is a second byte to read
  * 10b and 11b **Follow-up** are theoretically possible after more than 13 minutes of inactivity from all players in the game. They are never seen in practice because some automatic events are automatically generated at random times and prevent players from having 13 minutes of inactivity (actually _I_ was never able to reproduce that even after several hours of idle time. Feel free to contradict me).

Reading second byte:
| **Significant value** |
|:----------------------|
| 8 bits |

<br />
### How to decrypt the value ###
  * If the timestamp is 1 byte long, simply shift the value 2 bits to the right (or divide by 4). This will remove the **Follow-up** field.
  * If the timestamp is 2 bytes long, **Follow-up** field has to be removed. Then **Significant values** from both field have to be concatenated.

<br />
### Example ###
Reading:
| 0x19 | 0x65 |
|:-----|:-----|
| 0 0 0 1 1 0 0 1 | 0 1 1 0 0 1 0 1 |

First byte interpretation:
  * 0 0 0 1 1 0 is **significant value**
  * 0 1 is **follow-up**
Follow-up is not 00b, so the second byte is also part of the timestamp.

Final value:
  * (0 0 0 1 1 0) (~~0 1~~) (0 1 1 0 0 1 0 1) = 0 0 0 1 1 0 0 1 1 0 0 1 0 1 = 1637 (decimal)

This result is the number of **time unit** elapsed since the previous event. A **time unit** is exactly 1/16th of a second in "fast" mode. Other modes need to be checked.

In this example, 102.31 seconds (1637/16) elapsed since the previous event.

<br /><br />
# Event type #

This is a 3 bits long field.
| **Binary value** | **Meaning** | **Examples** | **Notes** |
|:-----------------|:------------|:-------------|:----------|
| 0 0 0 | Initialization | Enter game<br />Game start |  |
| 0 0 1 | Action | Selection<br />Use ability<br />... |  |
| 0 1 1 | Replay | Move screen | Those events have no incidence on the game but are kept inside the replay file to make the replay experience more realistic. |
| 1 0 0 | Inaction | Trade<br />Synchronization | Those have an influence over the course of the game but cannot be considered actions because they're not directly related to a game unit.<br />Some automatically generated synchronization events also use this event type. |
| 1 0 1 | System | ? | Needs investigation. |

Note: 010b, 110b and 111b were never seen. Feel free to contribute if you find them.

<br /><br />
# Global event flag #

This is a 1 bit long field.
| **Binary value** | **Meaning** | **Examples** | **Notes** |
|:-----------------|:------------|:-------------|:----------|
| 0 | Player specific event | All events _but_ Game start | Concerns 1 player only |
| 1 | Global event | Game start | Concerns everyone |

<br /><br />
# Player id #

This is a 4 bits long field.
  * Value is 0000b for global events

Notice that players have the same ID in all replay files. That means you can retrieve the player name corresponding to this ID inside replay.info and the messages inside replay.message.events.

<br /><br />
# Event code #

This is a 8 bits (1 byte) long field.

Known codes for _Initialization_ events (type = 000b):
| **Hexadecimal value** | **Meaning** | **Event data** |
|:----------------------|:------------|:---------------|
| 1B | Player enters the game  | No data |
| 05 | Game starts | No data |

<br />
Known codes for _Action_ events (type = 001b):
| **Hexadecimal value** | **Meaning** | **Event data** | **Notes** |
|:----------------------|:------------|:---------------|:----------|
| 09 | Player quits the game  | No data |  |
| 0B | Player uses an ability / gives an order | Event data size is variable.<br />See specific documentation. |  |
| 2F | Player sends resources | Event data size is always 17 bytes.<br />See specific documentation. |  |
| AC | Player changes current selection  | Event data size is variable.<br />See specific documentation. |  |
| xD | Player manually uses an hotkey  | Event data size is variable.<br />See specific documentation. | Might be (0D, 1D, 2D, ... 9D) |
| xC | Hotkey is automatically updated  | Event data size is variable.<br />See specific documentation. | Might be (0C, 1C, 2C, ... 9C)<br />Common reason for automatic update is when a unit transforms into another.<br />For example, an hatchery assigned to hotkey 3 that morphs into a lair generates a 3C action. |

<br />
Known codes for _Replay_ events (type = 011b):
| **Hexadecimal value** | **Meaning** | **Event data** |
|:----------------------|:------------|:---------------|
| 81 | Player moves screen  | Event data size is always 20 bytes.<br />See specific documentation. |

<br />
Known codes for _Inaction_ events (type = 100b):
| **Hexadecimal value** | **Meaning** | **Event data** | **Notes** |
|:----------------------|:------------|:---------------|:----------|
| 00 | Automatic synchronization  | Event data size is always 4 bytes.<br />Needs investigation. | Launched randomly about 1 time every 5 minutes.<br />Prevents the timestamp counter from reaching 13 minutes but probably has some other purpose. |
| 16 | Player sends a request for resources | Event data size is always 24 bytes.<br />See specific documentation. |  |
| 18 | Player cancels a request for resources | Event data size is always 4 bytes.<br />See specific documentation. |  |


<br />
Known codes for _System_ events (type = 101b):
| **Hexadecimal value** | **Meaning** | **Event data** |
|:----------------------|:------------|:---------------|
| 89 | Automatic synchronization?  | Event data size is always 4 bytes.<br />Needs investigation. |