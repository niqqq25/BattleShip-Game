#include "Game.h"
#include "HendleEvents.h"
#include "Board.h"
#include "PlayerActions.h"
#include "BotActions.h"
#include "Windows.h"

SDL_Surface *s;
SDL_Renderer* Game::renderer = nullptr; //need in order to use static...

HendleEvents *hendlevents;

Board *PlayersBoard;
Board *BotsBoard;
PlayerActions *playeractions;
BotActions *botactions;
Windows *windows;

void Game::CreateWindow()
{
	int Init = SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Battleship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 640, 0);

	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //can choose color

	if (Init != 0 || window == NULL) {

		isRunning = false;
	}

	windows = new Windows();
	hendlevents = new HendleEvents();
	PlayersBoard = new Board(50);
	BotsBoard = new Board(481);
	playeractions = new PlayerActions();
	botactions = new BotActions(*BotsBoard);
}

void Game::Update()
{
	if (HendleEvents::EventCode == -1) { //<-- Restart game
		delete PlayersBoard, BotsBoard, playeractions, botactions;
		PlayersBoard = new Board(50);
		BotsBoard = new Board(481);
		playeractions = new PlayerActions();
		botactions = new BotActions(*BotsBoard);
		isPlayerTurn = true;
		HendleEvents::EventCode = 2;
	}
	if (HendleEvents::EventCode == 0) { isRunning = false; }
	hendlevents->EventType();
	if (HendleEvents::EventCode == 2 || HendleEvents::EventCode == 3) { playeractions->PlayerActionsController(*hendlevents, *PlayersBoard, *BotsBoard, isPlayerTurn); }
	if (HendleEvents::EventCode == 3) { 
		botactions->ShootIntoPlayersBoats(*PlayersBoard, isPlayerTurn);
	}
	// <- Game physics (Map, objects)

}

void Game::Draw()
{
	SDL_RenderClear(renderer);
	PlayersBoard->DrawCoord(15, 0);
	PlayersBoard->DrawCoord(450, 0);
	PlayersBoard->DrawBoard();
	BotsBoard->DrawBoard();

	PlayersBoard->DrawBoxes(false);
	BotsBoard->DrawBoxes(true);

	windows->WhichBackground(*PlayersBoard, *BotsBoard);

	SDL_RenderPresent(renderer);
}


void Game::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::GetisRunning()
{
	return isRunning;
}
