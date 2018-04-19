#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

#include "Game.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "TransitionState.h"
#include "CreditsState.h"
#include "PreloadState.h"

#include "TextureManager.h"
#include "GameObjectFactory.h" 
#include "Player.h"
#include "Interactuable.h"
#include "Cartel.h"
#include "Key.h"


Game Game::s_pInstance;

Game::Game() : exit_(false), error_(false), FRAME_RATE_(16.7)
{
	srand(static_cast<unsigned int>(time(NULL)));

	initSDL();
	loadResources();
	registerTypes();
}

Game::~Game()
{
	clean();
}

void Game::initSDL()
{
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// SDL Fonts
	TTF_Init();

	// SDL Mixer (Music, Sound, etc)
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// SDL Image
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

	// Create window
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	winWidth_ = 800;
	winHeight_ = 600;
	WINDOW_ = SDL_CreateWindow("Red Brick Sky", winX, winY, winWidth_, winHeight_, SDL_WINDOW_SHOWN);

	// Create the renderer
	RENDERER_ = SDL_CreateRenderer(WINDOW_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Clear screen (background color)
	SDL_SetRenderDrawColor(RENDERER_, 0, 0, 0, 255);
	SDL_RenderClear(RENDERER_);
	SDL_RenderPresent(RENDERER_);

	zoom_ = 1;
}

void Game::loadResources()
{
	// Load Textures
	TheTextureManager::Instance()->load("..\\images\\play.png", "0", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bag.png", "1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\shop.png", "2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\exit.png", "3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\food2.png", "4", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\fruit.png", "5", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\invent.png", "6", RENDERER_);
	//TheTextureManager::Instance()->load("..\\images\\inventFront.png", "7", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\keyboard.png", "8", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\backPack.png", "9", RENDERER_);
	//TheTextureManager::Instance()->load("..\\images\\backPackBack.png", "10", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\abc.png", "11", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\selector.png", "12", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\name.png", "13", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\weapons.png", "14", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\potions.png", "15", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\items.png", "16", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Panel.png", "17", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\grey_button.png", "18", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Personajes.png", "19", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Vida.png", "20", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\weaponsSet.png", "21", RENDERER_, 8, 8);
	TheTextureManager::Instance()->load("..\\images\\transition.png", "22", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\go.png", "23", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bigbox.png", "24", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\enemyBox.png", "25", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\playerBox.png", "26", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\ground.png", "27", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\buttonArea.png", "28", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\emptyBox.png", "29", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\fondo.png", "fondoBatallaTuto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\MainMenu.png", "MainMenu", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\BattlePlayer.png", "BattlePlayer", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\BattleEnemy.png", "BattleEnemy", RENDERER_);
	//TheTextureManager::Instance()->load("..\\RedBrickSky\assets\\Personaje1.png", "Personaje1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\ataco.png", "atacoTexto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\jugadorAtaco.png", "jugAtacoTexto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\enemigoAtaco.png", "enemAtacoTexto", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\seleccionaOpcion.png", "selOptTexto", RENDERER_);
	TheTextureManager::Instance()->load("assets/BetaTutorial.png", "level0", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\tylerSS1.png", "tylerSS", RENDERER_, 1, 13);
	TheTextureManager::Instance()->load("..\\images\\arbolSS.png", "arbolSS", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\key.png", "Key", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bubble_speech.png", "vi�eta", Game::Instance()->getRenderer());
	TheTextureManager::Instance()->load("..\\images\\bg.png", "bgmm", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\newbutton.png", "nbutton", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\exitbutton.png", "ebutton", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg.png", "battlebg", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\blackboard.jpg", "blackboard", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\logo.png", "logo", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\blue.png", "blue", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\sky.jpg", "sky", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\amplogo.png", "amplogo", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\frase.png", "frase", RENDERER_);

	// Load Sounds
	TheSoundManager::Instance()->load("..\\sounds\\Crash_Woah.wav", "woah", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\click.wav", "click", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\punch.wav", "punch", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\punch_alt.wav", "punch_2", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_loop.wav", "loop_btl", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_loop_new.wav", "test", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_transition.wav", "trans_btl", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\music.wav", "music", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\theme.ogg", "menu", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle1.ogg", "battle", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\credits.ogg", "credits", SOUND_MUSIC);	
	TheSoundManager::Instance()->load("..\\sounds\\departure.ogg", "departure", SOUND_MUSIC);

	TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 2);
}

void Game::registerTypes()
{
	// Register types in Game Object Factory
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Interactuable", new InteractuableCreator());
	TheGameObjectFactory::Instance()->registerType("NPC", new NPCcreator());
	TheGameObjectFactory::Instance()->registerType("Cartel", new CartelCreator());
	TheGameObjectFactory::Instance()->registerType("Bag", new BagCreator());
	TheGameObjectFactory::Instance()->registerType("Key", new KeyCreator());
}

void Game::begin()
{
	stateMachine_ = new StateMachine();
	stateMachine_->pushState(new MainMenuState());
	run();
}

void Game::run()
{
	int startime, frametime;
	while (!exit_ && !error_)
	{
		startime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frametime = SDL_GetTicks() - startime;

		if (frametime < FRAME_RATE_) SDL_Delay(FRAME_RATE_ - frametime);
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	bool capturedEvent = false;
	//en cuanto capturemos un evento, salimos, asi evitamos fallos cuando cambiemos de estado
	//porque en cuanto cambiemos se dejaran de gestionar mas eventos

	while (SDL_PollEvent(&event) && !exit_ && !capturedEvent) 
	{
		if (event.type == SDL_KEYDOWN) 
		{
			if (event.key.keysym.sym == SDLK_f)	// fullscreen mode
			{
				// Comentando para que los PC dirty peasant no se rompan
				int flags = SDL_GetWindowFlags(TheGame::Instance()->getWindow());
				if (flags & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), 0);
				else SDL_SetWindowFullscreen(TheGame::Instance()->getWindow(), SDL_WINDOW_FULLSCREEN);
				break;
			}
		}

		capturedEvent = (stateMachine_->currentState()->handleEvent(event));
	}

	//Comprobaremos del mismo modo si se ha conectado o desconectado el mando 
	if (event.type == SDL_JOYDEVICEADDED && XboxController::Instance()->getNumControllers() == 0)
		XboxController::Instance()->insertController();
	else if (event.type == SDL_JOYDEVICEREMOVED)
		XboxController::Instance()->removeController();

}

void Game::update()
{
	stateMachine_->currentState()->update();
}

void Game::render() 
{
	if(!static_cast<TransitionState*>(stateMachine_->currentState())) SDL_RenderClear(Game::Instance()->getRenderer());

	//renderizamos los objetos
	SDL_SetRenderDrawColor(RENDERER_, 0, 255, 255, 255);
	stateMachine_->currentState()->render();
	if (!exit_) SDL_RenderPresent(RENDERER_);
}

void Game::clean()
{
	SoundManager::Instance()->clear();
	TextureManager::Instance()->clearTextureMap();

	delete stateMachine_;

	SDL_DestroyRenderer(RENDERER_);
	RENDERER_ = nullptr;

	SDL_DestroyWindow(WINDOW_);
	WINDOW_ = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();

	SDL_Quit();

	//no hay otra manera de borrar esto, gracias Shaun Mitchell!
	delete TheGameObjectFactory::Instance();
	delete TheTextureManager::Instance();
	delete TheSoundManager::Instance();
	delete GameManager::Instance();
}