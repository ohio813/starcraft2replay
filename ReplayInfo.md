# Byte aligned parsing #

Working, but not satisfying

```
  // Always 16 ?
  numberOfSlots_ = buffer[offset];
  offset += sizeof(uint8_t);

  for ( unsigned char i=0; i<numberOfSlots_; ++i )
  {
    uint8_t length = buffer[offset];
    offset += sizeof(uint8_t);
    
    if ( length > 0 )
      playerNames_.push_back( std::string( (const char*)(buffer+offset), length ) );
    offset += length*sizeof(uint8_t);
    
    offset += sizeof(uint8_t);  // Padding ?
    offset += sizeof(uint32_t); // Padding ?
  }
  
  // Why do we have an extra offset ? One of the slots have only 4 bytes padding ?
  offset -= sizeof(uint8_t);
  
  // What is this ?
  offset += sizeof(uint8_t);
  offset += sizeof(uint32_t);
  
  // A length and a string, storing what ?
  uint8_t unknownLength1_ = buffer[offset];
  offset += sizeof(uint8_t);
  
  offset += unknownLength1_*sizeof(uint8_t);
  
  // Alliance locked ?
  allianceLocked_ = buffer[offset] & 0x01;
  offset += sizeof(uint8_t);
  
  // A bunch of unknown bytes
  offset += 3 * sizeof(uint8_t);
  
  // Game speed
  speed_ = static_cast<GameSpeed>(buffer[offset] & 0x07);
  offset += sizeof(uint8_t);
  
  // A bunch of unknown bytes
  offset += 9 * sizeof(uint8_t);
  
  // Map filename length
  uint8_t mapFilenameLength = buffer[offset];
  offset += sizeof(uint8_t);
  
  // Map filename string
  mapFilename_ = std::string( (const char*)(buffer+offset), mapFilenameLength );
  offset += mapFilenameLength * sizeof(uint8_t);
  
  /*
  // Big bunch of unknown bytes, often equal between replays
  offset += 92 * sizeof(uint8_t);
  
  // Big bunch of unknown bytes again
  offset += 593 * sizeof(uint8_t);
  offset += sizeof(uint8_t);
  */
  // Temporary hack - skip the unknown variable length chunk
  while ( !(buffer[offset-1]==0x1F && buffer[offset]==0x28)  )
    offset += sizeof(uint8_t);
  
  offset += sizeof(uint8_t);
  
  // 5 structures starting with "s2ma" 0 "USB" ... 40 bytes long
  offset += 5 * 40 * sizeof(uint8_t);
  
  // 5 bytes always here
  offset += 5 * sizeof(uint8_t);
  
  /*
  // No idea :/ can't find the exact length, should be stored in the marker bytes
  //10 0E 02 06 08 01    64 02 06 15    80 24 2F 3F A6 AF 00                                  00 00 00 00
  //20 0C 02 06 08 03 01 64 02 06 15 01 80 24 2C 06 8F B4 00                                  00 00 00 00
  //10 0E 02 06 08 03 02 64 02 06 15 01 80 24 95 B6 1B A2 00                                  00 00 00 00
  //20 0C 02 06 08 01    64 02 06 15 01 81 24 A6 BF E3 22 00                                  00 00 00 00
  //20 2C 00 06 08 01    64 02 06 14 01 80 24 02 05 8F 00 C0 04 82 13 49 00 C0 04 94 B7 9E 32 00 00 00 00
  //               ^^ ^^          ^^ ^^                   ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^
  
  // For now, let's run until we find 4 bytes equals to 0, that sould be just before the name of the map
  uint8_t unknown1 = buffer[offset];
  offset += sizeof(uint8_t);
  
  // if 0x01, then followed by      0x64 0x02 0x06
  // if 0x03, then followed by 0x?? 0x64 0x02 0x06
  if ( unknown1==0x03 )
    offset += sizeof(uint8_t);
  
  // Always 0x64 0x02 0x06 ?
  offset += 3 * sizeof(uint8_t);
  
  uint8_t unknown2 = buffer[offset];
  offset += sizeof(uint8_t);
  
  uint8_t unknown3 = buffer[offset];
  offset += sizeof(uint8_t);
  
  // If 0x15 then short tail, if 0x14 then long tail ?
  if ( unknown2==0x15 && unknown3==0x80 )
    offset += 10 * sizeof(uint8_t);
  else if ( unknown2==0x15 && unknown3==0x01 )
    offset += 11 * sizeof(uint8_t);
  else if ( unknown2==0x14 && unknown3==0x01 )
    offset += 22 * sizeof(uint8_t);
  */
  
  // Temporary hack - skip the unknown variable length chunk
  while ( !( buffer[offset-3] == 0x00 &&
             buffer[offset-2] == 0x00 &&
             buffer[offset-1] == 0x00 &&
             buffer[offset  ] == 0x00 &&
             (buffer[offset+1]>0 || buffer[offset+2]>0) &&
             buffer[offset+3]  > 0x1F) )
    offset += sizeof(uint8_t);
  offset += sizeof(uint8_t);
  
  // Map name length
  uint16_t mapNameLength = (buffer[offset] << 2) + buffer[offset+sizeof(uint8_t)];
  offset+= sizeof(uint16_t);
  
  // Map name
  mapName_ = std::string( (const char*)buffer+offset, mapNameLength );
  offset += mapNameLength * sizeof(uint8_t);
  
  // Always 0 ?
  offset += sizeof(uint8_t);
  
  // Player display count
  numberOfPlayerDisplay_ = buffer[offset];
  offset += sizeof(uint8_t);
  
  // Players displays
  for ( uint8_t i=0; i<numberOfPlayerDisplay_; ++i )
  {
    // Name length
    uint8_t nameLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Name
    std::string name( (const char*)buffer+offset, nameLength );
    offset += nameLength * sizeof(uint8_t);
    
    // Race length
    uint8_t raceLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Race
    std::string race( (const char*)buffer+offset, raceLength );
    offset += raceLength * sizeof(uint8_t);
    
    // Color length
    uint8_t colorLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Color
    std::string color( (const char*)buffer+offset, colorLength );
    offset += colorLength * sizeof(uint8_t);
    
    playerDisplays_.push_back( PlayerDisplay( name, race, color ) );
  }
```

