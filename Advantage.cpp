#include "Game.h"
#include "Resource.h"
#include "Advantage.h"
#include <iomanip>

void Gaming::Advantage::print(std::ostream &os) const {
    os << ADVANTAGE_ID << __id;
}

Gaming::Advantage::Advantage(const Gaming::Game &g, const Gaming::Position &p, double capacity): Resource(g, p, capacity) {

}

double Gaming::Advantage::consume() {
    this->finish();
    return getCapacity()*ADVANTAGE_MULT_FACTOR;
}
