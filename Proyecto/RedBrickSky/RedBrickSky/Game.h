#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include "SoundManager.h"
#include "Font.h"
#include "Dialogue.h"

//para evitar inclusiones circulares
class StateMachine;
class PlayState;

class Game
{
private:
	Game();
	~Game();
	static Game* s_pInstance;

	SDL_Window* WINDOW_; //punteros de SDL
	SDL_Renderer* RENDERER_;
	bool error_; bool exit_; //booleanos de control
	int winWidth_, winHeight_; //tamaños de pantalla
	int FRAME_RATE_; //tiempo
	vector<Texture*> textures_;
	StateMachine* stateMachine_; //maquina de estados
	const string FONT_PATH = "..\\fonts\\";	//ruta para las fuentes
	SDL_Color Black;	//Color para la fuente
	Font* font = nullptr;	//puntero a la fuente
	Texture* fontTexture = nullptr;	//textura para la fuente

public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}

	void render(); //recorre la lista de game characters y llama a sus metodos render
	void update(); //recorre la lista de game characters y llama a sus metodos update
	void handleEvents(); //gestiona todos los eventos del juego
	void begin(); //mete el estado menu y llama al run
	void run(); //bucle principal del juego
	void textPrinter(string text, int destH, int destX, int destY, SDL_Color color);	//Pone un texto en pantalla
	void clean();
	//METODOS AUXILIARES
	Texture* getTexture(int t) { return textures_[t]; }; //para que objetos como los botones accedan a su textura
	StateMachine* getStateMachine() { return stateMachine_; }; //para poder gestionar estados accediendo a la maquina desde otras clases
	int getWinWidth() { return winWidth_; }; //para conocer el tamaño de la ventana
	int getWinHeight() { return winHeight_; };
	void cleanSreen() { SDL_RenderClear(RENDERER_); }; //limpia pantalla
	void exitApp(); //sale de la aplicacion
	SDL_Renderer* getRenderer() { return RENDERER_; };
	SDL_Window* getWindow() { return WINDOW_; };
	SDL_Color getBlackColor() { return Black; };
	bool canActivate(Dialogue* d);
};

typedef Game TheGame;
