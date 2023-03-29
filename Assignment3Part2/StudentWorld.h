#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>

class StudentWorld : public GameWorld {
public:
	StudentWorld(std::string assetPath);
	virtual ~StudentWorld();
	Board* getBoard() const;
	Hero* getPeach() const;
	Hero* getYoshi() const;
	Actor* getActorAtIndex(int index) const;
	int getVectorSize() const;
	int getBankBalance() const;
	void setBank(int addAmt);
	void addActor(Actor* newActor);
	virtual int init();
	virtual int move();
	virtual void cleanUp();

private:
	Hero* m_peach;
	Hero* m_yoshi;
	Board* m_board;
	int m_bank;
	std::vector<Actor*> actorVector;
};

#endif // STUDENTWORLD_H_
