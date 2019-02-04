// SDL
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "image\\SDL2_image.lib")

#ifdef _DEBUG
#pragma comment(lib,"libtmxlite-s-d.lib")
#else
#pragma comment(lib,"tmxlite.lib")
#endif 

#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.run();

	return 0;
}