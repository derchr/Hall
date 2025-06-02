#include <System.h>

volatile void* SYSTEM_TIME = (volatile void*)0x02000300;
volatile unsigned int* SYSTEM_TIME_0 = (volatile unsigned int*)SYSTEM_TIME + 0; //Least precise
volatile unsigned int* SYSTEM_TIME_1 = (volatile unsigned int*)SYSTEM_TIME + 4;
volatile unsigned int* SYSTEM_TIME_2 = (volatile unsigned int*)SYSTEM_TIME + 8;
volatile unsigned int* SYSTEM_TIME_3 = (volatile unsigned int*)SYSTEM_TIME + 12;
volatile unsigned int* SYSTEM_TIME_4 = (volatile unsigned int*)SYSTEM_TIME + 16;//Most precise

volatile void* CONTROLLER_START = (volatile void*)0x02000200;
volatile unsigned short* CONTROLLER_0 = (volatile unsigned short*)CONTROLLER_START + 0;
volatile unsigned short* CONTROLLER_1 = (volatile unsigned short*)CONTROLLER_START + 2;


unsigned int Hall::GetSystemTime(int precision)
{
	return *(SYSTEM_TIME_0 + precision);
}

unsigned short Hall::GetController(int id)
{
	return *(CONTROLLER_0 + id);
}
