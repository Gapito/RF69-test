



#include <SPI.h>
#include "RF69.h"


void setMode(uint8_t estado);
void writeRegister(uint8_t adreslavePin,uint8_t value);
uint8_t readRegister(uint8_t addreslavePin);
void setModulation(uint8_t mod);
void setOutputPower(uint8_t power);
void setHighPowerSettings(void);
void isr0(void);
void isr1(void);
void writeBurstRegiste(uint8_t adress, char *msg,uint8_t len);

//global variables
uint8_t state;

void initRF69(){

//configurar spi
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
// slavePin
  pinMode(slavePin, OUTPUT);
// configurações
  //Set Standby
  setMode(M_STDBY);
  //Set Frequency 434MHz
  writeRegister(RegFrfMsb,FrfMsb);
  writeRegister(RegFrfMid,FrfMid);
  writeRegister(RegFrfLsb,FrfLsb);

  //Set BitRate
  writeRegister(RegBitrateMsb,0x1A);
  writeRegister(RegBitrateLsb,0x0B);

  //Set modulation FSK
  setModulation(MODE_FSK);

  //Set OutputPower
  setOutputPower(13);
  // Turn off clckOUT
  writeRegister(RegDioMapping2, CLK_OUT_FXOSC_OFF);
  //put interrupts then
  //atach interrupts
  attachInterrupt(2,isr0,RISING);
  attachInterrupt(3,isr1,RISING);

// packet configuration

//Size of preamble de 4 bits.
writeRegister(RegPreambleLsb,4);

//config sync - 2 bytes
writeRegister(RegSyncConfig,SYNC_ON|SYNC_SIZE_2);

//Set two bytes on syncword;
writeRegister(RegSyncValue1,syncword[0]);
writeRegister(RegSyncValue2,syncword[1]);

//without NODE ADRESS filtering
writeRegister(RegPacketConfig1, PACKET1_FORMAT_FIXED |PACKET1_DC_FREE_OFF|PACKET1_CRC_ON|PACKET1_ADDRS_FILTR_NODE);

//length of paylaod 1 byte just to begin
writeRegister(RegPayloadLength,0x40);

}
void setRx(void)
{
  
}

void seTx(char *msg,uint8_t len){
  setMode(M_STDBY);
  //see if module is ready
  Serial.println("Ver se o modulo está rdy !");
  while(readRegister(RegIrqFlags1)&& IRQ1_MODE_RDY == 0x00);
  Serial.println("Ready!!!");

  writeRegister(RegDioMapping1, DIO0_MAPPING_00);

  writeBurstRegiste(RegFifo,msg,len);

  setMode(M_TX);


}

void writeRegister(uint8_t adress, char* msg,uint8_t len)
{
  digitalWrite(slavePin, LOW);
  SPI.transfer(SPI_WRITE | adress);
  uint8_t i = 0;
  for(; i<len ; i++)
  {
    SPI.transfer(*msg++);
  }

  digitalWrite(slavePin,HIGH);

}
void setOutputPower(uint8_t power){
  uint8_t Pout;

  if(power <= 13)
  {
    Pout = (power + 18) & 0x1F;
    writeRegister(RegPaLevel,PA0_ON | Pout);
  }
  else if(power > 13 && power <= 17){
    Pout = (14 + power) & 0x1F ;
    writeRegister(RegPaLevel, PA1_ON | PA2_ON | Pout);
  }
  else{
    setHighPowerSettings();
    Pout = (11 + power) & 0x1F;
    writeRegister(RegPaLevel,PA1_ON | PA2_ON | Pout);
  }
}

void setHighPowerSettings(void){
  writeRegister(RegOcp, 0x0F);
  writeRegister(RegTestPa1, 0x5D);
  writeRegister(RegTestPa2,0x7C);
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

void setMode(uint8_t estado){
  //ler o estado
  uint8_t value = readRegister(RegOpMode);
  value &= OPMODE_MODE_BITS;

if(estado == state)
  return;

  switch(estado){
     case M_SLP: // SLEEP = DORMIR
      value |= SLEEP;
      state = M_SLP;
      break;
     case M_STDBY:
      value |= STDBY;
      state =M_STDBY;
      break;
     case M_FS:
     break;
      value |= FS;
      state = M_FS;
     case M_TX:
      value |= TX;
      state = M_TX;
      break;
     case M_RX:
      value |= RX;
      state = M_RX;
     default:
      break;
    }

    writeRegister(RegOpMode,value);
    return;
}

void writeRegister(uint8_t adreslavePin,uint8_t value){
  digitalWrite(slavePin, LOW);
  SPI.transfer(SPI_WRITE | adreslavePin);
  SPI.transfer(value);
  digitalWrite(slavePin,HIGH);
}

uint8_t readRegister(uint8_t addreslavePin){
  digitalWrite(slavePin, LOW);
  SPI.transfer(addreslavePin & SPI_READ);
  uint8_t value = SPI.transfer(RegFifo);
  digitalWrite(slavePin,HIGH);
  return value;
}

void isr0(){
  if(state == M_TX)
  {
    setMode(M_STDBY);
    Serial.println("Packet Sent");
  }
}

void isr1(){

}
