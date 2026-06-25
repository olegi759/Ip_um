/**************************************
программа контроля звуковых линий IP усилителя
*********************************************/
#include "extern_ipCL.h"
//---------------------------------------
//проверка входов с внешн компаратора
//отличается от первой версии
//--------------------------------------
void test_in_comp(void){

//1
//P_in_L1==1 сработал!	
if(P_in_L1==1){
	c_in_comp1++;	
}
//2
if(P_in_L2==1){
	c_in_comp2++;
}
//3
if(P_in_L3==1){
	c_in_comp3++;
}
//4
if(P_in_L4==1){
	c_in_comp4++;
}

c_in_comp_total++;
}
//--------------------------
//запуск тестирования
//------------------------------
void set_test_L1(void){

//if(set_canal_test[0] ==0)return;
if(set_canal_test[0] ==1){range=1;GAIN_L1_MAX;}
else if(set_canal_test[0] ==2){range=2;GAIN_L1_MIN;}
else {Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=0;return;}

canal_test=1;
IDAC_L1_ON;
IDAC_L2_OFF;
IDAC_L3_OFF;
IDAC_L4_OFF;
//вкл???????	
code_IDAC=0;
//IDA0=
IDA0L=0;	
IDA0H=0;

set_tpic1();
set_tpic2();
F_run_test=1;//1-идет тест
F_end_test=0;//
F_rise_step_idac=1;//1- растет
//F_end_step_idac=0;//1-конец диапазона
F_hold_data_idac=0;//1-выполнено запоминание
hold_code_IDAC=0;//код срабатывания
//c_add_code_IDAC=0;//дополнительный подъем после срабатывания
c_in_comp1=0;
c_in_comp_total=0;
F_run_sum=0;//1-выполняем суммирование
sum_code_IDAC=0;//IDAC для интегрирования
c_sum_code=0;
F_load_idac=0;//флаг на загрузку ступеньки
F_first_step=1;
F_in_comp_on=0;
}	
//
void set_test_L2(void){

//if(set_canal_test[1] ==0)return;
if(set_canal_test[1] ==1){range=1;GAIN_L2_MAX;}
else if(set_canal_test[1] ==2){range=2;GAIN_L2_MIN;}
else {Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;return;}

canal_test=2;
IDAC_L1_OFF;
IDAC_L2_ON;
IDAC_L3_OFF;
IDAC_L4_OFF;
//вкл???????	
code_IDAC=0;
//IDA0=
IDA0L=0;	
IDA0H=0;

set_tpic1();
set_tpic2();
F_run_test=1;//1-идет тест
F_end_test=0;//
F_rise_step_idac=1;//1- растет
//F_end_step_idac=0;//1-конец диапазона
F_hold_data_idac=0;//1-выполнено запоминание
hold_code_IDAC=0;//код срабатывания
//c_add_code_IDAC=0;//дополнительный подъем после срабатывания
c_in_comp2=0;
c_in_comp_total=0;
F_run_sum=0;//1-выполняем суммирование
sum_code_IDAC=0;//IDAC для интегрирования
c_sum_code=0;
F_load_idac=0;//флаг на загрузку ступеньки
F_first_step=1;
F_in_comp_on=0;
}
//
void set_test_L3(void){

//if(set_canal_test[2] ==0)return;
if(set_canal_test[2] ==1){range=1;GAIN_L3_MAX;}
else if(set_canal_test[2] ==2){range=2;GAIN_L3_MIN;}
else {Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;return;}

canal_test=3;
IDAC_L1_OFF;
IDAC_L2_OFF;
IDAC_L3_ON;
IDAC_L4_OFF;
//вкл???????	
code_IDAC=0;	
//IDA0=
IDA0L=0;	
IDA0H=0;
set_tpic1();
set_tpic2();
F_run_test=1;//1-идет тест
F_end_test=0;//
F_rise_step_idac=1;//1- растет
//F_end_step_idac=0;//1-конец диапазона
F_hold_data_idac=0;//1-выполнено запоминание
hold_code_IDAC=0;//код срабатывания
//c_add_code_IDAC=0;//дополнительный подъем после срабатывания
c_in_comp3=0;
c_in_comp_total=0;
F_run_sum=0;//1-выполняем суммирование
sum_code_IDAC=0;//IDAC для интегрирования
c_sum_code=0;
F_load_idac=0;//флаг на загрузку ступеньки
F_first_step=1;
F_in_comp_on=0;
}
//
void set_test_L4(void){

//if(set_canal_test[3] ==0)return;
if(set_canal_test[3] ==1){range=1;GAIN_L4_MAX;}
else if(set_canal_test[3] ==2){range=2;GAIN_L4_MIN;}
else {Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;return;}

canal_test=4;
IDAC_L1_OFF;
IDAC_L2_OFF;
IDAC_L3_OFF;
IDAC_L4_ON;
//вкл???????	
code_IDAC=0;	
//IDA0=
IDA0L=0;	
IDA0H=0;
set_tpic1();
set_tpic2();
F_run_test=1;//1-идет тест
F_end_test=0;//
F_rise_step_idac=1;//1- растет
//F_end_step_idac=0;//1-конец диапазона
F_hold_data_idac=0;//1-выполнено запоминание
hold_code_IDAC=0;//код срабатывания
//c_add_code_IDAC=0;//дополнительный подъем после срабатывания
c_in_comp4=0;
c_in_comp_total=0;
F_run_sum=0;//1-выполняем суммирование
sum_code_IDAC=0;//IDAC для интегрирования
c_sum_code=0;
F_load_idac=0;//флаг на загрузку ступеньки
F_first_step=1;
F_in_comp_on=0;
}	
//--------------------------
//выплонение шага тестирования
//------------------------------
void step_test_L(void){	
WORD v_in_comp;

//для сброса неполных
if(F_first_step){
	F_first_step=0;
	//обнуляем
	c_in_comp_total=0;
	c_in_comp1=0;
	c_in_comp2=0;
	c_in_comp3=0;
	c_in_comp4=0;	
	return;
}	
	
//определяем компаратор	
if(canal_test==1){
	v_in_comp=c_in_comp_total>>2;
	if(v_in_comp>0){
		//если компаратор срабатывает то c_in_comp1 и c_in_comp_total накапливаются
		//хз зачем так сложно
		if(c_in_comp1 >(c_in_comp_total-v_in_comp)){
			F_in_comp_on = 1;
		}
		else if(c_in_comp1 <v_in_comp){
			F_in_comp_on=0;
		}
	}
	else{
		c_in_comp_total=0;
		c_in_comp1=0;
		return;
	}
}		
else if(canal_test==2){
	v_in_comp=c_in_comp_total>>2;
	if(v_in_comp>0){
		if(c_in_comp2 >(c_in_comp_total-v_in_comp))F_in_comp_on=1;
		else if(c_in_comp2 <v_in_comp)F_in_comp_on=0;
	}
	else{
		c_in_comp_total=0;
		c_in_comp2=0;
		return;
	}
}	
else if(canal_test==3){
	v_in_comp=c_in_comp_total>>2;
	if(v_in_comp>0){
		if(c_in_comp3 >(c_in_comp_total-v_in_comp))F_in_comp_on=1;
		else if(c_in_comp3 <v_in_comp)F_in_comp_on=0;
	}
	else{
		c_in_comp_total=0;
		c_in_comp3=0;
		return;
	}
}	
else if(canal_test==4){
	v_in_comp=c_in_comp_total>>2;
	if(v_in_comp>0){
		if(c_in_comp4 >(c_in_comp_total-v_in_comp))F_in_comp_on=1;
		else if(c_in_comp4 <v_in_comp)F_in_comp_on=0;
	}
	else{
		c_in_comp_total=0;
		c_in_comp4=0;
		return;
	}	
}
else {
	c_in_comp_total=0;
	c_in_comp1=0;
	c_in_comp2=0;
	c_in_comp3=0;
	c_in_comp4=0;
	F_run_test=0;//1-идет тест
	F_end_test=1;//1-	
	return;
}
//обнуляем
c_in_comp_total=0;
c_in_comp1=0;
c_in_comp2=0;
c_in_comp3=0;
c_in_comp4=0;

//проверка первого срабатывания
if(F_run_sum==0){//не выполняем суммирование
	if(F_rise_step_idac){//1- растет		

		if(F_in_comp_on){//1-сработал

			if(code_IDAC < CODE_DAC_CORESPONDING_ZERO){//???64 //128
				hold_code_IDAC=0;//код срабатывания
				F_hold_data_idac=1;//1-выполнено запоминание
				F_run_test=0;//1-идет тест
				F_end_test=1;//1-
				code_IDAC = 0x280;
			}
			else{
					
				UlogParam("first", footim);
				
				sum_code_IDAC = (code_IDAC>>6);//IDAC для интегрирования
				c_sum_code = 1;
				F_run_sum = 1;//1-выполняем суммирование
				F_rise_step_idac = 0;//вниз
				code_IDAC -= 64;
				//IDA0=code_IDAC;
				Hi_code_IDAC = (code_IDAC >>8);	
				IDA0L = code_IDAC & 0xFF;
				IDA0H = Hi_code_IDAC;
			}
			
		}
		else{
			//первоначально здесь растет ЦАП
			if(code_IDAC < MAX_CODE_DAC_REG){
				code_IDAC +=64;
				//IDA0=code_IDAC;
				Hi_code_IDAC=(code_IDAC >>8);	
				IDA0L=code_IDAC & 0xFF;
				IDA0H=Hi_code_IDAC;				
			}
			else{// F_end_step_idac=1;//1-конец диапазона
				//запоминаем
				hold_code_IDAC=(MAX_CODE_DAC_REG >> 6);
				F_hold_data_idac=1;//1-выполнено запоминание			
				//меняем направление
				F_rise_step_idac=0;
			}				
		}
		
	}
	else{//завершение вниз
		if(code_IDAC >63){
			code_IDAC -=64;
			//IDA0=code_IDAC;
			Hi_code_IDAC=(code_IDAC >>8);	
			IDA0L=code_IDAC & 0xFF;
			IDA0H=Hi_code_IDAC;	
			UlogParam("pila down until zero", footim);
		}	
		else {
			F_run_test=0;//1-идет тест
			F_end_test=1;//
			UlogParam("finish pila down", footim);
		}		
	}
}

//F_run_sum==1;//1-выполняем суммирование	
else{
	if(F_rise_step_idac == 0){//вниз
		if(F_in_comp_on == 0){//отпустил
			sum_code_IDAC += ((code_IDAC>>6) - 1);//????????IDAC для интегрирования
			c_sum_code++;
			if(c_sum_code >= INTEGRATION_COUNT){//64  усе
				
				UlogParam("finish", footim);
				
				//запоминаем
				hold_code_IDAC = sum_code_IDAC / INTEGRATION_COUNT;//64
				F_hold_data_idac = 1;//1-выполнено запоминание
				F_run_sum = 0;//1-выполняем суммирование
				
				code_IDAC = 0x280;
			}
			else{//разворот вверх				
				F_rise_step_idac=1;//
				code_IDAC +=64;
				//IDA0=code_IDAC;
				Hi_code_IDAC=(code_IDAC >>8);	
				IDA0L=code_IDAC & 0xFF;
				IDA0H=Hi_code_IDAC;		
				UlogParam("down; comp = 0; change, go up", footim);
			}
		}
		else{//еще ниже
			if(code_IDAC < CODE_DAC_CORESPONDING_ZERO){//???64 //128				
				hold_code_IDAC = 0;//код срабатывания
				F_hold_data_idac = 1;//1-выполнено запоминание
				F_run_test = 0;//1-идет тест
				F_end_test = 1;//1-
			}
			else{
				code_IDAC -=64;
				//IDA0=code_IDAC;
				Hi_code_IDAC=(code_IDAC >>8);	
				IDA0L=code_IDAC & 0xFF;
				IDA0H=Hi_code_IDAC;
				UlogParam("down; comp = 1; more down", footim);
			}				
		}

	}		
	else{//вверх
		if(F_in_comp_on){//1-сработал
			
			//if(code_IDAC<128){//???64 //128
			//	hold_code_IDAC=0;//код срабатывания
			//	F_hold_data_idac=1;//1-выполнено запоминание
			//	F_run_test=0;//1-идет тест
			//	F_end_test=1;//1-
			//}
			//else{
				sum_code_IDAC+=(code_IDAC>>6);//IDAC для интегрирования
				c_sum_code++;
				//F_run_sum=1;//1-выполняем суммирование
				F_rise_step_idac=0;//вниз
				code_IDAC -=64;
				//IDA0=code_IDAC;
				Hi_code_IDAC=(code_IDAC >>8);	
				IDA0L=code_IDAC & 0xFF;
				IDA0H=Hi_code_IDAC;	
				UlogParam("up; comp = 1; change, go down", footim);			
			//}
			
		}
		else{
			//вот здесь идет увеличение кода ЦАПА 
			if(code_IDAC <MAX_CODE_DAC_REG){//0xFFC0 - максимальное значение кода ЦАПА (если сденуть на 6 единиц врпаво)
				UlogParam("up; comp = 0; more up", footim);
				code_IDAC +=64;
				//IDA0=code_IDAC;
				Hi_code_IDAC=(code_IDAC >> 8);	
				IDA0L=code_IDAC & 0xFF;
				IDA0H=Hi_code_IDAC;				
			}
			else{// F_end_step_idac=1;//1-конец диапазона
				//запоминаем
				hold_code_IDAC=(MAX_CODE_DAC_REG >> 6);
				F_hold_data_idac=1;//1-выполнено запоминание			
				//меняем направление
				F_rise_step_idac=0;
				F_run_sum=0;//на выход ,1-выполняем суммирование
			}				
		}		
	}
}
}



