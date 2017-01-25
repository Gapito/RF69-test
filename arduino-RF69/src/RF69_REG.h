

// De acordo com o datasheet implemento os registos neste documento registos.h
// E assim melhorar a leitura do programa posteriormente


// Estes encontram-se nas paginas 60 - 74
#ifndef RF69_REG_H
#define RF69_REG_H
// pag.60


#define RegFifo 			0x00	//FIFO read/write access
#define RegOpMode 			0x01	//Operating modes of the transceiver
#define RegDataModul 		0x02	//Data operation mode and Modulation settings
#define RegBitrateMsb 		0x03	//Bit Rate setting, Most Significant Bits
#define RegBitrateLsb 		0x04 	//Bit Rate setting, Least Significant Bits
#define RegFdevMsb			0x05	//Frequency Deviation setting, Most Significant Bits
#define RegFdevLsb 			0x06	//Frequency Deviation setting, Least Significant Bits
#define RegFrfMsb 			0x07	//RF Carrier Frequency, Most Significant Bits
#define RegFrfMid 			0x08	//RF Carrier Frequency, Intermediate Bits
#define RegFrfLsb 			0x09	//RF Carrier Frequency, Least Significant Bits
#define RegOsc1  			0x0A	//RC Oscillators Settings
#define RegAfcCtrl 			0x0B	//AFC control in low modulation index situations
#define RegListe 			0x0D 	//Listen Mode settings
#define RegListen2      	0x0E	//Listen Mode Idle durantion
#define RegListen3 			0x0F	//Listen Mode Rx duration
#define RegVersion 			0x10	//Version of module
#define RegPaLevel			0x11	//PA selection and Output Power control
#define RegPaRamp 			0x12	//Control of the PA ramp time in FSK mode
#define RegOcp				0x13	//Over Current Protection control
#define RegLna 				0x18	// LNA settings
#define RegRxBw				0x19	//Channel Filter BW Control
#define RegAfcBw 			0x1A	//Channel Filter BW control during the AFC routine
#define RegOokPeak			0x1B	//OOK demodulator selection and control in peak mode
#define RegOokAvg			0x1C	//Average threshold control of the OOK demodulator
#define RegOokFix			0x1D	//Fixed threshold control of the OOK demodulator
#define	RegAfcFei 			0x1E	//AFC and FEI control and status
#define RegAfcMsb 			0x1F	//MSB of the frequency correction of the AFC
#define	RegAfcLsb			0x20	//LSB of the frequency correction of the AFC
#define RegFeiMsb			0x21	//MSB of the calculated frequency error
#define RegFeiLsb			0x22	//LSB of the calculated frequency error
#define RegRssiConfig 		0x23	//RSSI-related settings
#define RegRssiValue 		0x24	//RSSI value in dBm
#define	RegDioMapping1		0x25	//Mapping of pins DIO0 to DIO3
#define RegDioMapping2		0x26	//Mapping of pins DIO4 and DIO5, ClkOut frequency
#define	RegIrqFlags1 		0x27	//Status register: PLL Lock state, Timeout, RSSI > Threshold...
#define	RegIrqFlags2		0x28	//Status register: FIFO handling flags...
#define RegRssiTresh		0x29	//RSSI Threshold control
#define RegRxTimeout1		0x2A	//Timeout duration between Rx request and RSSI detection
#define RegRxTimeout2		0x2B	//Timeout duration between RSSI detection and PayloadReady
#define	RegPreambleMsb		0x2C	//Preamble length, MSB
#define	RegPreambleLsb		0x2D	//Preamble length, LSB
#define	RegSyncConfig		0x2E	//Sync Word Recognition control
#define RegSyncValue1 		0x2F	//Sync Word bytes, 1 through 8
#define RegSyncValue2   	0x30
#define RegSyncValue3  		0x31
#define RegSyncValue4 		0x32
#define RegSyncValue5  		0x33
#define RegSyncValue6  		0x34
#define RegSyncValue7  		0x35
#define RegSyncValue8  		0x36
#define RegPacketConfig1	0x37	//Packet mode settings
#define	RegPayloadLength	0x38	//Payload length settings
#define RegNodeAdrs			0x39	//Node Address
#define RegBroadcastAdrs	0x3A	//Broadcast Afdress
#define RegAutoModes		0x3B	//Auto modes settings
#define RegFifoTresh		0x3C	//Fifo threshold, Tx start condition
#define RegPacketConfig2	0x3D	//Packet mode settings
#define RegAesKey1			0x3E	//16 bytes of the cypher key
#define RegAesKey2 			0x3F
#define RegAesKey3 			0x40
#define RegAesKey4          0x41
#define RegAesKey5 			0x42
#define RegAesKey6 			0x43
#define RegAesKey7			0x44
#define RegAesKey8			0x45
#define RegAesKey9			0x46
#define RegAesKey10			0x47
#define RegAesKey11 		0x48
#define RegAesKey12			0x49
#define RegAesKey13			0x4A
#define RegAesKey14			0x4B
#define RegAesKey15			0x4C
#define RegAesKey16			0x4D
#define RegTemp1			0x4E	//Temperature Sensor control
#define RegTemp2			0x4F	//Temperature readout
#define RegTestLna			0x58	//Sensetive boost
#define RegTestPa1			0x5A	//High Power settings
#define RegTestPa2			0x5C	//High power settings
#define RegTestDagc 		0x6F	//Fading Margin Improvement
#define RegTestAfc 			0x71	// AFC offset for low modulation index ADC
#define RegTest 			0x50	//Internal test registers

