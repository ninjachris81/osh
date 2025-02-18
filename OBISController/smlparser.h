#ifndef SMLPARSER_H
#define SMLPARSER_H

#include <QObject>

#include "sharedlib.h"

/*
 * https://github.com/olliiiver/sml_parser
*/

class SHARED_LIB_EXPORT SmlParser : public QObject
{
    Q_OBJECT
public:
    explicit SmlParser(QObject *parent = nullptr);

#define MAX_LIST_SIZE 80
#define MAX_TREE_SIZE 10

    typedef enum {
      SML_START,
      SML_END,
      SML_VERSION,
      SML_NEXT,
      SML_LISTSTART,
      SML_LISTEND,
      SML_DATA,
      SML_HDATA,
      SML_DATAEND,
      SML_BLOCKSTART,
      SML_BLOCKEND,
      SML_CHECKSUM,
      SML_CHECKSUM_ERROR, /* calculated checksum does not match */
      SML_UNEXPECTED,     /* unexpected byte received */
      SML_FINAL,          /* final state, checksum OK */
      SML_DATA_SIGNED_INT,
      SML_DATA_UNSIGNED_INT,
      SML_DATA_OCTET_STRING,
    } sml_states_t;

    typedef enum {
      SML_YEAR = 1,
      SML_MONTH = 2,
      SML_WEEK = 3,
      SML_DAY = 4,
      SML_HOUR = 5,
      SML_MIN = 6,
      SML_SECOND = 7,
      SML_DEGREE = 8,
      SML_DEGREE_CELSIUS = 9,
      SML_CURRENCY = 10,
      SML_METRE = 11,
      SML_METRE_PER_SECOND = 12,
      SML_CUBIC_METRE = 13,
      SML_CUBIC_METRE_CORRECTED = 14,
      SML_CUBIC_METRE_PER_HOUR = 15,
      SML_CUBIC_METRE_PER_HOUR_CORRECTED = 16,
      SML_CUBIC_METRE_PER_DAY = 17,
      SML_CUBIC_METRE_PER_DAY_CORRECTED = 18,
      SML_LITRE = 19,
      SML_KILOGRAM = 20,
      SML_NEWTON = 21,
      SML_NEWTONMETER = 22,
      SML_PASCAL = 23,
      SML_BAR = 24,
      SML_JOULE = 25,
      SML_JOULE_PER_HOUR = 26,
      SML_WATT = 27,
      SML_VOLT_AMPERE = 28,
      SML_VAR = 29,
      SML_WATT_HOUR = 30,
      SML_VOLT_AMPERE_HOUR = 31,
      SML_VAR_HOUR = 32,
      SML_AMPERE = 33,
      SML_COULOMB = 34,
      SML_VOLT = 35,
      SML_VOLT_PER_METRE = 36,
      SML_FARAD = 37,
      SML_OHM = 38,
      SML_OHM_METRE = 39,
      SML_WEBER = 40,
      SML_TESLA = 41,
      SML_AMPERE_PER_METRE = 42,
      SML_HENRY = 43,
      SML_HERTZ = 44,
      SML_ACTIVE_ENERGY_METER_CONSTANT_OR_PULSE_VALUE = 45,
      SML_REACTIVE_ENERGY_METER_CONSTANT_OR_PULSE_VALUE = 46,
      SML_APPARENT_ENERGY_METER_CONSTANT_OR_PULSE_VALUE = 47,
      SML_VOLT_SQUARED_HOURS = 48,
      SML_AMPERE_SQUARED_HOURS = 49,
      SML_KILOGRAM_PER_SECOND = 50,
      SML_KELVIN = 52,
      SML_VOLT_SQUARED_HOUR_METER_CONSTANT_OR_PULSE_VALUE = 53,
      SML_AMPERE_SQUARED_HOUR_METER_CONSTANT_OR_PULSE_VALUE = 54,
      SML_METER_CONSTANT_OR_PULSE_VALUE = 55,
      SML_PERCENTAGE = 56,
      SML_AMPERE_HOUR = 57,
      SML_ENERGY_PER_VOLUME = 60,
      SML_CALORIFIC_VALUE = 61,
      SML_MOLE_PERCENT = 62,
      SML_MASS_DENSITY = 63,
      SML_PASCAL_SECOND = 64,
      SML_RESERVED = 253,
      SML_OTHER_UNIT = 254,
      SML_COUNT = 255
    } sml_units_t;

    static const unsigned char SML_1_8_0[];     // consumption total
    static const unsigned char SML_2_8_0[];     // production total

    sml_states_t smlState(unsigned char &byte);
    bool smlOBISCheck(const unsigned char *obis);
    void smlOBISManufacturer(unsigned char *str, int maxSize);
    void smlOBISByUnit(long long int &wh, signed char &scaler, sml_units_t unit);

    // Be aware that double on Arduino UNO is just 32 bit
    void smlOBISWh(double &wh);
    void smlOBISW(double &w);
    void smlOBISVolt(double &v);

protected:
    void reduceList();
    void setState(SmlParser::sml_states_t state, int byteLen);
    void checkMagicByte(unsigned char &byte);
    void crc16(unsigned char &byte);
    void pushListBuffer(unsigned char byte);

    char nodes[MAX_TREE_SIZE];
    unsigned short crc = 0xFFFF;
    signed char sc;
    unsigned short crcMine = 0xFFFF;
    unsigned short crcReceived = 0x0000;
    unsigned char len = 4;
    unsigned char listBuffer[MAX_LIST_SIZE]; /* keeps a list
                                                   as length + state + data  */
    unsigned char listPos = 0;


private:
    sml_states_t currentState = SmlParser::SML_START;
    unsigned char currentLevel = 0;


signals:

};

#endif // SMLPARSER_H
