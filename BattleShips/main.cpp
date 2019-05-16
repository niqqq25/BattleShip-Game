#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[]) {

	const int FPS = 60; // <-- can change FPS cap
	const int frameDelay = 1000 / FPS;

	game = new Game();

	game->CreateWindow();

	Uint32 FrameStart;
	int FrameTime;

	while (game->GetisRunning()) {

		FrameStart = SDL_GetTicks();
		game->Update();

		game->Draw();

		FrameTime = SDL_GetTicks() - FrameStart;
		if (frameDelay > FrameTime) {
			SDL_Delay(frameDelay - FrameTime);
		}
	}
	game->Destroy();

	return 0;
}