//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_STRATEGIC_H
#define PA5GAME_STRATEGIC_H

#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"

namespace Gaming {

    class Strategic : public Agent {
    private:
        static constexpr char STRATEGIC_ID = 'T';

        Strategy *__strategy;

    public:
        Strategic(const Game &g, const Position &p, double energy, Strategy *s = new DefaultAgentStrategy()): Agent(g, p, energy), __strategy(s) { }
        ~Strategic() { }

        PieceType getType() const override { return PieceType::STRATEGIC; }

        void print(std::ostream &os) const override;

        ActionType takeTurn(const Surroundings &s) const override;

    };

}


#endif //PA5GAME_STRATEGIC_H
