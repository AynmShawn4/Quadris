/*
 * Block.cpp
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#include "Block.h"

Block::Block(char t) {
	type = t;
	current = 0;
}

Block::~Block() {

}

void Block::undo(){
	current = current + 4;
	current = current - 1;
	current = current % 4;
}
char Block::getType(){
	return this->type;
}

Z::Z(): Block('z'),
		rot{ {{0,0},{0,1},{1,1},{1,2}},
			 {{0,2},{1,1},{1,2},{2,1}},
			 {{},{},{},{}},{{},{},{},{}}}{
}

Z::~Z(){
	//delete state
}

pair * Z::getRotation(){
	return rot[current];
}

void Z::rotate(){
	current = current + 1;
	current = current % 2;
}


IZ::IZ(): Block('Z'),
		rot{ {{0,1},{0,2},{1,0},{1,1}},
	 	   {{0,1},{1,1},{1,2},{2,2}},
	 	   {{},{},{},{}},{{},{},{},{}}}{
}

IZ::~IZ(){

}
pair * IZ::getRotation(){

	return rot[current];
}



void IZ::rotate(){
	current = current + 1;
	current = current % 2;
}

I::I(): Block('I'),
		rot{ {{0,0},{0,1},{0,2},{0,3}},
	 	   {{0,2},{1,2},{2,2},{3,2}},
	 	   {{},{},{},{}},{{},{},{},{}}}{
}

I::~I(){

}
pair * I::getRotation(){
	return rot[current];
}



void I::rotate(){
	current = current + 1;
	current = current % 2;
}
