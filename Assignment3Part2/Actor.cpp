#include "Actor.h"
#include "StudentWorld.h"

//DELETE LATER
#include <string>
#include <iostream>
using namespace std;

Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0) 
	: GraphObject(imageID, startX, startY, dir, depth, size) {
	m_world = world;
	m_walkDirection = dir;
	m_isAlive = true;
	m_impacted = false;
}

StudentWorld* Actor::getWorld() const {
	return m_world;
}

int Actor::getWalkDirection() const {
	return m_walkDirection;
}

bool Actor::getAliveStatus() const {
	return m_isAlive;
}

bool Actor::getImpacted() const {
	return m_impacted;
}

void Actor::setAliveStatus(bool isAlive) {
	m_isAlive = isAlive;
}

void Actor::setWalkDirection(int walkDirection) {
	m_walkDirection = walkDirection;
}

void Actor::setImpacted(bool isImpacted) {
	m_impacted = isImpacted;
}

bool Actor::atFork() const {
	bool fork = false;
	int walkDir = getWalkDirection();
	double xVal = getX();
	double yVal = getY();

	if (getX() % SPRITE_WIDTH != 0 || getY() % SPRITE_HEIGHT != 0) { //in the scenario ur in the middle of walking
		return fork;
	}

	int atLeastTwo = 0;

	switch (walkDir) { //2 out of 3 rule
	case right:
		/*if (canMoveForward(walkDir) && ((getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, ceil((yVal + 2) / (double)SPRITE_HEIGHT)) != Board::empty)
			|| (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, floor((yVal - 2) / (double)SPRITE_HEIGHT)) != Board::empty))) {
			/*cout << "canMoveForward(): " << (canMoveForward() ? "true" : "false") << endl;
			cout << "up: " << ((getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, ceil((yVal + 2) / (double)SPRITE_HEIGHT)) != Board::empty) ? "true" : "false") << endl;
			cout << "xVal, yVal: " << xVal << ", " << yVal << endl;
			cout << "ceil((yVal + 2) / (double)SPRITE_HEIGHT): " << ceil((yVal + 2) / (double)SPRITE_HEIGHT) << endl;
			cout << "down: " << ((getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, floor((yVal - 2) / (double)SPRITE_HEIGHT)) != Board::empty) ? "true" : "false") << endl;
			cout << "at fork right" << endl;
			cout << "fork while moving right" << endl;
			fork = true;
			if (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) == Board::empty) { //ifnothing in back, meaning game started
				fork = false;
			}
		}*/
		if (canMoveForward(walkDir))
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, ceil((yVal + 2) / (double)SPRITE_HEIGHT)) != Board::empty)
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, floor((yVal - 2) / (double)SPRITE_HEIGHT)) != Board::empty)
			atLeastTwo++;
		if (atLeastTwo >= 2) {
			fork = true;
			if (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) == Board::empty) { //ifnothing in back, meaning game started
				fork = false;
			}
			//cout << "fork while moving right" << endl;
		}
		break;
	case left:
		/*if (canMoveForward(walkDir) && ((getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, ceil((yVal + 2) / (double)SPRITE_HEIGHT)) != Board::empty)
			|| (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, floor((yVal - 2) / (double)SPRITE_HEIGHT)) != Board::empty))) {
			//cout << "fork while moving left" << endl;
			fork = true;
		}*/
		if (canMoveForward(walkDir))
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, ceil((yVal + 2) / (double)SPRITE_HEIGHT)) != Board::empty)
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, floor((yVal - 2) / (double)SPRITE_HEIGHT)) != Board::empty)
			atLeastTwo++;
		if (atLeastTwo >= 2) {
			fork = true;
		}
		break;
	case up:
		/*if (canMoveForward(walkDir) && ((getWorld()->getBoard()->getContentsOf(ceil((xVal + 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty)
			|| (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty))) {
			//cout << "fork while moving up" << endl;
			fork = true;
		}*/
		if (canMoveForward(walkDir))
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(ceil((xVal + 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty)
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty)
			atLeastTwo++;
		if (atLeastTwo >= 2) {
			fork = true;
		}
		break;
	case down:
		/*if (canMoveForward(walkDir) && ((getWorld()->getBoard()->getContentsOf(ceil((xVal + 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty)
			|| (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty))) {
			//cout << "fork while moving down" << endl;
			fork = true;
		}*/
		if (canMoveForward(walkDir))
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(ceil((xVal + 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty)
			atLeastTwo++;
		if (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty)
			atLeastTwo++;
		if (atLeastTwo >= 2) {
			fork = true;
		}
		break;
	}

	return fork;
}

int Actor::newWalkDir() {
	//cout << "getX(), getY(): " << getX() << ", " << getY() << endl;
	if (getWalkDirection() == left || getWalkDirection() == right) { //pref up over down
		if (getWorld()->getBoard()->getContentsOf(ceil(getX() / (double)SPRITE_WIDTH), ceil((getY() + 2) / (double)SPRITE_HEIGHT)) != Board::empty) { //if up is valid
			/*cout << "getX(): " << getX() << endl;
			cout << "getY() + 2: " << getY() + 2 << endl;
			cout << "(getY() + 2) / (double)SPRITE_HEIGHT: " << (getY() + 2) / (double)SPRITE_HEIGHT << endl;
			cout << ceil(getX() / (double)SPRITE_WIDTH) << endl;
			cout << ceil((getY() + 2) / (double) SPRITE_HEIGHT) << endl;
			cout << "up is valid" << endl;*/
			setWalkDirection(up);
			return up;
		}
		else { //if up isn't valid go down
			//cout << "down is valid bc up isnt my parents dont love me" << endl;
			setWalkDirection(down);
			return down;
		}
	}
	else { //getWalkDirection() == up or down, pref right over left
		if (getWorld()->getBoard()->getContentsOf(ceil((getX() + 2) / (double)SPRITE_WIDTH), ceil(getY() / (double)SPRITE_HEIGHT)) != Board::empty) { //if right is valid 
			/*cout << "getX() + 2: " << getX() + 2 << endl;
			cout << "getY(): " << getY() << endl;
			cout << "(getX() + 2)/ (double) SPRITE_WIDTH: " << (getX() + 2) / (double)SPRITE_WIDTH << endl;
			cout << ceil((getX() + 2) / (double)SPRITE_WIDTH) << endl;
			cout << ceil(getY() / (double)SPRITE_HEIGHT) << endl;
			cout << "right is valid" << endl;*/
			setWalkDirection(right);
			return right;
		}
		else { //if right isn't valid go left
			//cout << "left is valid bc right isnt and my dad is cheating rn" << endl;
			setWalkDirection(left);
			return left;
		}
	}
}

bool Actor::isSquare() const { //virtual
	return false;
}

bool Actor::isVillain() const { //virtual
	return false;
}

bool Actor::canMoveForward(int walkDir) const {
	bool canMove = false;
	//int walkDir = getWalkDirection();
	double xVal = getX();
	double yVal = getY();
	switch (walkDir) {
	case right:
		if (getWorld()->getBoard()->getContentsOf(ceil((xVal + 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty) {
			canMove = true;
		}
		break;
	case left:
		/*cout << "case is left" << endl;
		cout << "xVal, yVal: " << xVal << ", " << yVal << endl;
		cout << "floor((xVal - 2)/SPRITE_WIDTH): " << floor((xVal - 2) / SPRITE_WIDTH) << endl;
		cout << "ceil(yVal/SPRITE_HEIGHT): " << ceil(yVal / SPRITE_HEIGHT) << endl;*/
		if (getWorld()->getBoard()->getContentsOf(floor((xVal - 2) / (double)SPRITE_WIDTH), yVal / SPRITE_HEIGHT) != Board::empty) {
			//cout << "left can move" << endl;
			canMove = true;
		}
		break;
	case up:
		if (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, ceil((yVal + 2) / (double)SPRITE_HEIGHT)) != Board::empty) {
			canMove = true;
		}
		break;
	case down:
		if (getWorld()->getBoard()->getContentsOf(xVal / SPRITE_WIDTH, floor((yVal - 2) / (double)SPRITE_HEIGHT)) != Board::empty) {
			canMove = true;
		}
		break;
	}

	return canMove;
}

Hero::Hero(StudentWorld* world, int imageID, int playerID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0)
	: Actor(world, imageID, startX, startY, dir, depth, size) {
	m_numCoins = 0;
	m_numStars = 0;
	m_numVortex = 0;
	m_ticksToMove = 0;
	m_diceRoll = 0;
	m_playerID = playerID;
	m_waitToMove = true;
	m_justTP = false;
}

int Hero::getNumCoins() const {
	return m_numCoins;
}

int Hero::getNumStars() const {
	return m_numStars;
}

int Hero::getNumVortex() const {
	return m_numVortex;
}

int Hero::getTicksToMove() const {
	return m_ticksToMove;
}

int Hero::getDiceRolls() const {
	return m_diceRoll;
}

int Hero::getPlayerID() const {
	return m_playerID;
}

bool Hero::getWaitToMove() const {
	return m_waitToMove;
}

bool Hero::getJustTP() const {
	return m_justTP;
}

void Hero::setPlayerID(int playerID) {
	m_playerID = playerID;
}

void Hero::addCoins(int addedCoins) {
	m_numCoins += addedCoins;
	if (m_numCoins < 0) {
		m_numCoins = 0;
	}
}

void Hero::addStar() {
	m_numStars++;
}

void Hero::setStars(int newNumStar) {
	m_numStars = newNumStar;
}

void Hero::removeAllStars() {
	m_numStars = 0;
}

void Hero::giveVortex() {
	m_numVortex++;
	if (m_numVortex > 1) {
		m_numVortex = 1;
	}
}

void Hero::useVortex() {
	//...
	m_numVortex = 0;
}

void Hero::setTicksToMove(int newTicksToMove) {
	m_ticksToMove = newTicksToMove;
}

void Hero::setWaitToMove(bool waitToMoveState) {
	m_waitToMove = waitToMoveState;
}

void Hero::setJustTP(bool didYouTP) {
	m_justTP = didYouTP;
}

void Hero::doSomething() {
	int action = getWorld()->getAction(getPlayerID());

	if (m_waitToMove == true) {
		if (m_justTP && !canMoveForward(getWalkDirection())) {
			m_justTP = false;
			setWalkDirection(newWalkDir());
			if (getWalkDirection() == left) {
				setDirection(left);
			}
			else {
				setDirection(right);
			}
		}
		if (action == ACTION_ROLL) {
			//m_diceRoll = 2;
			m_diceRoll = (rand() % 10) + 1;
			m_ticksToMove = m_diceRoll * 8;
			m_waitToMove = false;
		} if (action == ACTION_FIRE) { 
			if (getNumVortex() >= 1) {
				int shitassX = getX();
				int shitassY = getY();
				getPositionInThisDirection(getWalkDirection(), SPRITE_HEIGHT, shitassX, shitassY);
				shitassX -= shitassX % SPRITE_WIDTH;
				shitassY -= shitassY % SPRITE_HEIGHT;
				getWorld()->addActor(new Vortex(getWorld(), IID_VORTEX, shitassX, shitassY, getWalkDirection(), right, 0, 1.0));
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				useVortex();
			}
		} else {
			return;
		}
	} 

	if (m_waitToMove == false) { //walking state
		int bruhX = getX();
		int bruhY = getY();
		
		if (getWorld()->getBoard()->getContentsOf(bruhX / SPRITE_WIDTH, bruhY / SPRITE_HEIGHT) == Board::up_dir_square 
			|| getWorld()->getBoard()->getContentsOf(bruhX / SPRITE_WIDTH, bruhY / SPRITE_HEIGHT) == Board::down_dir_square
			|| getWorld()->getBoard()->getContentsOf(bruhX / SPRITE_WIDTH, bruhY / SPRITE_HEIGHT) == Board::left_dir_square
			|| getWorld()->getBoard()->getContentsOf(bruhX / SPRITE_WIDTH, bruhY / SPRITE_HEIGHT) == Board::right_dir_square) { //stars
			if (bruhX % SPRITE_WIDTH == 0 && bruhY % SPRITE_HEIGHT == 0) {
				switch (getWorld()->getBoard()->getContentsOf(bruhX / SPRITE_WIDTH, bruhY / SPRITE_HEIGHT)) {
					case (Board::up_dir_square):
						setWalkDirection(up);
						break;
					case (Board::down_dir_square):
						setWalkDirection(down);
						break;
					case (Board::left_dir_square):
						setWalkDirection(left);
						break;
					case (Board::right_dir_square):
						setWalkDirection(right);
						break;
				}

				if (getWalkDirection() == left) {
					setDirection(left);
				} else {
					setDirection(right);
				}
			}
		} else if (atFork()) { 
			//cout << "at fork" << endl;
			if (action == ACTION_RIGHT || action == ACTION_LEFT || action == ACTION_UP || action == ACTION_DOWN) {
				/*cout << "action: " << action << endl;
				cout << "xVal, yVal: " << getX() << ", " << getY() << endl;*/
				int newDir;
				int backDir = (getWalkDirection() + 180) % 360;

				switch (action) {
					case ACTION_RIGHT:
						newDir = right;
						break;
					case ACTION_LEFT:
						newDir = left;
						break;
					case ACTION_UP:
						newDir = up;
						break;
					case ACTION_DOWN:
						newDir = down;
						break;
					default:
						return;
				}

				if (canMoveForward(newDir) && newDir != backDir) {
					//cout << "NENG ZOU CAN MOVE SUPERCARRYDOINBILOVEU" << endl;
					setWalkDirection(newDir);
					if (getWalkDirection() == left) {
						setDirection(left);
					} else {
						setDirection(right);
					}
				} else {
					return;
				}
			} else {
				return;
			}
		} else if (canMoveForward(getWalkDirection()) == false) { 
			//cout << "getWalkDirection(): " << getWalkDirection() << endl;
			if (newWalkDir() == left) {
				setDirection(left);
			} else {
				setDirection(right);
			}
		}
		
		moveAtAngle(getWalkDirection(), 2);
		m_ticksToMove--;
		if (m_ticksToMove == 0) {
			m_waitToMove = true;
		}
	}
}

Villain::Villain(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0)
	: Actor(world, imageID, startX, startY, dir, depth, size) {
	m_travelDist = 0;
	m_pauseCounter = 180;
	m_squaresToMove = 0;
	m_ticksToMove = 0;
	m_isWalking = false;
	m_newPeach = true;
	m_newYoshi = true;
}

int Villain::getTravelDist() const {
	return m_travelDist;
}

int Villain::getPauseCounter() const {
	return m_pauseCounter;
}

int Villain::getSquaresToMove() const {
	return m_squaresToMove;
}

int Villain::getTicksToMove() const {
	return m_ticksToMove;
}

bool Villain::getWalkingState() const {
	return m_isWalking;
}

void Villain::setTravelDist(int newTravelDist) {
	m_travelDist = newTravelDist;
}

void Villain::setPauseCounter(int newPauseCounter) {
	m_pauseCounter = newPauseCounter;
}

void Villain::setSquaresToMove(int newSquaresToMove) {
	m_squaresToMove = newSquaresToMove;
}

void Villain::setTicksToMove(int newTicksToMove) {
	m_ticksToMove = newTicksToMove;
}

void Villain::setWalkingState(int newWalkingState) {
	m_isWalking = newWalkingState;
}

bool Villain::getNewPeach() const {
	return m_newPeach;
}

bool Villain::getNewYoshi() const {
	return m_newYoshi;
}

void Villain::setNewPeach(bool newPeachStatus) {
	m_newPeach = newPeachStatus;
}

void Villain::setNewYoshi(bool newYoshiStatus) {
	m_newYoshi = newYoshiStatus;
}

void Villain::setNewDir() {
	bool newDirChosen = false;

	while (!newDirChosen) {
		int royalNeverGiveUp = (rand() % 4) + 1;
		//cout << royalNeverGiveUp << endl;

		switch (royalNeverGiveUp) {
		case (1): //right
			if (canMoveForward(right)) {
				newDirChosen = true;
				setWalkDirection(right);
			}
			break;
		case (2): //left
			if (canMoveForward(left)) {
				newDirChosen = true;
				setWalkDirection(left);
			}
			break;
		case (3): //up
			if (canMoveForward(up)) {
				newDirChosen = true;
				setWalkDirection(up);
			}
			break;
		case (4): //down
			if (canMoveForward(down)) {
				newDirChosen = true;
				setWalkDirection(down);
			}
			break;
		}
	}
}

bool Villain::isVillain() const { //virtual
	return true;
}

void Villain::doSomething() { //virtual

}

Bowser::Bowser(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0) 
	: Villain(world, imageID, startX, startY, dir, depth, size) {

}

void Bowser::doSomething() { //virtual
	if (!getWalkingState()) { //if it's paused
		if (getNewPeach() && getWorld()->getPeach()->getWaitToMove() //in waiting to roll state
			&& getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) {
			int coinFlipPeach = (rand() % 2) + 1; //random number 1 or 2
			//cout << "touchy touchie ;)" << endl;

			if (coinFlipPeach == 1) {
				//cout << "nom nom nom" << endl;
				getWorld()->getPeach()->addCoins(-getWorld()->getPeach()->getNumCoins());
				getWorld()->getPeach()->removeAllStars();
				getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
			}

			setNewPeach(false); //no repeat trigger
		} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
			setNewPeach(true);
		}

		if (getNewYoshi() && getWorld()->getYoshi()->getWaitToMove() //in waiting to roll state
			&& getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) {
			int coinFlipYoshi = (rand() % 2) + 1; //random number 1 or 2
			//cout << "touchy touchie ;)" << endl;

			if (coinFlipYoshi == 1) {
				//cout << "nom nom nom" << endl;
				getWorld()->getYoshi()->addCoins(-getWorld()->getYoshi()->getNumCoins());
				getWorld()->getYoshi()->removeAllStars();
				getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
			}

			setNewYoshi(false); //no repeat trigger
		} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
			setNewYoshi(true);
		}

		setPauseCounter(getPauseCounter() - 1);

		if (getPauseCounter() == 0) {
			setSquaresToMove((rand() % 10) + 1);
			setTicksToMove(getSquaresToMove() * 8);
			setNewDir();

			if (getWalkDirection() == left) {
				setDirection(left);
			} else {
				setDirection(right);
			}

			setWalkingState(true);
		} 
	}

	if (getWalkingState()) { //is currently walking
		if (atFork()) {
			setNewDir();

			if (getWalkDirection() == left) {
				setDirection(left);
			}
			else {
				setDirection(right);
			}
		} else if (canMoveForward(getWalkDirection()) == false) {
			if (newWalkDir() == left) {
				setDirection(left);
			}
			else {
				setDirection(right);
			}
		}

		moveAtAngle(getWalkDirection(), 2);
		setTicksToMove(getTicksToMove() - 1);

		if (getTicksToMove() == 0) {
			setWalkingState(false);
			setPauseCounter(180);

			int bruh = (rand() % 4) + 1;
			if (bruh == 1) { //25% chance
				int vectorSize = getWorld()->getVectorSize();
				for (int i = 0; i < vectorSize; i++) {
					Actor* currActor = getWorld()->getActorAtIndex(i);
					if (currActor->getX() == getX() && currActor->getY() == getY() && currActor->isSquare()) {
						currActor->setAliveStatus(false);
						getWorld()->addActor(new DropSquare(getWorld(), IID_DROPPING_SQUARE, getX(), getY(), right, 1, 1.0));
					}
				}
				getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
			}
		}
	}

	if (getImpacted() == true) {
		while (true) {
			int randXP = (rand() % 16); //random thru 0 to 15
			int randYP = (rand() % 16);

			if (getWorld()->getBoard()->getContentsOf(randXP, randYP) != Board::empty) {
				moveTo(randXP * SPRITE_WIDTH, randYP * SPRITE_HEIGHT);
				break;
			}
		}

		setWalkDirection(right);
		setDirection(right);
		setWalkingState(false);
		setPauseCounter(180);
		setImpacted(false);
	}
}

Boo::Boo(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0)
	: Villain(world, imageID, startX, startY, dir, depth, size) {

}

void Boo::doSomething() { //virtual
	if (!getWalkingState()) { //if it's paused
		if (getNewPeach() && getWorld()->getPeach()->getWaitToMove() //in waiting to roll state
			&& getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) {
			int coinFlipPeach = (rand() % 2) + 1; //random number 1 or 2

			if (coinFlipPeach == 1) {//SWAP COINS
				int tempCoinsPeach = getWorld()->getPeach()->getNumCoins();
				getWorld()->getPeach()->addCoins(-tempCoinsPeach + getWorld()->getYoshi()->getNumCoins());
				getWorld()->getYoshi()->addCoins(-getWorld()->getYoshi()->getNumCoins() + tempCoinsPeach);
			} else { //SWAP STARS
				int tempStarsPeach = getWorld()->getPeach()->getNumStars();
				getWorld()->getPeach()->removeAllStars();
				getWorld()->getPeach()->setStars(getWorld()->getYoshi()->getNumStars());
				getWorld()->getYoshi()->removeAllStars();
				getWorld()->getYoshi()->setStars(tempStarsPeach);
			}

			getWorld()->playSound(SOUND_BOO_ACTIVATE);
			setNewPeach(false); //no repeat trigger
		} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
			setNewPeach(true);
		}

		if (getNewYoshi() && getWorld()->getYoshi()->getWaitToMove() //in waiting to roll state
			&& getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) {
			int coinFlipYoshi = (rand() % 2) + 1; //random number 1 or 2

			if (coinFlipYoshi == 1) { //SWAP COINS
				int tempCoinsYoshi = getWorld()->getYoshi()->getNumCoins();
				getWorld()->getYoshi()->addCoins(-tempCoinsYoshi + getWorld()->getPeach()->getNumCoins());
				getWorld()->getPeach()->addCoins(-getWorld()->getPeach()->getNumCoins() + tempCoinsYoshi);
			} else { //SWAP STARS
				int tempStarsYoshi = getWorld()->getYoshi()->getNumStars();
				getWorld()->getYoshi()->removeAllStars();
				getWorld()->getYoshi()->setStars(getWorld()->getPeach()->getNumStars());
				getWorld()->getPeach()->removeAllStars();
				getWorld()->getPeach()->setStars(tempStarsYoshi);
			}

			getWorld()->playSound(SOUND_BOO_ACTIVATE);
			setNewYoshi(false); //no repeat trigger
		} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
			setNewYoshi(true);
		}

		setPauseCounter(getPauseCounter() - 1);

		if (getPauseCounter() == 0) {
			setSquaresToMove((rand() % 3) + 1);
			setTicksToMove(getSquaresToMove() * 8);
			setNewDir();

			if (getWalkDirection() == left) {
				setDirection(left);
			}
			else {
				setDirection(right);
			}

			setWalkingState(true);
		}
	}

	if (getWalkingState()) { //is currently walking
		if (atFork()) {
			setNewDir();

			if (getWalkDirection() == left) {
				setDirection(left);
			}
			else {
				setDirection(right);
			}
		}
		else if (canMoveForward(getWalkDirection()) == false) {
			if (newWalkDir() == left) {
				setDirection(left);
			}
			else {
				setDirection(right);
			}
		}

		moveAtAngle(getWalkDirection(), 2);
		setTicksToMove(getTicksToMove() - 1);

		if (getTicksToMove() == 0) {
			setWalkingState(false);
			setPauseCounter(180);
		}
	}

	if (getImpacted() == true) {
		while (true) {
			int randXP = (rand() % 16); //random thru 0 to 15
			int randYP = (rand() % 16);

			if (getWorld()->getBoard()->getContentsOf(randXP, randYP) != Board::empty) {
				moveTo(randXP * SPRITE_WIDTH, randYP * SPRITE_HEIGHT);
				break;
			}
		}

		setWalkDirection(right);
		setDirection(right);
		setWalkingState(false);
		setPauseCounter(180);
		setImpacted(false);
	}
}

