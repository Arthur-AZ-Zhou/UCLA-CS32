#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

class StudentWorld;

class Actor : public GraphObject { //Hero, Villain, Square
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	StudentWorld* getWorld() const;
	int getWalkDirection() const;
	bool getAliveStatus() const;
	bool getImpacted() const;
	void setAliveStatus(bool isAlive);
	void setWalkDirection(int walkDirection);
	void setImpacted(bool isImpacted);
	bool atFork() const;
	int newWalkDir();
	virtual bool isSquare() const;
	virtual bool isVillain() const;
	virtual bool canMoveForward(int walkDir) const;
	virtual void doSomething() = 0;
private:
	StudentWorld* m_world; //floating pointer after deletion?
	int m_walkDirection; //just let it sit there for squares?
	bool m_isAlive;
	bool m_impacted; //false if not hit, true if hit
};

class Hero : public Actor { //Peach and Yoshi
public: 
	static const int PEACH = 1;
	static const int YOSHI = 2;

	Hero(StudentWorld* world, int imageID, int playerID, int startX, int startY, int dir, int depth, double size);
	int getNumCoins() const;
	int getNumStars() const;
	int getNumVortex() const;
	int getTicksToMove() const;
	int getDiceRolls() const;
	int getPlayerID() const;
	bool getWaitToMove() const;
	bool getJustTP() const;
	void setPlayerID(int playerID);
	void addCoins(int addedCoins);
	void addStar();
	void setStars(int newNumStar);
	void removeAllStars();
	void giveVortex();
	void useVortex();
	void setTicksToMove(int newTicksToMove);
	void setWaitToMove(bool waitToMoveState);
	void setJustTP(bool didYouTP);
	virtual void doSomething();
private: 
	int m_numCoins;
	int m_numStars;
	int m_numVortex;
	int m_ticksToMove;
	int m_diceRoll;
	int m_playerID;
	bool m_waitToMove; //true: waiting to move, false: walking
	bool m_justTP;
};

class Villain : public Actor { //Bowser and Boo
public: 
	Villain(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	int getTravelDist() const;
	int getPauseCounter() const;
	int getSquaresToMove() const;
	int getTicksToMove() const;
	bool getWalkingState() const;
	void setTravelDist(int newTravelDist);
	void setPauseCounter(int newPauseCounter);
	void setSquaresToMove(int newSquaresToMove);
	void setTicksToMove(int ticksToMove);
	void setWalkingState(int newWalkingState);
	bool getNewPeach() const;
	bool getNewYoshi() const;
	void setNewPeach(bool newPeachStatus);
	void setNewYoshi(bool newYoshiStatus);
	void setNewDir();
	virtual bool isVillain() const;
	virtual void doSomething();
private: 
	int m_travelDist;
	int m_pauseCounter;
	int m_squaresToMove;
	int m_ticksToMove;
	bool m_isWalking; //true if walking, false if paused
	bool m_newPeach;
	bool m_newYoshi;
};

class Bowser : public Villain {
public:
	Bowser(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual void doSomething();
private:

};

class Boo : public Villain {
public:
	Boo(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual void doSomething();
private:

};

class Square : public Actor { //CoinSquare, StarSquare*, EventSquare, BankSquare*, DirectionSquare*, DropSquare
public: 
	Square(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	bool getNewPeach() const;
	bool getNewYoshi() const;
	void setNewPeach(bool newPeachStatus);
	void setNewYoshi(bool newYoshiStatus);
	virtual bool isSquare() const;
	virtual void doSomething();
private:
	bool m_newPeach;
	bool m_newYoshi;
};

class CoinSquare : public Square {
public: 
	CoinSquare(StudentWorld* world, int coinID, int imageID, int startX, int startY, int dir, int depth, double size);
	int getCoinID() const;
	void setAliveStatus(bool isAlive);
	void setCoinID(int coinID);
	virtual void doSomething();
private: 
	int m_coinID;
	int m_coinOperation; //3 or -3 to add or subtract 3 coins, differentiates blue or red
};

class StarSquare : public Square { //lands on and onto trigger
public:
	StarSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual void doSomething();
private:
	int m_negTwentyCoin;
};

class EventSquare : public Square {
public:
	EventSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual void doSomething();
private:

};

class BankSquare : public Square { //lands on and onto trigger
public:
	BankSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual void doSomething();
private:
	int m_uncleSamSuckingMeDry;
};

class DirectionSquare : public Square { //lands on and onto trigger
public:
	DirectionSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	int getForceDir() const;
	virtual void doSomething();
private:
	int m_forceDir;
};

class DropSquare : public Square {
public:
	DropSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size);
	virtual void doSomething();
private:
	int m_bruh;
};

class Vortex : public Actor {
public: 
	Vortex(StudentWorld* world, int imageID, int startX, int startY, int travelDir, int dir, int depth, double size);
	virtual void doSomething();
private: //use m_isAlive as active state
	int m_travelDir;
};

#endif // ACTOR_H_
