#include "smlparser.h"

#include <QDebug>

static const uint16_t smlCrcTable[256] =
    {0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF, 0x8C48,
     0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7, 0x1081, 0x0108,
     0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E, 0x9CC9, 0x8D40, 0xBFDB,
     0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876, 0x2102, 0x308B, 0x0210, 0x1399,
     0x6726, 0x76AF, 0x4434, 0x55BD, 0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E,
     0xFAE7, 0xC87C, 0xD9F5, 0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E,
     0x54B5, 0x453C, 0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD,
     0xC974, 0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
     0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3, 0x5285,
     0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A, 0xDECD, 0xCF44,
     0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72, 0x6306, 0x728F, 0x4014,
     0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9, 0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5,
     0xA96A, 0xB8E3, 0x8A78, 0x9BF1, 0x7387, 0x620E, 0x5095, 0x411C, 0x35A3,
     0x242A, 0x16B1, 0x0738, 0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862,
     0x9AF9, 0x8B70, 0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E,
     0xF0B7, 0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
     0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036, 0x18C1,
     0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E, 0xA50A, 0xB483,
     0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5, 0x2942, 0x38CB, 0x0A50,
     0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD, 0xB58B, 0xA402, 0x9699, 0x8710,
     0xF3AF, 0xE226, 0xD0BD, 0xC134, 0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7,
     0x6E6E, 0x5CF5, 0x4D7C, 0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1,
     0xA33A, 0xB2B3, 0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72,
     0x3EFB, 0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
     0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A, 0xE70E,
     0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1, 0x6B46, 0x7ACF,
     0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9, 0xF78F, 0xE606, 0xD49D,
     0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330, 0x7BC7, 0x6A4E, 0x58D5, 0x495C,
     0x3DE3, 0x2C6A, 0x1EF1, 0x0F78};

const unsigned char SmlParser::SML_1_8_0[6] = {
    0x01, 0x00, 0x01, 0x08, 0x00, 0xff,      //1.8.0
};

const unsigned char SmlParser::SML_2_8_0 [6] = {
    0x01, 0x00, 0x02, 0x08, 0x00, 0xff,      //2.8.0
};

SmlParser::SmlParser(QObject *parent)
    : QObject{parent}
{

}

void SmlParser::crc16(unsigned char &byte)
{
#ifdef ARDUINO
  crc =
      pgm_read_word_near(&smlCrcTable[(byte ^ crc) & 0xff]) ^ (crc >> 8 & 0xff);
#else
  crc = smlCrcTable[(byte ^ crc) & 0xff] ^ (crc >> 8 & 0xff);
#endif
}

void SmlParser::setState(SmlParser::sml_states_t state, int byteLen)
{
  currentState = state;
  len = byteLen;
}

void SmlParser::pushListBuffer(unsigned char byte)
{
  if (listPos < MAX_LIST_SIZE) {
    listBuffer[listPos++] = byte;
  }
}

void SmlParser::reduceList()
{
  if (currentLevel >= 0 && nodes[currentLevel] > 0)
    nodes[currentLevel]--;
}