Square::Square(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 1, double size = 1.0) 
	: Actor(world, imageID, startX, startY, dir, depth, size) {
	m_newPeach = true;
	m_newYoshi = true;
}

bool Square::getNewPeach() const {
	return m_newPeach;
}

bool Square::getNewYoshi() const {
	return m_newYoshi;
}

void Square::setNewPeach(bool newPeachStatus) {
	m_newPeach = newPeachStatus;
}

void Square::setNewYoshi(bool newYoshiStatus) {
	m_newYoshi = newYoshiStatus;
}

bool Square::isSquare() const {
	return true;
}

void Square::doSomething() { //virtual

}

CoinSquare::CoinSquare(StudentWorld* world, int coinID, int imageID, int startX, int startY, int dir = right, int depth = 1, double size = 1.0)
	: Square(world, imageID, startX, startY, dir, depth, size) {
	m_coinID = coinID;
	m_coinOperation = (coinID == IID_BLUE_COIN_SQUARE)? 3 : -3;
}

int CoinSquare::getCoinID() const {
	return m_coinID;
}

void CoinSquare::setCoinID(int coinID) {
	m_coinID = coinID;
}

void CoinSquare::doSomething() {
	if (!getAliveStatus()) {
		return;
	}

	if (getWorld()->getPeach()->getTicksToMove() == 0 && getNewPeach() 
		&& getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) { //for peach
		getWorld()->getPeach()->addCoins(m_coinOperation);
		getWorld()->playSound((m_coinOperation == 3)? SOUND_GIVE_COIN : SOUND_TAKE_COIN);
		setNewPeach(false);
	} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
		setNewPeach(true);
	}

	if (getWorld()->getYoshi()->getTicksToMove() == 0 && getNewYoshi() 
		&& getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) { //for yoshi
		getWorld()->getYoshi()->addCoins(m_coinOperation);
		getWorld()->playSound((m_coinOperation == 3) ? SOUND_GIVE_COIN : SOUND_TAKE_COIN);
		setNewYoshi(false);
	} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
		setNewYoshi(true);
	}
}

