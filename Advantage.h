//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_WEAPON_H
#define PA5GAME_WEAPON_H

#include "Game.h"
#include "Resource.h"

namespace Gaming {
    class Advantage : public Resource {
    private:
        static constexpr char ADVANTAGE_ID = 'D';

    public:
        static constexpr double ADVANTAGE_MULT_FACTOR = 2.0;

        Advantage(const Game &g, const Position &p, double capacity);
        ~Advantage() { }

        PieceType getType() const override { return PieceType::ADVANTAGE; }

        void print(std::ostream &os) const override;

        double getCapacity() const override {return __capacity*ADVANTAGE_MULT_FACTOR;}
        double consume() override;
    };
}


#endif //PA5GAME_WEAPON_H
