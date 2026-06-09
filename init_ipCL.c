/**************************
программа контроля звуковых линий IP усилителя
***************************/
//#include "C8051F330.h"
#include "extern_ipCL.h"

// Peripheral specific initialization functions,
// Called from the Init_Device() function

//сист 24,5М
void Oscillator_Init()
{
    OSCICN    = 0x83;
}



void Port_IO_Init()
{
    // P0.0  -  Unassigned,  Open-Drain, Digital
    // P0.1  -  Skipped,     Open-Drain, Analog
    // P0.2  -  Skipped,     Open-Drain, Digital
    // P0.3  -  Skipped,     Open-Drain, Digital
    // P0.4  -  TX0 (UART0), Push-Pull,  Digital
    // P0.5  -  RX0 (UART0), Open-Drain, Digital
    // P0.6  -  Skipped,     Open-Drain, Digital
    // P0.7  -  Skipped,     Open-Drain, Digital

    // P1.0  -  Skipped,     Open-Drain, Digital
    // P1.1  -  Skipped,     Open-Drain, Digital
    // P1.2  -  Skipped,     Open-Drain, Digital
    // P1.3  -  Skipped,     Open-Drain, Digital
    // P1.4  -  Skipped,     Open-Drain, Digital
    // P1.5  -  Skipped,     Open-Drain, Digital
    // P1.6  -  Skipped,     Open-Drain, Digital
    // P1.7  -  Skipped,     Open-Drain, Digital

    P0MDIN    = 0xFD;
    P0MDOUT   = 0x10;
    P0SKIP    = 0xCE;
    P1SKIP    = 0xFF;
    XBR0      = 0x01;
    XBR1      = 0x40;
	P_tpic1_G=1;
	P_tpic2_G=1;
	P_tpic1_DATA=0;
	P_tpic2_DATA=0;
	P_tpic1_SRCK=0;
	P_tpic2_SRCK=0;
	P_tpic1_RCK=0;
	P_tpic2_RCK=0;
}

//T1-8b,sis,uart 115200
//T2-16b,sis/12, 10ms
//T3 16b,sis,500us dac//для смирнова 4ms(2ms прерыв *2 в прерывании)
void Timer_Init()
{
    //T1
	//TCON      = 0x40;
	TF1     = 0;                   // Timer1 overflow flag
	TR1     = 1;                   // Timer1 on/off control
	TF0     = 0;                   // Timer0 overflow flag
	TR0     = 0;                   // Timer0 on/off control
	IE1     = 0;                   // Ext interrupt 1 edge flag
	IT1     = 0;                   // Ext interrupt 1 type
	IE0     = 0;                   // Ext interrupt 0 edge flag
	IT0     = 0;                   // Ext interrupt 0 type			
	
    TMOD      = 0x20;//T1-8b,
    CKCON     = 0x48;//T3-sis,T0T1-sis/12
    TH1       = 0x96;
    TMR2CN    = 0x04;//T2-sis/12,16b,on
    TMR2RLL   = 0x3F;
    TMR2RLH   = 0xB0;
    TMR2L     = 0x3F;
    TMR2H     = 0xB0;
    TMR3CN    = 0x04;//T3 16b,on
    TMR3RLL   = 0x97;//0x25;//для смирнова 2ms
    TMR3RLH   = 0x40;//0xD0;//для смирнова
    TMR3L     = 0x97;//0x25;//для смирнова
    TMR3H     = 0x40;//0xD0;//для смирнова
	//брос флага
	//TMR3CN &=0x7F;
}

//8b,1-sb
void UART_Init()
{
    SCON0     = 0x10;
}
//IDAC- on,1mA, start write IDA0H(первым IDA0L)
//ВЫРАВНИВАНИЕ ВПРАВО!!!!!!!
void DAC_Init()
{
    IDA0CN    = 0xF1;
	//IDA0=0;
	IDA0L=0;	
	IDA0H=0;
}

//собака 30ms
void PCA_Init()
{
    PCA0MD    &= ~0x40;
    PCA0MD    = 0x00;
    PCA0CPL2  = 0xEE;
    PCA0MD    |= 0x40;
    PCA0CPH2  = 0;//обязательно, первая запись!!!!!!
}

//монитор
void Reset_Sources_Init()
{
    int i = 0;
    VDM0CN    = 0x80;
    for (i = 0; i < 350; i++);  // Wait 100us for initialization
    RSTSRC    = 0x02;
}


//
void Interrupts_Init()
{
    //IE        = 0xB0;
	EA=0;                  // Global Interrupt Enable
	ESPI0=0;               // SPI0 Interrupt Enable
	ET2=1;                 // Timer 2 Interrupt Enable
	ES0=1;                 // UART0 Interrupt Enable
	ET1=0;                 // Timer 1 Interrupt Enable
	EX1=0;                 // External Interrupt 1 Enable
	ET0=0;                 // Timer 0 Interrupt Enable
	EX0=0;                 // External Interrupt 0 Enable
			
	EIE1      = 0x80;//Timer 3 Interrupt Enable
}

//
void init_v(void){

set_install=0;	
set_canal_test[0]=set_canal_test[1]=set_canal_test[2]=set_canal_test[3]=0;	
set_rele[0]=set_rele[1]=set_rele[2]=set_rele[3]=0;	
code_IDAC=0;
hold_code_IDAC=0;
F_load_idac=0;
F_run_test=0;//1-идет тест
F_end_test=0;//1-
F_rise_step_idac=0;//1- растет
//F_end_step_idac=0;//1-конец диапазона
F_hold_data_idac=0;//1-выполнено запоминание
F_run_sum=0;//1-выполняем суммирование
range=0;
canal_test=0;
//c_add_code_IDAC=0;
F_in_comp_on=0;//1-сработал
//F_in_comp2_on=0;//1-сработал
//F_in_comp3_on=0;//1-сработал
//F_in_comp4_on=0;//1-сработал
c_in_comp1=0;
c_in_comp2=0;
c_in_comp3=0;
c_in_comp4=0;
c_10ms=0;//по 10мс до 1 сек
c_seconds=0;//
F_start_test_L1=0;
F_start_test_L2=0;
F_start_test_L3=0;
F_start_test_L4=0;
st_Rx_PC=0;
st_Tx_PC=0;
F_run_com_PC=0;
Status_SL.NRange1=Status_SL.Data1_Hi=Status_SL.Data1_Lo=0;
Status_SL.NRange2=Status_SL.Data2_Hi=Status_SL.Data2_Lo=0;
Status_SL.NRange3=Status_SL.Data3_Hi=Status_SL.Data3_Lo=0;
Status_SL.NRange4=Status_SL.Data4_Hi=Status_SL.Data4_Lo=0;
F_div_f_start_dac=0;//для получения 4ms в прерывании
div_f_start_dac=0;

}

//
void init_ipCL(void)
{
	Oscillator_Init();
	PCA_Init();
	Timer_Init();
	UART_Init();
	Port_IO_Init();
	DAC_Init();//??????
	Reset_Sources_Init();
	init_v();
	Interrupts_Init();
}





