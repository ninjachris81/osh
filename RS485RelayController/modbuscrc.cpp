#include "modbuscrc.h"

bool ModbusCRC::crc_tab16_init = false;
uint16_t ModbusCRC::crc_tab16[256];

ModbusCRC::ModbusCRC(QObject *parent)
    : QObject{parent}
{

}

void ModbusCRC::appendCRC( QByteArray &data ) {
    unsigned char *buf = new unsigned char[data.size()];
    memcpy(buf, data.data(), data.size());
    uint16_t crc = crc_modbus(buf, data.size());
    data.append(char(crc & 0xFF));
    data.append(char(crc >>  8));
}

uint16_t ModbusCRC::crc_modbus( const unsigned char *input_str, size_t num_bytes ) {

    uint16_t crc;
    const unsigned char *ptr;
    size_t a;

    if ( ! crc_tab16_init ) init_crc16_tab();

    crc = CRC_START_MODBUS;
    ptr = input_str;

    if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

        crc = (crc >> 8) ^ crc_tab16[ (crc ^ (uint16_t) *ptr++) & 0x00FF ];
    }

    return crc;

}

void ModbusCRC::init_crc16_tab( void ) {

    uint16_t i;
    uint16_t j;
    uint16_t crc;
    uint16_t c;

    for (i=0; i<256; i++) {

        crc = 0;
        c   = i;

        for (j=0; j<8; j++) {

            if ( (crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ CRC_POLY_16;
            else                      crc =   crc >> 1;

            c = c >> 1;
        }

        crc_tab16[i] = crc;
    }

    crc_tab16_init = true;

}
