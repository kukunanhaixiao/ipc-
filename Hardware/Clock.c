#include "clock.h"
#include "stdlib.h"

pClock cthis;

void Clock_Show(void);
void Clock_Turn(void);

pClock Clock_Create(void)
{
	pClock clock_c = (pClock)malloc(sizeof(pClock));
	
	if(clock_c == NULL)
	{
		return NULL;
	}
	
	clock_c->Second = 0;
	clock_c->Minute = 0;
	clock_c->Hour = 0;
	
	clock_c->pClock_Show = Clock_Show;
	clock_c->pClock_Turn = Clock_Turn;
	
	cthis = clock_c;
	return clock_c;
}

pClock Clock_CreateWithArgs(uint8_t Hour, uint8_t Minute, uint8_t Second)
{
	pClock clock_c = Clock_Create();
	//判断是否有效
	if(clock_c == NULL)
	{
		return NULL;
	}
	Second_ = Second;
	clock_c->Second = Second;
	clock_c->Minute = Minute;
	clock_c->Hour = Hour;
	
	return clock_c;
} 
//在OLED上显示出时  分  秒
void Clock_Show(void)
{
	OLED_ShowNum(1, 1, cthis->Hour, 2);
	OLED_ShowString(1, 3, ":");
	OLED_ShowNum(1, 4, cthis->Minute, 2);
	OLED_ShowString(1, 6, ":");
	OLED_ShowNum(1, 7, cthis->Second, 2);
}
//时间跳动
void Clock_Turn(void)
{
	cthis->Second = Second_;
	if(cthis->Second >= 60)
	{
		cthis->Minute += cthis->Second / 60;
		cthis->Second %= 60;
		Second_ %= 60;
		
		if(cthis->Minute >= 60)
		{
			cthis->Hour += cthis->Minute / 60;
			cthis->Minute %= 60;
			
			if(cthis->Hour == 24)
			{
				cthis->Hour %= 24;
			}
		}
	}
}