void SmlParser::checkMagicByte(unsigned char &byte)
{
  unsigned int size = 0;
  while (currentLevel > 0 && nodes[currentLevel] == 0) {
    /* go back in tree if no nodes remaining */
    //SML_TREELOG(currentLevel, "back to previous list\n");
    currentLevel--;
  }
  if (byte > 0x70 && byte < 0x7F) {
    /* new list */
    size = byte & 0x0F;
    reduceList();
    if (currentLevel < MAX_TREE_SIZE)
      currentLevel++;
    nodes[currentLevel] = size;
    //SML_TREELOG(currentLevel, "LISTSTART on level %i with %i nodes\n", currentLevel, size);
    setState(SML_LISTSTART, size);
    // @todo workaround for lists inside obis lists
    if (size > 5) {
      listPos = 0;
      memset(listBuffer, '\0', MAX_LIST_SIZE);
    }
    else {
      pushListBuffer(size);
      pushListBuffer(currentState);
    }
  }
  else if (byte >= 0x01 && byte <= 0x6F && nodes[currentLevel] > 0) {
    if (byte == 0x01) {
      /* no data, get next */
      //SML_TREELOG(currentLevel, " Data %i (empty)\n", nodes[currentLevel]);
      pushListBuffer(0);
      pushListBuffer(currentState);
      if (nodes[currentLevel] == 1) {
        setState(SML_LISTEND, 1);
        //SML_TREELOG(currentLevel, "LISTEND\n");
      }
      else {
        setState(SML_NEXT, 1);
      }
    }
    else {
      size = (byte & 0x0F) - 1;
      setState(SML_DATA, size);
      if ((byte & 0xF0) == 0x50) {
        setState(SML_DATA_SIGNED_INT, size);
      }
      else if ((byte & 0xF0) == 0x60) {
        setState(SML_DATA_UNSIGNED_INT, size);
      }
      else if ((byte & 0xF0) == 0x00) {
        setState(SML_DATA_OCTET_STRING, size);
      }
      //SML_TREELOG(currentLevel, " Data %i (length = %i%s): ", nodes[currentLevel], size, (currentState == SML_DATA_SIGNED_INT)     ? ", signed int" : (currentState == SML_DATA_UNSIGNED_INT) ? ", unsigned int" : (currentState == SML_DATA_OCTET_STRING) ? ", octet string" : "");
      pushListBuffer(size);
      pushListBuffer(currentState);
    }
    reduceList();
  }
  else if (byte == 0x00) {
    /* end of block */
    reduceList();
    //SML_TREELOG(currentLevel, "End of block at level %i\n", currentLevel);
    if (currentLevel == 0) {
      setState(SML_NEXT, 1);
    }
    else {
      setState(SML_BLOCKEND, 1);
    }
  }
  else if (byte >= 0x80 && byte <= 0x8F) {
    // MSB bit is set, another TL byte will follow
    setState(SML_HDATA, (byte & 0x0F) << 4);
  }
  else if (byte == 0x1B && currentLevel == 0) {
    /* end sequence */
    setState(SML_END, 3);
  }
  else {
    /* Unexpected Byte */
    //SML_TREELOG(currentLevel, "UNEXPECTED magicbyte >%02X< at currentLevel %i\n", byte, currentLevel);
    setState(SML_UNEXPECTED, 4);
  }
}

SmlParser::sml_states_t SmlParser::smlState(unsigned char &currentByte)
{
  unsigned char size;
  if (len > 0)
    len--;
  crc16(currentByte);
  switch (currentState) {
  case SML_UNEXPECTED:
  case SML_CHECKSUM_ERROR:
  case SML_FINAL:
  case SML_START:
    currentState = SML_START;
    currentLevel = 0; // Reset current level at the begin of a new transmission
                      // to prevent problems
    if (currentByte != 0x1b)
      setState(SML_UNEXPECTED, 4);
    if (len == 0) {
      //SML_TREELOG(0, "START\n");
      /* completely clean any garbage from crc checksum */
      crc = 0xFFFF;
      currentByte = 0x1b;
      crc16(currentByte);
      crc16(currentByte);
      crc16(currentByte);
      crc16(currentByte);
      setState(SML_VERSION, 4);
    }
    break;
  case SML_VERSION:
    if (currentByte != 0x01)
      setState(SML_UNEXPECTED, 4);
    if (len == 0) {
      setState(SML_BLOCKSTART, 1);
    }
    break;
  case SML_END:
    if (currentByte != 0x1b) {
      //SML_LOG("UNEXPECTED char >%02X< at SML_END\n", currentByte);
      setState(SML_UNEXPECTED, 4);
    }
    if (len == 0) {
      setState(SML_CHECKSUM, 4);
    }
    break;
  case SML_CHECKSUM:
    // SML_LOG("CHECK: %02X\n", currentByte);
    if (len == 2) {
      crcMine = crc ^ 0xFFFF;
    }
    if (len == 1) {
      crcReceived += currentByte;
    }
    if (len == 0) {
      crcReceived = crcReceived | (currentByte << 8);
      //SML_LOG("Received checksum: %02X\n", crcReceived);
      //SML_LOG("Calculated checksum: %02X\n", crcMine);
      if (crcMine == crcReceived) {
        setState(SML_FINAL, 4);
      }
      else {
        setState(SML_CHECKSUM_ERROR, 4);
      }
      crc = 0xFFFF;
      crcReceived = 0x000; /* reset CRC */
    }
    break;
  case SML_HDATA:
    size = len + currentByte - 1;
    setState(SML_DATA, size);
    pushListBuffer(size);
    pushListBuffer(currentState);
    //SML_TREELOG(currentLevel, " Data (length = %i): ", size);
    break;
  case SML_DATA:
  case SML_DATA_SIGNED_INT:
  case SML_DATA_UNSIGNED_INT:
  case SML_DATA_OCTET_STRING:
    //SML_LOG("%02X ", currentByte);
    pushListBuffer(currentByte);
    if (nodes[currentLevel] == 0 && len == 0) {
      //SML_LOG("\n");
      //SML_TREELOG(currentLevel, "LISTEND on level %i\n", currentLevel);
      currentState = SML_LISTEND;
    }
    else if (len == 0) {
      currentState = SML_DATAEND;
      //SML_LOG("\n");
    }
    break;
  case SML_DATAEND:
  case SML_NEXT:
  case SML_LISTSTART:
  case SML_LISTEND:
  case SML_BLOCKSTART:
  case SML_BLOCKEND:
    checkMagicByte(currentByte);
    break;
  }
  return currentState;
}

