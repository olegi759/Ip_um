/**************************
программа контрол€ звуковых линий IP усилител€
***************************/
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
sbit P_tpic2_RCK		=P1 ^ 1;
sbit P_tpic2_SRCK		=P1 ^ 2;
sbit P_tpic2_DATA		=P1 ^ 3;
sbit P_tpic1_G			=P1 ^ 4;
sbit P_tpic1_RCK		=P1 ^ 5;
sbit P_tpic1_SRCK		=P1 ^ 6;
sbit P_tpic1_DATA		=P1 ^ 7;

//загрузка tpic 1
extern BYTE bdata tpic1;
	extern bit rele_L1;
	extern bit rele_L2;
	extern bit gain_L1;
	extern bit gain_L2;
	extern bit idac_L1;
	extern bit idac_L2;

//загрузка tpic 2
extern BYTE bdata tpic2;
	extern bit rele_L3;
	extern bit rele_L4;
	extern bit gain_L3;
	extern bit gain_L4;
	extern bit idac_L3;
	extern bit idac_L4;

//каналы инстал€ции
extern BYTE bdata set_install;
	extern bit install_cahal_1;
	extern bit install_cahal_2;
	extern bit install_cahal_3;
	extern bit install_cahal_4;
	
//каналы тестировани€(указание диапазона)
extern BYTE set_canal_test[];
//реле трансл€ции,0xFF- вкл
extern BYTE set_rele[];
//выполнить загрузку
//extern bit F_load_tpic_1;
//extern bit F_load_tpic_2;

//измерени€
extern WORD data code_IDAC;//IDAC
extern WORD data Hi_code_IDAC;//дл€ загрузки старшего байта

extern WORD data hold_code_IDAC;//код срабатывани€
extern WORD data install_code_IDAC_1;//
extern WORD data install_code_IDAC_2;//
extern WORD data test1_install;//дл€ вычислений
extern WORD data test2_install;//дл€ вычислений
extern WORD data sum_code_IDAC;//IDAC дл€ интегрировани€
extern BYTE data c_sum_code;//

extern bit F_load_idac;
extern bit F_first_step;//флаг пропуск первого
extern bit F_run_test;//1-идет тест
extern bit F_end_test;//1-
extern bit F_rise_step_idac;//1- растет
//extern bit F_end_step_idac;//1-конец диапазона
extern bit F_hold_data_idac;//1-выполнено запоминание
extern bit F_run_sum;//1-выполн€ем суммирование

extern BYTE data range;//диапазон 1,2
extern BYTE data canal_test;//1,2,3,4
//extern BYTE data c_add_code_IDAC;//дополнительный подъем после срабатывани€

//обработка вх сигналов срабатывани€ компаратора
extern bit F_in_comp_on;//1-сработал
//extern bit F_in_comp2_on;//1-сработал
//extern bit F_in_comp3_on;//1-сработал
//extern bit F_in_comp4_on;//1-сработал
extern WORD xdata c_in_comp1;
extern WORD xdata c_in_comp2;
extern WORD xdata c_in_comp3;
extern WORD xdata c_in_comp4;
extern WORD xdata c_in_comp_total;


//секундный таймер
extern int data footim;
extern BYTE data c_10ms;//по 10мс до 1 сек
extern BYTE data c_seconds;//
extern BYTE bdata F_start_test;
extern bit F_start_test_L1;
extern bit F_start_test_L2;
extern bit F_start_test_L3;
extern bit F_start_test_L4;
//
extern BYTE data v_test;
extern bit F_div_f_start_dac;//дл€ получени€ 4ms в прерывании
extern BYTE data div_f_start_dac;//дл€ получени€ 8ms в прерывании

/*---------------------------------------------
обмен с компом 
-----------------------------------------------*/
extern BYTE data st_Rx_PC;				//состо€ние обмена (приним "старт","адр" и т.д.
extern BYTE data st_Tx_PC;				//состо€ние обмена (приним "старт","адр" и т.д.
extern BYTE data v_PC;				//внутр переменна€ дл€ обработки прин€того байта
extern bit F_run_com_PC;		  //флаг на обработку

extern BYTE	data Rx_command_PC;		   //код команды
extern BYTE	data Tx_command_PC;		   //код команды
extern BYTE 	data Tx_counter_or_error;  //колл байт или код ошибки
extern BYTE data n_byte_Rx_PC;		// необходимо прин€ть байт
extern BYTE data n_byte_Tx_PC;		// необходимо передать байт
extern union _WB data CRC_Rx_PC;		   //контрольна€ сумма
extern union _WB data CRC_Tx_PC;		   //контрольна€ сумма


extern BYTE	xdata bufTX_PC[];	
extern BYTE	xdata bufRX_PC[];

extern BYTE	data c_bufTX_PC;		//счетчик переданнх байт
extern BYTE	data c_bufRX_PC;		//счетчик прин€тых байт

//структуры обмена с пк
extern struct _Status_SL		Status_SL;
extern struct _Status_Rele_SL		Status_Rele_SL;
// *************************************************************
// SEGMENT: CODE	

extern WORD code wCRCTable[];

extern struct _DacStartValueLines DacStartValueLines;

extern bit F_delaed_response;


