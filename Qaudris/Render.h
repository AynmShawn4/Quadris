/*
 * Render.h
 *
 *  Created on: 2017Äê5ÔÂ14ÈÕ
 *      Author: ShawnTang
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <SDL2/SDL.h>
#include "Block.h"


class Render {
private:
	SDL_Window * w;
	SDL_Renderer * r;
public:
	Render();
	void init();
	void render( char ** c, int w, int h, Block * b, int x, int y);
	virtual ~Render();
};

#endif /* RENDER_H_ */
