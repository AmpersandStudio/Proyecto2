#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "SDL_mixer.h"

#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game::Instance()->begin();
	//Game::Instance()->clean();

	return (0);
}