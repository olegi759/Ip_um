/*******************************************************
обработка прерывания uart0  канал связи с компом

*****************************************************/
#include "extern_ipCL.h"

void uart_0(void) interrupt 4{



	if( RI0 ) {	// //флаг приема

		RI0=0;		// Очистить флаг прерывания
		v_PC = SBUF0;
		if(st_Rx_PC == RX_WAIT){//если ожидание новой посылки
			if(v_PC == COD_START_RX_PC){				//получили Старт
				st_Rx_PC =RX_START;
			}

		}
		
			
		switch( st_Rx_PC ) {
			// ------------------------------------------------
			case RX_WAIT: return;			  ////нарушение приема,переходим в ожидание новой посылки
			/**/
			case RX_START:
				 st_Rx_PC =RX_ADDRESS;		 //будем ждать байт адресса
				 return;
			/**/
			case RX_ADDRESS:
				if(v_PC ==ADDR_IPCL){	  //наш адресс
					CRC_Rx_PC.w = 0x5BBF;	// UART1_CRC.w = CRC16(0xFFFF, '$'); начали считать сумму						
					st_Rx_PC =RX_COMMAND;
					F_run_com_PC=0;						//снимаем флаг на обработку команды компа
				}
				else {
					st_Rx_PC = RX_WAIT;		   //не наш адресс
					return;
				}
				break;
		   /**/
		   case RX_COMMAND:
				st_Rx_PC =RX_BYTECOUNT;
				Rx_command_PC=v_PC;			   //получили команду
				break;
		   /**/
		   case RX_BYTECOUNT:
				if(v_PC==0)st_Rx_PC =RX_CRC_1;	//данных не будет //будем прин сумму
				else{			   
					if( v_PC <= 25 ) {
						c_bufRX_PC = 0;				//счет принятых
						n_byte_Rx_PC = v_PC;		//байт данных в посылке
						st_Rx_PC    = RX_DATA;
					}
					else {
						st_Rx_PC = RX_WAIT;		   //не наш адресс
						return;
					}			   
				}
				break; 
		   /**/
		   case	RX_DATA:
				bufRX_PC[c_bufRX_PC]=v_PC;
				c_bufRX_PC++;
				if(c_bufRX_PC==n_byte_Rx_PC)st_Rx_PC =RX_CRC_1; //усё получили
				break;
		   /**/
		   case RX_CRC_1:
				if(v_PC==CRC_Rx_PC.b[1])st_Rx_PC =RX_CRC_2;
				else	st_Rx_PC = RX_WAIT;					  //ошибка суммы
				return;

			/**/
			case RX_CRC_2:
				if(v_PC==CRC_Rx_PC.b[0]){
					F_run_com_PC=1;						//флаг на обработку команды компа
				}
				st_Rx_PC = RX_WAIT;				   //посылка получена
				return;

			}									 //законч case
			 
		/*считаем сумму*/
		v_PC = v_PC ^ CRC_Rx_PC.b[1];		// | UART1_CRC.w = CRC16(UART1_CRC.w, UART1_b);
		CRC_Rx_PC.b[1] = CRC_Rx_PC.b[0];			// |
		CRC_Rx_PC.b[0] = 0;					// |
		CRC_Rx_PC.w ^= wCRCTable[v_PC];		// |



	}
	// -------------------------------------------------------------------
	// Передача: '#'(Address)(Command)(ByteCount)(CRC16)
	// -------------------------------------------------------------------
	if( TI0 ) {	// TI1 = 1
		TI0=0;		// Очистить флаг прерывания
		
			switch( st_Tx_PC ) {
			
				case TX_ADDRESS:
					SBUF0 =v_PC=ADDR_IPCL;
					CRC_Tx_PC.w= 0x99FE;	// UART1_CRC.w = CRC16(0xFFFF, '#');
					st_Tx_PC=TX_COMMAND;
				break;

				case TX_COMMAND:
					SBUF0 =v_PC=Tx_command_PC;
					st_Tx_PC=TX_BYTECOUNT;
				break;
			
				case TX_BYTECOUNT:
					SBUF0 =v_PC=Tx_counter_or_error;
					if(n_byte_Tx_PC){
						st_Tx_PC=TX_DATA;
						c_bufTX_PC=0;
					}
					else st_Tx_PC=TX_CRC_1;
				break;
			
				case TX_DATA:
					SBUF0 =v_PC=bufTX_PC[c_bufTX_PC];
					c_bufTX_PC++;
					if(c_bufTX_PC==n_byte_Tx_PC)st_Tx_PC=TX_CRC_1;

				break;
			
				case TX_CRC_1:
					 SBUF0 =CRC_Tx_PC.b[1];
					 st_Tx_PC=TX_CRC_2;
					 return;
				break;
			
				case TX_CRC_2:
					 SBUF0 =CRC_Tx_PC.b[0];
					 st_Tx_PC=TX_END;
					 return;
				break;

				default:
					//OFF_TX_PC;		//Выкл передатчик 485
					//SCON1 |= 0x10;			   //разреш прием
					return;
			
			}	
	
			/*считаем сумму*/
			v_PC = v_PC ^ CRC_Tx_PC.b[1];		// | UART1_CRC.w = CRC16(UART1_CRC.w, UART1_b);
			CRC_Tx_PC.b[1] = CRC_Tx_PC.b[0];			// |
			CRC_Tx_PC.b[0] = 0;					// |
			CRC_Tx_PC.w ^= wCRCTable[v_PC];		// |
		
	}

}
