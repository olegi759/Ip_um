/**************************
программа контрол€ звуковых линий IP усилител€
***************************/
//#include "C8051F330.h"
#include "extern_ipCL.h"
#include <string.h>
//обработка команды
void work_PC(void){

   switch (Rx_command_PC){		   //код команды
	case CMD_PC_INSTALL_SL:
		set_install=0;
		if(bufRX_PC[0]==0xFF)install_cahal_1=1;
		if(bufRX_PC[1]==0xFF)install_cahal_2=1;
		if(bufRX_PC[2]==0xFF)install_cahal_3=1;
		if(bufRX_PC[3]==0xFF)install_cahal_4=1;

		//инстал€ци€ звуковых линий
		install_SL();
	
		//отправл€ем результат
		 Tx_command_PC=CMD_PC_INSTALL_SL;
		 n_byte_Tx_PC=sizeof(struct _Status_SL);
		 /*загружаем данные в буф передачи*/
		 memcpy(&bufTX_PC[0],&Status_SL,n_byte_Tx_PC);
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;
		//сброс старых
		Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=0;
		Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;
		Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;
		Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;	
	break;	   
	case CMD_PC_TEST_SL:
		set_canal_test[0]=bufRX_PC[0];
		set_canal_test[1]=bufRX_PC[1];
		set_canal_test[2]=bufRX_PC[2];
		set_canal_test[3]=bufRX_PC[3];

		//ответ
		 Tx_command_PC=CMD_PC_TEST_SL;
		 n_byte_Tx_PC=sizeof(struct _Status_SL);
		 /*загружаем данные в буф передачи*/
		 memcpy(&bufTX_PC[0],&Status_SL,n_byte_Tx_PC);
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;	
	
		//сброс старых
		if(set_canal_test[0]==0){Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=0;}
		if(set_canal_test[1]==0){Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;}
		if(set_canal_test[2]==0){Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;}
		if(set_canal_test[3]==0){Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;}		
	break;	   
	case CMD_PC_SET_RELE_SL:
		if(bufRX_PC[0]==0xFF){
			set_rele[0]=0xFF;
			set_canal_test[0]=0;
			RELE_L1_ON;
			
			if(F_run_test){//1-идет тест
				if(canal_test==1){
					IDAC_L1_OFF;
					F_run_test=0;
					//IDA0=0;
					IDA0L=0;	
					IDA0H=0;
				}
			}
		}
		else{
			set_rele[0]=0;
			RELE_L1_OFF;						
		}
		if(bufRX_PC[1]==0xFF){
			set_rele[1]=0xFF;
			set_canal_test[1]=0;
			RELE_L2_ON;
			
			if(F_run_test){//1-идет тест
				if(canal_test==2){
					IDAC_L2_OFF;
					F_run_test=0;
					//IDA0=0;
					IDA0L=0;	
					IDA0H=0;
				}
			}
		}
		else{
			set_rele[1]=0;
			RELE_L2_OFF;						
		}
		if(bufRX_PC[2]==0xFF){
			set_rele[2]=0xFF;
			set_canal_test[2]=0;
			RELE_L3_ON;
			
			if(F_run_test){//1-идет тест
				if(canal_test==3){
					IDAC_L3_OFF;
					F_run_test=0;
					//IDA0=0;
					IDA0L=0;	
					IDA0H=0;
				}
			}
		}
		else{
			set_rele[2]=0;
			RELE_L3_OFF;						
		}
		if(bufRX_PC[3]==0xFF){
			set_rele[3]=0xFF;
			set_canal_test[3]=0;
			RELE_L4_ON;
			
			if(F_run_test){//1-идет тест
				if(canal_test==4){
					IDAC_L4_OFF;
					F_run_test=0;
					//IDA0=0;
					IDA0L=0;	
					IDA0H=0;
				}
			}
		}
		else{
			set_rele[3]=0;
			RELE_L4_OFF;						
		}
		//ответ
		 Tx_command_PC=CMD_PC_SET_RELE_SL;
		 n_byte_Tx_PC=4;
		 /*загружаем данные в буф передачи*/
		 bufTX_PC[0]=set_rele[0];
		 bufTX_PC[1]=set_rele[1];
		 bufTX_PC[2]=set_rele[2];
		 bufTX_PC[3]=set_rele[3];
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;
		
		//загрузка tpic
		PCA0CPH2  = 0;//reset wdt
		set_tpic1();
		set_tpic2();
		
	break;
	case CMD_PC_READ_RELE_SL:
		//ответ
		 Tx_command_PC=CMD_PC_READ_RELE_SL;
		 n_byte_Tx_PC=4;
		 /*загружаем данные в буф передачи*/
		 bufTX_PC[0]=set_rele[0];
		 bufTX_PC[1]=set_rele[1];
		 bufTX_PC[2]=set_rele[2];
		 bufTX_PC[3]=set_rele[3];
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;
	break;
	case CMD_PC_DEBUG_SL:
		
		 /*загружаем данные в буф передачи*/
		 memcpy(&bufTX_PC[0],&Status_SL,n_byte_Tx_PC);
		//ответ
		 Tx_command_PC=CMD_PC_DEBUG_SL;
		 n_byte_Tx_PC=4 + sizeof(struct _Status_SL);
		 /*загружаем данные в буф передачи*/
		 bufTX_PC[0]=(BYTE)(footim >> 8);
		 bufTX_PC[1]=(BYTE)footim;
		 bufTX_PC[2]=c_10ms;
		 bufTX_PC[3]=c_seconds;
		 memcpy(&bufTX_PC[4], &Status_SL, sizeof(struct _Status_SL));
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;
	break;
   }
   
}


