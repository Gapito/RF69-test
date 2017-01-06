

#ifndef RF69_H
#define RF69_H

#include <SPI.h>
#include "RF69_REG.h"

#define SPI_WRITE 0x80
#define SPI_READ 0x7F
//states modes
#define M_SLP 0
#define M_STDBY 1
#define M_FS 2
#define M_TX 3
#define M_RX 4
//Slave select
#define slavePin 8




//modulations types
#define MODE_FSK 0
#define MODE_OOK 1

void initRF69(void);



#endif
