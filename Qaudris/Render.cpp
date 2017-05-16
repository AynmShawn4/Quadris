/*
 * Render.cpp
 *
 *  Created on: 2017Äê5ÔÂ14ÈÕ
 *      Author: ShawnTang
 */

#include "Render.h"
#include <iostream>

/*using SDL2 to draw */
struct pair;

Render::Render() {
	w = SDL_CreateWindow
		    (
		        "Windows", SDL_WINDOWPOS_UNDEFINED,
		        SDL_WINDOWPOS_UNDEFINED,
		        600,
		        800,
		        SDL_WINDOW_SHOWN
		    );
	r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	init();
}

void Render::init(){
	/* do initialization */
	SDL_SetRenderDrawColor( r, 255, 255, 255, 255 );
}


void Render::render(char ** c, int h, int w, Block * b, int px, int py){
		/* h = 40, w = 30 */
		SDL_RenderClear( r );
		/* Draw Static Grid */
		for (int i = 0 ; i < h ; i ++){
			for (int j = 0; j < w; j++){
				SDL_Rect block;
				block.x = j * 20;
				block.y =  i* 20;
				block.w = 20;
				block.h = 20;
				if (c[i][j] == 'Z'){
					SDL_SetRenderDrawColor( r, 233, 22, 2, 222 );
				} else if (c[i][j] == 'z'){
					SDL_SetRenderDrawColor( r, 255, 255, 15, 120 );
				} else if (c[i][j] == 'I'){
					SDL_SetRenderDrawColor( r, 2, 19, 25, 120 );
				} else {
					SDL_SetRenderDrawColor( r, 255, 255, 255, 120 );
				}
				SDL_RenderFillRect( r, &block );
			}
		}
		/* Draw Moving Block */
		pair * pairs = b->getRotation();
		for (int i = 0 ; i< 4; i++){
			int y = pairs[i].y + py;
			int x = pairs[i].x + px;
			SDL_Rect block;
			block.x = x * 20;
			block.y = y * 20;
			block.w = 20;
			block.h = 20;
			if (b->getType() == 'Z'){
				SDL_SetRenderDrawColor( r, 233, 22, 2, 222 );
			} else if (b->getType() == 'z'){
				SDL_SetRenderDrawColor( r, 255, 255, 15, 120 );
			}else if (b->getType() == 'I'){
				SDL_SetRenderDrawColor( r, 2, 19, 25, 120 );
			} else {
				SDL_SetRenderDrawColor( r, 255, 255, 15, 120 );
			}
			SDL_RenderFillRect( r, &block );
		}
		SDL_RenderPresent(r);
}

Render::~Render() {
	/* cleanup */
	 SDL_DestroyWindow(w);
	 SDL_Quit();

}

