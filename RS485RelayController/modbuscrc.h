#ifndef MODBUSCRC_H
#define MODBUSCRC_H

#include <QObject>

/*
 * see https://github.com/lammertb/libcrc
*/

#define		CRC_POLY_16		0xA001
#define		CRC_START_MODBUS	0xFFFF

class ModbusCRC : public QObject
{
    Q_OBJECT
public:
    explicit ModbusCRC(QObject *parent = nullptr);

    static bool crc_tab16_init;

    static uint16_t crc_tab16[256];

    static void appendCRC( QByteArray &data );

    static uint16_t crc_modbus( const unsigned char *input_str, size_t num_bytes );

    static void init_crc16_tab();

signals:

};

#endif // MODBUSCRC_H
