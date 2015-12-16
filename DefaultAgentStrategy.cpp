#include "Strategy.h"
#include "DefaultAgentStrategy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

Gaming::ActionType Gaming::DefaultAgentStrategy::operator()(const Gaming::Surroundings &s) const {
    std::vector<int> possible_moves;
    bool preform = false;

    for(int i = 0; i < 9; i++){
        if(s.array[i] == PieceType::ADVANTAGE){
            preform = true;
            possible_moves.push_back(i);
        }
    }

    if(!preform){
        for(int i = 0; i < 9; i++){
            if(s.array[i] == PieceType::FOOD){
                preform = true;
                possible_moves.push_back(i);
            }
        }
    }

    if(!preform){
        for(int i = 0; i < 9; i++){
            if(s.array[i] == PieceType::EMPTY){
                preform = true;
                possible_moves.push_back(i);
            }
        }
    }

    if(!preform){
        for(int i = 0; i < 9; i++){
            if(s.array[i] == PieceType::SIMPLE){
                preform = true;
                possible_moves.push_back(i);
            }
        }
    }

    if(!preform){
        possible_moves.push_back(4);
    }

    srand((unsigned int) time(NULL));
    switch(possible_moves[rand() % possible_moves.size()]){
        case 0:
            return ActionType::NW;
        case 1:
            return ActionType::N;
        case 2:
            return ActionType::NE;
        case 3:
            return ActionType::W;
        case 4:
            return ActionType::STAY;
        case 5:
            return ActionType::E;
        case 6:
            return ActionType::SW;
        case 7:
            return ActionType::S;
        case 8:
            return ActionType::SE;
        default:
            assert(false);
    }
}