//pag.12 Frequency Synthesis

#define R69_FXOSC 			32000000 //Crystal oscillator frequency
#define R69_FSTEP			61.0352	 //FXOSC/2^19


//434MHz module pag.17	FRF = Fstep * Frf(23,0)	=> Frf = FRF(434MHz)/FSTEP

#define FrfMsb				0x6C
#define FrfMid 				0x40
#define FrfLsb  			0x00

//pagina 20 - bitrates ! FxOSC/BR = BitRate -> regBitRate

//some examples
//#define double bitRate [] = {1.2,2.4,4.8,9.6,19.2,38.4,76.8,153.6,57.6,115.2,12.5,25,50,100,150,200,300}
//#define int bitRateMSB [] = {0x68,0x34,0x1A,0x0D,0x06,0x03,0x01,0x00,0x02,0x01,0x0A,0x05,0x02,0x01,0x00,0x00,0x00,0x00}
//#define int bitRateLSB [] = {0x2B,0x15,0x0B,0x05,0x83,0x41,0xA1,0xD0,0x2C,0x16,0x00,0x00,0x80,0x40,0xD5,0xA0,0x80,0x6B}

//FSK MODULATION Fdev =FStep*Fdev(13,0) & Fdev+BR/2 <= 500 KHz


//Power Amplifiers Mode pag.21   -> RegPaLevel
//bits pa1 -> 7 pa1 bit-> 6 pa2 -> 5 bit(5-0) -> Pout (-18dB -> 20dBm)

#define PA0_ON	0x80
#define PA1_ON 	0x40
#define PA2_ON	0x20


//LNA GAIN SETTINGS

#define LNA_AGC 	0x00
#define LNA_MAX 	0x01
#define LNA_6DB 	0x02
#define LNA_12DB 	0x03
#define LNA_24DB 	0x04
#define LNA_36DB 	0x05
#define LNA_48DB	0x06

//Impedancia de entrada

#define LNA_ZIN_50 	0x00
#define LNA_ZIN_200 0x80

// Reg OP Mode

#define SEQ_ON 		0x80 	//Sequencer ON
#define SEQ_OFF 	0x00 	//Sequencer OFF

#define LIS_ON 		0x40		//Listen ON !
#define LIS_OFF 	0x00 	//ListenOFF

#define LIS_ABOR 	0x20	//Listen abort
#define OPMODE_MODE_BITS	 0xE3
#define SLEEP 		0x00 	// Estados -- bits 4-2
#define	STDBY 	0x04
#define FS 			0x08
#define TX 			0x0C
#define RX 			0x10

//RegDataModul
#define DATAMODE_BITS  0x60
#define PACKTET		0x00  //DataMode
#define CONT_BS 	0x40
#define CONT_NBS	0x60
#define	MOD_TYPE_BITS	0x18
#define FSK			0x00 //Modulation type
#define OOK 		0x08

#define	MOD_SHAPE_BITS	0x03

#define NO_SHAPPING 0x00 //Modulation shapping

#define FSK_GF1		0x01
#define FSK_GF05	0x02
#define FSK_GF03	0x03

#define OOK_FCBR 	0x01
#define OOK_FC2BR 	0x02

//regOsc1
#define RCCAL_START 0x80
#define RCCAL_DONE 	0x40

//Reglisten1
#define LISTEN_IDLE_BITS	0xC0
#define LISTEN_IDLE_RES64 	0x40
#define LISTEN_IDLE_RES41 	0x80
#define LISTEN_IDLE_RES262	0xC0

#define LISTEN_RX_BITS		0x30
#define LISTEN_RX_RES64		0x10
#define LISTEN_RX_RES41		0x20
#define LISTEN_RX_RES262	0x30

#define LISTEN_CRIT_BITS		0x08
#define LISTEN_CRIT_RSSI		0x00
#define LISTEN_CRIT_RSSI_SYNC 	0x08

