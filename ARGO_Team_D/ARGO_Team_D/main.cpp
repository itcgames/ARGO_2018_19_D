// Libraries
#ifdef _DEBUG
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "image\\SDL2_image.lib")
#pragma comment(lib, "SDL2test.lib") // Does this need to be in release?
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

#pragma comment(lib,"Box2D.lib")


#include "Game.h"

int main(int argc, char* argv[])
{

	Game game;
	game.run();

	return 0;
}