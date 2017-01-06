

#ifndef RF69_H
#define RF69_H

#include <SPI.h>
#include "RF69_REG.h"

#define SPI_WRITE 0x80

//states modes
#define M_SLP 0
#define M_STDBY 1
#define M_FS 2
#define M_TX 3
#define M_RX 4

//modulations types
#define MODE_FSK 0
#define MODE_OOK 1

void initRF69(void);



#endif
