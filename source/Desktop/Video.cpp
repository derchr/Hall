#include <Hall/Video.h>
#include <map>
#include <cstdlib>
extern "C" 
{
	#include "raylib.h"
}
#include <exception>

static const int ctSizes[6] = {0, 1, 2, 4, 8, 16};
static const unsigned short ctMasks[6] = {0, 0b1, 0b11, 0b1111, 0b11111111, 0b1111111111111111};


std::map<Hall::Color*, ::Texture2D> textures;
Hall::Color Hall::colorTable[2048];

Hall::Color* 		IMAGE_START;
short 				IMAGE_X;
short 				IMAGE_Y;
unsigned short 		IMAGE_WIDTH;
short 				IMAGE_SCALE_X;
short 				IMAGE_SCALE_Y;
bool 				IMAGE_FLIP_X;
bool 				IMAGE_FLIP_Y;
Hall::CTType 		COLOR_TABLE_TYPE;
Hall::Color*	 	COLOR_TABLE_OFFSET;
short 				EXCERPT_WIDTH;
short 				EXCERPT_HEIGHT;
short 				SCREEN_X;
short 				SCREEN_Y;
Hall::Color 		DRAW_COLOR;
Hall::Shape 		DRAW_SHAPE;
Hall::ColorSource 	DRAW_COLOR_SOURCE;
bool 				COMMAND_DRAW;
bool 				IS_BUSY;
bool 				VSYNC;
bool 				HSYNC;
bool 				COMMAND_SWAP_BUFFERS;
bool 				VSYNC_BUFFER_SWAP;

::RenderTexture2D screen;
::Camera2D camera;

static void AddImage(Hall::Color* data, short imageWidth)
{
	if(textures.count(data)) return;
	::Image image;
	image.data = data;
	image.width = imageWidth;
	image.height = 480; //Just needs to be higher than any actual height. I hope this does not breaks something
	image.mipmaps = 1;
	image.format = PIXELFORMAT_UNCOMPRESSED_R5G5B5A1;
	Texture2D texture = ::LoadTextureFromImage(image);

	textures[data] = texture;
}

void Hall::SetImage(const Color* image, unsigned short imageWidth)
{
	AddImage((Color*)image, imageWidth);
	IMAGE_START = (Color*)image;
	IMAGE_WIDTH = imageWidth;
}

void Hall::SetImage(const IndexContainer* image, unsigned short imageWidth)
{
	//This is ugly code, but it represents the hardware
	AddImage((Color*)image, imageWidth);
	IMAGE_START = (Color*)image;
	IMAGE_WIDTH = imageWidth;
}

void Hall::SetExcerpt(short x, short y)
{
	IMAGE_X = x;
	IMAGE_Y = y;
}

void Hall::SetExcerpt(short x, short y, short width, short height)
{
	IMAGE_X = x;
	IMAGE_Y = y;
	EXCERPT_WIDTH = width;
	EXCERPT_HEIGHT = height;
}

void Hall::SetScale(short x, short y)
{
	IMAGE_SCALE_X = x;
	IMAGE_SCALE_Y = y;
}

void Hall::SetFlip(bool x, bool y)
{
	IMAGE_FLIP_X = x;
	IMAGE_FLIP_Y = y;
}

void Hall::SetColorTable(CTType type)
{
	COLOR_TABLE_TYPE = type;
}

void Hall::SetColorTable(CTType type, const Color* colorTable)
{
	throw std::exception("COLOR TABLES ARE NOT SUPPORTED IN DESKTOP VERSION OF HALL");
	COLOR_TABLE_TYPE = type;
	COLOR_TABLE_OFFSET = (Color*)colorTable;
}

void Hall::SetScreenPosition(short x, short y)
{
	SCREEN_X = x;
	SCREEN_Y = y;
}

void Hall::SetColorSource(ColorSource ColorSource)
{
	DRAW_COLOR_SOURCE = ColorSource;
}

void Hall::SetColor(Color color)
{
	DRAW_COLOR = color;
}

void Hall::SetShape(Shape shape)
{
	DRAW_SHAPE = shape;
}

