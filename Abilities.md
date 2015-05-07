## Warning: ##
Patch 1 changed the AbilCmd codes.

All codes presented in this page are only valid for replays recorded **after** February 25th.

For replays created with build 13891, another set of codes has to be used (most of the time, those codes were `[`_current code minus 2 on second byte_`]`)

Example:
  * before February 25th, code for training a Zergling was 0A **0B** 01.
  * after February 25th, code changed to 0A **0D** 01. This is still valid today and this is what you find on this page.

<br /><br />
# Ability Codes #
## Common ##
| **Code** | **Name** |
|:---------|:---------|
| 0x020400 | Stop |
| 0x020501 | Hold fire |
| 0x020600 | Move |
| 0x020601 | Patrol |
| 0x020602 | Hold position |
| 0x020900 | Attack |
| 0x060800 | Cancel |
| 0x060400 | Gather |
| 0xFFFF0F | Right-Click |

## Terran ##

| **Code** | **Name** |
|:---------|:---------|
| 0x030A00 | Point Defense Drone            |
| 0x040700 | Seeker Missile                 |
| 0x050500 | Set rally point                |
| 0x050D00 | Stimpack (Marauder)            |
| 0x050F00 | 250mm Strike Cannon            |
| 0x060401 | Return cargo                   |
| 0x060D00 | Build Command Center           |
| 0x060D01 | Build Supply Depot             |
| 0x060D02 | Build Refinery                 |
| 0x060D03 | Build Barracks                 |
| 0x060D04 | Build Engineering Bay          |
| 0x060D05 | Build Missile Turret           |
| 0x060D06 | Build Bunker                   |
| 0x060D08 | Build Sensor Tower             |
| 0x060D09 | Build Ghost Academy            |
| 0x060D0A | Build Factory                  |
| 0x060D0B | Build Starport                 |
| 0x060D0D | Build Armory                   |
| 0x060D0F | Build Fusion Core              |
| 0x060F00 | Stimpack (Marine)              |
| 0x070000 | Cloack (Ghost)                 |
| 0x070001 | Decloack (Ghost)               |
| 0x070100 | Sniper Round                   |
| 0x070200 | Heal (Medivac)                 |
| 0x070300 | Siege Mode (Siege Tank)        |
| 0x070400 | Tank Mode (Siege Tank)         |
| 0x070500 | Cloack (Banshee)               |
| 0x070501 | Decloack (Banshee)             |
| 0x070600 | Load (Medivac)                 |
| 0x070602 | Unload all (Medivac)           |
| 0x070800 | Yamato Cannon                  |
| 0x070900 | Assault Mode (Viking)          |
| 0x070A00 | Fighter Mode (Viking)          |
| 0x070C01 | Unload all (Command Center)    |
| 0x070C04 | Load (Command Center)          |
| 0x070D00 | Lift off (Command Center)      |
| 0x070E00 | Land (Command Center)          |
| 0x070F00 | Build Tech Lab (Barracks)      |
| 0x070F01 | Build Reactor (Barracks)       |
| 0x080100 | Build Tech Lab (Factory)       |
| 0x080300 | Build Tech Lab (Starport)      |
| 0x080700 | Train SCV                      |
| 0x080900 | Lower (Supply Depot)           |
| 0x080A00 | Raise (Supply Depot)           |
| 0x080B00 | Train Marine                   |
| 0x080B01 | Train Reaper                   |
| 0x080B02 | Train Ghost                    |
| 0x080B03 | Train Marauder                 |
| 0x080C01 | Train Siege Tank               |
| 0x080C04 | Train Thor                     |
| 0x080C05 | Train Hellion                  |
| 0x080D00 | Train Medivac                  |
| 0x080D01 | Train Banshee                  |
| 0x080D02 | Train Raven                    |
| 0x080D03 | Train Battlecruiser            |
| 0x080D04 | Train Viking                   |
| 0x080E00 | Upgrade Hi-Sec Auto Tracking   |
| 0x080E01 | Upgrade Building Armor         |
| 0x080E02 | Upgrade Infantry Weapons 1     |
| 0x080E03 | Upgrade Infantry Weapons 2     |
| 0x080E04 | Upgrade Infantry Weapons 3     |
| 0x080E06 | Upgrade Infantry Armor 1       |
| 0x080E07 | Upgrade Infantry Armor 2       |
| 0x080E08 | Upgrade Infantry Armor 3       |
| 0x080E05 | Upgrade Neosteel Frame         |
| 0x080F03 | Research Nitro Packs           |
| 0x090000 | Arm Silo with Nuke             |
| 0x090100 | Research Stimpack              |
| 0x090101 | Research Combat Shield         |
| 0x090200 | Research Siege Tech            |
| 0x090201 | Research Infernal Pre-Igniter  |
| 0x090300 | Research Cloacking Field       |
| 0x090302 | Research Caduceus Reactor      |
| 0x090303 | Research Corvid Reactor        |
| 0x090306 | Research Seeker Missiles       |
| 0x090307 | Research Durable Materials     |
| 0x090400 | Research Personal Cloacking    |
| 0x090401 | Research Moebius Reactor       |
| 0x090502 | Upgrade Vehicle Plating 1      |
| 0x090503 | Upgrade Vehicle Plating 2      |
| 0x090504 | Upgrade Vehicle Plating 3      |
| 0x090505 | Upgrade Vehicle Weapons 1      |
| 0x090506 | Upgrade Vehicle Weapons 2      |
| 0x090507 | Upgrade Vehicle Weapons 3      |
| 0x090508 | Upgrade Ship Plating 1         |
| 0x090509 | Upgrade Ship Plating 2         |
| 0x09050A | Upgrade Ship Plating 3         |
| 0x09050B | Upgrade Ship Weapons 1         |
| 0x09050C | Upgrade Ship Weapons 2         |
| 0x09050D | Upgrade Ship Weapons 3         |
| 0x0C0700 | Upgrade to Planetary Fortress  |
| 0x0D0600 | Research Weapon Refit          |
| 0x0D0601 | Research Behemoth Reactor      |
| 0x0D0900 | Tac Nuclear Strike             |
| 0x0D0C00 | EMP Round                      |
| 0x0F0400 | Auto-Turret                    |
| 0x080301 | Build Reactor on Factory |
| 0x080301 | Build Reactor on Starport |


