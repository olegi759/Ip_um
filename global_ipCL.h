
#include "compiler_defs.h"
#include "C8051F330_defs.h"
#include "define_ipCL.h"
#include "struct.h"
#include "fun_prototype.h"

/* PORT 0*/
sbit P_in_L4			=P0 ^ 2;
sbit P_in_L3			=P0 ^ 3;
sbit P_in_L2			=P0 ^ 6;
sbit P_in_L1			=P0 ^ 7;

/* PORT 1*/
sbit P_tpic2_G			=P1 ^ 0;
sbit P_tpic2_RCK			=P1 ^ 1;
sbit P_tpic2_SRCK			=P1 ^ 2;
sbit P_tpic2_DATA			=P1 ^ 3;
sbit P_tpic1_G			=P1 ^ 4;
sbit P_tpic1_RCK			=P1 ^ 5;
sbit P_tpic1_SRCK			=P1 ^ 6;
sbit P_tpic1_DATA			=P1 ^ 7;

//загрузка tpic 1
BYTE bdata tpic1;
	sbit rele_L1		=tpic1 ^ 0;
	sbit rele_L2		=tpic1 ^ 1;
	sbit gain_L1		=tpic1 ^ 2;
	sbit gain_L2		=tpic1 ^ 3;
	sbit idac_L1		=tpic1 ^ 4;
	sbit idac_L2		=tpic1 ^ 5;

//загрузка tpic 2
BYTE bdata tpic2;
	sbit rele_L3		=tpic2 ^ 0;
	sbit rele_L4		=tpic2 ^ 1;
	sbit gain_L3		=tpic2 ^ 2;
	sbit gain_L4		=tpic2 ^ 3;
	sbit idac_L3		=tpic2 ^ 4;
	sbit idac_L4		=tpic2 ^ 5;

//каналы инстал€ции
BYTE bdata set_install;
	sbit install_cahal_1		=set_install ^ 0;
	sbit install_cahal_2		=set_install ^ 1;
	sbit install_cahal_3		=set_install ^ 2;
	sbit install_cahal_4		=set_install ^ 3;
	
//каналы тестировани€(указание диапазона)
BYTE set_canal_test[4];//0-нет,1-GAIN_MAX,2-GAIN_MIN
//реле трансл€ции,0xFF- вкл
BYTE set_rele[4];
//выполнить загрузку
//bit F_load_tpic_1;
//bit F_load_tpic_2;

//измерени€
WORD data code_IDAC;//IDAC
WORD data Hi_code_IDAC;//дл€ загрузки старшего байта

WORD data hold_code_IDAC;//код срабатывани€
WORD data install_code_IDAC_1;//значение 1 диапазона
WORD data install_code_IDAC_2;//значение 2 диапазона
WORD data test1_install;//дл€ вычислений
WORD data test2_install;//дл€ вычислений
WORD data sum_code_IDAC;//IDAC дл€ интегрировани€
BYTE data c_sum_code;//

bit F_load_idac;//флаг на загрузку ступеньки
bit F_first_step;//флаг пропуск первого
bit F_run_test;//1-идет тест
bit F_end_test;//1-
bit F_rise_step_idac;//1- растет
//bit F_end_step_idac;//1-конец диапазона
bit F_hold_data_idac;//1-выполнено запоминание
bit F_run_sum;//1-выполн€ем суммирование
bit F_fast_test;//1-проводим быстрый тест линии 

BYTE data range;//диапазон 1,2
BYTE data canal_test;//1,2,3,4
//BYTE data c_add_code_IDAC;//дополнительный подъем после срабатывани€

//обработка вх сигналов срабатывани€ компаратора
bit F_in_comp_on;//1-сработал
//bit F_in_comp2_on;//1-сработал
//bit F_in_comp3_on;//1-сработал
//bit F_in_comp4_on;//1-сработал
WORD xdata c_in_comp1;
WORD xdata c_in_comp2;
WORD xdata c_in_comp3;
WORD xdata c_in_comp4;
WORD xdata c_in_comp_total;

//секундный таймер
BYTE data c_10ms;//по 10мс до 1 сек
int data footim;
BYTE data c_seconds;//

BYTE bdata F_start_test;
	sbit F_start_test_L1 = F_start_test ^ 0;
	sbit F_start_test_L2 = F_start_test ^ 1;
	sbit F_start_test_L3 = F_start_test ^ 2;
	sbit F_start_test_L4 = F_start_test ^ 3;

//
BYTE data v_test;
bit F_div_f_start_dac;//дл€ получени€ 4ms в прерывании
BYTE data div_f_start_dac;//дл€ получени€ 8ms в прерывании

/*---------------------------------------------
обмен с компом 
-----------------------------------------------*/
BYTE data st_Rx_PC;				//состо€ние обмена (приним "старт","адр" и т.д.
BYTE data st_Tx_PC;				//состо€ние обмена (ѕ≈–≈ƒј≈ћ "старт","адр" и т.д.
BYTE data v_PC;				//внутр переменна€ дл€ обработки прин€того байта
bit F_run_com_PC;		  //флаг на обработку

BYTE	data Rx_command_PC;		   //код команды
BYTE	data Tx_command_PC;		   //код команды
BYTE 	data Tx_counter_or_error;  //колл байт или код ошибки
BYTE data n_byte_Rx_PC;		// необходимо прин€ть байт
BYTE data n_byte_Tx_PC;		// необходимо передать байт
union _WB data CRC_Rx_PC;		   //контрольна€ сумма
union _WB data CRC_Tx_PC;		   //контрольна€ сумма

BYTE xdata bufTX_PC[TX_BUFFER_SIZE];	
BYTE xdata bufRX_PC[RX_BUFFER_SIZE];

BYTE	data c_bufTX_PC;		//счетчик переданнх байт
BYTE	data c_bufRX_PC;		//счетчик прин€тых байт

bit F_delaed_response;
struct _DacStartValueLines DacStartValueLines;

//структуры обмена с пк
struct _Status_SL		Status_SL;
struct _Status_Rele_SL	Status_Rele_SL;
// *************************************************************
//таблица дл€ вычислени€ контрольной суммы обмена с компом
// SEGMENT: CODE	

WORD code wCRCTable[] = {
   0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
   0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
   0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
   0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
   0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
   0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
   0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
   0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
   0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
   0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
   0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
   0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
   0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
   0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
   0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
   0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
   0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
   0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
   0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
   0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
   0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
   0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
   0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
   0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
   0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
   0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
   0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
   0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
   0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
   0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
   0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
   0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};


	