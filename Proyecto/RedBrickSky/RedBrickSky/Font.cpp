#include "Font.h"


Font::Font()
{
}

Font::Font(std::string filename, int size)
{
	load(filename, size);
}

Font::~Font()
{
	free();
}

bool Font::load(std::string filename, int size)
{
	font_ = TTF_OpenFont(filename.c_str(), size);
	return font_ != nullptr;
}

void Font::free()
{
	if (font_ != nullptr) TTF_CloseFont(font_);
	font_ = nullptr;
}

SDL_Surface* Font::generateSurface(std::string text, SDL_Color color) const
{
		return TTF_RenderText_Solid(font_, text.c_str(), color);
	
}
