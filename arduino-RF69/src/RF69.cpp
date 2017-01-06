


#include <SPI.h>
#include "RF69.h"

void config_Spi(void);
void config_RF_69(void);
void setMode(uint8_t state);
void setFreq(void);
void writeRegister(uint8_t adress,uint8_t value);
void setBitR(uint8_t kbs);
void setModulation(uint8_t mod);





void initRF69(void){
  config_Spi();
  SPI.begin();
  config_RF_69();
}

void config_Spi(void)
{
  SPI.setClockDivider(SPI_CLOCK_DIV8); //2MHz in arduino uno
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
}


//set freq
//set Idle
//Fdev after
//Bit Rate

void config_RF_69(){
  setMode(M_STDBY);
  setFreq(); //depois colocar Fdev
  //Fdev no inicio vai com o valor padrao mas depois colocar uma funçao
  setBitR(2);
  setModulation(FSK);

}

void setModulation(uint8_t mod){
  switch(mod){
    case MODE_FSK:
        writeRegister(0xEE, 0x43);
        break;
    case MODE_OOK:
        writeRegister(0xee, 0x24);
    default:
      break;
  }
}

void setBitR(uint8_t kbs){
  writeRegister(RegBitrateMsb,0x1A);
  writeRegister(RegBitrateLsb,0x0B);
}


void setFreq(){
  writeRegister(RegFrfMsb,FrfMsb);
  writeRegister(RegFrfMid,FrfMid);
  writeRegister(RegFrfLsb,FrfLsb);
}

void setMode(uint8_t state){
  //ler o estado
  byte value = SPI.transfer(RegOpMode);
  value &= OPMODE_MODE_BITS;

  switch(state){
     case M_SLP: // SLEEP = DORMIR
      value |= SLEEP;
      break;
     case M_STDBY:
      value |= STDBY;
      break;
     case M_FS:
     break;
      value |= FS;
     case M_TX:
      value |= TX;
      break;
     case M_RX:
      value |= RX;
     default:
      break;
    }

    writeRegister(RegOpMode,value);

}

void writeRegister(uint8_t adress,uint8_t value){
  SPI.transfer(SPI_WRITE | adress);
  SPI.transfer(value);
}
