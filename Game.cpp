#include "Gaming.h"
#include "DefaultAgentStrategy.h"
#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Exceptions.h"
#include <iomanip>

enum Status { NOT_STARTED, PLAYING, OVER };

void Gaming::Game::populate() {
    int _numInitAgents = (__width*__height)/NUM_INIT_AGENT_FACTOR;
    int _numInitResources = (__width*__height)/NUM_INIT_RESOURCE_FACTOR;

    unsigned int numStrategic = (unsigned int) (_numInitAgents/2);
    unsigned int numSimple = _numInitAgents-numStrategic;
    unsigned int numAdvantages = (unsigned int) (_numInitResources/4);
    unsigned int numFoods = _numInitResources-numAdvantages;

    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width*__height);

    while(numStrategic > 0){
        int i = d(gen);
        if(__grid[i] == nullptr){
            Position pos(i/__width,i%__width);
            __grid[i] = new Gaming::Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
            numStrategic--;
        }
    }

    while(numSimple > 0){
        int i = d(gen);
        if(__grid[i] == nullptr){
            Position pos(i/__width,i%__width);
            __grid[i] = new Gaming::Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
            numSimple--;
        }
    }

    while(numAdvantages > 0){
        int i = d(gen);
        if(__grid[i] == nullptr){
            Position pos(i/__width,i%__width);
            __grid[i] = new Gaming::Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
            numAdvantages--;
        }
    }

    while(numFoods > 0){
        int i = d(gen);
        if(__grid[i] == nullptr){
            Position pos(i/__width,i%__width);
            __grid[i] = new Gaming::Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
            numFoods--;
        }
    }
}

Gaming::Game::Game(): __width(3), __height(3), __round(1), __status(Status::NOT_STARTED) {
    for(int i = 0; i < __width*__height; i++){
        __grid.push_back(nullptr);
    }
}

Gaming::Game::Game(unsigned width, unsigned height, bool manual):__width(width), __height(height), __round(1), __status(Status::NOT_STARTED) {
    if(width < MIN_WIDTH && height < MIN_HEIGHT){
        InsufficientDimensionsEx ex(MIN_WIDTH, MIN_HEIGHT, width, height);
        throw ex;
    }

    for(int i = 0; i < __width*__height; i++){
        __grid.push_back(nullptr);
    }

    if(!manual){
        populate();
    }
}

Gaming::Game::Game(const Gaming::Game &another):__width(another.__width) , __height(another.__height), __round(another.__round), __status(another.__status), __grid(another.__grid){

}

Gaming::Game::~Game() {
    for(int i = __width*__height-1; i >= 0; i--){
        delete __grid[i];
    }
}

unsigned int Gaming::Game::getNumSimple() const {
    unsigned int curr = 0;

    for(int i = 0; i < __grid.size(); i++){
        //if(__grid[i]->getType() == PieceType::SIMPLE) curr++;
    }

    return curr;
}

unsigned int Gaming::Game::getNumStrategic() const {
    unsigned int curr = 0;

    for(int i = 0; i < __grid.size(); i++){
        //if(__grid[i]->getType() == PieceType::STRATEGIC) curr++;
    }

    return curr;
}

unsigned int Gaming::Game::getNumResources() const {
    unsigned int curr = 0;

    for(int i = 0; i < __grid.size(); i++){
        //if(__grid[i]->getType() == PieceType::FOOD || __grid[i]->getType() == PieceType::ADVANTAGE) curr++;
    }

    return curr;
}

bool Gaming::Game::addSimple(const Gaming::Position &position) {
    //if(position.x < 0 || position.y < 0 || position.x >= __width || position.y >= __height){
    //    OutOfBoundsEx ex(__width, __height, position.x, position.y);
    //    throw ex;
    //}

    int index = (__width*position.x)+position.y;

    if(__grid[index] != nullptr){
        return false;
    }

    __grid[index] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    return true;
}

bool Gaming::Game::addStrategic(const Gaming::Position &position, Gaming::Strategy *s) {
    //if(position.x < 0 || position.y < 0 || position.x >= __width || position.y >= __height){
    //    OutOfBoundsEx ex(__width, __height, position.x, position.y);
    //    throw ex;
    //}

    int index = (__width*position.x)+position.y;

    if(__grid[index] != nullptr){
        return false;
    }

    __grid[index] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    return true;
}