StarSquare::StarSquare(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 1, double size = 1.0)
	: Square(world, imageID, startX, startY, dir, depth, size){
	m_negTwentyCoin = -20;
}

void StarSquare::doSomething() { //virtual
	if (getNewPeach()
		&& getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) { //for peach
		if (getWorld()->getPeach()->getNumCoins() < 20) {
			return;
		} else {
			getWorld()->getPeach()->addCoins(m_negTwentyCoin);
			getWorld()->getPeach()->addStar();
			getWorld()->playSound(SOUND_GIVE_STAR);
		}
		setNewPeach(false);
	} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
		setNewPeach(true);
	}

	if (getNewYoshi()
		&& getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) { //for yoshi
		if (getWorld()->getYoshi()->getNumCoins() < 20) {
			return;
		} else {
			getWorld()->getYoshi()->addCoins(m_negTwentyCoin);
			getWorld()->getYoshi()->addStar();
			getWorld()->playSound(SOUND_GIVE_STAR);
		}
		setNewYoshi(false);
	} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
		setNewYoshi(true);
	}
}

EventSquare::EventSquare(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 1, double size = 1.0)
	: Square(world, imageID, startX, startY, dir, depth, size) {

}

void EventSquare::doSomething() { //virtual
	int scenarioP = (rand() % 3) + 1; //random number between 1 and 3
	int scenarioY = (rand() % 3) + 1;

	if (getNewPeach() && getWorld()->getPeach()->getTicksToMove() == 0
		&& getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) {
		switch (scenarioP) {
			case (1): //tp
			{
				while (true) {
					int randXP = (rand() % 16); //random thru 0 to 15
					int randYP = (rand() % 16);
					if (getWorld()->getBoard()->getContentsOf(randXP, randYP) != Board::empty) {
						getWorld()->getPeach()->moveTo(randXP * SPRITE_WIDTH, randYP * SPRITE_HEIGHT);
						getWorld()->getPeach()->setJustTP(true);
						getWorld()->playSound(SOUND_PLAYER_TELEPORT);
						break;
					}
				}
			}
				break;
			case (2): //swap
			{
				int tempXPeach = getWorld()->getPeach()->getX();
				int tempYPeach = getWorld()->getPeach()->getY();
				int tempTicksPeach = getWorld()->getPeach()->getTicksToMove();
				int tempWalkDirPeach = getWorld()->getPeach()->getWalkDirection();
				int tempSpriteDirPeach = getWorld()->getPeach()->getDirection();
				bool tempWaitToMovePeach = getWorld()->getPeach()->getWaitToMove(); //true: waiting to move | false: walking

				getWorld()->getPeach()->moveTo(getWorld()->getYoshi()->getX(), getWorld()->getYoshi()->getY());
				getWorld()->getPeach()->setTicksToMove(getWorld()->getYoshi()->getTicksToMove());
				getWorld()->getPeach()->setWalkDirection(getWorld()->getYoshi()->getWalkDirection());
				getWorld()->getPeach()->setDirection(getWorld()->getYoshi()->getDirection());
				getWorld()->getPeach()->setWaitToMove(getWorld()->getYoshi()->getWaitToMove());

				getWorld()->getYoshi()->moveTo(tempXPeach, tempYPeach);
				getWorld()->getYoshi()->setTicksToMove(tempTicksPeach);
				getWorld()->getYoshi()->setWalkDirection(tempWalkDirPeach);
				getWorld()->getYoshi()->setDirection(tempSpriteDirPeach);
				getWorld()->getYoshi()->setWaitToMove(tempWaitToMovePeach);

				getWorld()->playSound(SOUND_PLAYER_TELEPORT);
				setNewYoshi(false); //doesn't trigger on yoshi
			}
				break;
			case (3): //vortex
			{
				if (getWorld()->getPeach()->getNumVortex() == 0) {
					//cout << "vortex given" << endl;
					getWorld()->getPeach()->giveVortex();
					getWorld()->playSound(SOUND_GIVE_VORTEX);
				}
			}
				break;
		}
		setNewPeach(false);
	} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
		setNewPeach(true);
	}

	if (getNewYoshi() && getWorld()->getYoshi()->getTicksToMove() == 0
		&& getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) {
		switch (scenarioY) {
			case (1): //tp
			{
				while (true) {
					int randXY = (rand() % 16); //random thru 0 to 15
					int randYY = (rand() % 16);
					if (getWorld()->getBoard()->getContentsOf(randXY, randYY) != Board::empty) {
						getWorld()->getYoshi()->moveTo(randXY * SPRITE_WIDTH, randYY * SPRITE_HEIGHT);
						getWorld()->getYoshi()->setJustTP(true);
						getWorld()->playSound(SOUND_PLAYER_TELEPORT);
						break;
					}
				}
			}
				break;
			case (2): //swap
			{
				int tempXYoshi = getWorld()->getYoshi()->getX();
				int tempYYoshi = getWorld()->getYoshi()->getY();
				int tempTicksYoshi = getWorld()->getYoshi()->getTicksToMove();
				int tempWalkDirYoshi = getWorld()->getYoshi()->getWalkDirection();
				int tempSpriteDirYoshi = getWorld()->getYoshi()->getDirection();
				bool tempWaitToMoveYoshi = getWorld()->getYoshi()->getWaitToMove(); //true: waiting to move | false: walking

				getWorld()->getYoshi()->moveTo(getWorld()->getPeach()->getX(), getWorld()->getPeach()->getY());
				getWorld()->getYoshi()->setTicksToMove(getWorld()->getPeach()->getTicksToMove());
				getWorld()->getYoshi()->setWalkDirection(getWorld()->getPeach()->getWalkDirection());
				getWorld()->getYoshi()->setDirection(getWorld()->getPeach()->getDirection());
				getWorld()->getYoshi()->setWaitToMove(getWorld()->getPeach()->getWaitToMove());

				getWorld()->getPeach()->moveTo(tempXYoshi, tempYYoshi);
				getWorld()->getPeach()->setTicksToMove(tempTicksYoshi);
				getWorld()->getPeach()->setWalkDirection(tempWalkDirYoshi);
				getWorld()->getPeach()->setDirection(tempSpriteDirYoshi);
				getWorld()->getPeach()->setWaitToMove(tempWaitToMoveYoshi);

				getWorld()->playSound(SOUND_PLAYER_TELEPORT);
				setNewPeach(false); //doesn't trigger on peach
			}
				break;
			case (3): //vortex
			{
				if (getWorld()->getYoshi()->getNumVortex() == 0) {
					//cout << "vortex given" << endl;
					getWorld()->getYoshi()->giveVortex();
					getWorld()->playSound(SOUND_GIVE_VORTEX);
				}
			}
				break;
			}
		setNewYoshi(false);
	} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
		setNewYoshi(true);
	}
}

