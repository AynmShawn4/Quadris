/*
 * BlockFactory.cpp
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#include "BlockFactory.h"
#include <stdlib.h>
#include <time.h>

BlockFactory::BlockFactory(int level) : level(level) ,
levels{{25,50,75,100}, {20,40,70,100},{ 15,30,65,100}}{
	 srand (time(NULL));

}

BlockFactory::~BlockFactory() {
}

Block * BlockFactory::getBlock(){
	/* 7 type of blocks, using rand to generate */
	/* not finished */
	int num = rand() % 100;
	int n = rand() % 2;
	Block * ret;
	if (num >= levels[level - 1][1]){
		if ( n == 0){
			ret = new Z();
		} else {
			ret = new IZ();
		}
	} else if (num < levels[level - 1][1]){
		ret = new I();
	}
	return ret;

}
