#include "Game.h"
#include "Resource.h"
#include "Food.h"
#include <iomanip>

Gaming::Food::Food(const Gaming::Game &g, const Gaming::Position &p, double capacity): Resource(g, p, capacity) {

}

void Gaming::Food::print(std::ostream &os) const {
    os << FOOD_ID << __id;
}
