/**************************************
программа контроля звуковых линий IP усилителя
*********************************************/
#include "extern_ipCL.h"

void delay_ipCL(BYTE v){
	while(v){//6 тик
		v--;
	}
}

#define DELAY_TPIC	delay_ipCL(40)//10us

//загрузка tpic1
void set_tpic1(void){

if(tpic1 &128)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &64)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &32)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &16)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &8)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &4)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &2)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

if(tpic1 &1)P_tpic1_DATA=1;
else P_tpic1_DATA=0;	
DELAY_TPIC;
P_tpic1_SRCK=1;	
DELAY_TPIC;
P_tpic1_SRCK=0;

DELAY_TPIC;
P_tpic1_RCK=1;
DELAY_TPIC;
P_tpic1_RCK=0;

}


//загрузка tpic2
void set_tpic2(void){

if(tpic2 &128)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &64)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &32)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &16)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &8)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &4)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &2)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

if(tpic2 &1)P_tpic2_DATA=1;
else P_tpic2_DATA=0;	
DELAY_TPIC;
P_tpic2_SRCK=1;	
DELAY_TPIC;
P_tpic2_SRCK=0;

DELAY_TPIC;
P_tpic2_RCK=1;
DELAY_TPIC;
P_tpic2_RCK=0;

}