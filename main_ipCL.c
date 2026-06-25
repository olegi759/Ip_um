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
F_delaed_response = 0;	

	
//++	
while(1){
	
//++

PCA0CPH2  = 0;//reset wdt
//	
if(F_run_com_PC){
	F_run_com_PC=0;
	work_PC();	
}

delayed_response_PC();


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
		code_IDAC = DacStartValueLines.LineDac1 << 6;
		UlogParam("start test at line1 ", footim);
	}
	//запуск тестирования
	else if(F_start_test_L2){
		F_start_test_L2=0;
		set_test_L2();
		code_IDAC = DacStartValueLines.LineDac2 << 6;
		UlogParam("start test at line2 ", footim);
	}
	//запуск тестирования
	else if(F_start_test_L3){
		F_start_test_L3=0;
		set_test_L3();
		code_IDAC = DacStartValueLines.LineDac3 << 6;
		UlogParam("start test at line3 ", footim);
	}
	//запуск тестирования
	else if(F_start_test_L4){
		F_start_test_L4=0;
		set_test_L4();
		code_IDAC = DacStartValueLines.LineDac4 << 6;
		UlogParam("start test at line4", footim);
	}	
	
}

//закончили тест одной линии
if(F_end_test){
	UlogParam("in end test", footim);
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
			set_canal_test[0] = 0;
			//TMR2CN = 0;
			//set_canal_test[0] = 0;	
			//тест линии конец
			UlogParam("end", footim);
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
			set_canal_test[1] = 0;
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
			set_canal_test[2] = 0;
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
			set_canal_test[3] = 0;
			UlogParam("end", footim);
		}
				
	set_f_start_test_Lx();

	F_hold_data_idac=0;
}


}
}