//--------------------------
//инсталяция звуковых линий
//------------------------------
void install_SL(void){

Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=0;
Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;
Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;
Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;		

PCA0CPH2  = 0;//reset wdt
//++канал 1	
if(install_cahal_1){
	//смотрим первый диапазон
	set_canal_test[0]=1;
	set_test_L1();
	while(1){
		test_in_comp();		
		if(F_load_idac){//флаг на загрузку ступеньки
			F_load_idac=0;//флаг на загрузку ступеньки
			step_test_L();
			PCA0CPH2  = 0;//reset wdt
		}		
		//закончили тест одной линии
		if(F_end_test)break;
	}
	
	if(F_hold_data_idac){//1-выполнено запоминание
		install_code_IDAC_1=hold_code_IDAC;
		
		//смотрим 2 диапазон
		set_canal_test[0]=2;
		set_test_L1();
		while(1){
			test_in_comp();		
			if(F_load_idac){//флаг на загрузку ступеньки
				F_load_idac=0;//флаг на загрузку ступеньки
				step_test_L();
				PCA0CPH2  = 0;//reset wdt
			}		
			//закончили тест одной линии
			if(F_end_test)break;
		}		
		
		if(F_hold_data_idac){//1-выполнено запоминание
			install_code_IDAC_2=hold_code_IDAC;		
			//выбираем значение
			//install_code_IDAC_1=(install_code_IDAC_1 >>6);
			//install_code_IDAC_2=(install_code_IDAC_2 >>6);
			v_test=optimal_value_selection(1);
			if(v_test==1){
				Status_SL.NRange1=1;
				Status_SL.Data1_Lo=(install_code_IDAC_1 &0xFF);
				install_code_IDAC_1=(install_code_IDAC_1 >>8);
				Status_SL.Data1_Hi=(install_code_IDAC_1 &0xFF);
			}
			else if(v_test==2){
				Status_SL.NRange1=2;
				Status_SL.Data1_Lo=(install_code_IDAC_2 &0xFF);
				install_code_IDAC_2=(install_code_IDAC_2 >>8);
				Status_SL.Data1_Hi=(install_code_IDAC_2 &0xFF);
			}						
		}
	}
	
}
//++канал 2	
PCA0CPH2  = 0;//reset wdt
if(install_cahal_2){
	//смотрим первый диапазон
	set_canal_test[1]=1;
	set_test_L2();
	while(1){
		test_in_comp();		
		if(F_load_idac){//флаг на загрузку ступеньки
			F_load_idac=0;//флаг на загрузку ступеньки
			step_test_L();
			PCA0CPH2  = 0;//reset wdt
		}		
		//закончили тест одной линии
		if(F_end_test)break;
	}
	
	if(F_hold_data_idac){//1-выполнено запоминание
		install_code_IDAC_1=hold_code_IDAC;
		
		//смотрим 2 диапазон
		set_canal_test[1]=2;
		set_test_L2();
		while(1){
			test_in_comp();		
			if(F_load_idac){//флаг на загрузку ступеньки
				F_load_idac=0;//флаг на загрузку ступеньки
				step_test_L();
				PCA0CPH2  = 0;//reset wdt
			}		
			//закончили тест одной линии
			if(F_end_test)break;
		}		
		
		if(F_hold_data_idac){//1-выполнено запоминание
			install_code_IDAC_2=hold_code_IDAC;		
			//выбираем значение
			//install_code_IDAC_1=(install_code_IDAC_1 >>6);
			//install_code_IDAC_2=(install_code_IDAC_2 >>6);
			v_test=optimal_value_selection(2);
			if(v_test==1){
				Status_SL.NRange2=1;
				Status_SL.Data2_Lo=(install_code_IDAC_1 &0xFF);
				install_code_IDAC_1=(install_code_IDAC_1 >>8);
				Status_SL.Data2_Hi=(install_code_IDAC_1 &0xFF);
			}
			else if(v_test==2){
				Status_SL.NRange2=2;
				Status_SL.Data2_Lo=(install_code_IDAC_2 &0xFF);
				install_code_IDAC_2=(install_code_IDAC_2 >>8);
				Status_SL.Data2_Hi=(install_code_IDAC_2 &0xFF);
			}			
			
		}
	}
	
}
//++канал 3	
PCA0CPH2  = 0;//reset wdt
if(install_cahal_3){
	//смотрим первый диапазон
	set_canal_test[2]=1;
	set_test_L3();
	while(1){
		test_in_comp();		
		if(F_load_idac){//флаг на загрузку ступеньки
			F_load_idac=0;//флаг на загрузку ступеньки
			step_test_L();
			PCA0CPH2  = 0;//reset wdt
		}		
		//закончили тест одной линии
		if(F_end_test)break;
	}
	
	if(F_hold_data_idac){//1-выполнено запоминание
		install_code_IDAC_1=hold_code_IDAC;
		
		//смотрим 2 диапазон
		set_canal_test[2]=2;
		set_test_L3();
		while(1){
			test_in_comp();		
			if(F_load_idac){//флаг на загрузку ступеньки
				F_load_idac=0;//флаг на загрузку ступеньки
				step_test_L();
				PCA0CPH2  = 0;//reset wdt
			}		
			//закончили тест одной линии
			if(F_end_test)break;
		}		
		
		if(F_hold_data_idac){//1-выполнено запоминание
			install_code_IDAC_2=hold_code_IDAC;		
			//выбираем значение
			//install_code_IDAC_1=(install_code_IDAC_1 >>6);
			//install_code_IDAC_2=(install_code_IDAC_2 >>6);
			v_test=optimal_value_selection(3);
			if(v_test==1){
				Status_SL.NRange3=1;
				Status_SL.Data3_Lo=(install_code_IDAC_1 &0xFF);
				install_code_IDAC_1=(install_code_IDAC_1 >>8);
				Status_SL.Data3_Hi=(install_code_IDAC_1 &0xFF);
			}
			else if(v_test==2){
				Status_SL.NRange3=2;
				Status_SL.Data3_Lo=(install_code_IDAC_2 &0xFF);
				install_code_IDAC_2=(install_code_IDAC_2 >>8);
				Status_SL.Data3_Hi=(install_code_IDAC_2 &0xFF);
			}			
			
		}
	}
	
}
//++канал 4	
PCA0CPH2  = 0;//reset wdt
if(install_cahal_4){
	//смотрим первый диапазон
	set_canal_test[3]=1;
	set_test_L4();
	while(1){
		test_in_comp();		
		if(F_load_idac){//флаг на загрузку ступеньки
			F_load_idac=0;//флаг на загрузку ступеньки
			step_test_L();
			PCA0CPH2  = 0;//reset wdt
		}		
		//закончили тест одной линии
		if(F_end_test)break;
	}
	
	if(F_hold_data_idac){//1-выполнено запоминание
		install_code_IDAC_1=hold_code_IDAC;
		
		//смотрим 2 диапазон
		set_canal_test[3]=2;
		set_test_L4();
		while(1){
			test_in_comp();		
			if(F_load_idac){//флаг на загрузку ступеньки
				F_load_idac=0;//флаг на загрузку ступеньки
				step_test_L();
				PCA0CPH2  = 0;//reset wdt
			}		
			//закончили тест одной линии
			if(F_end_test)break;
		}		
		
		if(F_hold_data_idac){//1-выполнено запоминание
			install_code_IDAC_2=hold_code_IDAC;		
			//выбираем значение
			//install_code_IDAC_1=(install_code_IDAC_1 >>6);
			//install_code_IDAC_2=(install_code_IDAC_2 >>6);
			v_test=optimal_value_selection(4);
			if(v_test==1){
				Status_SL.NRange4=1;
				Status_SL.Data4_Lo=(install_code_IDAC_1 &0xFF);
				install_code_IDAC_1=(install_code_IDAC_1 >>8);
				Status_SL.Data4_Hi=(install_code_IDAC_1 &0xFF);
			}
			else if(v_test==2){
				Status_SL.NRange4=2;
				Status_SL.Data4_Lo=(install_code_IDAC_2 &0xFF);
				install_code_IDAC_2=(install_code_IDAC_2 >>8);
				Status_SL.Data4_Hi=(install_code_IDAC_2 &0xFF);
			}			
			
		}
	}
	
}
IDAC_L1_OFF;
IDAC_L2_OFF;
IDAC_L3_OFF;
IDAC_L4_OFF;
set_tpic1();
set_tpic2();

set_canal_test[0]=set_canal_test[1]=set_canal_test[2]=set_canal_test[3]=0;	
c_seconds=0;
F_hold_data_idac=0;
F_end_test=0;
F_start_test_L1=F_start_test_L2=F_start_test_L3=F_start_test_L4=0;

}	


//--------------------------
//выбор оптимального значения
//------------------------------
BYTE optimal_value_selection(BYTE chNumber){

if(install_code_IDAC_1 > 512) test1_install = install_code_IDAC_1 - 512;
else test1_install = 512 - install_code_IDAC_1;
	
if(install_code_IDAC_2 > 512)test2_install=install_code_IDAC_2 - 512;
else test2_install = 512 - install_code_IDAC_2;	
	
if(test1_install > test2_install) {
	((WORD*)&DacStartValueLines)[chNumber - 1] = install_code_IDAC_2 - 20;	
	return 2;
}
else {
	((WORD*)&DacStartValueLines)[chNumber - 1] = install_code_IDAC_1 - 20;
	return 1;		
}	
}

//--------------------------
//выбор следующего канала участвующего в тесте 
//------------------------------
BYTE i = 0;
void set_f_start_test_Lx(){	
	for(i = 0; i < 4; ++i){
		if(set_canal_test[i] != 0){			
			F_start_test = (1 << i);
			return;
		}
	}
}