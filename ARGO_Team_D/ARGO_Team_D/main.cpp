// SDL

#ifdef _DEBUG
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
//#pragma comment(lib, "image\\SDL2_image.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "libtmxlite-s-d.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#else
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "image\\SDL2_image.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "tmxlite.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#endif 


#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.run();

	return 0;
}