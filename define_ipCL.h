//параметры проведения теста линий 
#define CODE_DAC_CORESPONDING_ZERO        128
#define MAX_CODE_DAC_REG                  0xFFC0
#define INTEGRATION_COUNT                 32


//упавление выходными сигналами tpic
#define RELE_L1_ON		rele_L1=1
#define RELE_L1_OFF		rele_L1=0
#define RELE_L2_ON		rele_L2=1
#define RELE_L2_OFF		rele_L2=0
#define RELE_L3_ON		rele_L3=1
#define RELE_L3_OFF		rele_L3=0
#define RELE_L4_ON		rele_L4=1
#define RELE_L4_OFF		rele_L4=0
#define GAIN_L1_MAX		gain_L1=0
#define GAIN_L1_MIN		gain_L1=1
#define GAIN_L2_MAX		gain_L2=0
#define GAIN_L2_MIN		gain_L2=1
#define GAIN_L3_MAX		gain_L3=0
#define GAIN_L3_MIN		gain_L3=1
#define GAIN_L4_MAX		gain_L4=0
#define GAIN_L4_MIN		gain_L4=1
#define IDAC_L1_ON		idac_L1=1
#define IDAC_L1_OFF		idac_L1=0
#define IDAC_L2_ON		idac_L2=1
#define IDAC_L2_OFF		idac_L2=0
#define IDAC_L3_ON		idac_L3=1
#define IDAC_L3_OFF		idac_L3=0
#define IDAC_L4_ON		idac_L4=1
#define IDAC_L4_OFF		idac_L4=0


/*------------------------------------------------------
текущее состояние UART0 (связь с компом)
------------------------------------------------------*/

#define RX_BUFFER_SIZE      25
#define TX_BUFFER_SIZE      50

#define RX_WAIT 			0x00	// 	   
#define RX_START			0x01	// 
#define RX_ADDRESS			0x02	// 
#define RX_COMMAND			0x03	// 
#define RX_BYTECOUNT		0x04	// 
#define RX_DATA				0x05	// 
#define RX_CRC_1			0x06	// 
#define RX_CRC_2			0x07	//

#define TX_WAIT 			0x00	// 	   
#define TX_START			0x01	// 
#define TX_ADDRESS			0x02	// 
#define TX_COMMAND			0x03	// 
#define TX_BYTECOUNT		0x04	// 
#define TX_DATA				0x05	// 
#define TX_CRC_1			0x06	// 
#define TX_CRC_2			0x07	//
#define TX_END				0x08	//
#define TX_DEBUG_BEGIN      0x0D
#define TX_DEBUG            0x1D      

#define ADDR_IPCL		0x10	//адресс cpu контроля линий
#define ADDR_IPCP		0x11	//адресс cpu контроля источ питания
#define COD_START_RX_PC		'$'
#define COD_START_TX_PC		'#'

//------------------------------
//команды обмена
//---------------------------------

#define CMD_PC_INSTALL_SL         0x01    //провести инстал звуковых линий
#define CMD_PC_TEST_SL            0x02    //провести тест звуковых линий
#define CMD_PC_SET_RELE_SL		0x03	//управление реле трансл
#define CMD_PC_READ_RELE_SL 		0x04	//ЗАПРОС состоян реле трансл

#define CMD_PC_DEBUG_SL 		0xDD	


