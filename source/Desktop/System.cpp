#include <Hall/Hall.h>
#include "hans_logo.h"
extern "C" 
{
	#include "raylib.h"
}
#include <iostream>

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

	::SetTargetFPS(30);
	::InitAudioDevice();

	::Image image;
	image.data = hans_logo;
	image.width = HANS_LOGO_WIDTH;
	image.height = HANS_LOGO_HEIGHT;
	image.mipmaps = 1;
	image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	::SetWindowIcon(image);

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
	std::cout << "SYSTEM TIME EXCERPT IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;
	return 0;
}

Hall::ControllerState Hall::GetController(int id)
{
	bool left, right, up, down;
	bool start, select;
	bool a, b, x, y;
	bool l, r;

	if(id == 0)
	{
		left = ::IsKeyDown(CONT0_LEFT);
		right = ::IsKeyDown(CONT0_RIGHT);
		up = ::IsKeyDown(CONT0_UP);
		down = ::IsKeyDown(CONT0_DOWN);
		start = ::IsKeyDown(CONT0_START);
		select = ::IsKeyDown(CONT0_SELECT);
		a = ::IsKeyDown(CONT0_A);
		b = ::IsKeyDown(CONT0_B);
		x = ::IsKeyDown(CONT0_X);
		y = ::IsKeyDown(CONT0_Y);
		l = ::IsKeyDown(CONT0_L);
		r = ::IsKeyDown(CONT0_R);
	}
	if(id == 1)
	{
		left = ::IsKeyDown(CONT1_LEFT);
		right = ::IsKeyDown(CONT1_RIGHT);
		up = ::IsKeyDown(CONT1_UP);
		down = ::IsKeyDown(CONT1_DOWN);
		start = ::IsKeyDown(CONT1_START);
		select = ::IsKeyDown(CONT1_SELECT);
		a = ::IsKeyDown(CONT1_A);
		b = ::IsKeyDown(CONT1_B);
		x = ::IsKeyDown(CONT1_X);
		y = ::IsKeyDown(CONT1_Y);
		l = ::IsKeyDown(CONT1_L);
		r = ::IsKeyDown(CONT1_R);
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

	return result;
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
