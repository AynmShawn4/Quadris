/*
 * GameManager.cpp
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#include "GameManager.h"

GameManager::GameManager(): g(new Game()) {

	//initializing Game Board, state

}

GameManager::~GameManager() {
	delelte g;
	// TODO Auto-generated destructor stub
}

void GameManager::start(){

	g->start();

}
