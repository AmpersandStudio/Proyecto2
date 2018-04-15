#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

Texture::Texture(SDL_Renderer* renderer, string filename) {
	RENDERER = renderer;
	FILENAME = filename;
}

Texture::~Texture()
{
}

void Texture::load(int rows, int cols) {
	//si creas una nueva textura y no llenas la que tienes ya creada en el .h, 
	//a la hora de pasarlo a game.cpp recibe una textura "nullptr"
	SDL_Surface* surface = IMG_Load(FILENAME.c_str());
	TEXTURE = SDL_CreateTextureFromSurface(RENDERER, surface);
	W = surface->w;
	H = surface->h;
	SDL_FreeSurface(surface);
	//Tamaños
	SDL_QueryTexture(TEXTURE, nullptr, nullptr, &W, &H);
	FW = W / cols;
	FH = H / rows;
}

void Texture::render(const SDL_Rect& rect, SDL_RendererFlip flip) {
	SDL_RenderCopy(RENDERER, TEXTURE, &rect, nullptr);
	//SDL_RenderPresent(RENDERER);
}

void Texture::renderComplete() {
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = W;
	srcRect.h = H;
	render(srcRect);

}

void Texture::renderFrame(SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip) {
	//Crea un rectangulo fuente
	SDL_Rect rect;
	rect.x = col * FW;
	rect.y = row * FH;
	rect.w = FW;
	rect.h = FH;

	SDL_RenderCopy(RENDERER, TEXTURE, &rect, &destRect);
}