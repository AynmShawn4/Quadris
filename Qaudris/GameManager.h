/*
 * GameManager.h
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Game.h"

class GameManager {
private:
	Game * g;
public:
	GameManager();
	void start();
	virtual ~GameManager();
};

#endif /* GAMEMANAGER_H_ */
