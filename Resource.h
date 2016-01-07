//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_RESOURCE_H
#define PA5GAME_RESOURCE_H

#include <assert.h>
#include "Game.h"
#include "Piece.h"
#include "Agent.h"

namespace Gaming {

    class Resource : public Piece {

    protected:
        double __capacity;
        
    public:
        static constexpr double RESOURCE_SPOIL_FACTOR = 1.2;

        Resource(const Game &g, const Position &p, double __capacity);
        ~Resource() { }

        virtual double getCapacity() const { return __capacity; }
        virtual double consume() {
            this->finish();
            return __capacity;
        }

        void age() override final;

        bool isViable() const override final { return !isFinished() && __capacity-.05 > 0.0; }

        ActionType takeTurn(const Surroundings &s) const override;

        // note: these won't be called while resources don't move
        Piece &operator*(Piece &other) override final {
            return other.interact(this);
        }
        Piece &interact(Agent *a) override final {
            assert(false);
        }
        Piece &interact(Resource *r) override final {
            assert(false);
        } // note: no interaction between resources
    };

}


#endif //PA5GAME_RESOURCE_H
