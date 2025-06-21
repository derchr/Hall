#include <Hall/Video.h>

volatile char* GPU_START				  = (char*)0x02000000;
const Color ** GPU_IMAGE_START            = (const Color**)		(GPU_START + 0);
unsigned short* GPU_IMAGE_X               = (unsigned short*)	(GPU_START + 4);
unsigned short* GPU_IMAGE_Y               = (unsigned short*)	(GPU_START + 8);
unsigned short* GPU_IMAGE_WIDTH           = (unsigned short*)	(GPU_START + 12);
short* GPU_IMAGE_SCALE_X                  = (short*)			(GPU_START + 16);
short* GPU_IMAGE_SCALE_Y                  = (short*)			(GPU_START + 20);
bool* GPU_IMAGE_FLIP_X                    = (bool*)				(GPU_START + 24);
bool* GPU_IMAGE_FLIP_Y                    = (bool*)				(GPU_START + 28);
CTType* GPU_COLOR_TABLE_TYPE              = (CTType*)			(GPU_START + 32);
unsigned short* GPU_COLOR_TABLE_OFFSET    = (unsigned short*)	(GPU_START + 36);
unsigned short* GPU_EXCERPT_WIDTH         = (unsigned short*)	(GPU_START + 40);
unsigned short* GPU_EXCERPT_HEIGHT        = (unsigned short*)	(GPU_START + 44);
unsigned short* GPU_SCREEN_X              = (unsigned short*)	(GPU_START + 48);
unsigned short* GPU_SCREEN_Y              = (unsigned short*)	(GPU_START + 52);
Color* GPU_DRAW_COLOR                     = (Color*)			(GPU_START + 56);
Shape* GPU_DRAW_SHAPE                     = (Shape*)			(GPU_START + 60);
ColorSource* GPU_DRAW_COLOR_SOURCE        = (ColorSource*)		(GPU_START + 64);
bool* GPU_COMMAND_DRAW                    = (bool*)				(GPU_START + 68);
bool* GPU_IS_BUSY                         = (bool*)				(GPU_START + 72);
bool* GPU_VSYNC                           = (bool*)				(GPU_START + 76);
bool* GPU_HSYNC                           = (bool*)				(GPU_START + 80);
bool* GPU_COMMAND_SWAP_BUFFERS            = (bool*)				(GPU_START + 84);
bool* GPU_VSYNC_BUFFER_SWAP               = (bool*)				(GPU_START + 88);



void Hall::Draw(const unsigned short* data, unsigned short xOffset, unsigned short yOffset, unsigned short screenX, unsigned short screenY, unsigned short width, unsigned short height, unsigned short dataWidth)
{
	*GPU_IMAGE_START = data;
	*GPU_IMAGE_X_OFFSET = xOffset;
	*GPU_IMAGE_Y_OFFSET = yOffset;
	*GPU_IMAGE_WIDTH = dataWidth;
	*GPU_WIDTH = width;
	*GPU_HEIGHT = height;
	*GPU_SCREEN_X = screenX;
	*GPU_SCREEN_Y = screenY;
	*GPU_COMMAND_DRAW = true;
}


void Hall::Clear(unsigned short color)
{
	*GPU_CLEAR_COLOR = color;
	*GPU_COMMAND_CLEAR = true;
}

void Hall::SetData(const unsigned short* data)
{
	*GPU_IMAGE_START = data;
}

void Hall::SetXOffset(unsigned short xOffset)
{
	*GPU_IMAGE_X_OFFSET = xOffset;
}

void Hall::SetYOffset(unsigned short yOffset)
{
	*GPU_IMAGE_Y_OFFSET = yOffset;
}

void Hall::SetImageWidth(unsigned short imageWidth)
{
	*GPU_IMAGE_WIDTH = imageWidth;
}

void Hall::SetWidth(unsigned short width)
{
	*GPU_WIDTH = width;
}

void Hall::SetHeight(unsigned short height)
{
	*GPU_HEIGHT = height;
}


void Hall::SetScreenX(unsigned short x)
{
	*GPU_SCREEN_X = x;
}


void Hall::SetScreenY(unsigned short y)
{
	*GPU_SCREEN_Y = y;
}

void Hall::SetClearColor(unsigned short color)
{
	*GPU_CLEAR_COLOR = color;
}

void Hall::SetCommandDraw()
{
	*GPU_COMMAND_DRAW = true;
}

void Hall::SetCommandClear()
{
	*GPU_COMMAND_CLEAR = true;
}

void Hall::SetCommandSwapBuffers()
{
	*GPU_COMMAND_SWAP_BUFFERS = true;
}

bool Hall::GetIsGPUBusy()
{
	return *GPU_IS_BUSY;
}

bool Hall::GetVSync()
{
	return *GPU_VSYNC;
}

bool Hall::GetHSync()
{
	return *GPU_HSYNC;
}
