#include <Hall/System.h>

volatile char* SYSTEM_TIME = (volatile char*)0x02000300;
volatile unsigned int* SYSTEM_TIME_0 = (volatile unsigned int*)(SYSTEM_TIME + 0); //Least precise
volatile unsigned int* SYSTEM_TIME_1 = (volatile unsigned int*)(SYSTEM_TIME + 4);
volatile unsigned int* SYSTEM_TIME_2 = (volatile unsigned int*)(SYSTEM_TIME + 8);
volatile unsigned int* SYSTEM_TIME_3 = (volatile unsigned int*)(SYSTEM_TIME + 12);
volatile unsigned int* SYSTEM_TIME_4 = (volatile unsigned int*)(SYSTEM_TIME + 16);//Most precise

volatile char* CONTROLLER_START = (volatile char*)0x02000200;
volatile unsigned short* CONTROLLER_0 = (volatile unsigned short*)(CONTROLLER_START + 0);
volatile unsigned short* CONTROLLER_1 = (volatile unsigned short*)(CONTROLLER_START + 2);

void Hall::Init()
{
	
}

bool Hall::ShouldClose()
{
	return false;
}

unsigned long long Hall::GetSystemTime()
{
	unsigned long long result = *SYSTEM_TIME_0;
	result = result << 32;
	result += *SYSTEM_TIME_4;
	return result;
}

unsigned int Hall::GetSystemTimeExcerpt(int precision)
{
	return *(SYSTEM_TIME_0 + precision);
}

Hall::ControllerState Hall::GetController(int id)
{
	return *(CONTROLLER_0 + id);
}

bool Hall::GetA(ControllerState controller)
{
	return controller & (1 << 8);
}

bool Hall::GetB(ControllerState controller)
{
	return controller & (1 << 0);
}

bool Hall::GetX(ControllerState controller)
{
	return controller & (1 << 9);
}

bool Hall::GetY(ControllerState controller)
{
	return controller & (1 << 1);
}

bool Hall::GetStart(ControllerState controller)
{
	return controller & (1 << 3);
}

bool Hall::GetSelect(ControllerState controller)
{
	return controller & (1 << 2);
}

bool Hall::GetUp(ControllerState controller)
{
	return controller & (1 << 4);
}

bool Hall::GetDown(ControllerState controller)
{
	return controller & (1 << 5);
}

bool Hall::GetLeft(ControllerState controller)
{
	return controller & (1 << 6);
}

bool Hall::GetRight(ControllerState controller)
{
	return controller & (1 << 7);
}

bool Hall::GetL(ControllerState controller)
{
	return controller & (1 << 10);
}

bool Hall::GetR(ControllerState controller)
{
	return controller & (1 << 11);
}
