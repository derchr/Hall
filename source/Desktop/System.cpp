#include <Hall/Hall.h>
extern "C" 
{
	#include "raylib.h"
}
#include <exception>

//Change these, if you want to change the desktop mapping of the controllers
const ::KeyboardKey CONT0_UP 		= KEY_W;
const ::KeyboardKey CONT0_DOWN 		= KEY_S;
const ::KeyboardKey CONT0_LEFT 		= KEY_A;
const ::KeyboardKey CONT0_RIGHT 	= KEY_D;
const ::KeyboardKey CONT0_START 	= KEY_ENTER;
const ::KeyboardKey CONT0_SELECT 	= KEY_BACKSPACE;
const ::KeyboardKey CONT0_A 		= KEY_L;
const ::KeyboardKey CONT0_B 		= KEY_K;
const ::KeyboardKey CONT0_X 		= KEY_I;
const ::KeyboardKey CONT0_Y 		= KEY_J;
const ::KeyboardKey CONT0_L 		= KEY_U;
const ::KeyboardKey CONT0_R 		= KEY_O;

const ::KeyboardKey CONT1_UP 		= KEY_NULL;
const ::KeyboardKey CONT1_DOWN 		= KEY_NULL;
const ::KeyboardKey CONT1_LEFT 		= KEY_NULL;
const ::KeyboardKey CONT1_RIGHT 	= KEY_NULL;
const ::KeyboardKey CONT1_START 	= KEY_NULL;
const ::KeyboardKey CONT1_SELECT 	= KEY_NULL;
const ::KeyboardKey CONT1_A 		= KEY_NULL;
const ::KeyboardKey CONT1_B 		= KEY_NULL;
const ::KeyboardKey CONT1_X 		= KEY_NULL;
const ::KeyboardKey CONT1_Y 		= KEY_NULL;
const ::KeyboardKey CONT1_L 		= KEY_NULL;
const ::KeyboardKey CONT1_R 		= KEY_NULL;


extern ::RenderTexture2D screen;
extern ::Camera2D camera;

void Hall::Init()
{
	::SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	::InitWindow(800, 480, "wueHans Desktop Simulatior 2025");
	screen = ::LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera.offset = { 0, 0 };
	camera.rotation = 0.0f;
	camera.target = { 0, 0 };
	camera.zoom = 1.0f;

	::SetTargetFPS(60);

	::BeginTextureMode(screen);
	::BeginMode2D(camera);
}

bool Hall::ShouldClose()
{
	return WindowShouldClose();
}

unsigned long long Hall::GetSystemTime()
{
	double inSeconds = ::GetTime();
	unsigned long long inTicks = inSeconds * (unsigned long long)SYSTEM_CLK_FREQUENCY;
	return inTicks;
}

unsigned int Hall::GetSystemTimeExcerpt(int precision)
{
	throw std::exception("SYSTEM TIME EXCERPT IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");
	return 0;
}

unsigned short Hall::GetController(int id)
{
	bool left, right, up, down;
	bool start, select;
	bool a, b, x, y;
	bool l, r;

	if(id == 0)
	{
		left = ::IsKeyPressed(CONT0_LEFT);
		right = ::IsKeyPressed(CONT0_RIGHT);
		up = ::IsKeyPressed(CONT0_UP);
		down = ::IsKeyPressed(CONT0_DOWN);
		start = ::IsKeyPressed(CONT0_START);
		select = ::IsKeyPressed(CONT0_SELECT);
		a = ::IsKeyPressed(CONT0_A);
		b = ::IsKeyPressed(CONT0_B);
		x = ::IsKeyPressed(CONT0_X);
		y = ::IsKeyPressed(CONT0_Y);
		l = ::IsKeyPressed(CONT0_L);
		r = ::IsKeyPressed(CONT0_R);
	}
	if(id == 1)
	{
		left = ::IsKeyPressed(CONT1_LEFT);
		right = ::IsKeyPressed(CONT1_RIGHT);
		up = ::IsKeyPressed(CONT1_UP);
		down = ::IsKeyPressed(CONT1_DOWN);
		start = ::IsKeyPressed(CONT1_START);
		select = ::IsKeyPressed(CONT1_SELECT);
		a = ::IsKeyPressed(CONT1_A);
		b = ::IsKeyPressed(CONT1_B);
		x = ::IsKeyPressed(CONT1_X);
		y = ::IsKeyPressed(CONT1_Y);
		l = ::IsKeyPressed(CONT1_L);
		r = ::IsKeyPressed(CONT1_R);
	}
	unsigned short result = 0;
	result |= b 		<< 0;
	result |= y 		<< 1;
	result |= select 	<< 2;
	result |= start 	<< 3;
	result |= up 		<< 4;
	result |= down 		<< 5;
	result |= left 		<< 6;
	result |= right 	<< 7;
	result |= a 		<< 8;
	result |= x 		<< 9;
	result |= l 		<< 10;
	result |= r 		<< 11;
}

bool Hall::GetA(unsigned short controller)
{
	return controller & (1 << 8);
}

bool Hall::GetB(unsigned short controller)
{
	return controller & (1 << 0);
}

bool Hall::GetX(unsigned short controller)
{
	return controller & (1 << 9);
}

bool Hall::GetY(unsigned short controller)
{
	return controller & (1 << 1);
}

bool Hall::GetStart(unsigned short controller)
{
	return controller & (1 << 3);
}

bool Hall::GetSelect(unsigned short controller)
{
	return controller & (1 << 2);
}

bool Hall::GetUp(unsigned short controller)
{
	return controller & (1 << 4);
}

bool Hall::GetDown(unsigned short controller)
{
	return controller & (1 << 5);
}

bool Hall::GetLeft(unsigned short controller)
{
	return controller & (1 << 6);
}

bool Hall::GetRight(unsigned short controller)
{
	return controller & (1 << 7);
}

bool Hall::GetL(unsigned short controller)
{
	return controller & (1 << 10);
}

bool Hall::GetR(unsigned short controller)
{
	return controller & (1 << 11);
}