bool Gaming::Game::addFood(const Gaming::Position &position) {
    //if(position.x < 0 || position.y < 0 || position.x >= __width || position.y >= __height){
    //    OutOfBoundsEx ex(__width, __height, position.x, position.y);
    //    throw ex;
    //}

    int index = (__width*position.x)+position.y;

    if(__grid[index] != nullptr){
        return false;
    }

    __grid[index] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    return true;
}

bool Gaming::Game::addAdvantage(const Gaming::Position &position) {
    if(position.x < 0 || position.y < 0 || position.x >= __width || position.y >= __height){
        OutOfBoundsEx ex(__width, __height, position.x, position.y);
        throw ex;
    }

    int index = (__width*position.x)+position.y;

    if(__grid[index] != nullptr){
        return false;
    }

    __grid[index] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    return true;
}

const Gaming::Surroundings Gaming::Game::getSurroundings(const Gaming::Position &pos) const {
    if(pos.x < 0 || pos.y < 0 || pos.x >= __width || pos.y >= __height){
        OutOfBoundsEx ex(__width, __height, pos.x, pos.y);
        throw ex;
    }

    Surroundings s;
    s.array = {PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY, PieceType::EMPTY};
    Position curr;
    int index;
    bool done;
    PieceType temp;

    for(int ix = -1; ix <= 1; ix++){
        for(int iy = -1; iy <= 1; iy++){
            curr = pos;
            curr.x += ix;
            curr.y += iy;
            index = (__width*curr.x)+curr.y;
            done = false;

            if(curr.x < 0 || curr.y < 0 || curr.x >= __width || curr.y >= __height){
                s.array[(3*(ix+1))+iy+1] = PieceType::INACCESSIBLE;
                done = true;
            }

            if(!done){
                if(curr.x == pos.x && curr.y == pos.y){
                    s.array[(3*(ix+1))+iy+1] = PieceType::SELF;
                    done = true;
                }
            }

            if(!done){
                if(__grid[index] == nullptr){
                    s.array[(3*(ix+1))+iy+1] = PieceType::EMPTY;
                    done = true;
                }
            }

            if(!done){
                temp = __grid[index]->getType();
                s.array[(3*(ix+1))+iy+1] = temp;
            }
        }
    }

    return s;
}

bool Gaming::Game::addAdvantage(unsigned x, unsigned y) {
    Position pos;
    pos.x = x;
    pos.y = y;

    return addAdvantage(pos);
}

bool Gaming::Game::addFood(unsigned x, unsigned y) {
    Position pos;
    pos.x = x;
    pos.y = y;

    return addFood(pos);
}

bool Gaming::Game::addStrategic(unsigned x, unsigned y, Gaming::Strategy *s) {
    Position pos;
    pos.x = x;
    pos.y = y;

    return addStrategic(pos, s);
}

bool Gaming::Game::addSimple(unsigned x, unsigned y) {
    Position pos;
    pos.x = x;
    pos.y = y;

    return addSimple(pos);
}

unsigned int Gaming::Game::getNumAgents() const {
    return getNumStrategic() + getNumSimple();
}

unsigned int Gaming::Game::getNumPieces() const {
    return getNumAgents() + getNumResources();
}

const Gaming::ActionType Gaming::Game::reachSurroundings(const Gaming::Position &from, const Gaming::Position &to) {
    int deltaX = to.x - from.x;
    int deltaY = to.y - from.y;

    switch (deltaX){
        case -1:
            switch (deltaY){
                case -1:
                    return ActionType::SE;
                case 0:
                    return ActionType::S;
                case 1:
                    return ActionType::SW;
                default:
                    return ActionType::STAY;
            }
        case 0:
            switch (deltaY){
                case -1:
                    return ActionType::E;
                case 0:
                    return ActionType::STAY;
                case 1:
                    return ActionType::W;
                default:
                    return ActionType::STAY;
            }
        case 1:
            switch (deltaY){
                case -1:
                    return ActionType::NE;
                case 0:
                    return ActionType::N;
                case 1:
                    return ActionType::NW;
                default:
                    return ActionType::STAY;
            }
        default:
            return ActionType::STAY;
    }
}