#define LIST_END_BITS	0x60
#define LISTEN_END_00	0x00
#define	LISTEN_END_01	0x02
#define	LISTEN_END_10	0x04


//RegPaRamp

#define PA_RAMP_34 	0x00
#define PA_RAMP_2  	0x01
#define PA_RAMP_1  	0x02
#define PA_RAMP_500 0x03
#define PA_RAMP_250	0x04
#define PA_RAMP_125	0x05
#define PA_RAMP_100	0x06
#define PA_RAMP_62	0x07
#define PA_RAMP_50  0x08
#define PA_RAMP_40	0x09
#define PA_RAMP_31  0x0A
#define PA_RAMP_25  0x0B
#define PA_RAMP_20  0x0C
#define PA_RAMP_15  0x0D
#define PA_RAMP_12  0x0E
#define PA_RAMP_10  0x0F

//RegOcp

#define OCP_ON 	0x10
#define OCP_OFF 0x00

//RegBwMant

#define RX_BW_MANT_16 0x00
#define RX_BW_MANT_20 0x04
#define RX_BW_MANT_24 0x10

//RegOokPeak

#define	OOK_TRESH_TYPE_FIX 	0x00
#define OOK_TRESH_TYPE_PEAK 0x40
#define OOK_TRESH_TYPE_AVG	0x80

#define OOK_PEAK_TRESH_STEP_05 0x00
#define OOK_PEAK_TRESH_STEP_15 0x10
#define OOK_PEAK_TRESH_STEP_3  0x20
#define OOK_PEAK_TRESH_STEP_5  0x30
#define OOK_PEAK_TRESH_STEP_1  0x08
#define OOK_PEAK_TRESH_STEP_2  0x18
#define OOK_PEAK_TRESH_STEP_4  0x28
#define OOK_PEAK_TRESH_STEP_6  0x38

#define OOK_PEAK_TRESH_DEC_1_C 		0x00
#define OOK_PEAK_TRESH_DEC_1_2C 	0x01
#define OOK_PEAK_TRESH_DEC_1_4C		0x02
#define OOK_PEAK_TRESH_DEC_1_8C		0x03
#define OOK_PEAK_TRESH_DEC_2_C		0x04
#define OOK_PEAK_TRESH_DEC_4_C		0x05
#define OOK_PEAK_TRESH_DEC_8_C		0x06
#define OOK_PEAK_TRESH_DEC_16_C		0x07


//regFeiDone

#define FEI_DONE 		0x40
#define FEI_START 		0x20
#define AFC_DONE 		0x10
#define AUTO_CLEAR_ON 	0x08
#define AFC_AUTO_ON 	0x04
#define AFC_CLEAR 		0x02
#define AFC_START 		0x01

//RegRSSICONFIG

#define RSSI_DONE 	0x02
#define RSSI_START	0x01

//RegDioMapping

#define DIO0_MAPPING_BITS 			 0xC0
#define DIO0_MAPPING_00				 	 0x00
#define DIO0_MAPPING_01					 0x40
#define DIO0_MAPPING_10					 0x80
#define DIO0_MAPPING_11					 0xC0


#define	DIO1_MAPPING_BITS                0x30
#define DIO1_MAPPING_00                  0x00
#define DIO1_MAPPING_01                  0x10
#define DIO1_MAPPING_10                  0x20
#define DIO1_MAPPING_11                  0x30

#define DIO2_MAPPING_BITS                0x0c
#define DIO2_MAPPING_00                  0x00
#define DIO2_MAPPING_01                  0x04
#define DIO2_MAPPING_10                  0x08
#define DIO2_MAPPING_11                  0x0c


#define DIO3_MAPPING_BITS                0x03
#define DIO3_MAPPING_00                  0x00
#define DIO3_MAPPING_01                  0x01
#define DIO3_MAPPING_10                  0x02
#define DIO3_MAPPING_11                  0x03



//REGDIOMAPPING2

#define DIO4_MAPPING_BITS                0xC0
#define DIO4_MAPPING_00                  0x00
#define DIO4_MAPPING_01                  0x40
#define DIO4_MAPPING_10                  0x80
#define DIO4_MAPPING_11                  0xC0

#define DIO5_MAPPING_BITS                0x30
#define DIO5_MAPPING_00                  0x00
#define DIO5_MAPPING_01                  0x10
#define DIO5_MAPPING_10                  0x20
#define DIO5_MAPPING_11                  0x30

