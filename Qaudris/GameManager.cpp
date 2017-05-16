/*
 * GameManager.cpp
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#include "GameManager.h"

GameManager::GameManager(): g(new Game()) {

}

GameManager::~GameManager() {
	delelte g;
}

void GameManager::start(){

	g->start();

}