bool SmlParser::smlOBISCheck(const unsigned char *obis)
{
  return (memcmp(obis, &listBuffer[2], 6) == 0);
}

void SmlParser::smlOBISManufacturer(unsigned char *str, int maxSize)
{
  int i = 0, pos = 0, size = 0;
  while (i < listPos) {
    size = (int)listBuffer[i];
    i++;
    pos++;
    if (pos == 6) {
      /* get manufacturer at position 6 in list */
      size = (size > maxSize - 1) ? maxSize : size;
      memcpy(str, &listBuffer[i + 1], size);
      str[size + 1] = 0;
    }
    i += size + 1;
  }
}

void pow(double &val, signed char &scaler)
{
  if (scaler < 0) {
    while (scaler++) {
      val /= 10;
    }
  }
  else {
    while (scaler--) {
      val *= 10;
    }
  }
}

void SmlParser::smlOBISByUnit(long long int &val, signed char &scaler, sml_units_t unit)
{
  unsigned char i = 0, pos = 0, size = 0, y = 0, skip = 0;
  sml_states_t type;
  val = -1; /* unknown or error */
  while (i < listPos) {
    pos++;
    size = (int)listBuffer[i++];
    type = (sml_states_t)listBuffer[i++];
    if (type == SML_LISTSTART && size > 0) {
      // skip a list inside an obis list
      skip = size;
      while (skip > 0) {
        size = (int)listBuffer[i++];
        type = (sml_states_t)listBuffer[i++];
        i += size;
        skip--;
      }
      size = 0;
    }
    if (pos == 4 && listBuffer[i] != unit) {
      /* return unknown (-1) if unit does not match */
      return;
    }
    if (pos == 5) {
      scaler = listBuffer[i];
    }
    if (pos == 6) {
      y = size;
      // initialize 64bit signed integer based on MSB from received value
      val =
          (type == SML_DATA_SIGNED_INT && (listBuffer[i] & (1 << 7))) ? ~0 : 0;
      for (y = 0; y < size; y++) {
        // left shift received bytes to 64 bit signed integer
        val = (val << 8) | listBuffer[i + y];
      }
    }
    i += size;
  }
}

void SmlParser::smlOBISWh(double &wh)
{
  long long int val;
  smlOBISByUnit(val, sc, SML_WATT_HOUR);
  wh = val;
  pow(wh, sc);
}

void SmlParser::smlOBISW(double &w)
{
  long long int val;
  smlOBISByUnit(val, sc, SML_WATT);
  w = val;
  pow(w, sc);
}

void SmlParser::smlOBISVolt(double &v)
{
  long long int val;
  smlOBISByUnit(val, sc, SML_VOLT);
  v = val;
  pow(v, sc);
}