#define CLK_OUT_FXOSC_BITS				 0x07
#define CLK_OUT_FXOSC 					 0x00
#define CLK_OUT_FXOSC_DIV_2				 0x01
#define CLK_OUT_FXOSC_DIV_4				 0x02
#define CLK_OUT_FXOSC_DIV_8				 0x03
#define CLK_OUT_FXOSC_DIV_16		     0x04
#define CLK_OUT_FXOSC_DIV_32			 0x05
#define CLK_OUT_FXOSC_RC				 0x06
#define CLK_OUT_FXOSC_OFF			     0x07



//RegIrqFlags

#define IRQ1_MODE_RDY		 0x80
#define IRQ1_RX_RDY		     0x40
#define IRQ1_TX_RDY			 0x20
#define IRQ1_PLL_LOCK		 0x10
#define IRQ1_RSSI			 0x08
#define IRQ1_TIME_OUT		 0x04
#define IRQ1_AUTO_MODE		 0x02
#define IRQ1_SYNC_ADRS_MATCH 0x01


//RegIrqFlags2

#define IRQ2_FIFO_FULL 			0x80
#define IRQ2_FIFO_NOT_EMPTY 	0x40
#define IRQ2_FIFO_LEVEL			0x20
#define IRQ2_FIFO_OVERRUN		0x10
#define IRQ2_PACKET_SENT		0x08
#define IRQ2_PAYLOAD_RDY		0x04
#define IRQ2_CRC_OK				0x02

//RegSyncConfig

#define SYNC_ON				0x80
#define FIFO_FILL_COND 		0x40
#define SYNC_SIZE_BITS		0x38
#define SYNC_TOL_BITS		0x07

#define SYNC_SIZE_1            0x00
#define SYNC_SIZE_2            0x08
#define SYNC_SIZE_3            0x10
#define SYNC_SIZE_4            0x18  // Default
#define SYNC_SIZE_5            0x20
#define SYNC_SIZE_6            0x28
#define SYNC_SIZE_7            0x30
#define SYNC_SIZE_8            0x38
//RegPacketConfig1

#define PACKET1_FORMAT_VARIABLE		0x80
#define PACKET1_FORMAT_FIXED 0x00
#define PACKET1_DC_FREE_BITS		0x60
#define PACKET1_DC_FREE_OFF			0x00
#define PACKET1_DC_FREE_MANCH		0x20
#define PACKET1_DC_FREE_WHIT		0x40
#define PACKET1_CRC_ON				0x10
#define PACKET1_CRC_AUTO_CLEAR_OFF	0x40
#define PACKET1_ADDRS_FILTR_BITS 	0x06
#define PACKET1_ADDRS_FILTR_OFF		0x00
#define PACKET1_ADDRS_FILTR_NODE 	0x02
#define PACKET1_ADDRS_FILTR_NODE_BRDC 0x04

//Regautomodes
/*
#define AUTO_MODE_ENTER_BITS 				0xE0
#define AUTO_MODE_ENTER_NONE 				0x00
#define AUTO_MODE_ENTER_FIFO_NOT_EMPTY		0x20
#define AUTO_MODE_ENTER_FIFO_LEVEL			0x40
#define AUTO_MODE_ENTER_CRC_OK				0x60
#define AUTO_MODE_ENTER_PAYLOAD_RDY			0x80
#define AUTO_MODE_ENTER_SYNCADRR			0xA0
#define AUTO_MODE_ENTER_PACKET_SENT			0xC0
#define AUTO_MODE_ENTER_FIFO_NOT_EMPTY		0xE0

#define AUTO_MODE_EXIT_BITS 				0x1C
#define AUTO_MODE_EXIT_NONE 				0x00
#define AUTO_MODE_EXIT_FIFO_NOT_EMPTY		0x04
#define AUTO_MODE_EXIT_FIFO_LEVEL_TIMEOUT	0x08
#define AUTO_MODE_EXIT_CRC_OK_TIMEOUT		0x0C
#define AUTO_MODE_EXIT_PAYLOAD_RDY_TIMEOUT	0x10
#define AUTO_MODE_EXIT_SYNCADRR_TIMEOUT		0x14
#define AUTO_MODE_EXIT_PACKET_SENT			0x18
#define AUTO_MODE_EXIT_FIFO_NOT_EMPTY		0x1C

#define AUTO_MODE_INT_BITS					0x03
#define AUTO_MODE_INT_SLEEP					0x00
#define AUTO_MODE_INT_STBY					0x01
#define AUTO_MODE_INT_RX					0x02
#define AUTO_MODE_INT_TX					0x03

*/
//RegFifoTresh


 #define TX_START_FIFO_NOT_EMPTY			0x80
 #define FIFO_TRESHOLD_BITS					0x7F
 #define RESTART_RX							0x04
#define AUTO_RESTART_RX						0x02
#define	AES_ON								0x01


#endif
