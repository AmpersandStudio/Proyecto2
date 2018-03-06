#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include "SoundManager.h"

//para evitar inclusiones circulares
class StateMachine;
class PlayState;

class Game
{
private:
	SDL_Window* WINDOW_; //punteros de SDL
	SDL_Renderer* RENDERER_;
	bool error_; bool exit_; //booleanos de control
	int winWidth_, winHeight_; //tamaños de pantalla
	int FRAME_RATE_; //tiempo
	vector<Texture*> textures_;
	StateMachine* stateMachine_; //maquina de estados


public:
	Game();
	~Game();
	void loadTexture(string filename, int rows, int cols); //se encarga de cargar las texturas y llamar a su constructora
	void render(); //recorre la lista de game characters y llama a sus metodos render
	void update(); //recorre la lista de game characters y llama a sus metodos update
	void handleEvents(); //gestiona todos los eventos del juego
	void begin(); //mete el estado menu y llama al run
	void run(); //bucle principal del juego
	//METODOS AUXILIARES
	Texture* getTexture(int t) { return textures_[t]; }; //para que objetos como los botones accedan a su textura
	StateMachine* getStateMachine() { return stateMachine_; }; //para poder gestionar estados accediendo a la maquina desde otras clases
	int getWinWidth() { return winWidth_; }; //para conocer el tamaño de la ventana
	int getWinHeight() { return winHeight_; };
	void cleanSreen() { SDL_RenderClear(RENDERER_); }; //limpia pantalla
	void exitApp(); //sale de la aplicacion
	SDL_Renderer* getRenderer() { return RENDERER_; };
};

