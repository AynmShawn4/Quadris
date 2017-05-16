/*
 * Block.h
 *
 *  Created on: 2017 May 14th
 *      Author: ShawnTang
 */

#ifndef BLOCK_H_
#define BLOCK_H_

struct pair{
	int x;
	int y;

};
class Block {
	char type;
protected:
	int current;

public:
	char getType();
	Block(char t);
	void undo() ;
	virtual void rotate() = 0;
	virtual pair * getRotation() = 0;
	virtual ~Block();
};

/* ZZ
 *  ZZ
 */
class Z : public Block{
	pair rot[4][4];
public:
	Z();
	void rotate();
	pair * getRotation();
	~Z();
};

/*  ZZ
 * ZZ
 */
class IZ : public Block{
	pair rot[4][4];
public:
	IZ();
	void rotate();
	pair * getRotation();
	~IZ();
};

/* IIII */
class I : public Block{
	pair rot[4][4];
public:
	I();
	void rotate();
	pair * getRotation();
	~I();
};
#endif /* BLOCK_H_ */
/*
class O : public Block{
	O();
	void rotate();
	~O();
};

class I : public Block{
	I();
	void rotate();
	~I();
};

class L : public Block{
	L();
	void rotate();
	~L();
};



class A : public Block{
	A();
	void rotate();
	~A();
};*/




