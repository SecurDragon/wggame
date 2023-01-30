#include "Game.hpp"

// Prevent spawn of console window
#ifdef WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
	Game game;
	game.init();
	game.loop();

	return -1;
}