# Bitstream parsing #

Satisfying, but not working ATM

```
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <list>

//--------------------------------------------------
// BITSTREAM
//--------------------------------------------------

class Bitstream
{
public:
  Bitstream();
  ~Bitstream();

public:
  void loadFromFile( const std::string& filename );
  
public:
  template <typename T>
  void read( T& out, unsigned char size ) const;
  void skip( unsigned char size ) const;
  void rewind( unsigned char size ) const;
  void align() const;
  
public:
  unsigned int         position() const;
  const unsigned char* buffer  () const;
  unsigned int         size    () const;
  
private:
  unsigned char*       buffer_;
  mutable unsigned int position_;
  unsigned int         size_;
};

Bitstream::Bitstream()
  : buffer_  ( 0 ),
    position_( 0 ),
    size_    ( 0 )
{
}

Bitstream::~Bitstream()
{
  delete [] buffer_;
}

void Bitstream::loadFromFile( const std::string& filename )
{
  delete [] buffer_;
  size_ = 0;
  position_ = 0;
  
  std::ifstream file( filename.c_str(), std::ios::binary );
  
  assert( file && "Error, cannot find replay file." );
  
  file.seekg( 0, std::ios::end );
  size_ = file.tellg();
  file.seekg( 0, std::ios::beg );
  
  buffer_ = new unsigned char[size_];
  file.read( (char*)buffer_, size_ );
  
  file.close();
}

template <typename T>
void Bitstream::read( T& out, unsigned char size ) const
{
  // sanity check
  assert( sizeof(T)*8 >= size && "Error, size of input higher than size of output in Bitstream::read()" );

  // Clean up the output
  out = (T)0;
  
  // Construct the output
  for ( int currentBit=position_; currentBit < position_+size; ++currentBit )
    out |= ((((int)(buffer_[currentBit>>3])&(1<<(currentBit&7)))!=0)?1:0) << (currentBit-position_);
  
  // Update the position
  position_ += size;
}

void Bitstream::skip( unsigned char size ) const
{
  position_ += size;
}

void Bitstream::rewind( unsigned char size ) const
{
  position_ -= size;
}

void Bitstream::align() const
{
  position_ += 8-(position_%8);
}

unsigned int Bitstream::position() const
{
  return position_;
}

const unsigned char* Bitstream::buffer() const
{
  return buffer_;
}

unsigned int Bitstream::size() const
{
  return size_;
}

//--------------------------------------------------
// BITSTRUCTURE
//--------------------------------------------------

class BitStructure
{
public:
  virtual void serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum ) = 0;
};

//--------------------------------------------------
// LIST
//--------------------------------------------------

template <typename T>
class List : public BitStructure
{
public:
  List();
  ~List();
  
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=8, unsigned int minimum=0, unsigned int maximum=255 );
  
public:
  const std::list<T>& list() const;
  
private:
  unsigned int size_;
  std::list<T> items_;
};

template <typename T>
List<T>::List()
  : size_( 0 )
{
}

template <typename T>
List<T>::~List()
{
}

template <typename T>
void List<T>::serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum )
{
  stream.read( size_, size );
  
  for ( unsigned int i=0; i<size_; ++i )
  {
    T item;
    item.serialize( stream );
    items_.push_back( item );
  }
}

template <typename T>
const std::list<T>& List<T>::list() const
{
  return items_;
}

//--------------------------------------------------
// ASCIISTRING
//--------------------------------------------------

class AsciiString : public BitStructure
{
public:
  AsciiString();
  ~AsciiString();
  
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=8, unsigned int minimum=0, unsigned int maximum=255 );
  
public:
  const std::string& text() const;
  
//private:
  unsigned int size_;
  std::string  text_;
};

AsciiString::AsciiString()
  : size_( 0 )
{
}

AsciiString::~AsciiString()
{
}

void AsciiString::serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum )
{
  // Align if needed
  if ( stream.position()%8 )
    stream.align();
  
  stream.read( size_, size );
  
  for ( int i=0; i<size_; ++i )
  {
    // Align if needed
    if ( stream.position()%8 )
      stream.align();
    
    unsigned char c;
    stream.read( c, 8 );
    text_.append( 1, c );
  }
}

const std::string& AsciiString::text() const
{
  return text_;
}

//--------------------------------------------------
// UNICODESTRING
//--------------------------------------------------

//class UnicodeString : public BitStructure
//{
//public:
//  UnicodeString();
//  ~UnicodeString();
//  
//public:
//  virtual void serialize( const Bitstream& stream, unsigned char size=8, unsigned int minimum=0, unsigned int maximum=0 );
//};

typedef AsciiString UnicodeString;

//--------------------------------------------------
// FIXEDSTRING
//--------------------------------------------------

class FixedString : public BitStructure
{
public:
  FixedString();
  ~FixedString();
  
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int minimum=0, unsigned int maximum=255 );
  
public:
  const std::string& text() const;
  
//private:
  unsigned int size_;
  std::string  text_;
};

FixedString::FixedString()
{
}

FixedString::~FixedString()
{
}

void FixedString::serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum )
{
  size_ = size;
  
  for ( int i=0; i<size_; ++i )
  {
    // Align if needed
    if ( stream.position()%8 )
      stream.align();
    
    unsigned char c;
    stream.read( c, 8 );
    text_.append( 1, c );
  }
}

const std::string& FixedString::text() const
{
  return text_;
}

//--------------------------------------------------
// NULLABLE
//--------------------------------------------------

template <typename T>
class Nullable : public BitStructure
{
public:
  Nullable();
  ~Nullable();
  
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=8, unsigned int minimum=0, unsigned int maximum=255 );
  
//private:
  T    item_;
  bool present_;
};

template <typename T>
Nullable<T>::Nullable()
  : present_( false )
{
}

template <typename T>
Nullable<T>::~Nullable()
{
}

template <typename T>
void Nullable<T>::serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum )
{
  stream.read( present_, 1 );
  
  if ( present_ )
    item_.serialize( stream, size );
}

//--------------------------------------------------
// INTEGER
//--------------------------------------------------

class Integer : public BitStructure
{
public:
  Integer();
  Integer( unsigned int );
  ~Integer();
  
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=32, unsigned int minimum=0, unsigned int maximum=0xFFFFFFFF );
  
//private:
  unsigned int value_;
};

Integer::Integer()
  : value_( 0 )
{
}

Integer::Integer( unsigned int i )
  : value_( i )
{
}

Integer::~Integer()
{
}

void Integer::serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum )
{
  stream.read( value_, size );
}

//--------------------------------------------------
// BOOL
//--------------------------------------------------

class Bool : public BitStructure
{
public:
  Bool();
  ~Bool();
  
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=1, unsigned int minimum=0, unsigned int maximum=1 );
  
//private:
  bool value_;
};

Bool::Bool()
 : value_( false )
{
}

Bool::~Bool()
{
}

void Bool::serialize( const Bitstream& stream, unsigned char size, unsigned int minimum, unsigned int maximum )
{
  stream.read( value_, 1 );
}

//--------------------------------------------------
// STRUCTURES
//--------------------------------------------------

enum Unknown045
{
  unknown045_0 = 0,
  unknown045_1 = 1,
  unknown045_2 = 2
};

enum Unknown1A0
{
  unknown1A0_0 = 0,
  unknown1A0_1 = 1,
  unknown1A0_2 = 2,
  unknown1A0_3 = 3,
  unknown1A0_4 = 4
};

enum Unknown19D
{
  unknown19D_0 = 0,
  unknown19D_1 = 1,
  unknown19D_2 = 2,
  unknown19D_3 = 3
};

enum Unknown19E
{
  unknown19E_0 = 0,
  unknown19E_1 = 1,
  unknown19E_2 = 2,
  unknown19E_3 = 3
};

enum Unknown19F
{
  unknown19F_0 = 0,
  unknown19F_1 = 1,
  unknown19F_2 = 2
};

enum Unknown0B0
{
  unknown0B0_0 = 0,
  unknown0B0_1 = 1,
  unknown0B0_2 = 2,
  unknown0B0_3 = 3,
  unknown0B0_4 = 4
};

enum Unknown1AD
{
  unknown1AD_0 = 0,
  unknown1AD_1 = 1,
  unknown1AD_2 = 2,
  unknown1AD_3 = 3,
  unknown1AD_4 = 4,
  unknown1AD_5 = 5,
  unknown1AD_6 = 6
};

enum Unknown19B
{
  unknown19B_0 = 0,
  unknown19B_1 = 1,
  unknown19B_2 = 2,
  unknown19B_3 = 3,
  unknown19B_4 = 4,
  unknown19B_5 = 5
};

struct PlayerInfo : public BitStructure
{
public:
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    name.serialize ( stream, 8, 0, 32 );
    race.serialize ( stream, 8, 0, 63 );
    color.serialize( stream, 7, 0, 31 );
  }
  
//private:
  AsciiString name;
  AsciiString race;
  AsciiString color;
};

struct Unknown060 : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    unknown061.serialize( stream, 5, 0, 31 );
  }

  Nullable<Integer> unknown061;
};

struct Unknown022 : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    unknown023.serialize( stream, 8, 0, 254 );
  }

  Nullable<Integer> unknown023;
};

struct Unknown1B1 : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    unknown1B2.serialize( stream, 6, 0,  32 );
    unknown1B3.serialize( stream, 8, 0, 255 );
    unknown1B4.serialize( stream, 6, 0,  32 );
    unknown1B5.serialize( stream, 8, 0, 255 );
    unknown1B6.serialize( stream, 2, 0,   3 );
  }

  List<Bool> unknown1B2;
  List<Bool> unknown1B3;
  List<Bool> unknown1B4;
  List<Bool> unknown1B5;
  List<Bool> unknown1B6;
};

struct Unknown1A1 : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    unknown1A2.serialize( stream );
    unknown1A3.serialize( stream );
    unknown1A4.serialize( stream );
    unknown1A5.serialize( stream );
    unknown1A6.serialize( stream );
    unknown1A7.serialize( stream );
    unknown1A8.serialize( stream );
    
    int enumeration;
    stream.read( enumeration, 3 ); unknown1A9 = (Unknown1A0)enumeration;
    stream.read( enumeration, 2 ); unknown1AA = (Unknown19D)enumeration;
    stream.read( enumeration, 2 ); unknown1AB = (Unknown19E)enumeration;
    stream.read( enumeration, 2 ); unknown1AC = (Unknown19F)enumeration;
  }

  Bool       unknown1A2;
  Bool       unknown1A3;
  Bool       unknown1A4;
  Bool       unknown1A5;
  Bool       unknown1A6;
  Bool       unknown1A7;
  Bool       unknown1A8;
  Unknown1A0 unknown1A9;
  Unknown19D unknown1AA;
  Unknown19E unknown1AB;
  Unknown19F unknown1AC;
};

struct PlayerSetup : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    stream.align();
    unknown1D7.serialize( stream, 8 );
    unknown1D8.serialize( stream, 4, 0, 15 );
    unknown1D9.serialize( stream, 4 );
    unknown1DA.serialize( stream );
    unknown1DB.serialize( stream );
    unknown1DC.serialize( stream, 6 );
    unknown1DD.serialize( stream, 7 );
    
    int enumeration;
    stream.read( enumeration, 2 ); unknown1DE = (Unknown045)enumeration;
  }

  Integer           unknown1D7;
  Nullable<Integer> unknown1D8;
  Integer           unknown1D9;
  Unknown060        unknown1DA;
  Unknown022        unknown1DB;
  Integer           unknown1DC;
  Integer           unknown1DD;
  Unknown045        unknown1DE;
};

struct Unknown1E2 : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    //------------------- NOT WORKING ATM -------------------
    int enumeration;
    stream.read( enumeration, 3 ); unknown1E3 = (Unknown19B)enumeration;
    
    unknown1E4.serialize( stream, 5 );
    unknown1E5.serialize( stream, 5 );
    
    stream.align();
    playerSetup.serialize( stream, 5, 0, 16 );
    
    stream.align();
    unknown1E7.serialize( stream, 32 );
    
    stream.align();
    unknown1E8.serialize( stream, 4, 0, 15 );
    
    stream.align();
    unknown1E9.serialize( stream );
    
    stream.align();
    unknown1EA.serialize( stream, 32 );
    
    stream.align();
    unknown1EB.serialize( stream, 6 );
    //-------------------------------------------------------
  }

  Unknown19B        unknown1E3;
  Integer           unknown1E4;
  Integer           unknown1E5;
  List<PlayerSetup> playerSetup;
  Integer           unknown1E7;
  Nullable<Integer> unknown1E8;
  Bool              unknown1E9;
  Integer           unknown1EA;
  Integer           unknown1EB;
};

struct NeededFile : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    type_.serialize( stream, 4 );
    unknown_.serialize( stream, 8 );
    locale_.serialize( stream, 3 );
    hash_.serialize( stream, 32 );
  }

  FixedString type_;
  Integer     unknown_;
  FixedString locale_;
  FixedString hash_;
};

struct MapInfo : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    unknown1BF.serialize( stream, 32 );
    unknown1C0.serialize( stream, 8, 0, 255 );
    unknown1C1.serialize( stream );

    int enumeration;
    stream.read( enumeration, 3 ); unknown1C2 = (Unknown0B0)enumeration;
    stream.read( enumeration, 3 ); unknown1C3 = (Unknown1AD)enumeration;

    unknown1C4.serialize( stream,  5 );
    unknown1C5.serialize( stream,  5 );
    unknown1C6.serialize( stream,  4 );
    unknown1C7.serialize( stream,  4 );
    unknown1C8.serialize( stream,  5 );
    unknown1C9.serialize( stream,  8 );
    unknown1CA.serialize( stream,  8 );
    unknown1CB.serialize( stream,  8 );
    unknown1CC.serialize( stream,  8 );
    unknown1CD.serialize( stream, 32 );
    
    cachePath.serialize( stream, 8, 0, 128 );
    
    //------------------- NOT WORKING ATM -------------------
    //unknown1CF.serialize( stream, 32 );
    //unknown1D0.serialize( stream, 8, 0, 128 );
    //unknown1D1.serialize( stream, 5, 0, 16 );
    //unknown1D2.serialize( stream, 6 );
    //-------------------------------------------------------
    // Structures commented below does not work. So skip them for now
    stream.align();
    while ( stream.buffer()[stream.position()/8+1]!=0x73 )
      stream.skip(8);
    stream.skip(3);
    //-------------------------------------------------------
    
    neededFiles.serialize( stream, 4, 0, 8 );
  }

  Integer          unknown1BF;
  AsciiString      unknown1C0;
  Unknown1A1       unknown1C1;
  Unknown0B0       unknown1C2;
  Unknown1AD       unknown1C3;
  Integer          unknown1C4;
  Integer          unknown1C5;
  Integer          unknown1C6;
  Integer          unknown1C7;
  Integer          unknown1C8;
  Integer          unknown1C9;
  Integer          unknown1CA;
  Integer          unknown1CB;
  Integer          unknown1CC;
  Integer          unknown1CD;
  AsciiString      cachePath;
  Integer          unknown1CF;
  AsciiString      unknown1D0;
  List<Unknown1B1> unknown1D1;
  Integer          unknown1D2;
  List<NeededFile> neededFiles;
};

struct Client : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    name.serialize( stream, 8, 0, 32 );
    
    unknown049.serialize( stream, 32 );
    
    unknown04A.serialize( stream );
    unknown04B.serialize( stream );
    unknown04C.serialize( stream );
    
    int enumeration;
    stream.read( enumeration, 2 ); unknown04D = (Unknown045)enumeration;
  }

  AsciiString name;
  Integer     unknown049;
  Unknown022  unknown04A;
  Bool        unknown04B;
  Bool        unknown04C;
  Unknown045  unknown04D;
};

struct GameInfo : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    clients.serialize( stream, 5, 0, 16 );
    mapInfo.serialize( stream );
    unknown1F0.serialize( stream );
  }

  List<Client> clients;
  MapInfo      mapInfo;
  Unknown1E2   unknown1F0;
};

struct ReplayInfo : public BitStructure
{
  virtual void serialize( const Bitstream& stream, unsigned char size=0, unsigned int min=0, unsigned int max=0 )
  {
    gameInfo.serialize( stream );
    std::cout << "Offset at map title: " << stream.position()/8 << ":" << stream.position()%8 << std::endl;
    mapTitle.serialize( stream, 8, 0, 255 );
    unknown22D.serialize( stream, 8, 0, 63 );
    players.serialize( stream, 5, 0, 16 );
  }

  GameInfo         gameInfo;
  AsciiString      mapTitle;
  AsciiString      unknown22D;
  List<PlayerInfo> players;
};

//--------------------------------------------------
// DISPLAY
//--------------------------------------------------


std::ostream& operator<<( std::ostream& out, const Unknown045& v )
{
  switch (v)
  {
    case unknown045_0: { out << "[Unknown045]unknown045_0" << std::endl;} break;
    case unknown045_1: { out << "[Unknown045]unknown045_1" << std::endl;} break;
    case unknown045_2: { out << "[Unknown045]unknown045_2" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown1A0& v )
{
  switch (v)
  {
    case unknown1A0_0: { out << "[Unknown1A0]unknown1A0_0" << std::endl;} break;
    case unknown1A0_1: { out << "[Unknown1A0]unknown1A0_1" << std::endl;} break;
    case unknown1A0_2: { out << "[Unknown1A0]unknown1A0_2" << std::endl;} break;
    case unknown1A0_3: { out << "[Unknown1A0]unknown1A0_3" << std::endl;} break;
    case unknown1A0_4: { out << "[Unknown1A0]unknown1A0_4" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown19D& v )
{
  switch (v)
  {
    case unknown19D_0: { out << "[Unknown19D]unknown19D_0" << std::endl;} break;
    case unknown19D_1: { out << "[Unknown19D]unknown19D_1" << std::endl;} break;
    case unknown19D_2: { out << "[Unknown19D]unknown19D_2" << std::endl;} break;
    case unknown19D_3: { out << "[Unknown19D]unknown19D_3" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown19E& v )
{
  switch (v)
  {
    case unknown19E_0: { out << "[Unknown19E]unknown19E_0" << std::endl;} break;
    case unknown19E_1: { out << "[Unknown19E]unknown19E_1" << std::endl;} break;
    case unknown19E_2: { out << "[Unknown19E]unknown19E_2" << std::endl;} break;
    case unknown19E_3: { out << "[Unknown19E]unknown19E_3" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown19F& v )
{
  switch (v)
  {
    case unknown19F_0: { out << "[Unknown19F]unknown19F_0" << std::endl;} break;
    case unknown19F_1: { out << "[Unknown19F]unknown19F_1" << std::endl;} break;
    case unknown19F_2: { out << "[Unknown19F]unknown19F_2" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown0B0& v )
{
  switch (v)
  {
    case unknown0B0_0: { out << "[Unknown0B0]unknown0B0_0" << std::endl;} break;
    case unknown0B0_1: { out << "[Unknown0B0]unknown0B0_1" << std::endl;} break;
    case unknown0B0_2: { out << "[Unknown0B0]unknown0B0_2" << std::endl;} break;
    case unknown0B0_3: { out << "[Unknown0B0]unknown0B0_3" << std::endl;} break;
    case unknown0B0_4: { out << "[Unknown0B0]unknown0B0_4" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown1AD& v )
{
  switch (v)
  {
    case unknown1AD_0: { out << "[Unknown1AD]unknown1AD_0" << std::endl;} break;
    case unknown1AD_1: { out << "[Unknown1AD]unknown1AD_1" << std::endl;} break;
    case unknown1AD_2: { out << "[Unknown1AD]unknown1AD_2" << std::endl;} break;
    case unknown1AD_3: { out << "[Unknown1AD]unknown1AD_3" << std::endl;} break;
    case unknown1AD_4: { out << "[Unknown1AD]unknown1AD_4" << std::endl;} break;
    case unknown1AD_5: { out << "[Unknown1AD]unknown1AD_5" << std::endl;} break;
    case unknown1AD_6: { out << "[Unknown1AD]unknown1AD_6" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown19B& v )
{
  switch (v)
  {
    case unknown19B_0: { out << "[Unknown19B]unknown19B_0" << std::endl;} break;
    case unknown19B_1: { out << "[Unknown19B]unknown19B_1" << std::endl;} break;
    case unknown19B_2: { out << "[Unknown19B]unknown19B_2" << std::endl;} break;
    case unknown19B_3: { out << "[Unknown19B]unknown19B_3" << std::endl;} break;
    case unknown19B_4: { out << "[Unknown19B]unknown19B_4" << std::endl;} break;
    case unknown19B_5: { out << "[Unknown19B]unknown19B_5" << std::endl;} break;
  };
  return out;
}

std::ostream& operator<<( std::ostream& out, const Bool& v )
{
  if ( v.value_ )
    out << "true";
  else
    out << "false";
  return out;
}

std::ostream& operator<<( std::ostream& out, const Integer& v )
{
  out << v.value_;
  return out;
}

std::ostream& operator<<( std::ostream& out, const FixedString& string )
{
  out << "(" << string.size_ << ")" << string.text_;
}

std::ostream& operator<<( std::ostream& out, const AsciiString& string )
{
  out << "(" << string.size_ << ")" << string.text_;
}

//--------------------------------------------------
// STRUCTURES DISPLAY
//--------------------------------------------------

std::ostream& operator<<( std::ostream& out, const Unknown060& v )
{
  if ( !v.unknown061.present_ )
    out << "<nullable not present>";
  else
    out << "<nullable present>" << v.unknown061.item_;
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown022& v )
{
  if ( !v.unknown023.present_ )
    out << "<nullable not present>";
  else
    out << "<nullable present>" << v.unknown023.item_;
  return out;
}

std::ostream& operator<<( std::ostream& out, const Client& client )
{
  out << "[Client] " << std::endl;
  out << "  name:       " << client.name       << std::endl;
  out << "  unknown049: " << client.unknown049 << std::endl;
  out << "  unknown04A: " << client.unknown04A << std::endl;
  out << "  unknown04B: " << client.unknown04B << std::endl;
  out << "  unknown04C: " << client.unknown04C << std::endl;
  out << "  unknown04D: " << client.unknown04D;
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const List<Client>& tclients )
{
  const std::list<Client>& clients = tclients.list();
  std::list<Client>::const_iterator it = clients.begin();
  for (; it != clients.end(); ++it )
  {
    // Skip empty slots
    if ( it->name.text().empty() )
      continue;
    
    out << *it << std::endl;
  }
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const PlayerSetup& ps )
{
  out << "[Player Setup]" << std::endl;
  return out;
}

std::ostream& operator<<( std::ostream& out, const List<PlayerSetup>& ps )
{
  const std::list<PlayerSetup>& players = ps.list();
  std::list<PlayerSetup>::const_iterator it = players.begin();
  for (; it != players.end(); ++it )
  {
    out << *it << std::endl;
  }
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const Unknown1E2& unk )
{
  out << "[Unknown1E2]" << std::endl;
  out << "  unknown1E3:  " << unk.unknown1E3;
  out << "  unknown1E4:  " << unk.unknown1E4 << std::endl;
  out << "  unknown1E5:  " << unk.unknown1E5 << std::endl;
  out << "  playerSetup(" << unk.playerSetup.list().size() << "): " << unk.playerSetup << std::endl;
  out << "  unknown1E7:  " << unk.unknown1E7  << std::endl;
  //out << "  unknown1E8:  " << unk.unknown1E8  << std::endl;
  out << "  unknown1E9:  " << unk.unknown1E9  << std::endl;
  out << "  unknown1EA:  " << unk.unknown1EA  << std::endl;
  out << "  unknown1EB:  " << unk.unknown1EB  << std::endl;
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const NeededFile& neededFile )
{
  out << "Type:    " << neededFile.type_    << std::endl;
  out << "unknown: " << neededFile.unknown_ << std::endl;
  out << "locale:  " << neededFile.locale_  << std::endl;
  out << "hash:    " << "..."    << std::endl;
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const List<NeededFile>& tfiles )
{
  const std::list<NeededFile>& files = tfiles.list();
  out << "(" << files.size() << ")" << "[NeededFiles]" << std::endl;
  std::list<NeededFile>::const_iterator it = files.begin();
  for (; it != files.end(); ++it )
  {
    out << *it << std::endl;
  }
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const MapInfo& map )
{
  out << "[Map Info]" << std::endl;
  out << "unknown1BF:  " << map.unknown1BF  << std::endl;
  out << "unknown1C0:  " << map.unknown1C0  << std::endl;
  //out << "unknown1C1:  " << map.unknown1C1  << std::endl;
  //out << "unknown1C2:  " << map.unknown1C2  << std::endl;
  //out << "unknown1C3:  " << map.unknown1C3  << std::endl;
  out << "unknown1C4:  " << map.unknown1C4  << std::endl;
  out << "unknown1C5:  " << map.unknown1C5  << std::endl;
  out << "unknown1C6:  " << map.unknown1C6  << std::endl;
  out << "unknown1C7:  " << map.unknown1C7  << std::endl;
  out << "unknown1C8:  " << map.unknown1C8  << std::endl;
  out << "unknown1C9:  " << map.unknown1C9  << std::endl;
  out << "unknown1CA:  " << map.unknown1CA  << std::endl;
  out << "unknown1CB:  " << map.unknown1CB  << std::endl;
  out << "unknown1CC:  " << map.unknown1CC  << std::endl;
  out << "unknown1CD:  " << map.unknown1CD  << std::endl;
  out << "cachePath:   " << map.cachePath   << std::endl;
  out << "unknown1CF:  " << map.unknown1CF  << std::endl;
  out << "unknown1D0:  " << map.unknown1D0  << std::endl;
  //out << "unknown1C1:  " << map.unknown1D1  << std::endl;
  out << "unknown1D2:  " << map.unknown1D2  << std::endl;
  out << "neededFiles: " << map.neededFiles << std::endl;
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const GameInfo& game )
{
  out << game.clients    << std::endl;
  out << game.mapInfo    << std::endl;
  out << game.unknown1F0 << std::endl;
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const PlayerInfo& pi )
{
  out << "[PlayerInfo]" << std::endl;
  out << "  name:  " << pi.name  << std::endl;
  out << "  race:  " << pi.race  << std::endl;
  out << "  color: " << pi.color << std::endl;
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const List<PlayerInfo>& tlist )
{
  const std::list<PlayerInfo>& list = tlist.list();
  out << "(" << list.size() << ")" << "[PlayerInfos]" << std::endl;
  std::list<PlayerInfo>::const_iterator it = list.begin();
  for (; it != list.end(); ++it )
  {
    out << *it << std::endl;
  }
  
  return out;
}

std::ostream& operator<<( std::ostream& out, const ReplayInfo& replay )
{
  out << "---------- GAME INFO  ----------" << std::endl << replay.gameInfo   << std::endl;
  out << "---------- MAP TITLE  ----------" << std::endl << replay.mapTitle   << std::endl;
  out << "---------- UNKNOWN22D ----------" << std::endl << replay.unknown22D << std::endl;
  out << "---------- PLAYERS    ----------" << std::endl << replay.players    << std::endl;
  
  return out;
}

//--------------------------------------------------
// MAIN
//--------------------------------------------------

int main( int argc, char** argv )
{
  Bitstream stream;
  
  stream.loadFromFile( "./Debug/replay2.info.dump" );
  
  ReplayInfo replay;
  
  replay.serialize( stream );
  
  std::cout << replay << std::endl;
  
  
  return EXIT_SUCCESS;
}
```