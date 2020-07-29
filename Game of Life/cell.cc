#include "cell.h"
#include "info.h"


static const int zeroNeigh {0};
static const int twoNeigh {2};
static const int threeNeigh {3};


// constructor
Cell::Cell(size_t r, size_t c) : r {r}, c {c}, state{State::Dead}, neighbours {0} {}


// Cell::setLiving() marks cell as alive
void Cell::setLiving() {
	state = State::Alive;
}


// Cell::reset() resets neighbour count to 0
void Cell::reset() {
	neighbours = zeroNeigh;
}


// Cell::notify() notifies my neighbours if I'm alive
void Cell::notify() {
	notifyObservers();
}


// Cell::notify(whoNotified) will be called by my neighbours to let me know if they're alive
void Cell::notify(Subject& whoNotified) {
	Info info {whoNotified.getInfo()};

	if (info.state == State::Alive) ++neighbours;
	
}


// Cell::recalculate() reassess my living-or-dead status, based on info from neighbours
void Cell::recalculate() {
	if ((state == State::Alive) && ((neighbours < twoNeigh) || (neighbours > threeNeigh))) {
		state = State::Dead;
		return;
	} 
	
	if ((state == State::Dead) && (neighbours == threeNeigh)) {
		state = State::Alive;
	}
}


// Cell::getIno() const retrieves info about cell
Info Cell::getInfo() const {
	return Info {state, r, c};
}