void Hall::SetRectangle(signed x, signed y, signed width, signed height)
{
	SCREEN_X = x;
	SCREEN_Y = y;
	EXCERPT_WIDTH = width;
	EXCERPT_HEIGHT = height;
}

static ::Image CreateFromColorTable_COLOR()
{
	Hall::Color* tempImage = (Hall::Color*)malloc(sizeof(Hall::Color) * EXCERPT_WIDTH * EXCERPT_HEIGHT);
	::Image image;
	image.data = tempImage;
	image.width = EXCERPT_HEIGHT;
	image.height = EXCERPT_WIDTH; 
	image.mipmaps = 1;
	image.format = PIXELFORMAT_UNCOMPRESSED_R5G5B5A1;
	
	int j = 16 - ctSizes[COLOR_TABLE_TYPE];
	unsigned short index;
	for(int i = 0; i < EXCERPT_WIDTH * EXCERPT_HEIGHT; i++)
	{
		index = (DRAW_COLOR >> j) && ctMasks[COLOR_TABLE_TYPE];
		tempImage[i] = Hall::colorTable[(unsigned int)COLOR_TABLE_OFFSET + index];
		j -= ctSizes[COLOR_TABLE_TYPE];
		if(j < 0) 
		{
			j = 16 - ctSizes[COLOR_TABLE_TYPE];
		}
	}

	return image;
}

static ::Image CreateFromColorTable_MEMORY()
{
	Hall::Color* tempImage = (Hall::Color*)malloc(sizeof(Hall::Color) * EXCERPT_WIDTH * EXCERPT_HEIGHT);
	::Image image;
	image.data = tempImage;
	image.width = EXCERPT_HEIGHT;
	image.height = EXCERPT_WIDTH; 
	image.mipmaps = 1;
	image.format = PIXELFORMAT_UNCOMPRESSED_R5G5B5A1;
	
	int j = 16 - ctSizes[COLOR_TABLE_TYPE];
	int k = 0;
	Hall::Color color = IMAGE_START[k];
	unsigned short index;
	for(int i = 0; i < EXCERPT_WIDTH * EXCERPT_HEIGHT; i++)
	{
		index = (color >> j) && ctMasks[COLOR_TABLE_TYPE];
		tempImage[i] = Hall::colorTable[(unsigned int)COLOR_TABLE_OFFSET + index];
		j -= ctSizes[COLOR_TABLE_TYPE];
		if(j < 0) 
		{
			j = 16 - ctSizes[COLOR_TABLE_TYPE];
			k++;
			color = IMAGE_START[k];
		}
	}

	return image;
}

void Hall::Draw()
{
	float width = IMAGE_FLIP_X ? -EXCERPT_WIDTH : EXCERPT_WIDTH;
	float height = IMAGE_FLIP_Y ? -EXCERPT_HEIGHT : EXCERPT_HEIGHT;
	float scale_x = IMAGE_SCALE_X < 0 ? (1 / (float)-IMAGE_SCALE_X) : IMAGE_SCALE_X;
	float scale_y = IMAGE_SCALE_Y < 0 ? (1 / (float)-IMAGE_SCALE_Y) : IMAGE_SCALE_Y;
	float dest_width = EXCERPT_WIDTH * scale_x;
	float dest_height = EXCERPT_HEIGHT * scale_y;
	::Vector2 origin = {0, 0};
	::Color color = {255, 255, 255, 255};

	if (COLOR_TABLE_TYPE == NONE && DRAW_COLOR_SOURCE == COLOR)
	{
		unsigned char red = ((DRAW_COLOR >> 11) & 0b11111) << 3;
		unsigned char green = ((DRAW_COLOR >> 6) & 0b11111) << 3;
		unsigned char blue = ((DRAW_COLOR >> 1) & 0b11111) << 3;
		unsigned char alpha = (DRAW_COLOR & 0b1)* 255;
		color = {red, green, blue, alpha};

		::DrawRectangle(SCREEN_X, SCREEN_Y, dest_width, dest_height, color);
	}
	else
	{
		Texture2D texture;
		Image image;
		if(COLOR_TABLE_TYPE != NONE && DRAW_COLOR_SOURCE == COLOR)
		{
			image = CreateFromColorTable_COLOR();
			texture = ::LoadTextureFromImage(image);
		}
		else if(COLOR_TABLE_TYPE != NONE && DRAW_COLOR_SOURCE == MEMORY)
		{
			image = CreateFromColorTable_MEMORY();
			texture = ::LoadTextureFromImage(image);
		}
		else if(COLOR_TABLE_TYPE == NONE && DRAW_COLOR_SOURCE == MEMORY)
		{
			texture = textures[IMAGE_START];
		}

		::DrawTexturePro(texture, 
		{ (float)IMAGE_X, (float)IMAGE_Y, width, height }, 
		{ (float)SCREEN_X, (float)SCREEN_Y, dest_width, dest_height },
		origin, 0, color);

		if(COLOR_TABLE_TYPE != NONE)
		{
			free(image.data);
		}
	}


}

