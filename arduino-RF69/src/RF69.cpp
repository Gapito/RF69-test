



#include <SPI.h>
#include "RF69.h"


void setMode(uint8_t estado);
void writeRegister(uint8_t adreslavePin,uint8_t value);
uint8_t readRegister(uint8_t addreslavePin);
void setModulation(uint8_t mod);
void setOutputPower(uint8_t power);
void setHighPowerSettings(void);
void isr0(void);
//void isr1(void);
void writeBurstRegister(uint8_t adress, char *msg,uint8_t len);
void readMessage(void);



//global variables
uint8_t state=M_STDBY;
uint8_t payloadok;
uint8_t receive = 0;
uint8_t node = 1;
uint8_t node_to = 2;
void initRF69(){

//configurar spi
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4); //2MHz in arduino uno
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
// slavePin
  pinMode(slavePin, OUTPUT);
  digitalWrite(slavePin,HIGH);
// configurações
  //Set Standby

  writeRegister(RegOpMode, SEQ_ON |LIS_OFF |STDBY);
  setMode(M_STDBY);

  writeRegister(RegDataModul,0);


  //Set Frequency 434MHz
  writeRegister(RegFrfMsb,FrfMsb);//433MH
  writeRegister(RegFrfMid,FrfMid);
  writeRegister(RegFrfLsb,FrfLsb);

  //Set BitRate
  writeRegister(RegBitrateMsb,0x02); //55Kbs
  writeRegister(RegBitrateLsb,0x40);


  //Frequency Deviation 50Khz
  writeRegister(RegFdevMsb, 0x03);
  writeRegister(RegFdevLsb, 0x33);


  attachInterrupt(digitalPinToInterrupt(2), isr0, RISING);

  writeRegister(RegDioMapping2, CLK_OUT_FXOSC_OFF);
  writeRegister(RegDioMapping1, DIO0_MAPPING_01);

  //afc control
  //writeRegister(RegAfcCtrl, 0);

  //125 Khz
  writeRegister(RegRxBw,0x40|RX_BW_MANT_16|0x02); //100Khz

  writeRegister(RegIrqFlags2,0x10);
  //writeRegister(RegAfcFei, 0);

  writeRegister(RegRssiTresh, 220);

  writeRegister(RegPreambleMsb, 0);
  writeRegister(RegPreambleLsb,16);
  //Pa level
  //writeRegister(RegPaLevel, 0x60 | 0b011111);
  //writeRegister(RegOcp, 0x0F);




  writeRegister(RegSyncConfig,SYNC_ON | 0x08);

  writeRegister(RegSyncValue1, 0x2D);
  writeRegister(RegSyncValue2, NETWORKID);



  writeRegister(RegPacketConfig1, PACKET1_FORMAT_VARIABLE | PACKET1_DC_FREE_OFF | PACKET1_CRC_ON | PACKET1_ADDRS_FILTR_NODE );



  writeRegister(RegPayloadLength, 66);

  writeRegister(RegFifoTresh,0x80 | 0x0F);

  writeRegister(RegPacketConfig2,0x10 | 0x02);

  writeRegister(RegTestDagc, 0x30) ;
}

void setRx(void)
{

  if(state != M_RX)
  {
    receive = 0;
    setMode(M_STDBY);

    writeRegister(RegTestPa1, 0x55);
    writeRegister(RegTestPa2, 0x70);

    Serial.println("Ver se o modulo está rdy !");
    while(readRegister(RegIrqFlags1)&& IRQ1_MODE_RDY == 0x00);
    Serial.println("Ready!!!");


    writeRegister(RegDioMapping1, DIO0_MAPPING_01);


    setMode(M_RX);


  }


}
void getMessage()
{
  Serial.println(readRegister(RegIrqFlags2)&0x04);
}
void seTx(char msg[],uint8_t len){
  if(state != M_TX)
  {
    setMode(M_STDBY);
    //see if module is ready

    writeRegister(RegTestPa1, 0x55);
    writeRegister(RegTestPa2, 0x70);
    Serial.println("Ver se o modulo está rdy !");
    while(readRegister(RegIrqFlags1)&& IRQ1_MODE_RDY == 0x00);
    Serial.println("Ready!!!");

    writeRegister(RegDioMapping1, DIO0_MAPPING_00);

    writeBurstRegister(RegFifo,msg,len);

    setMode(M_TX);
    Serial.println("A enviar");


  }

}

void writeBurstRegister(uint8_t adress, char msg [],uint8_t len)
{
  digitalWrite(slavePin, LOW);
  SPI.transfer(0x80);



  uint8_t i = 0;
  for(;i<len;i++)
  {
    Serial.println(msg[i]);
    SPI.transfer(msg[i]);
  }

  digitalWrite(slavePin,HIGH);

}
void setOutputPower(uint8_t power){
  uint8_t Pout;

  if(power <= 13)
  {
    Serial.println("Setpower 13 ");
    writeRegister(RegTestPa1,0x5D);
    writeRegister(RegTestPa2, 0x70);
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
    uint8_t now = value & 0b011100;
  value &= OPMODE_MODE_BITS;

  Serial.println(now);
  if(estado != now >> 2)
  {
  switch(estado){
     case M_SLP: // SLEEP = DORMIR
      value |= SLEEP;
      state = M_SLP;
      break;
     case M_STDBY:
     Serial.println("Estou me stdby");
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
     Serial.print("Estou em RX");
      value |= RX;
      state = M_RX;
     default:
      break;
    }

    writeRegister(RegOpMode,value);
  }
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
void readMessage(void){
  noInterrupts();
  digitalWrite(slavePin, LOW);
  char c;
  SPI.transfer(RegFifo); //Reg fifo = 0x00 logo pede ja para a leitura

  uint8_t i = 0;
  for(  ; i<29 ; i++ )
  {
  c =SPI.transfer(RegFifo);
  Serial.println(c);
  }

  digitalWrite(slavePin,HIGH);

  interrupts();
//  payloadok = 1;

  Serial.println("saijdsfhs ");
}

void isr0(){
Serial.println("HERE");
/*int8_t i = 0;
char c ;
digitalWrite(8,LOW);
SPI.transfer(0);
for (;i<33;i++)
{
  c=SPI.transfer(0);
  Serial.println(c);
}
digitalWrite(8,HIGH);
*/
}
