#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT

volatile uint32_t delay_dec = 0;// объ€вление переменной delay_dec

void SysTickInit(void)
{
	SysTick->LOAD |= (8000)-1;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Pos;
	SysTick->CTRL |= SysTick_CTRL_COUNTFLAG_Pos;
	SysTick->CTRL |= ~SysTick_CTRL_ENABLE_Pos;	
}


void SysTick_Handler(void)
{
	if (delay_dec !=0) 
		delay_dec--;
}

void delay_ms(uint32_t delay_ms)
{
	delay_dec = delay_ms;//присвоить delay_dec значение delay_ms
	
	while (delay_dec) {}; // выполн€ть функцию пока delay_dec не станет равным 0
}

void Init_PortA(void)
{
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	
	PORT_InitTypeDef PORTA_InitStruct;
	
	PORTA_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORTA_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORTA_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTA_InitStruct.PORT_OE = PORT_OE_OUT;
	PORTA_InitStruct.PORT_Pin = PORT_Pin_1 | PORT_Pin_3 | PORT_Pin_5;
	PORTA_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORTA_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	
	PORT_Init(MDR_PORTA, &PORTA_InitStruct);
}

int main(void)
{
	SysTickInit();
	Init_PortA();
	
	while(1)
	{
		PORT_SetBits(MDR_PORTA, PORT_Pin_1);
		delay_ms(500);
		PORT_ResetBits(MDR_PORTA, PORT_Pin_1);
		delay_ms(500);
	}
}