## Zerg ##
| **Code** | **Name** |
|:---------|:---------|
| 0x0a0300 | Build Hatchery |
| 0x0a0302 | Build Extractor |
| 0x0a0303 | Build Spawning Pool |
| 0x0a0304 | Build Evolution Chamber |
| 0x0a0305 | Build Hydralisk Den |
| 0x0a0306 | Build Spire |
| 0x0a0307 | Build Ultralisk Cavern |
| 0x0a0308 | Build Infestation Pit |
| 0x0a0309 | Build Nydus Network |
| 0x0a030a | Build Baneling Nest |
| 0x0a030d | Build Roach Warren |
| 0x0a030e | Build Spine Crawler |
| 0x0a030f | Build Spore Crawler |
| 0x0A0500 | Research Melee Weapons 1 |
| 0x0A0501 | Research Melee Weapons 2 |
| 0x0A0502 | Research Melee Weapons 3 |
| 0x0A0503 | Research Ground Armor 1 |
| 0x0A0504 | Research Ground Armor 2 |
| 0x0A0505 | Research Ground Armor 3 |
| 0x0A0506 | Research Missile Weapons 1 |
| 0x0A0507 | Research Missile Weapons 2 |
| 0x0A0508 | Research Missile Weapons 3 |
| 0x0A050A | Research Burrow |
| 0x0A0600 | Build Lair |
| 0x0A0700 | Build Hive |
| 0x0A0800 | Research Greater Spire |
| 0x0A0801 | Cancel Greater Spire Research |
| 0x0A0901 | Research Overlord Speed |
| 0x0A0902 | Research Ventral Sacks |
| 0x0A0A00 | Research Zergling Attack Speed |
| 0x0A0A01 | Research Zergling Movement Speed |
| 0x0A0B02 | Research Hydralisk Speed |
| 0x0A0C00 | Research Flyer Attack 1 |
| 0x0A0C01 | Research Flyer Attack 2 |
| 0x0A0C02 | Research Flyer Attack 3 |
| 0x0A0C03 | Research Flyer Armor 1 |
| 0x0A0C04 | Research Flyer Armor 2 |
| 0x0A0C05 | Research Flyer Armor 3 |
| 0x0a0d00 | Train Drone |
| 0x0a0d01 | Train Zergling |
| 0x0a0d02 | Train Overlord |
| 0x0a0d03 | Train Hydralisk |
| 0x0a0d04 | Train Mutalisk |
| 0x0a0d06 | Train Ultralisk |
| 0x0a0d09 | Train Roach |
| 0x0a0d0a | Train Infestor |
| 0x0a0d0b | Train Corruptor |
| 0x0a0e00 | Train Broodlord |
| 0x0A0E01 | Cancel BroodLord Mutation |
| 0x0C0901 | Research Peristalsis |
| 0x0C0902 | Research Infestor Energy Upgrade |
| 0x0C0A00 | Research Centrifical Hooks |
| 0x0D0E00 | Train queen |
| 0x0E0D00 | Generate Creep (Overlord) |
| 0x0E0F00 | Uproot (Spine Crawler) |
| 0x0F0100 | Root (Spine Crawler) |
| 0x0F0600 | Build Nydus Worm |
| 0x030400 | Fungal Growth (Infestor) |
| 0x050700 | Set rally point (Hatchery) |
| 0x050701 | Set rally point for drones |
| 0x050800 | Research Organic Carapace |
| 0x050801 | Research Glial Regeneration |
| 0x050802 | Research Tunneling Claws |
| 0x050C00 | Spawn Larva (Queen) |
| 0x060201 | Research Anabolic Synthesis 2 |
| 0x060202 | Research Chitinous Plating |

