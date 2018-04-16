#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
	m_Fonts[ARIAL16] = { "fonts/ARIAL.ttf", 16 };
	m_Fonts[ARIAL24] = { "fonts/ARIAL.ttf", 24 };
	m_Fonts[NESChimera16] = { "fonts/NES-Chimera.ttf", 16 };
	m_Fonts[NESChimera24] = { "fonts/NES-Chimera.ttf", 24 };
	m_Fonts[CaptureIt16] = { "fonts/Capture_it.ttf", 16 };
	m_Fonts[CaptureIt24] = { "fonts/Capture_it.ttf", 24 };

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
		m_textureMap[id] = pTexture;
		m_textureDims[id] = std::pair<int, int>(w, h);
		m_textureRows[id] = std::pair<int, int>(row, col);
		return true;
	}

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

void TextureManager::drawFullCamera(std::string id, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect = { 0, 0, Game::Instance()->getWinWidth() , Game::Instance()->getWinHeight()};

	srcRect.x = Camera::Instance()->getPosition().getX();
	srcRect.y = Camera::Instance()->getPosition().getY();
	srcRect.w = Game::Instance()->getWinWidth();
	srcRect.h = Game::Instance()->getWinHeight();



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
	srcRect.w = width; destRect.w = width;
	srcRect.h = height; destRect.h = height;
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
	srcRect.w = width; destRect.w = width;
	srcRect.h = height;  destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawText(std::string text, FontId id, const SDL_Color color, int x, int y, SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	Font* font = new Font(m_Fonts[id].fileName, m_Fonts[id].size);

	if (font != nullptr)
	{
		SDL_Surface* textSurface = font->renderText(text, color);

		if (textSurface != nullptr)
		{
			int w = textSurface->w;
			int h = textSurface->h;

			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
			SDL_FreeSurface(textSurface);

			if (pTexture != nullptr)
			{
				SDL_Rect destRect = { x, y, w, h };

				SDL_RenderCopyEx(pRenderer, pTexture, NULL, &destRect, 0, 0, SDL_FLIP_NONE);
				font->close();
				return;
			}
		}
	}

	std::cout << "Algo no ha salido bien.\n";
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
