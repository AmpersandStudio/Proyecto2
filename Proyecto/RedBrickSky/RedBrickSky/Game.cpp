#include "Game.h"
#include<stdlib.h>
#include<time.h>
#include <fstream>
#include <math.h>
#include "StateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	winWidth_ = 1280;
	winHeight_ = 720;
	Black.a = 255; Black.b = 0; Black.r = 0; Black.g = 0;	//color negro

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	WINDOW_ = SDL_CreateWindow("RBS", winX, winY,
		winWidth_, winHeight_, SDL_WINDOW_SHOWN);
	RENDERER_ = SDL_CreateRenderer(WINDOW_, -1, SDL_RENDERER_ACCELERATED);
	if (WINDOW_ == nullptr || RENDERER_ == nullptr)
		cout << "Error initializing SDL\n";

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Error initializing SDL_Mixer" << endl;
	}

	srand(time(nullptr)); //semilla de aleatorios

	//Creamos maquina de estados
	stateMachine_ = new StateMachine();

	//Fuente
	font = new Font(FONT_PATH + "OpenSans-Regular.ttf", 50);

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
	loadTexture("..\\images\\abc.png", 9, 6);
	loadTexture("..\\images\\selector.png", 1, 1);
	loadTexture("..\\images\\name.png", 1, 1);
	loadTexture("..\\images\\Weapons.png", 1, 1);//14
	loadTexture("..\\images\\Potions.png", 1, 1);
	loadTexture("..\\images\\Items.png", 1, 1);
		//BattleState
	loadTexture("..\\images\\Battle_UI_Panel.png", 1, 1); //17
	loadTexture("..\\images\\grey_button.png", 1, 1);
	loadTexture("..\\images\\Battle_UI_Personajes.png", 1, 1);
	loadTexture("..\\images\\Battle_UI_Vida.png", 1, 1);
	//Objeto de tienda

	loadTexture("..\\images\\weaponsSet.png", 8, 8); //21

	//objeto de presentacion
	loadTexture("..\\images\\transition.png", 1, 1);//22
	loadTexture("..\\images\\go.png", 1, 1); //23

	//CARGA DE SONIDOS
	TheSoundManager::Instance()->load("..\\sounds\\Crash_Woah.wav", "woah", SOUND_SFX);

	//inicializamos booleanos de control
	exit_ = false; error_ = false; 

	// milliseconds per frame -> 16.7 = 60 frames/s - 33.3 = 30 frames/s
	FRAME_RATE_ = 33.3; // El valor original era 130, por si fuera necesario
}

Game::~Game()
{
	//borramos memoria dinamica
	for (int i = 0; i < textures_.size(); i++) {
		delete textures_[i];
		textures_[i] = nullptr;
	}
	Mix_Quit();
	delete stateMachine_;
}

void Game::loadTexture(string filename, int rows, int cols) {
	if (filename == " ") { // WARMIMG!!!!!!!!!!!!!!
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

void Game::textPrinter(string text, int destH, int destX, int destY, SDL_Color color) {

	SDL_Rect font_dest;

	font_dest.w = destH * text.size();
	font_dest.h = destH;
	
	font_dest.x = destX;
	font_dest.y = destY;

	fontTexture->loadFromText(RENDERER_, text, font, color);
	fontTexture->render(font_dest, SDL_FLIP_NONE);
	SDL_RenderPresent(RENDERER_);

}