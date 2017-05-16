/*
 * Game.h
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#ifndef GAME_H_
#define GAME_H_

/*used pimpl idiom */

class Game {
private:
	class GamePimpl;
	GamePimpl * p;
public:
	Game();
	void start();
	virtual ~Game();
};

#endif /* GAME_H_ */