## Protoss ##
| **Code** | **Name** |
|:---------|:---------|
| 0x090600 | Build Nexus |
| 0x090601 | Build Pylon |
| 0x090602 | Build Assimilator |
| 0x090603 | Build Gateway |
| 0x090604 | Build Forge |
| 0x090605 | Build Fleet Beacon |
| 0x090606 | Build Twilight Council |
| 0x090607 | Build Photon Canon |
| 0x090609 | Build Stargate |
| 0x09060a | Build Templar Archive |
| 0x09060b | Build Dark Shrine |
| 0x09060c | Build Robotics Bay |
| 0x09060d | Build Robotics Facility |
| 0x09060e | Build Cybenetics Core |
| 0x090800 | Train Zealot |
| 0x090801 | Train Stalker |
| 0x090803 | Train High Templar |
| 0x090804 | Train Dark Templar |
| 0x090805 | Train Sentry /Disruptor |
| 0x090900 | Train Phoenix |
| 0x090902 | Train Carrier |
| 0x090904 | Train Voidray |
| 0x090a00 | Train Warpprism |
| 0x090a01 | Train Observer |
| 0x090a02 | Train Colossus |
| 0x090a03 | Train Immortal |
| 0x090b00 | Train Probe |
| 0x0A0000 | Research Ground Weapons Level 1 |
| 0x0A0001 | Research Ground Weapons Level 2 |
| 0x0A0002 | Research Ground Weapons Level 3 |
| 0x0A0003 | Research Ground Armor Level 1 |
| 0x0A0004 | Research Ground Armor Level 2 |
| 0x0A0005 | Research Ground Armor Level 3 |
| 0x0A0006 | Research Shields Level1 |
| 0x0A0007 | Research Shields Level2 |
| 0x0A0008 | Research Shields Level3 |
| 0x0A0101 | Research Gravitic Booster |
| 0x0A0102 | Research Gravitic Drive |
| 0x0A0105 | Research Extended Thermal Lance |
| 0x0A0200 | Research High Templar Energy Upgrade |
| 0x0A0204 | Research Psi Storm |
| 0x0b0e00 | Train Zealot (Warp Gate) |
| 0x0b0e01 | Train Stalker (Warp Gate) |
| 0x0b0e03 | Train High Templar (Warp Gate) |
| 0x0b0e04 | Train Dark Templar (Warp Gate) |
| 0x0b0e05 | Train Sentry (Warp Gate) |
| 0x0C0F00 | Upgrade to Warp Gate |
| 0x0D0300 | Force Field (Sentry) |
| 0x0D0700 | Research Air Weapons Level 1 |
| 0x0D0701 | Research Air Weapons Level 2 |
| 0x0D0702 | Research Air Weapons Level 3 |
| 0x0D0703 | Research Air Armor Level 1 |
| 0x0D0704 | Research Air Armor Level 2 |
| 0x0D0705 | Research Air Armor Level 3 |
| 0x0D0706 | Research Warp Gate |
| 0x0D0709 | Research Hallucination |
| 0x0D0800 | Research Charge |
| 0x0D0801 | Research Charge |
| 0x030300 | Research Void Ray Speed Upgrade |
| 0x030301 | Research Interceptor Launch Speed Upgrade |
| 0x030500 | Guardian Shield (Sentry) |
| 0x030700 | Train Mothership |
| 0x030D00 | Train Colossus Hallucination (Sentry) |
| 0x040000 | Train Phoenix Hallucination (Sentry) |
| 0x060100 | Chrono Boost |
| 0x060B00 | Cancel a build in progress (Pylon) |

<br /><br /><br />
# Complete List (to be merged) #
The following list has 402 codes is about 96% complete.

The ~15 remaining codes ( = 4% ) are probably unused and can be ignored.