BankSquare::BankSquare(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 1, double size = 1.0)
	: Square(world, imageID, startX, startY, dir, depth, size) {
	m_uncleSamSuckingMeDry = -5;
}

void BankSquare::doSomething() {
	if (getNewPeach() && getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) {
		if (getWorld()->getPeach()->getTicksToMove() == 0) { //landed on
			getWorld()->getPeach()->addCoins(getWorld()->getBankBalance());
			getWorld()->setBank(0);
			getWorld()->playSound(SOUND_WITHDRAW_BANK);
		}
		else { //on the run
			int coinsTaxedPeach;
			if (getWorld()->getPeach()->getNumCoins() < m_uncleSamSuckingMeDry) {
				coinsTaxedPeach = getWorld()->getPeach()->getNumCoins();
			}
			else {
				coinsTaxedPeach = -m_uncleSamSuckingMeDry;
			}
			getWorld()->getPeach()->addCoins(m_uncleSamSuckingMeDry);
			getWorld()->setBank(getWorld()->getBankBalance() + coinsTaxedPeach);
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
		setNewPeach(false);
	} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
		setNewPeach(true);
	}

	if (getNewYoshi() && getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) {
		if (getWorld()->getYoshi()->getTicksToMove() == 0) { //landed on
			getWorld()->getYoshi()->addCoins(getWorld()->getBankBalance());
			getWorld()->setBank(0);
			getWorld()->playSound(SOUND_WITHDRAW_BANK);
		}
		else { //on the run
			int coinsTaxedYoshi;
			if (getWorld()->getYoshi()->getNumCoins() < m_uncleSamSuckingMeDry) {
				coinsTaxedYoshi = getWorld()->getYoshi()->getNumCoins();
			}
			else {
				coinsTaxedYoshi = -m_uncleSamSuckingMeDry;
			}
			getWorld()->getYoshi()->addCoins(m_uncleSamSuckingMeDry);
			getWorld()->setBank(getWorld()->getBankBalance() + coinsTaxedYoshi);
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
		setNewYoshi(false);
	} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
		setNewYoshi(true);
	}
}