bool Gaming::Game::isLegal(const Gaming::ActionType &ac, const Gaming::Position &pos) const {
    if(pos.x < 0 || pos.y < 0 || pos.x >= __width || pos.y >= __height){
        OutOfBoundsEx ex(__width, __height, pos.x, pos.y);
        throw ex;
    }

    if(pos.x == 0 && (ac == ActionType::N || ac == ActionType::NW || ac == ActionType::NE)) return false;

    if(pos.y == 0 && (ac == ActionType::W || ac == ActionType::NW || ac == ActionType::SW)) return false;

    if(pos.x == __height-1 && (ac == ActionType::S || ac == ActionType::SW || ac == ActionType::SE)) return false;

    return !(pos.y == __width-1 && (ac == ActionType::E || ac == ActionType::NE || ac == ActionType::SE));
}

const Gaming::Position Gaming::Game::move(const Gaming::Position &pos, const Gaming::ActionType &ac) const {
    Position next = pos;

    switch (ac){
        case ActionType::N:
            next.x--;
            break;
        case ActionType::NW:
            next.x--;
            next.y++;
            break;
        case ActionType::W:
            next.y++;
            break;
        case ActionType::SW:
            next.x++;
            next.y++;
            break;
        case ActionType::S:
            next.x++;
            break;
        case ActionType::SE:
            next.x++;
            next.y--;
            break;
        case ActionType::E:
            next.y--;
            break;
        case ActionType::NE:
            next.x--;
            next.y--;
            break;
        default:
            break;
    }

    return next;
}

void Gaming::Game::round() {
    bool repeat = true;

    while(repeat){
        repeat = false;

        for(int i = 0; i <__width*__height; i++){
            if(__grid[i] != nullptr){
                if(__grid[i]->isViable()){
                    if(!__grid[i]->getTurned()){
                        __grid[i]->setTurned(true);

                        Position p;
                        p.x = i / __width;
                        p.y = i % __width;

                        ActionType ac = __grid[i]->takeTurn(getSurroundings(p));

                        Position newP = move(p, ac);

                        if(__grid[(__width*newP.x)+newP.y] != nullptr && ac != ActionType::STAY){
                            *__grid[(__width*newP.x)+newP.y] * *__grid[i];

                            if(!__grid[(__width*newP.x)+newP.y]->isViable()){
                                delete __grid[(__width*newP.x)+newP.y];
                            }
                        }

                        if(__grid[i]->isViable() && __grid[(__width*newP.x)+newP.y] == nullptr){
                            __grid[(__width*newP.x)+newP.y] = __grid[i];
                            __grid[i]->finish();
                        }

                        if(!__grid[i]->isViable()){
                            delete __grid[i];
                        }

                        repeat = true;
                    }
                }
                else{
                    delete __grid[i];
                    repeat = true;
                }
            }
        }
    }

    for(int i = 0; i <__width*__height; i++){
        if(__grid[i] != nullptr){
            __grid[i]->age();
            __grid[i]->setTurned(false);

            if(!__grid[i]->isViable()){
                delete __grid[i];
            }
        }
    }

    if(getNumResources() == 0){
        __status = Status::OVER;
    }
    else{
        __status = Status::PLAYING;
    }
}

void Gaming::Game::play(bool verbose) {
    __status = Status::PLAYING;

    if(verbose){
        std::cout << this;
    }

    while(__status != Status::OVER){
        round();

        if(verbose){
            std::cout << this;
        }
    }
}

std::ostream &Gaming::operator<<(std::ostream &os, const Gaming::Game &game) {
    os << "Round " << game.getRound() << ":" << std::endl;

    for(int x = 0; x < game.getHeight(); x++){
        for(int y = 0; y < game.getWidth(); y++){
            if(game.getGrid()[(game.getWidth()*x)+y] == nullptr){
                os << "[]";
            }
            else{
                os << "[" << game.getGrid()[(game.getWidth()*x)+y] << "]";
            }

            os << std::endl;
        }
    }

    os << "Status: ";

    switch (game.getStatus()){
        case Status::NOT_STARTED:
            os << "Not Started" << std::endl;
            break;
        case Status::OVER:
            os << "Over!" << std::endl;
            break;
        case Status::PLAYING:
            os << "Playing..." << std::endl;
            break;
    }

    return os;
}