```
            if (val == 0x020400) return "stops";
            if (val == 0x020402) return "cheers";
            if (val == 0x020403) return "dances";
            if (val == 0x020501) return "holds fire";
            if (val == 0x020600) return "moves";
            if (val == 0x020601) return "patrols";
            if (val == 0x020602) return "holds position";
            if (val == 0x020603) return "stops";
            if (val == 0x020900) return "attacks";
            if (val == 0x030000) return "uses Acid Spores (Unknown Unit)";
            if (val == 0x030100) return "uses Corruption (Corruptor)";
            if (val == 0x030200) return "uses Explode (Baneling)";
            if (val == 0x030300) return "researches ResearchVoidRaySpeedUpgrade (Fleet Beacon)";
            if (val == 0x030301) return "researches ResearchInterceptorLaunchSpeedUpgrade (Fleet Beacon)";
            if (val == 0x030400) return "uses Fungal Growth (Infestor)";
            if (val == 0x030500) return "uses Guardian Shield (Sentry)";
            if (val == 0x030600) return "repairs (MULE)";
            if (val == 0x030700) return "trains a Mothership (Nexus)";
            if (val == 0x030800) return "uses Feedback (High Templar)";
            if (val == 0x030900) return "uses Mass Recall (Mothership)";
            if (val == 0x030A00) return "uses Place Point Defense Drone (Raven)";
            if (val == 0x030C00) return "trains an Archon Hallucination (Sentry)";
            if (val == 0x030D00) return "trains a Colossus Hallucination (Sentry)";
            if (val == 0x030E00) return "trains a High Templar Hallucination (Sentry)";
            if (val == 0x030F00) return "trains an Immortal Hallucination (Sentry)";
            if (val == 0x040000) return "trains a Phoenix Hallucination (Sentry)";
            if (val == 0x040100) return "trains a Probe Hallucination (Sentry)";
            if (val == 0x040200) return "trains a Stalker Hallucination (Sentry)";
            if (val == 0x040300) return "trains a Void Ray Hallucination (Sentry)";
            if (val == 0x040400) return "trains a Warp Prism Hallucination (Sentry)";
            if (val == 0x040500) return "trains a Zealot Hallucination (Sentry)";
            if (val == 0x040600) return "gathers resources (MULE)";
            if (val == 0x040700) return "uses HunterSeekerMissile (Raven)";
            if (val == 0x040800) return "uses Calldown MULE (Orbital Command)";
            if (val == 0x040900) return "uses Graviton Beam (Phoenix)";
            if (val == 0x040B00) return "uses Siphon (Infestor)";
            if (val == 0x040C00) return "uses Spawn Changeling (Overseer)";
            if (val == 0x040D00) return "uses Disguise (Changeling)";
            if (val == 0x040E00) return "uses Disguise As Zealot (Changeling)";
            if (val == 0x040F00) return "uses Disguise As Marine With Shield (Changeling)";
            if (val == 0x050000) return "uses Disguise As Marine Without Shield (Changeling)";
            if (val == 0x050100) return "uses Disguise As Zergling With Wings (Changeling)";
            if (val == 0x050200) return "uses Disguise As Zergling Without Wings (Changeling)";
            if (val == 0x050300) return "uses Phase Shift (High Templar)";
            if (val == 0x050400) return "sets rally point (General Building)";
            if (val == 0x050500) return "sets rally point (Command Center)";
            if (val == 0x050600) return "sets rally point (Nexus)";
            if (val == 0x050700) return "sets rally point (Hatchery)";
            if (val == 0x050701) return "sets rally point for drones (Hatchery)";
            if (val == 0x050800) return "researches EvolveOrganicCarapace (Roach Warren)";
            if (val == 0x050801) return "researches EvolveGlialRegeneration (Roach Warren)";
            if (val == 0x050802) return "researches EvolveTunnelingClaws (Roach Warren)";
            if (val == 0x050900) return "uses Sap Structure (Baneling)";
            if (val == 0x050A00) return "uses Infested Terrans (Infestor)";
            if (val == 0x050B00) return "uses Neural Parasite (Infestor)";
            if (val == 0x050C00) return "uses Spawn Mutant Larva (Queen)";
            if (val == 0x050D00) return "uses Stimpack (Marauder)";
            if (val == 0x050E00) return "uses Supply Drop (Orbital Command)";
            if (val == 0x050F00) return "uses 250mm Strike Cannons (Thor)";
            if (val == 0x060000) return "uses Temporal Rift (High Templar)";
            if (val == 0x060100) return "uses Time Warp (Nexus)";
            if (val == 0x060201) return "researches EvolveAnabolicSynthesis2 (Ultralisk Cavern)";
            if (val == 0x060202) return "researches EvolveChitinousPlating (Ultralisk Cavern)";
            if (val == 0x060300) return "uses Wormhole Transit (Mothership)";
            if (val == 0x060400) return "gathers resources (SCV)";
            if (val == 0x060401) return "uses Return Cargo (SCV)";
            if (val == 0x060500) return "gathers resources (Probe)";
            if (val == 0x060501) return "uses Return Cargo (Probe)";
            if (val == 0x060700) return "cancels a mutation in progress (Drone?)";
            if (val == 0x060701) return "cancels something… (research needed)";
            if (val == 0x060800) return "cancels an attack";
            if (val == 0x060801) return "cancels a build in progress (SCV)";
            if (val == 0x060900) return "cancels something… (research needed)";
            if (val == 0x060901) return "cancels a search in progress (ResearchSiegeTech)";
            if (val == 0x060A00) return "cancels something… (research needed)";
            if (val == 0x060A01) return "cancels a build in progress (SCV at Planetary Fortress)";
            if (val == 0x060B00) return "cancels a build in progress (Pylon)";
            if (val == 0x060C00) return "repairs (SCV)";
            if (val == 0x060D00) return "builds a Command Center";
            if (val == 0x060D01) return "builds a Supply Depot";
            if (val == 0x060D02) return "builds a Refinery";
            if (val == 0x060D03) return "builds a Barracks";
            if (val == 0x060D04) return "builds an Engineering Bay";
            if (val == 0x060D05) return "builds a Missile Turret";
            if (val == 0x060D06) return "builds a Bunker";
            if (val == 0x060D08) return "builds a Sensor Tower";
            if (val == 0x060D09) return "builds a Ghost Academy";
            if (val == 0x060D0A) return "builds a Factory";
            if (val == 0x060D0B) return "builds a Starport";
            if (val == 0x060D0D) return "builds an Armory";
            if (val == 0x060D0F) return "builds a Fusion Core";
            if (val == 0x061D0E) return "cancels a build in progress (Terran Building)";
            if (val == 0x060E00) return "builds an Auto Turret (Raven)";
            if (val == 0x060E01) return "builds a Spider Mine (Raven)";
            if (val == 0x060E03) return "builds a Sensor Tower (Raven)";
            if (val == 0x060E04) return "builds a Targeting Drone (Raven)";
            if (val == 0x061E0E) return "cancels a build in progress (Raven Building)";
            if (val == 0x060F00) return "uses Stimpack (Mixed Units)";
            if (val == 0x070000) return "uses Cloak (Ghost)";
            if (val == 0x070001) return "uses Decloak (Ghost)";
            if (val == 0x070100) return "uses Snipe (Ghost)";
            if (val == 0x070200) return "uses Heal (Medivac)";
            if (val == 0x070300) return "uses Siege Mode (Siege Tank)";
            if (val == 0x070400) return "uses Tank Mode (Siege Tank)";
            if (val == 0x070500) return "uses Cloak (Banshee)";
            if (val == 0x070501) return "uses Decloak (Banshee)";
            if (val == 0x070600) return "uses Load (Medivac)";
            if (val == 0x070601) return "uses Unload All (Medivac)";
            if (val == 0x070602) return "uses Unload All At (Medivac)";
            if (val == 0x070603) return "uses Unload Unit (Medivac)";
            if (val == 0x070604) return "uses Load All (Medivac)";
            if (val == 0x070700) return "uses Scanner Sweep (Orbital Command)";
            if (val == 0x070800) return "uses Yamato Gun (Battlecruiser)";
            if (val == 0x070900) return "uses Assault Mode (Viking)";
            if (val == 0x070A00) return "uses Fighter Mode (Viking)";
            if (val == 0x070B00) return "uses Load (Bunker)";
            if (val == 0x070B01) return "uses Unload All (Bunker)";
            if (val == 0x070B02) return "uses Unload All At (Bunker)";
            if (val == 0x070B03) return "uses Unload Unit (Bunker)";
            if (val == 0x070B04) return "uses Load All (Bunker)";
            if (val == 0x070C00) return "uses Load (Command Center)";
            if (val == 0x070C01) return "uses Unload All (Command Center)";
            if (val == 0x070C02) return "uses Unload All At (Command Center)";
            if (val == 0x070C03) return "uses Unload Unit (Command Center)";
            if (val == 0x070C04) return "uses Load All (Command Center)";
            if (val == 0x070D00) return "uses Lift Off (Command Center)";
            if (val == 0x070E00) return "uses Land (Command Center)";
            if (val == 0x070F00) return "builds a LabTech (Barracks)";
            if (val == 0x070F01) return "builds a Reactor (Barracks)";
            if (val == 0x071F0E) return "cancels an Addon (Barracks)";
            if (val == 0x080000) return "uses Lift Off (Barracks)";
            if (val == 0x080100) return "builds a LabTech (Factory)";
            if (val == 0x080101) return "builds a Reactor (Factory)";
            if (val == 0x08110E) return "cancels an Addon (Factory)";
            if (val == 0x080200) return "sets rally point (Factory)";
            if (val == 0x080300) return "builds a LabTech (Starport)";
            if (val == 0x080301) return "builds a Reactor (Starport)";
            if (val == 0x08130E) return "cancels an Addon (Starport)";
            if (val == 0x080400) return "uses Lift Off (Starport)";
            if (val == 0x080500) return "uses Land (Factory)";
            if (val == 0x080600) return "uses Land (Starport)";
            if (val == 0x080700) return "trains a SCV (Command Center)";
            if (val == 0x080800) return "uses Land (Barracks)";
            if (val == 0x080900) return "lowers a Supply Depot";
            if (val == 0x080A00) return "raises a Supply Depot";
            if (val == 0x080B00) return "trains a Marine (Barracks)";
            if (val == 0x080B01) return "trains a Reaper (Barracks)";
            if (val == 0x080B02) return "trains a Ghost (Barracks)";
            if (val == 0x080B03) return "trains a Marauder (Barracks)";
            if (val == 0x080C01) return "trains a Siege Tank (Factory)";
            if (val == 0x080C04) return "trains a Thor (Factory)";
            if (val == 0x080C05) return "trains a Hellion (Factory)";
            if (val == 0x080D00) return "trains a Medivac (Starport)";
            if (val == 0x080D01) return "trains a Banshee (Starport)";
            if (val == 0x080D02) return "trains a Raven (Starport)";
            if (val == 0x080D03) return "trains a Battlecruiser (Starport)";
            if (val == 0x080D04) return "trains a Viking Fighter (Starport)";
            if (val == 0x080E00) return "researches ResearchHiSecAutoTracking (Engineering Bay)";
            if (val == 0x080E01) return "researches UpgradeBuildingArmorLevel1 (Engineering Bay)";
            if (val == 0x080E02) return "researches TerranInfantryWeaponsLevel1 (Engineering Bay)";
            if (val == 0x080E03) return "researches TerranInfantryWeaponsLevel2 (Engineering Bay)";
            if (val == 0x080E04) return "researches TerranInfantryWeaponsLevel3 (Engineering Bay)";
            if (val == 0x080E05) return "researches ResearchNeosteelFrame (Engineering Bay)";
            if (val == 0x080E06) return "researches TerranInfantryArmorLevel1 (Engineering Bay)";
            if (val == 0x080E07) return "researches TerranInfantryArmorLevel2 (Engineering Bay)";
            if (val == 0x080E08) return "researches TerranInfantryArmorLevel3 (Engineering Bay)";
            if (val == 0x080F03) return "researches ReaperSpeed (Barracks TechLab)";
            if (val == 0x090000) return "arms Silo With Nuke";
            if (val == 0x090100) return "researches StimPack (Barracks TechLab)";
            if (val == 0x090101) return "researches ResearchShieldWall (Barracks TechLab)";
            if (val == 0x090102) return "researches ResearchPunisherGrenades (Barracks TechLab)";
            if (val == 0x090200) return "researches ResearchSiegeTech (Factory TechLab)";
            if (val == 0x090201) return "researches ResearchHighCapacityBarrels (Factory TechLab)";
            if (val == 0x090300) return "researches ResearchBansheeCloak (Starport TechLab)";
            if (val == 0x090302) return "researches ResearchMedivacEnergyUpgrade (Starport TechLab)";
            if (val == 0x090303) return "researches ResearchRavenEnergyUpgrade (Starport TechLab)";
            if (val == 0x090306) return "researches ResearchSeekerMissile (Starport TechLab)";
            if (val == 0x090307) return "researches ResearchDurableMaterials (Starport TechLab)";
            if (val == 0x090400) return "researches ResearchPersonalCloaking (Ghost Academy)";
            if (val == 0x090401) return "researches GhostMoebiusReactor (Ghost Academy)";
            if (val == 0x090405) return "researches EMP (Ghost Academy)";
            if (val == 0x090502) return "researches TerranVehiclePlatingLevel1 (Armory)";
            if (val == 0x090503) return "researches TerranVehiclePlatingLevel2 (Armory)";
            if (val == 0x090504) return "researches TerranVehiclePlatingLevel3 (Armory)";
            if (val == 0x090505) return "researches TerranVehicleWeaponsLevel1 (Armory)";
            if (val == 0x090506) return "researches TerranVehicleWeaponsLevel2 (Armory)";
            if (val == 0x090507) return "researches TerranVehicleWeaponsLevel3 (Armory)";
            if (val == 0x090508) return "researches TerranShipPlatingLevel1 (Armory)";
            if (val == 0x090509) return "researches TerranShipPlatingLevel2 (Armory)";
            if (val == 0x09050A) return "researches TerranShipPlatingLevel3 (Armory)";
            if (val == 0x09050B) return "researches TerranShipWeaponsLevel1 (Armory)";
            if (val == 0x09050C) return "researches TerranShipWeaponsLevel2 (Armory)";
            if (val == 0x09050D) return "researches TerranShipWeaponsLevel3 (Armory)";
            if (val == 0x090600) return "builds a Nexus";
            if (val == 0x090601) return "builds a Pylon";
            if (val == 0x090602) return "builds an Assimilator";
            if (val == 0x090603) return "builds a Gateway";
            if (val == 0x090604) return "builds a Forge";
            if (val == 0x090605) return "builds a Fleet Beacon";
            if (val == 0x090606) return "builds a Twilight Council";
            if (val == 0x090607) return "builds a Photon Cannon";
            if (val == 0x090609) return "builds a Stargate";
            if (val == 0x09060A) return "builds a Templar Archive";
            if (val == 0x09060B) return "builds a Dark Shrine";
            if (val == 0x09060C) return "builds a Robotics Bay";
            if (val == 0x09060D) return "builds a Robotics Facility";
            if (val == 0x09060E) return "builds a Cybenetics Core";
            if (val == 0x09060F) return "builds an Obelisk";
            if (val == 0x09160E) return "cancels a build in progress (Protoss Building)";
            if (val == 0x090700) return "uses Load (Warp Prism)";
            if (val == 0x090701) return "uses Unload All (Warp Prism)";
            if (val == 0x090702) return "uses Unload All At (Warp Prism)";
            if (val == 0x090703) return "uses Unload Unit (Warp Prism)";
            if (val == 0x090704) return "uses Load All (Warp Prism)";
            if (val == 0x090800) return "trains a Zealot (Gateway)";
            if (val == 0x090801) return "trains a Stalker (Gateway)";
            if (val == 0x090803) return "trains a High Templar (Gateway)";
            if (val == 0x090804) return "trains a Dark Templar (Gateway)";
            if (val == 0x090805) return "trains a Sentry /Disruptor (Gateway)";
            if (val == 0x090900) return "trains a Phoenix (Stargate)";
            if (val == 0x090902) return "trains a Carrier (Stargate)";
            if (val == 0x090904) return "trains a Void Ray (Stargate)";
            if (val == 0x090A00) return "trains a Warp Prism (Robotics Facility)";
            if (val == 0x090A01) return "trains an Observer (Robotics Facility)";
            if (val == 0x090A02) return "trains a Colossus (Robotics Facility)";
            if (val == 0x090A03) return "trains an Immortal (Robotics Facility)";
            if (val == 0x090B00) return "trains a Probe (Nexus)";
            if (val == 0x090C00) return "uses Psi Storm (High Templar)";
            if (val == 0x090F00) return "trains an Interceptor (Carrier)";
            if (val == 0x0A0000) return "researches ProtossGroundWeaponsLevel1 (Forge)";
            if (val == 0x0A0001) return "researches ProtossGroundWeaponsLevel2 (Forge)";
            if (val == 0x0A0002) return "researches ProtossGroundWeaponsLevel3 (Forge)";
            if (val == 0x0A0003) return "researches ProtossGroundArmorLevel1 (Forge)";
            if (val == 0x0A0004) return "researches ProtossGroundArmorLevel2 (Forge)";
            if (val == 0x0A0005) return "researches ProtossGroundArmorLevel3 (Forge)";
            if (val == 0x0A0006) return "researches ProtossShieldsLevel1 (Forge)";
            if (val == 0x0A0007) return "researches ProtossShieldsLevel2 (Forge)";
            if (val == 0x0A0008) return "researches ProtossShieldsLevel3 (Forge)";
            if (val == 0x0A0101) return "researches ResearchGraviticBooster (Robotics Bay)";
            if (val == 0x0A0102) return "researches ResearchGraviticDrive (Robotics Bay)";
            if (val == 0x0A0105) return "researches ResearchExtendedThermalLance (Robotics Bay)";
            if (val == 0x0A0200) return "researches ResearchHighTemplarEnergyUpgrade (Templar Archives)";
            if (val == 0x0A0204) return "researches ResearchPsiStorm (Templar Archives)";
            if (val == 0x0A0300) return "builds a Hatchery";
            if (val == 0x0A0301) return "builds a Creep Tumor";
            if (val == 0x0A0302) return "builds an Extractor";
            if (val == 0x0A0303) return "builds a Spawning Pool";
            if (val == 0x0A0304) return "builds an Evolution Chamber";
            if (val == 0x0A0305) return "builds a Hydralisk Den";
            if (val == 0x0A0306) return "builds a Ppire";
            if (val == 0x0A0307) return "builds an Ultralisk Cavern";
            if (val == 0x0A0308) return "builds an Infestation Pit";
            if (val == 0x0A0309) return "builds a Nydus Network";
            if (val == 0x0A030A) return "builds a Baneling Nest";
            if (val == 0x0A030B) return "builds a Lurker Den";
            if (val == 0x0A030D) return "builds a Roach Warren";
            if (val == 0x0A030E) return "builds a Spine Crawler";
            if (val == 0x0A030F) return "builds a Spore Crawler";
            if (val == 0x0A130E) return "cancels a build in progress (Zerg Building)";
            if (val == 0x0A0400) return "gathers resources (Drone)";
            if (val == 0x0A0401) return "uses Return Cargo (Drone)";
            if (val == 0x0A0500) return "researches zergmeleeweapons1 (Evolution Chamber)";
            if (val == 0x0A0501) return "researches zergmeleeweapons2 (Evolution Chamber)";
            if (val == 0x0A0502) return "researches zergmeleeweapons3 (Evolution Chamber)";
            if (val == 0x0A0503) return "researches zerggroundarmor1 (Evolution Chamber)";
            if (val == 0x0A0504) return "researches zerggroundarmor2 (Evolution Chamber)";
            if (val == 0x0A0505) return "researches zerggroundarmor3 (Evolution Chamber)";
            if (val == 0x0A0506) return "researches zergmissileweapons1 (Evolution Chamber)";
            if (val == 0x0A0507) return "researches zergmissileweapons2 (Evolution Chamber)";
            if (val == 0x0A0508) return "researches zergmissileweapons3 (Evolution Chamber)";
            if (val == 0x0A050A) return "researches ResearchBurrow (Evolution Chamber)";
            if (val == 0x0A0600) return "upgrades to Lair (Hatchery)";
            if (val == 0x0A0601) return "cancels Lair upgrade (Hatchery)";
            if (val == 0x0A0700) return "upgrades to Hive (Lair)";
            if (val == 0x0A0701) return "cancels Hive upgrade (Lair)";
            if (val == 0x0A0800) return "upgrades to Greater Spire (Spire)";
            if (val == 0x0A0801) return "cancels Greater Spire upgrade (Spire)";
            if (val == 0x0A0901) return "researches overlordspeed (Lair)";
            if (val == 0x0A0902) return "researches EvolveVentralSacks (Lair)";
            if (val == 0x0A0903) return "researches EnduringCorruption (Lair)";
            if (val == 0x0A0904) return "researches RazorTech (Lair)";
            if (val == 0x0A0A00) return "researches zerglingattackspeed (Spawning Pool)";
            if (val == 0x0A0A01) return "researches zerglingmovementspeed (Spawning Pool)";
            if (val == 0x0A0B02) return "researches hydraliskspeed (Hydralisk Den)";
            if (val == 0x0A0C00) return "researches zergflyerattack1 (Spire)";
            if (val == 0x0A0C01) return "researches zergflyerattack2 (Spire)";
            if (val == 0x0A0C02) return "researches zergflyerattack3 (Spire)";
            if (val == 0x0A0C03) return "researches zergflyerarmor1 (Spire)";
            if (val == 0x0A0C04) return "researches zergflyerarmor2 (Spire)";
            if (val == 0x0A0C05) return "researches zergflyerarmor3 (Spire)";
            if (val == 0x0A0D00) return "trains a Drone (Larva)";
            if (val == 0x0A0D01) return "trains a Zergling (Larva)";
            if (val == 0x0A0D02) return "trains an Overlord (Larva)";
            if (val == 0x0A0D03) return "trains a Hydralisk (Larva)";
            if (val == 0x0A0D04) return "trains a Mutalisk (Larva)";
            if (val == 0x0A0D05) return "trains a Scourge (Larva)";
            if (val == 0x0A0D06) return "trains an Ultralisk (Larva)";
            if (val == 0x0A0D07) return "trains a Baneling (Larva)";
            if (val == 0x0A0D09) return "trains a Roach (Larva)";
            if (val == 0x0A0D0A) return "trains an Infestor (Larva)";
            if (val == 0x0A0D0B) return "trains a Corruptor (Larva)";
            if (val == 0x0A0D0C) return "trains a Mutalisk (Larva)";
            if (val == 0x0A0E00) return "mutates into a Brood Lord (Corruptor)";
            if (val == 0x0A0E01) return "cancels Brood Lord mutation (Corruptor)";
            if (val == 0x0A0F00) return "uses Burrow (Baneling)";
            if (val == 0x0B0000) return "uses Unburrow (Baneling)";
            if (val == 0x0B0100) return "uses Burrow (Drone)";
            if (val == 0x0B0200) return "uses Unburrow (Drone)";
            if (val == 0x0B0300) return "uses Burrow (Hydralisk)";
            if (val == 0x0B0400) return "uses Unburrow (Hydralisk)";
            if (val == 0x0B0500) return "uses Burrow (Roach)";
            if (val == 0x0B0600) return "uses Unburrow (Roach)";
            if (val == 0x0B0700) return "uses Burrow (Zergling)";
            if (val == 0x0B0800) return "uses Unburrow (Zergling)";
            if (val == 0x0B0900) return "uses Burrow (InfestorTerran)";
            if (val == 0x0B0A00) return "uses Unburrow (InfestorTerran)";
            if (val == 0x0B0B00) return "uses Load (Overlord)";
            if (val == 0x0B0B01) return "uses Unload All (Overlord)";
            if (val == 0x0B0B02) return "uses Unload All At (Overlord)";
            if (val == 0x0B0B03) return "uses Unload Unit (Overlord)";
            if (val == 0x0B0B04) return "uses Load All (Overlord)";
            if (val == 0x0B0E00) return "trains a Zealot (Warp Gate)";
            if (val == 0x0B0E01) return "trains a Stalker (Warp Gate)";
            if (val == 0x0B0E02) return "trains an Immortal (Warp Gate)";
            if (val == 0x0B0E03) return "trains a High Templar (Warp Gate)";
            if (val == 0x0B0E04) return "trains a Dark Templar (Warp Gate)";
            if (val == 0x0B0E05) return "trains a Sentry (Warp Gate)";
            if (val == 0x0B0F00) return "uses Burrow (Queen)";
            if (val == 0x0C0000) return "uses Unburrow (Queen)";
            if (val == 0x0C0100) return "mutates into a Baneling (Zergling)";
            if (val == 0x0C0200) return "uses Load (Nydus Worm)";
            if (val == 0x0C0201) return "uses Unload All (Nydus Worm)";
            if (val == 0x0C0202) return "uses Unload All At (Nydus Worm)";
            if (val == 0x0C0203) return "uses Unload Unit (Nydus Worm)";
            if (val == 0x0C0204) return "uses Load All (Nydus Worm)";
            if (val == 0x0C0300) return "uses Blink (Stalker)";
            if (val == 0x0C0400) return "uses Burrow (Infestor)";
            if (val == 0x0C0500) return "uses Unburrow (Infestor)";
            if (val == 0x0C0600) return "mutates into an Overseer (Overlord)";
            if (val == 0x0C0601) return "cancels Overseer mutation";
            if (val == 0x0C0700) return "upgrades to Planetary Fortress (Command Center)";
            if (val == 0x0C0701) return "cancels Planetary Fortress upgrade";
            if (val == 0x0C0900) return "researches Disease (Infestation Pit)";
            if (val == 0x0C0901) return "researches InfestorPeristalsis (Infestation Pit)";
            if (val == 0x0C0902) return "researches InfestorEnergyUpgrade (Infestation Pit)";
            if (val == 0x0C0A00) return "researches EvolveCentrificalHooks (Baneling Nest)";
            if (val == 0x0C0B00) return "uses Burrow (Ultralisk)";
            if (val == 0x0C0C00) return "uses Unburrow (Ultralisk)";
            if (val == 0x0C0D00) return "uses D8 Charge (Unknown Unit)";
            if (val == 0x0C0E00) return "upgrades to Orbital Command (Command Center)";
            if (val == 0x0C0E01) return "cancels Orbital Command upgrade (Command Center)";
            if (val == 0x0C0F00) return "upgrades to Warp Gate (Gateway)";
            if (val == 0x0C0F01) return "cancels Warp Gate upgrade (Gateway)";
            if (val == 0x0D0000) return "mutates into a Gateway (Warp Gate)";
            if (val == 0x0D0001) return "cancels Gateway mutation (Warp Gate)";
            if (val == 0x0D0100) return "uses Lift Off (Orbital Command)";
            if (val == 0x0D0200) return "uses Land (Orbital Command)";
            if (val == 0x0D0300) return "uses Force Field (Sentry)";
            if (val == 0x0D0400) return "uses Phasing Mode (Warp Prism)";
            if (val == 0x0D0500) return "uses Transport Mode (Warp Prism)";
            if (val == 0x0D0600) return "researches BattlecruiserEnableSpecializations (Fusion Core)";
            if (val == 0x0D0601) return "researches BattlecruiserBehemothReactor (Fusion Core)";
            if (val == 0x0D0700) return "researches ProtossAirWeaponsLevel1 (Cybernetics Core)";
            if (val == 0x0D0701) return "researches ProtossAirWeaponsLevel2 (Cybernetics Core)";
            if (val == 0x0D0702) return "researches ProtossAirWeaponsLevel3 (Cybernetics Core)";
            if (val == 0x0D0703) return "researches ProtossAirArmorLevel1 (Cybernetics Core)";
            if (val == 0x0D0704) return "researches ProtossAirArmorLevel2 (Cybernetics Core)";
            if (val == 0x0D0705) return "researches ProtossAirArmorLevel3 (Cybernetics Core)";
            if (val == 0x0D0706) return "researches ResearchWarpGate (Cybernetics Core)";
            if (val == 0x0D0709) return "researches ResearchHallucination (Cybernetics Core)";
            if (val == 0x0D0800) return "researches Charge (Twilight Council)";
            if (val == 0x0D0801) return "researches BlinkTech (Twilight Council)";
            if (val == 0x0D0900) return "uses Tactical Nuclear Strike (Ghost)";
            if (val == 0x0D0901) return "cancels Tactical Nuclear Strike (Ghost)";
            if (val == 0x0D0B00) return "uses Salvage (Bunker)";
            if (val == 0x0D0C00) return "uses EMP (Ghost)";
            if (val == 0x0D0D00) return "uses Vortex (Mothership)";
            if (val == 0x0D0E00) return "trains a Queen (Hatchery, Lair or Hive)";
            if (val == 0x0D0F00) return "uses Burrow (Creep Tumor)";
            if (val == 0x0E0000) return "uses Transfusion (Queen)";
            if (val == 0x0E0900) return "attacks (Mixed Units)";
            if (val == 0x0E0A00) return "uses Stimpack (Mixed Units)";
            if (val == 0x0E0B00) return "stops (Mixed Units)";
            if (val == 0x0E0C00) return "stops (Mixed Units)";
            if (val == 0x0E0D00) return "uses Generate Creep (Overlord)";
            if (val == 0x0E0D01) return "cancels Generate Creep (Overlord)";
            if (val == 0x0E0E00) return "builds Creep Tumor (Queen)";
            if (val == 0x0E1E0E) return "cancels a build in progress (Queen Building)";
            if (val == 0x0E0F00) return "uses Uproot (Spine Crawler)";
            if (val == 0x0F0000) return "uses Uproot (Spore Crawler)";
            if (val == 0x0F0100) return "uses Root (Spine Crawler)";
            if (val == 0x0F0200) return "uses Root (Spore Crawler)";
            if (val == 0x0F0300) return "builds Creep Tumor (Creep Tumor)";
            if (val == 0x0F130E) return "cancels a build in progress (Creep Tumor Building)";
            if (val == 0x0F0400) return "uses Auto Turret (Raven)";
            if (val == 0x0F0500) return "uses Archon Warp (High Templar or Dark Templar)";
            if (val == 0x0F0600) return "builds a Nydus Canal (Nydus Network)";
            if (val == 0x0F160E) return "cancels a build in progress (Nydus Network Building)";
            if (val == 0x0F0700) return "trains Broodling Escort (Brood Lord)";
            if (val == 0x0F0800) return "uses Charge (Zealot)";
            if (val == 0x0F0A00) return "mutates into an Infested Terran (Infested Terrans Egg)";
            if (val == 0xFFFF0F) return "right-clicks";
```