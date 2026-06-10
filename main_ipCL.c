/**************************************
программа контроля звуковых линий IP усилителя
*********************************************/

//#include "C8051F330.h"
#include "global_ipCL.h"

/*
v6
шаг 8мс
сумм 32
20 сек на канал

*/

/*
v2
обнуление после инсталяции
F_end_test=0;


*/



/*
v1
*/


void main(void){


init_ipCL();

//установка
RELE_L1_OFF;RELE_L2_OFF;RELE_L3_OFF;RELE_L4_OFF;
GAIN_L1_MAX;GAIN_L2_MAX;GAIN_L3_MAX;GAIN_L4_MAX;	
IDAC_L1_OFF;IDAC_L2_OFF;IDAC_L3_OFF;IDAC_L4_OFF;	
set_tpic1();
set_tpic2();
P_tpic1_G=0;//вкл
P_tpic2_G=0;
	
EA=1;                  // Global Interrupt Enable	
	
	
	
	
Rx_command_PC = CMD_PC_READ_RELE_SL;
F_run_com_PC = 1;
//++	
while(1){
	
//++

PCA0CPH2  = 0;//reset wdt
//	
if(F_run_com_PC){
	F_run_com_PC=0;
	work_PC();	
}
//

delay_ipCL(1000);
//SBUF0 = 0xDA;


//выплонение шага тестирования
if(F_run_test){//1-идет тест
	test_in_comp();

	if(F_load_idac){//флаг на загрузку ступеньки
		F_load_idac=0;//флаг на загрузку ступеньки
		step_test_L();
	}
}
else{
	//запуск тестирования
	if(F_start_test_L1){
		F_start_test_L1=0;
		set_test_L1();
	}
	//запуск тестирования
	else if(F_start_test_L2){
		F_start_test_L2=0;
		set_test_L2();
	}
	//запуск тестирования
	else if(F_start_test_L3){
		F_start_test_L3=0;
		set_test_L3();
	}
	//запуск тестирования
	else if(F_start_test_L4){
		F_start_test_L4=0;
		set_test_L4();
	}	
	
}

//закончили тест одной линии
if(F_end_test){
	F_end_test=0;
	PCA0CPH2  = 0;//reset wdt
		//переносим в буфер передачи
		if(canal_test==1){
			if(F_hold_data_idac){//1-выполнено запоминание
				Status_SL.NRange1=range;
				//hold_code_IDAC=(hold_code_IDAC >>6);
				Status_SL.Data1_Lo=(hold_code_IDAC &0xFF);
				hold_code_IDAC=(hold_code_IDAC >>8);
				Status_SL.Data1_Hi=(hold_code_IDAC &0xFF);
			}
			else{
				Status_SL.NRange1=0;
				Status_SL.Data1_Lo=0;
				Status_SL.Data1_Hi=0;				
			}
			IDAC_L1_OFF;
			set_tpic1();
		}			
		else if(canal_test==2){
			if(F_hold_data_idac){//1-выполнено запоминание
				Status_SL.NRange2=range;
				//hold_code_IDAC=(hold_code_IDAC >>6);
				Status_SL.Data2_Lo=(hold_code_IDAC &0xFF);
				hold_code_IDAC=(hold_code_IDAC >>8);
				Status_SL.Data2_Hi=(hold_code_IDAC &0xFF);
			}
			else{
				Status_SL.NRange2=0;
				Status_SL.Data2_Lo=0;
				Status_SL.Data2_Hi=0;				
			}			
			IDAC_L2_OFF;
			set_tpic1();
		}			
		else if(canal_test==3){
			if(F_hold_data_idac){//1-выполнено запоминание			
				Status_SL.NRange3=range;
				//hold_code_IDAC=(hold_code_IDAC >>6);
				Status_SL.Data3_Lo=(hold_code_IDAC &0xFF);
				hold_code_IDAC=(hold_code_IDAC >>8);
				Status_SL.Data3_Hi=(hold_code_IDAC &0xFF);
			}
			else{
				Status_SL.NRange3=0;
				Status_SL.Data3_Lo=0;
				Status_SL.Data3_Hi=0;				
			}			
			IDAC_L3_OFF;
			set_tpic2();
		}			
		else if(canal_test==4){
			if(F_hold_data_idac){//1-выполнено запоминание			
				Status_SL.NRange4=range;
				//hold_code_IDAC=(hold_code_IDAC >>6);
				Status_SL.Data4_Lo=(hold_code_IDAC &0xFF);
				hold_code_IDAC=(hold_code_IDAC >>8);
				Status_SL.Data4_Hi=(hold_code_IDAC &0xFF);
			}
			else{
				Status_SL.NRange4=0;
				Status_SL.Data4_Lo=0;
				Status_SL.Data4_Hi=0;				
			}			
			IDAC_L4_OFF;
			set_tpic2();
		}
				
	

	F_hold_data_idac=0;
}


}
}