#ifdef DESKTOP
void Hall::UpdateRaylibTexture(const Color* image)
{
	::UpdateTexture(textures[(Color*)image], image);
}
#endif


void Hall::Draw(const unsigned short* data, unsigned short xOffset, unsigned short yOffset, unsigned short screenX, unsigned short screenY, unsigned short width, unsigned short height, unsigned short dataWidth)
{
	AddImage((Color*)data, dataWidth);
	SetColorSource(Hall::MEMORY);
	SetScale(1, 1);
	SetFlip(false, false);
	IMAGE_START = (Color*)data;
	IMAGE_X = xOffset;
	IMAGE_Y = yOffset;
	IMAGE_SCALE_X = 1;
	IMAGE_SCALE_Y = 1;
	IMAGE_WIDTH = dataWidth;
	EXCERPT_WIDTH = width;
	EXCERPT_HEIGHT = height;
	SCREEN_X = screenX;
	SCREEN_Y = screenY;
	Draw();
}


void Hall::Clear(unsigned short color)
{
	SetRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetColor(color);
	SetColorSource(Hall::COLOR);
	SetColorTable(Hall::NONE);
	SetScale(1, 1);
	SetShape(Hall::RECTANGLE);
	Draw();
}

void Hall::SetData(const unsigned short* data)
{
	IMAGE_START = (Color*)data;
}

void Hall::SetXOffset(unsigned short xOffset)
{
	IMAGE_X = xOffset;
}

void Hall::SetYOffset(unsigned short yOffset)
{
	IMAGE_Y = yOffset;
}

void Hall::SetImageWidth(unsigned short imageWidth)
{
	IMAGE_WIDTH = imageWidth;
}

void Hall::SetWidth(unsigned short width)
{
	EXCERPT_WIDTH = width;
}

void Hall::SetHeight(unsigned short height)
{
	EXCERPT_HEIGHT = height;
}


void Hall::SetScreenX(unsigned short x)
{
	SCREEN_X = x;
}


void Hall::SetScreenY(unsigned short y)
{
	SCREEN_Y = y;
}

void Hall::SetClearColor(unsigned short color)
{
	DRAW_COLOR = color;
}

void Hall::SetCommandDraw()
{
	COMMAND_DRAW = true;
}

void Hall::SetCommandClear()
{
	Draw();
}

void _UpdateAudio(float frameTime);

void Hall::SetCommandSwapBuffers()
{
	::EndMode2D();
	::EndTextureMode();
	::BeginDrawing();
	::DrawTexturePro(screen.texture, { 0, 0, (float)screen.texture.width, (float)-screen.texture.height}, { 0, 0, (float)::GetScreenWidth(), (float)::GetScreenHeight()}, {0, 0}, 0, ::Color{255, 255, 255, 255});
	::EndDrawing();

	_UpdateAudio(GetFrameTime());

	::BeginTextureMode(screen);
	::BeginMode2D(camera);
}

bool Hall::GetIsGPUBusy()
{
	return false;
}

bool Hall::GetVSync()
{
	//This is a bit stupid, but the swap buffer command is already ensuring that the game loop
	//waits for vsync. Just returning true here will of course not work, of VSync is needed for
	//something else than assuring timing
	static bool temp = false;
	temp = !temp;
	return temp;
}

bool Hall::GetHSync()
{
	//We can't do that here :(
	return true;
}
