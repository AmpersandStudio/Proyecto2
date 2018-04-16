#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Font.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>


class TextureManager
{
public:

	enum FontId { ARIAL16, ARIAL24, NESChimera16, NESChimera24, CaptureIt16, CaptureIt24 };

	~TextureManager();

	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}	

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer, int row = 1, int col = 1);

	void draw(std::string id, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFullCamera(std::string id, SDL_Renderer * pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFull(std::string id, int destX, int destY, int destW, int destH, SDL_Renderer * pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	void drawText(std::string text, FontId id, const SDL_Color color, int x, int y, SDL_Renderer * pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawItem(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, int rows, int cols, SDL_Renderer * pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawF(std::string id, int destX, int destY, int destW, int destH, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip,
		int row, int col);

	void clearTextureMap();
	void clearFromTextureMap(std::string id);

	inline SDL_Texture* getTexture(std::string id) { return m_textureMap[id]; }
	inline int getRows(std::string id) { return m_textureRows[id].first; }
	inline int getCols(std::string id) { return m_textureRows[id].second; }
	inline int getWidth(std::string id) { return m_textureDims[id].first; }
	inline int getHeight(std::string id) { return m_textureDims[id].second; }

private:
	TextureManager();

	struct FontInfo
	{
		std::string fileName;
		int size;
	};

	std::map<std::string, SDL_Texture*> m_textureMap;
	std::map<std::string, std::pair<int, int>> m_textureDims;
	std::map<std::string, std::pair<int, int>> m_textureRows;
	std::map<FontId, FontInfo> m_Fonts;

	static TextureManager* s_pInstance;

	int zoom_;
};

typedef TextureManager TheTextureManager;

