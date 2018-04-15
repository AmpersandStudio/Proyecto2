#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "Font.h"
#include "checkML.h"

using namespace std;

class Texture
{
private:
	SDL_Texture* TEXTURE = nullptr; 
	SDL_Renderer* RENDERER = nullptr;
	string FILENAME;
	int	W = 0;
	int	H = 0; 
	int FW = 0;
	int FH = 0;


public:
	Texture(SDL_Renderer* renderer, string filename = " ");
	~Texture();

	void load(int rows, int cols); 

	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderComplete();
	void renderFrame(SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE);

	
	SDL_Texture* getSDLText() { return TEXTURE; };
};

