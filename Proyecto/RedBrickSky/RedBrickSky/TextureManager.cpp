#include "TextureManager.h"
#include "Game.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer, int row, int col)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	int w = pTempSurface->w;
	int h = pTempSurface->h;

	if (pTempSurface == NULL)
	{
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != NULL)
	{
		std::cout << "Texture load success!\n";
		m_textureMap[id] = pTexture;
		m_textureDims[id] = std::pair<int, int>(w, h);
		m_textureRows[id] = std::pair<int, int>(row, col);
		return true;
	}

	std::cout << "Texture load fail!\n";
	return false;
}


void TextureManager::draw(std::string id, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_textureDims[id].first;
	srcRect.h = m_textureDims[id].second;


	destRect.x = 0;
	destRect.y = 0;
	destRect.w = TheGame::Instance()->getWinWidth();
	destRect.h = TheGame::Instance()->getWinHeight();

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
	
}

void TextureManager::drawFull(std::string id, int destX, int destY, int destW, int destH, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_textureDims[id].first;
	srcRect.h = m_textureDims[id].second;

	destRect.x = destX;
	destRect.y = destY;
	destRect.w = destW;
	destRect.h = destH;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawItem(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, int rows, int cols, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = (m_textureDims[id].first / cols) * currentFrame;
	srcRect.y =  (m_textureDims[id].second / rows) * currentRow;
	srcRect.w = m_textureDims[id].first / cols;	
	srcRect.h = m_textureDims[id].second / rows;

	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::clearTextureMap()
{
	m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}
