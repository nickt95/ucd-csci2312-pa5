#include "Game.h"
#include "Piece.h"
#include "Agent.h"

Gaming::Resource::Resource(const Gaming::Game & g, const Gaming::Position & p, double __capacity): Piece(g, p), __capacity(__capacity){

}

void Gaming::Resource::age() {
    __capacity /= RESOURCE_SPOIL_FACTOR;
}

Gaming::ActionType Gaming::Resource::takeTurn(const Gaming::Surroundings &s) const {
    return ActionType::STAY;
}