DirectionSquare::DirectionSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth = 1, double size = 1.0) 
	: Square(world, imageID, startX, startY, dir, depth, size) {
	m_forceDir = dir;
}

int DirectionSquare::getForceDir() const {
	return m_forceDir;
}

void DirectionSquare::doSomething() {
	/*if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) { //for peach
		getWorld()->getPeach()->setWalkDirection(m_forceDir);
		//cout << "set walk direction" << endl;
		if (getWorld()->getPeach()->atFork()) {
			switch (m_forceDir) {
				case right:

					break;
				case left:

					break;
				case up:

					break; 
				case down:

					break;
			}
		}
		if (getWorld()->getPeach()->getWalkDirection() == left) {
			getWorld()->getPeach()->setDirection(left);
		} else {
			getWorld()->getPeach()->setDirection(right);
		}
	}

	if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) { //for yoshi
		getWorld()->getYoshi()->setWalkDirection(m_forceDir);
		//cout << "set walk direction" << endl;
		if (getWorld()->getYoshi()->atFork()) {

		}
		if (getWorld()->getYoshi()->getWalkDirection() == left) {
			getWorld()->getYoshi()->setDirection(left);
		} else {
			getWorld()->getYoshi()->setDirection(right);
		}
	}*/
}

DropSquare::DropSquare(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 1, double size = 1.0) 
	: Square(world, imageID, startX, startY, dir, depth, size) { //HAVE NOT TESTED BC NOT MADE
	m_bruh = -10;
}

