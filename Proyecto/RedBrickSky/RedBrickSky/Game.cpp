#include "Game.h"
#include<stdlib.h>
#include<time.h>
#include <fstream>
#include <math.h>
#include "StateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"

Game::Game()
{
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	winWidth_ = 1280;
	winHeight_ = 720;

	SDL_Init(SDL_INIT_EVERYTHING);
	WINDOW_ = SDL_CreateWindow("RBS", winX, winY,
		winWidth_, winHeight_, SDL_WINDOW_SHOWN);
	RENDERER_ = SDL_CreateRenderer(WINDOW_, -1, SDL_RENDERER_ACCELERATED);
	if (WINDOW_ == nullptr || RENDERER_ == nullptr)
		cout << "Error initializing SDL\n";

	srand(time(nullptr)); //semilla de aleatorios

	//Creamos maquina de estados
	stateMachine_ = new StateMachine();

	//Cargamos las texturas
	loadTexture("..\\images\\play.png", 1, 1);
	loadTexture("..\\images\\bag.png", 1, 1);
	loadTexture("..\\images\\shop.png", 1, 1);
	loadTexture("..\\images\\exit.png", 1, 1);
	//Para la tienda 4 -> incluido
	loadTexture("..\\images\\food2.png", 1, 1);
	loadTexture("..\\images\\fruit.png", 1, 1);
	loadTexture("..\\images\\invent.png", 1, 1);
	loadTexture("..\\images\\inventFront.png", 1, 1);
	loadTexture("..\\images\\keyboard.png", 1, 2);
	loadTexture("..\\images\\backPack.png", 1, 1); //9
	loadTexture("..\\images\\backPackBack.png", 1, 1);

	//inicializamos booleanos de control
	exit_ = false; error_ = false;

	FRAME_RATE_ = 130;
}

Game::~Game()
{
	//borramos memoria dinamica
	for (int i = 0; i < textures_.size(); i++) {
		delete textures_[i];
		textures_[i] = nullptr;
	}
	delete stateMachine_;
}

void Game::loadTexture(string filename, int rows, int cols) {
	if (filename == " ") {
		cout << "Error cargando la textura";
	}
	else {
		Texture* text = new Texture(RENDERER_, filename);
		text->load(rows, cols);
		textures_.push_back(text);
	}
}

void Game::render() {
	//renderizamos los objetos
	SDL_SetRenderDrawColor(RENDERER_, 0, 255, 255, 255);
	SDL_RenderClear(RENDERER_);
	stateMachine_->currentState()->render();
	if (!exit_) SDL_RenderPresent(RENDERER_);
}

void Game::update() {
	stateMachine_->currentState()->update();
}

void Game::handleEvents() {
	SDL_Event event;
	bool capturedEvent = false;
	//en cuanto capturemos un evento, salimos, asi evitamos fallos cuando cambiemos de estado
	//porque en cuanto cambiemos se dejaran de gestionar mas eventos

	while (SDL_PollEvent(&event) && !exit_ && !capturedEvent) {
		capturedEvent = (stateMachine_->currentState()->handleEvent(event));
	}
}

void Game::begin() {
	GameState* aux = new MainMenuState(this);
	stateMachine_->pushState(aux);
	run();
}

void Game::exitApp() {
	exit_ = true;
}

void Game::run() {
	int startime, frametime;
	while (!exit_ && !error_) {
		//flujo natural de bucle
		startime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		frametime = SDL_GetTicks() - startime;
		if (frametime < FRAME_RATE_)SDL_Delay(FRAME_RATE_ - frametime);
	}
	stateMachine_->clearStack(); 
	//en cuanto salgamos de la app, limpiamos la maquina de estados (vaciamos la pila y su memoria dinamica)
}