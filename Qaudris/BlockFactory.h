/*
 * BlockFactory.h
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#ifndef BLOCKFACTORY_H_
#define BLOCKFACTORY_H_

#include "Block.h"

class BlockFactory {
private:
	int level;
	int levels[3][4];

public:
	BlockFactory(int l);
	Block * getBlock();
	virtual ~BlockFactory();
};

#endif /* BLOCKFACTORY_H_ */
