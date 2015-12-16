#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"
#include "Strategic.h"

void Gaming::Strategic::print(std::ostream& os) const{
    os << STRATEGIC_ID << __id;
}

Gaming::ActionType Gaming::Strategic::takeTurn(const Gaming::Surroundings &s) const {
    return (*__strategy)(s);
}
