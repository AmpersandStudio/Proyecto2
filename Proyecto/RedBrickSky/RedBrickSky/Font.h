#pragma once
#include "SDL_ttf.h"
#include <string>


class Font
{
private:
	TTF_Font* font_ = nullptr;
public:
	Font();
	Font(std::string	filename, int size);
	~Font();
	bool load(std::string filename, int size);
	void free();
	SDL_Surface* generateSurface(std::string text, SDL_Color color) const;

};

