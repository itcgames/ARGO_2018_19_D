// Libraries
#ifdef _DEBUG
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "image\\SDL2_image.lib")
#pragma comment(lib, "SDL2test.lib") // Does this need to be in release?
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "libtmxlite-s-d.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib,"Box2D.lib")
#pragma comment (lib, "ws2_32.lib")
#else
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "image\\SDL2_image.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "tmxlite.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib,"Box2D.lib")
#pragma comment (lib, "ws2_32.lib")
#endif 

#include "Game.h"

int main(int argc, char* argv[])
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}


	Game game;
	game.run();

	return 0;
}