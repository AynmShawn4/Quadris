/*
 * Game.cpp
 *
 *  Created on: 2017  May 14th
 *      Author: ShawnTang
 */

#include "Game.h"
#include "BlockFactory.h"
#include "Render.h"

bool pressed[] = {false, false, false, false};

class Game::GamePimpl{

private:
	int CurrentScore;
	int HighScore;
	int level;
	Block* CurrentBlock;
	Block* NextBlock;
	char ** Board ;
	Render * render;
	bool quit;
	BlockFactory * factory;
	int posiX;
	int posiY;
	int count;
	int height;
	int change[3];

	/* function for handling use input */
	void handleKey(){
		SDL_Event event;
		unsigned start_time = SDL_GetTicks();
		while( SDL_WaitEventTimeout( &event, 50 ) ){
			if (event.type == SDL_QUIT){
				quit = true;
			} else {
				switch( event.key.keysym.sym ){
					case SDLK_LEFT:
						if (event.type == SDL_KEYDOWN){
							pressed[0] = true;
						} else {
							pressed[0] = !pressed[0];
						}
						break;
					case SDLK_UP:
						if (event.type == SDL_KEYDOWN){
							pressed[1] = true;
						} else {
							pressed[1] = !pressed[1];
						}
						break;
					case SDLK_DOWN:
						if (event.type == SDL_KEYDOWN){
							pressed[2]  = true;
						} else {
							pressed[2] = !pressed[2];
						}
						break;
					case SDLK_SPACE:
						if (event.type == SDL_KEYDOWN){
							pressed[3] = !pressed[3];
						}
						break;
					default:
						break;
				}
			}

			unsigned current_time = SDL_GetTicks();
			unsigned elapsed_time = current_time - start_time;
			if (elapsed_time >= 50){
				break;
			}
		}
	}


	void erase(char ** b,int h, int w, int min, int max){
		/* calculate what to erase */
		int times = 0;
		for (int i = max ; i > min ; i--){
			bool erase = true;
			for (int j = 0; j < w; j++){
				if (b[i][j] == 0 ){
					erase = false;
					break;
				}
			}
			if (erase){
				times++;
				for (int j = 0; j < w; j++){
					b[i][j] = 1;
				}
			}

		}
		if (times){
			int gap = 1;
			for (int i = max ; i > height ; i--){
				for (int j = 0; j < w; j++){
					if (b[i][j] == 1){
						while (b[i - gap][j] == 1){
							gap++;
						}
						b[i][j] = b[i - gap][j];
						b[i - gap][j] = 1;
					} else {
						break;
					}
				}
				gap = 1;
			}
			for (int j = 0 ; j < w; j++){
				b[height][j] = 0;
			}
			height = height + times;

		}
	}

	void Calculate(){
		bool indicator = false;
		int below = 0;
		/* Calculate whether block has moved beyond boundaries */
		pair * pairs = CurrentBlock->getRotation();
		for (int i = 0 ; i< 4; i++){
			int y = pairs[i].y + posiY;
			int x = pairs[i].x + posiX;
			if ((x >= 0) && (x <= 29 ) && (y  <= 39) && (Board[y][x] > 1)){
				unupdate();
				pairs = CurrentBlock->getRotation();
				i = -1;
				below = 0;
				if (count == 0){
					posiY++;
				}
				continue;
			}
			if (y > 39){
				unupdate();
				indicator = true;

				break;

			}
			if ((x < 0) || (x > 29)){
				posiX = posiX - change[0];
			}
			if ((y+1 <= 39) && (x >= 0)  && (x <= 29)&&(Board[y+1][x] > 1)){
				below++;

			}
			if ((below) && (i == 3)){
				indicator = true;
				break;
			}
		}

		int minY = 40;
		int maxY = -1;
		if (indicator){
			for (int i = 0; i < 4; i ++){
				int y = pairs[i].y + posiY;
				int x = pairs[i].x + posiX;
				Board[y][x] = CurrentBlock->getType();
				if (y > maxY){
					maxY = y;
				}
				if (y < minY){
					minY = y;
				}
				if ( y < height){
					height = y;
				}
			}
			delete CurrentBlock;
			CurrentBlock = NextBlock;
			NextBlock = factory->getBlock();
			posiX = 15;
			posiY = 0;
		}

		change[0] = 0;
		change[1] = 0;
		change[2] = 0;

		erase(Board, 40, 30, minY, maxY);
	}

	void unupdate(){
		if (change[0] != 0){
			posiX -= change[0];
		}
		if (change[1] != 0){
				posiY -= change[1];
		}
		if (change[2] != 0 ){
			CurrentBlock->undo();
		}

	}
	void update(){
		if (pressed[0]){
			posiX = posiX - 1;
			change[0]--;
		}
		if (pressed[1]){
			posiX = posiX + 1;
			change[0]++;
		}
		if ((pressed[2]) || (count == 0)){
			posiY = posiY + 1;
			change[1] = 1;
		}
		if ((pressed[3])){
			CurrentBlock->rotate();
			change[2] = 1;
			pressed[3] = false;
		}
	}

public:
	GamePimpl(): change{0,0,0}{
		CurrentScore = 0;
		HighScore = 0;
		level = 1;
		CurrentBlock = NULL;
		NextBlock = NULL;
		Board = new char*[40];
		for(int i = 0; i < 40; ++i) {
		    Board[i] = new char[30]();
		}

		factory = new BlockFactory(level);
		render = new Render();
		quit = false;
		posiX = 15;
		posiY = 0;
		count = 0;
		height = 40;

	}
	~GamePimpl(){
		for (int i = 0; i < 40; i++){
			delete [] Board[i];
		}
		delete [] Board;
		delete render;
		delete factory;

	}

	/* Game Loop */
	void start(){
		NextBlock = factory->getBlock();
		CurrentBlock = factory->getBlock();

		while (!quit){
			count++;
			if (count == 10){
				//posiY = posiY + 1;
				change[1] = 1;
				count = 0;
			}
			//handling key
			handleKey();

			update();
			//do calculation whether erase block or not
			Calculate();

			//render
			render->render(Board, 40 ,30, CurrentBlock, posiX, posiY);
		}
	}
};

Game::Game() : p(new GamePimpl()) {

}

Game::~Game() {
	delete p;
}

void Game::start(){
	p->start();
}

