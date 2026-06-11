/**************************
программа контроля звуковых линий IP усилителя
***************************/
//#include "C8051F330.h"
#include "extern_ipCL.h"


/*********************************************
обработка прерывания Т2
// Программа обработки прерывания таймера 3 
// 16 bit auto reload
// Timer clock = SYSCLK = sis/12
// Прерывание 10ms
*****************************************************/ 
void INT_Timer_2( void ) interrupt 5
{
	

	TF2H=0;
	
	
	
	if(c_10ms==0){
		c_10ms=99;
		if(c_seconds>=79){//49
			c_seconds=0;			
		}
		else c_seconds++;
		
		if(c_seconds==1)F_start_test_L1=1;//2
		else if(c_seconds==21)F_start_test_L2=1;//14		
		else if(c_seconds==41)F_start_test_L3=1;//26		
		else if(c_seconds==61)F_start_test_L4=1;//38		
	}
	else c_10ms--;
}

/*********************************************
обработка прерывания Т3
// Программа обработки прерывания таймера 3 
// 16 bit auto reload
// Timer clock = SYSCLK = 
// Прерывание 500us dac
//для смирнова 4ms(2ms прерыв *2 в прерывании)
//v6 8ms (2прер *4)
*****************************************************/ 
void INT_Timer_3( void ) interrupt 14
{

	TMR3CN &=0x7F;//TF3H=0;
	footim++;
	div_f_start_dac++;
	if(div_f_start_dac >3){
		div_f_start_dac=0;
		F_load_idac=1;
		
	}

	
/*
	if(F_div_f_start_dac==0)F_div_f_start_dac=1;
	else{
		F_div_f_start_dac=0;
		F_load_idac=1;
	}		
*/		
			
}