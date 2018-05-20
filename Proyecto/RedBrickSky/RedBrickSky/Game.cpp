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
#include "Door.h"
#include"Teleport.h"

#include "StringToScreen.h"


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

	scaleFact = 2;

	strings = StringToScreen::Instance();
}

void Game::loadResources()
{
	// Load Textures
	TheTextureManager::Instance()->load("..\\images\\jugarButton.png", "0", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bag.png", "1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\tiendaButton.png", "2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\salirButton.png", "3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\food2.png", "4", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\fruit.png", "5", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\shop1.png", "shop1", RENDERER_);
	//TheTextureManager::Instance()->load("..\\images\\inventFront.png", "7", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\keyboard.png", "8", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\BackPack.png", "9", RENDERER_);
	//TheTextureManager::Instance()->load("..\\images\\backPackBack.png", "10", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\abc.png", "11", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\selector.png", "12", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\nombreButton.png", "13", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\armasButton.png", "14", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\pocionesButton.png", "15", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\objetosButton.png", "16", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Panel.png", "17", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\grey_button.png", "18", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Personajes.png", "19", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\Battle_UI_Vida.png", "20", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\weaponsSet.png", "21", RENDERER_, 8, 8);
	TheTextureManager::Instance()->load("..\\images\\transition.png", "22", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\go2.png", "23", RENDERER_);
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
	TheTextureManager::Instance()->load("..\\images\\tylerSS1.png", "tylerSS", RENDERER_, 1, 37);
	TheTextureManager::Instance()->load("..\\images\\arbolSS.png", "arbolSS", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\escoba.png", "escoba", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\pelotas.png", "pelotas", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\basura.png", "basura", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\bocata.png", "bocata", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\Libro_1.png", "libro1", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\Libro_2.png", "libro2", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\Taquilla.png", "taquilla", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\Avion_Pato.png", "avion", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\Globo.png", "globo", RENDERER_, 1, 2);
	TheTextureManager::Instance()->load("..\\images\\key.png", "Key", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\bubble_speech.png", "viñeta", Game::Instance()->getRenderer());
	TheTextureManager::Instance()->load("..\\images\\bg.png", "bgmm", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\jugarButton.png", "nbutton", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\salirButton.png", "ebutton", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg1.png", "battlebg1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg2.png", "battlebg2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg3.png", "battlebg3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg4.png", "battlebg4", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg5.png", "battlebg5", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg6.png", "battlebg6", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg7.png", "battlebg7", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg8.png", "battlebg8", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg9.png", "battlebg9", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg10.jpg", "battlebg10", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\battlebg11.jpg", "battlebg11", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\blackboard.jpg", "blackboard", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\logo.png", "logo", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\blue.png", "blue", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\sky.jpg", "sky", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\amplogo.png", "amplogo", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\frase.png", "frase", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\candy.png", "sweet", RENDERER_,1,2); 
	TheTextureManager::Instance()->load("..\\images\\playerInventBox.png", "inventHP", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\creditosButton.png", "credits", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\ATQ+.png", "ATQ+", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\ATQ-.png", "ATQ-", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\DEF+.png", "DEF+", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\DEF-.png", "DEF-", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\PRC+.png", "PRC+", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\PRC-.png", "PRC-", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\pauseBG.png", "pbg", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\potionsFB.png", "potiFB", RENDERER_,1,2);
	TheTextureManager::Instance()->load("..\\assets\\Tutorial.png", "level1-1", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\JardinesInferiores.png", "level1-2", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\Pasillos.png", "level1-3", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\JardinesSuperiores.png", "level1-4", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\Gimnasio.png", "level1-5", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\Nivel2.png", "level2", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\Tienda.png", "tiendaLevel", RENDERER_);
	TheTextureManager::Instance()->load("..\\assets\\PasilloFinal.png", "level3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\cleonButton.png", "clb", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\election.png", "election", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\qbg.png", "qbg", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\yesbutton.png", "yesbutton", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\nobutton.png", "nobutton", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q1_1.png", "q1_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q1_2.png", "q1_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q1_3.png", "q1_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q2_1.png", "q2_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q2_2.png", "q2_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q2_3.png", "q2_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q3_1.png", "q3_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q3_2.png", "q3_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q3_3.png", "q3_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q4_1.png", "q4_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q4_2.png", "q4_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q4_3.png", "q4_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q5_1.png", "q5_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q5_2.png", "q5_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q5_3.png", "q5_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q6_1.png", "q6_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q6_2.png", "q6_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q6_3.png", "q6_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q7_1.png", "q7_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q7_2.png", "q7_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q7_3.png", "q7_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q8_1.png", "q8_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q8_2.png", "q8_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q8_3.png", "q8_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q9_1.png", "q9_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q9_2.png", "q9_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q9_3.png", "q9_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q10_1.png", "q10_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q10_2.png", "q10_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q10_3.png", "q10_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q11_1.png", "q11_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q11_2.png", "q11_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q11_3.png", "q11_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q12_1.png", "q12_1", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q12_2.png", "q12_2", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\q12_3.png", "q12_3", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\buttonA.png", "buttonA", RENDERER_);
	TheTextureManager::Instance()->load("..\\images\\BotonesXbox.png", "botonesXbox", RENDERER_,1,5);
	TheTextureManager::Instance()->load("..\\images\\bokoblinSS.png", "bokoblinSS", RENDERER_, 1, 2);

	// Load Music
	TheSoundManager::Instance()->load("..\\sounds\\Battle_loop.wav", "loop_btl", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_loop_new.wav", "test", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle_transition.wav", "trans_btl", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\music.wav", "music_", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\theme.ogg", "menu_", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle1.ogg", "battle", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\credits.ogg", "credits", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\departure.ogg", "departure", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\boss_battle_loop.wav", "BossMusic", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\funk.wav", "funk", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\victory.ogg", "victory", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\ExplorationBSO.ogg", "music", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\ExplorationBSO2.ogg", "music2", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\MainMenuBSO.ogg", "menu", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\questions.ogg", "questions", SOUND_MUSIC);
	TheSoundManager::Instance()->load("..\\sounds\\Battle3.ogg", "bbattle", SOUND_MUSIC);

	//Load SFX
	TheSoundManager::Instance()->load("..\\sounds\\Ambiente_exterior.wav", "exteriores", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Ambiente_interior.wav", "interiores", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Crash_Woah.wav", "woah", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\click.wav", "click", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\punch.wav", "punch", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\punch_alt.wav", "punch_2", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\pasos.wav", "piedra", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\pasos2.wav", "piedra2", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\hierba.wav", "hierba", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Censor_Beep.wav", "censura", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\coins.wav", "monedas", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Collision.wav", "rebote", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\compra_tienda.wav", "compra", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\cremallera.wav", "cremallera", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\dialogue_sound.wav", "dialogo", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\door_close.wav", "Puerta_cerrar", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\door_open.wav", "Puerta_abrir", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\hit.wav", "golpe", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\pick_up.wav", "recoger", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\reglazo.wav", "reglazo", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\School_ring.wav", "timbre", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\tirachinas.wav", "Tirachinas", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\newgame.ogg", "newgame", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\select.ogg", "select", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Wrong.wav", "wrong", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\Huida.wav", "escape", SOUND_SFX);
	TheSoundManager::Instance()->load("..\\sounds\\ampersand.wav", "ampersand", SOUND_SFX);

	TheSoundManager::Instance()->setMusicVolume(MIX_MAX_VOLUME / 3);
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
	TheGameObjectFactory::Instance()->registerType("Door", new DoorCreator());
	TheGameObjectFactory::Instance()->registerType("Teleport", new TeleportCreator());
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
	SDL_SetRenderDrawColor(RENDERER_, 255, 255, 255, 255);
	stateMachine_->currentState()->render();

	strings->render();
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
	delete StringToScreen::Instance();
}