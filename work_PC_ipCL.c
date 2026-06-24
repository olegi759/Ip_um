/**************************
программа контроля звуковых линий IP усилителя
***************************/
//#include "C8051F330.h"
#include "extern_ipCL.h"
#include <string.h>\
#include <stdarg.h>
//обработка команды
void work_PC(void){

   switch (Rx_command_PC){		   //код команды
	case CMD_PC_INSTALL_SL:
		set_install=0;
		if(bufRX_PC[0]==0xFF)install_cahal_1=1;
		if(bufRX_PC[1]==0xFF)install_cahal_2=1;
		if(bufRX_PC[2]==0xFF)install_cahal_3=1;
		if(bufRX_PC[3]==0xFF)install_cahal_4=1;

		//инсталяция звуковых линий
		install_SL();
	
		//отправляем результат
		 Tx_command_PC=CMD_PC_INSTALL_SL;
		 n_byte_Tx_PC=sizeof(struct _Status_SL);
		 /*загружаем данные в буф передачи*/
		 memcpy(&bufTX_PC[0],&Status_SL,n_byte_Tx_PC);
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;
		//сброс старых
		Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=1;
		Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;
		Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;
		Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;	
	break;	   
	case CMD_PC_TEST_SL:
		
		TMR2CN = 0x04;
		footim = 0;
	
		//сброс старых
		Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=0;
		Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;
		Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;
		Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;
	
		set_canal_test[0]=bufRX_PC[0];
		set_canal_test[1]=bufRX_PC[1];
		set_canal_test[2]=bufRX_PC[2];
		set_canal_test[3]=bufRX_PC[3];
	
		F_delaed_response = 1;
	
		set_f_start_test_Lx();
	
		
				
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
		
		n_byte_Tx_PC= 4;
		//ответ
		 Tx_command_PC=CMD_PC_DEBUG_SL;
		 
		 /*загружаем данные в буф передачи*/
		 bufTX_PC[0]=footim >> 8;
		 bufTX_PC[1]=footim & 0xFF;
		 bufTX_PC[2]=1;
		 bufTX_PC[3]=5;
		 st_Tx_PC=TX_ADDRESS;
		 Tx_counter_or_error=n_byte_Tx_PC;

		SBUF0 =COD_START_TX_PC;
	break;
	default:
	break;	
   }
   
}

void delayed_response_PC(){
	if(F_delaed_response == 1){
		// если все флаги нули, значит по всем линиям измерения закончились, можно отдавать результат
			if(set_canal_test[0] != 0 || set_canal_test[1] != 0 || set_canal_test[2] != 0 || set_canal_test[3] != 0) {
				return;
			}
				
			
			F_delaed_response = 0; // сбрасываем отложенный ответ
		
			//ответ
			Tx_command_PC=CMD_PC_TEST_SL;
			n_byte_Tx_PC=sizeof(struct _Status_SL);
			/*загружаем данные в буф передачи*/
			memcpy(&bufTX_PC[0],&Status_SL,sizeof(struct _Status_SL));
			st_Tx_PC=TX_ADDRESS;
			Tx_counter_or_error=n_byte_Tx_PC;

			SBUF0 =COD_START_TX_PC;	
			
			TMR2CN = 0x00;
	}
	
}

void SendPc(BYTE* logBuffer, int length){
	int i = 0;
	for(i = 1; i < length; i++){
		bufTX_PC[i - 1] = logBuffer[i];
	}
	Tx_counter_or_error = length - 1;
	st_Tx_PC = TX_DEBUG;
	SBUF0 = logBuffer[0];
}

//// ========== ulog ==========

//#define MAX_LOG_LEN  TX_BUFFER_SIZE

//// Буфер для логов – статический, в XDATA (если есть XRAM)
//char xdata logBuffer[MAX_LOG_LEN];
//static unsigned int msg_id = 0;

//// Вспомогательная функция: дописывает unsigned int в строку
//static void append_uint(char **ptr, unsigned int val) {
//    char tmp[12];
//    int i = 0;
//    do {
//        tmp[i++] = '0' + (val % 10);
//        val /= 10;
//    } while (val);
//    while (i > 0) {
//        *(*ptr)++ = tmp[--i];
//    }
//}

//// Вспомогательная функция: копирует строку с ограничением по длине
//static void copy_string(char **dest, const char *src, int max_len) {
//    while (max_len > 0 && *src != '\0') {
//        *(*dest)++ = *src++;
//        max_len--;
//    }
//}

//// Функция с одним параметром (только строка)
//void Ulog1(char *txt) {
//    char *ptr = logBuffer;
//    int remaining = MAX_LOG_LEN;
//    int len;

//    msg_id++;

//    // Добавляем префикс "[ID] "
//    *ptr++ = '[';
//    remaining--;
//    append_uint(&ptr, msg_id);
//    *ptr++ = ']';
//    *ptr++ = ' ';
//    remaining -= 2;

//    // Копируем текст, оставляя место для завершающего нуля
//    if (remaining > 1) {
//        len = remaining - 1;   // максимальная длина копирования
//        copy_string(&ptr, txt, len);
//    }
//    *ptr = '\0';

//    SendPc((BYTE*)logBuffer, (int)(ptr - logBuffer));
//}

//// Функция с двумя параметрами (строка + число)
//void Ulog2(char *txt, int val) {
//    char *ptr = logBuffer;
//    int remaining = MAX_LOG_LEN;
//    int len;

//    msg_id++;

//    // Префикс
//    *ptr++ = '[';
//    remaining--;
//    append_uint(&ptr, msg_id);
//    *ptr++ = ']';
//    *ptr++ = ' ';
//    remaining -= 2;

//    // Копируем текст, оставляя место для '=', числа (макс. 11 символов) и '\0'
//    if (remaining > 1 + 11) {
//        len = remaining - 1 - 11;
//        copy_string(&ptr, txt, len);
//    } else {
//        len = 0;
//    }

//    // Добавляем "="
//    *ptr++ = '=';
//    remaining -= (len + 1);

//    // Добавляем число
//    append_uint(&ptr, (unsigned int)val);
//    *ptr = '\0';

//    SendPc((BYTE*)logBuffer, (int)(ptr - logBuffer));
//}