void DropSquare::doSomething() { //virtual
	if (getWorld()->getPeach()->getTicksToMove() == 0 && getNewPeach()
		&& getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) { //for peach
		getWorld()->getPeach()->addCoins(m_bruh);
		getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
		setNewPeach(false);
	} if (getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY()) {
		setNewPeach(true);
	}

	if (getWorld()->getYoshi()->getTicksToMove() == 0 && getNewYoshi()
		&& getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) { //for yoshi
		getWorld()->getYoshi()->addCoins(m_bruh);
		getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
		setNewYoshi(false);
	} if (getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY()) {
		setNewYoshi(true);
	}
}

Vortex::Vortex(StudentWorld* world, int imageID, int startX, int startY, int travelDir, int dir = right, int depth = 0, double size = 1.0) 
	: Actor(world, imageID, startX, startY, dir, depth, size) {
	m_travelDir = travelDir;
}

void Vortex::doSomething() { //virtual
	if (!getAliveStatus()) {
		return;
	}

	moveAtAngle(m_travelDir, 2);

	if (getX() < 0 || VIEW_WIDTH <= getX() || getY() < 0 || VIEW_HEIGHT <= getY()) { //outta bounds, dead vortex
		setAliveStatus(false); //you dead bitch
	}

	int vectorSize = getWorld()->getVectorSize();

	for (int i = 0; i < vectorSize; i++) {
		Actor* currActor = getWorld()->getActorAtIndex(i);
		if (currActor->isVillain()) { //hit a villain
			if (currActor->getX() - SPRITE_WIDTH <= getX() && getX() <= currActor->getX() + SPRITE_WIDTH
				&& currActor->getY() - SPRITE_HEIGHT <= getY() && getY() <= currActor->getY() + SPRITE_HEIGHT) {
				//cout << "SKT1 IMPACT!!!" << endl;
				currActor->setImpacted(true);
				setAliveStatus(false); //kys
				getWorld()->playSound(SOUND_HIT_BY_VORTEX);
			}
		}
	}
}