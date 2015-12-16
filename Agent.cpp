#include "Game.h"
#include "Piece.h"
#include "Agent.h"
#include "Resource.h"

Gaming::Agent::Agent(const Gaming::Game &g, const Gaming::Position &p, double energy): Piece(g, p), __energy(energy) {

}

Gaming::Piece &Gaming::Agent::interact(Gaming::Agent *other) {
    if(this->getEnergy() == other->getEnergy()){
        this->finish();
        other->finish();
    }
    else if(this->getEnergy() > other->getEnergy()){
        this->__energy -= other->getEnergy();
        other->finish();
    }
    else{
        other->__energy -= this->getEnergy();
        this->finish();
    }

    return *this;
}

Gaming::Piece &Gaming::Agent::interact(Gaming::Resource *resource) {
    this->addEnergy(resource->consume());

    return *this;
}
