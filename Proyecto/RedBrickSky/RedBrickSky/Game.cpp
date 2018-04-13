#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

#include "Game.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "TransitionState.h"

#include "TextureManager.h"
#include "GameObjectFactory.h" 
#include "Player.h"
#include "Interactuable.h"
#include "Cartel.h"


Game Game::s_pInstance;

Game::Game()
{
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	winWidth_ = 800;
	winHeight_ = 600;
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
	fontTexture = new Texture(RENDERER_); //ESTO CREO QUE HABRIA QUE CAMBIARLO A TEXTURE MANAGER

	//Cargamos las texturas
	TheTextureManager::Instance()->load("..\\images\\play.png", "0", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bag.png", "1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\shop.png", "2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\exit.png", "3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\food2.png", "4", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\fruit.png", "5", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\invent.png", "6", RENDERER_);
	//TheTextureManager::Instance()->load("..\\images\\inventFront.png", "7", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\keyboard.png", "8", RENDERER_, 1 ,2);
	TheTextureManager::Instance()->load("..\\images\\backPack.png", "9", RENDERER_);
	//TheTextureManager::Instance()->load("..\\images\\backPackBack.png", "10", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\abc.png", "11", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\selector.png", "12", RENDERER_, 1,2);
	TheTextureManager::Instance()->load("..\\images\\name.png", "13", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\weapons.png", "14", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\potions.png", "15", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\items.png", "16", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Panel.png", "17", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\grey_button.png", "18", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Personajes.png", "19", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Vida.png", "20", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\weaponsSet.png", "21", RENDERER_, 8,8);
	TheTextureManager::Instance()->load("..\\images\\transition.png", "22", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\go.png", "23", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bigbox.png", "24", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\enemyBox.png", "25", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\playerBox.png", "26", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\ground.png", "27", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\buttonArea.png", "28", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\emptyBox.png", "29", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\fondo.png", "fondoBatallaTuto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\MainMenu.png", "MainMenu", RENDERER_, 1,2);
	TheTextureManager::Instance()->load("..\\images\\BattlePlayer.png", "BattlePlayer", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\BattleEnemy.png", "BattleEnemy", RENDERER_);
	//TheTextureManager::Instance()->load("..\\RedBrickSky\assets\\Personaje1.png", "Personaje1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\ataco.png", "atacoTexto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\jugadorAtaco.png", "jugAtacoTexto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\enemigoAtaco.png", "enemAtacoTexto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\seleccionaOpcion.png", "selOptTexto", RENDERER_);
	TheTextureManager::Instance()->load("assets/BetaTutorial.png", "level0", RENDERER_);

	//CARGA DE SONIDOS
	TheSoundManager::Instance()->load("..\\sounds\\Crash_Woah.wav", "woah", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\click.wav", "click", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\punch.wav", "punch", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\punch_alt.wav", "punch_2", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_loop.wav", "loop_btl", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_loop_new.wav", "test", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_transition.wav", "trans_btl", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\music.wav", "music", SOUND_MUSIC);

	TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 2);

	//Registramos los tipos en la Game Object Factory
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Interactuable", new InteractuableCreator());
	TheGameObjectFactory::Instance()->registerType("NPC", new NPCcreator());
	TheGameObjectFactory::Instance()->registerType("Cartel", new CartelCreator());
	TheGameObjectFactory::Instance()->registerType("Bag", new BagCreator());

	//inicializamos booleanos de control
	exit_ = false; 
	error_ = false; 

	// milliseconds per frame -> 16.7 = 60 frames/s - 33.3 = 30 frames/s
	FRAME_RATE_ = 33.3; // El valor original era 130, por si fuera necesario


}

Game::~Game()
{
	clean();
}

void Game::render() 
{
	if(!dynamic_cast<TransitionState*>(stateMachine_->currentState())) SDL_RenderClear(Game::Instance()->getRenderer()); // CACA CACA CACA. MUCHA CACA

	//renderizamos los objetos
	SDL_SetRenderDrawColor(RENDERER_, 0, 255, 255, 255);
	stateMachine_->currentState()->render();
	if (!exit_) SDL_RenderPresent(RENDERER_);
}

void Game::update() 
{
	stateMachine_->currentState()->update();
}

void Game::handleEvents() 
{
	SDL_Event event;

	bool capturedEvent = false;
	//en cuanto capturemos un evento, salimos, asi evitamos fallos cuando cambiemos de estado
	//porque en cuanto cambiemos se dejaran de gestionar mas eventos

	while (SDL_PollEvent(&event) && !exit_ &&!capturedEvent) {
		capturedEvent = (stateMachine_->currentState()->handleEvent(event));
	}

	//Comprobaremos del mismo modo si se ha conectado o desconectado el mando 
	if (event.type == SDL_JOYDEVICEADDED && XboxController::Instance()->getNumControllers() == 0) 
		XboxController::Instance()->insertController();
	else if (event.type == SDL_JOYDEVICEREMOVED)
		XboxController::Instance()->removeController();
	
}

void Game::begin() 
{
	stateMachine_->pushState(new MainMenuState());
	run();
}

void Game::exitApp() 
{
	exit_ = true;
}

void Game::run() 
{
	int startime, frametime;
	while (!exit_ && !error_) 
	{
		//flujo natural de bucle
		startime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frametime = SDL_GetTicks() - startime;

		if (frametime < FRAME_RATE_)SDL_Delay(FRAME_RATE_ - frametime);
	}
}

void Game::textPrinter(string text, int destH, int destX, int destY, SDL_Color color) 
{
	std::cout << "Printing text" << std::endl;

	SDL_Rect font_dest;

	font_dest.w = destH * text.size();
	font_dest.h = destH;
	
	font_dest.x = destX;
	font_dest.y = destY;

	fontTexture->loadFromText(RENDERER_, text, font, color);
	fontTexture->render(font_dest, SDL_FLIP_NONE);
	SDL_RenderPresent(RENDERER_); //ESTE RENDER PRESENT TIENE QUE DESAPARECER AHHHHHHHHHHHHH
}


bool Game::canActivate(Dialogue* d)
{
	bool ret = true;

	/*for (Character* character : characters_)
	{
		if (character->isActive())
			ret = false;
	}*/

	return ret;
}


void Game::clean()
{
	SoundManager::Instance()->clear();
	TextureManager::Instance()->clearTextureMap();

	delete stateMachine_;

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}