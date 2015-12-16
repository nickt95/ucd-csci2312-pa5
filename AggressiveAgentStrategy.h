//
// Created by Ivo Georgiev on 12/9/15.
//

#ifndef PA5GAME_AGGRESSIVEAGENTSTRATEGY_H
#define PA5GAME_AGGRESSIVEAGENTSTRATEGY_H

#include "Strategy.h"
#include "Game.h"

namespace Gaming {

    class AggressiveAgentStrategy : public Strategy {
        double __agentEnergy;

    public:
        static constexpr double DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY*.75;

        AggressiveAgentStrategy(double agentEnergy);
        ~AggressiveAgentStrategy() { }
        ActionType operator()(const Surroundings &s) const override;

    };

}


#endif //PA5GAME_AGGRESSIVEAGENTSTRATEGY_H
