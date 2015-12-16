//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_SIMPLE_H
#define PA5GAME_SIMPLE_H

#include "Game.h"
#include "Agent.h"

namespace Gaming {

    class Simple : public Agent {
    private:
        static constexpr char SIMPLE_ID = 'S';

    public:
        Simple(const Game &g, const Position &p, double energy): Agent(g, p, energy) { }
        ~Simple() { }

        PieceType getType() const override { return PieceType::SIMPLE; }

        void print(std::ostream &os) const override;

        ActionType takeTurn(const Surroundings &s) const override;

    };
}

#endif //PA5GAME_SIMPLE_H
