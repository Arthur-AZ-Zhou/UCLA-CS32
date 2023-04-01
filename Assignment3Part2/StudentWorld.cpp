#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath) { //don't edit
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath) {
    m_board = nullptr;
    m_peach = nullptr;
    m_yoshi = nullptr;
    m_bank = 0;
}

StudentWorld::~StudentWorld() { //virtual, iterate thru vector to delete dynamically allocated pointers
    cleanUp();
    delete m_board;
}

Board* StudentWorld::getBoard() const {
    return m_board;
}

Hero* StudentWorld::getPeach() const {
    return m_peach;
}

Hero* StudentWorld::getYoshi() const {
    return m_yoshi;
}

Actor* StudentWorld::getActorAtIndex(int index) const {
    return actorVector[index];
}

int StudentWorld::getVectorSize() const {
    return actorVector.size();
}

int StudentWorld::getBankBalance() const {
    return m_bank;
}

void StudentWorld::setBank(int setAmt) {
    m_bank = setAmt;
}

void StudentWorld::addActor(Actor* newActor) {
    actorVector.push_back(newActor);
}

int StudentWorld::init() { //virtual
	startCountdownTimer(99);
    m_board = new Board();
    string boardFile = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
    Board::LoadResult result = m_board->loadBoard(boardFile);

    if (result == Board::load_fail_bad_format || result == Board::load_fail_file_not_found) {
        return GWSTATUS_BOARD_ERROR;
    }

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            switch (m_board->getContentsOf(x, y)) {
                case Board::player: //make pointers for peach and yoshi, then put in vector
                    m_peach = new Hero(this, IID_PEACH, Hero::PEACH, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 0, 1.0);
                    m_yoshi = new Hero(this, IID_YOSHI, Hero::YOSHI, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 0, 1.0);
                    actorVector.push_back(m_peach);
                    actorVector.push_back(m_yoshi);
                    actorVector.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::bowser:
                    actorVector.push_back(new Bowser(this, IID_BOWSER, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 0, 1.0));
                    actorVector.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::boo:
                    actorVector.push_back(new Boo(this, IID_BOO, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 0, 1.0));
                    actorVector.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::blue_coin_square:
                    actorVector.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::red_coin_square:
                    actorVector.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, IID_RED_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::star_square:
                    actorVector.push_back(new StarSquare(this, IID_STAR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::event_square:
                    actorVector.push_back(new EventSquare(this, IID_EVENT_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::bank_square:
                    actorVector.push_back(new BankSquare(this, IID_BANK_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                case Board::up_dir_square:
                    actorVector.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::up, 1, 1.0));
                    break;
                case Board::down_dir_square:
                    actorVector.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::down, 1, 1.0));
                    break;
                case Board::left_dir_square:
                    actorVector.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::left, 1, 1.0));
                    break;
                case Board::right_dir_square:
                    actorVector.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, GraphObject::right, 1, 1.0));
                    break;
                default: //emtpy
                    break;
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() { //virtual
    if (timeRemaining() <= 0) {
        playSound(SOUND_GAME_FINISHED);
        if (m_peach->getNumStars() > m_yoshi->getNumStars()) {
            setFinalScore(m_peach->getNumStars(), m_peach->getNumCoins());
            return GWSTATUS_PEACH_WON;
        } else if (m_peach->getNumStars() < m_yoshi->getNumStars()) {
            setFinalScore(m_yoshi->getNumStars(), m_yoshi->getNumCoins());
            return GWSTATUS_YOSHI_WON;
        } else { //tie
            if (m_peach->getNumCoins() > m_yoshi->getNumCoins()) {
                setFinalScore(m_peach->getNumStars(), m_peach->getNumCoins());
                return GWSTATUS_PEACH_WON;
            }
            else if (m_peach->getNumCoins() < m_yoshi->getNumCoins()) {
                setFinalScore(m_yoshi->getNumStars(), m_yoshi->getNumCoins());
                return GWSTATUS_YOSHI_WON;
            } else { //ties again
                return ((rand() % 10 + 1 <= 5) ? GWSTATUS_PEACH_WON : GWSTATUS_YOSHI_WON);
            }
        }
    }

    for (size_t i = 0; i < actorVector.size(); i++) {
        actorVector[i]->doSomething(); //look for dead/inactive actors and delete
    }

    for (size_t i = 0; i < actorVector.size(); i++) {
        if (actorVector[i]->getAliveStatus() == false) { //you dead bitch
            delete actorVector[i];
            actorVector.erase(actorVector.begin() + i);
            i--;
        }
    }

    setGameStatText("P1 Roll: " + to_string((int)ceil(m_peach->getTicksToMove() / (double)SPRITE_WIDTH) + ((m_peach->getTicksToMove() > 0) ? 1 : 0))
        + " Stars: " + to_string(m_peach->getNumStars()) 
        + " $$: " + to_string(m_peach->getNumCoins()) 
        + ((m_peach->getNumVortex() > 0)? " VOR" : "")
        + " | Time: " + to_string(timeRemaining()) 
        + " | Bank: " + to_string(m_bank) 
        + " | P2 Roll: " + to_string((int) ceil(m_yoshi->getTicksToMove()/(double) SPRITE_WIDTH) + ((m_yoshi->getTicksToMove() > 0) ? 1 : 0)) 
        + " Stars: " + to_string(m_yoshi->getNumStars()) 
        + " $$: " + to_string(m_yoshi->getNumCoins())
        + ((m_yoshi->getNumVortex() > 0)? " VOR" : ""));

    /*setGameStatText("P1 Roll: " + to_string((m_peach->getTicksToMove() + 15) / 16)
        + " Stars: " + to_string(m_peach->getNumStars())
        + " $$: " + to_string(m_peach->getNumCoins())
        + ((m_peach->getNumVortex() > 0) ? " VOR" : "")
        + " | Time: " + to_string(timeRemaining())
        + " | Bank: " + to_string(m_bank)
        + " | P2 Roll: " + to_string((m_yoshi->getTicksToMove() + 15) / 16)
        + " Stars: " + to_string(m_yoshi->getNumStars())
        + " $$: " + to_string(m_yoshi->getNumCoins())
        + ((m_yoshi->getNumVortex() > 0) ? " VOR" : ""));*/
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() { //virtual
    for (size_t i = 0; i < actorVector.size(); i++) {
        delete actorVector[i];
    }

    //delete m_board;
    actorVector.clear();
}
