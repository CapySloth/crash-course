#include "Die.h"
#include <cstdlib>
#include <iostream>

const unsigned int Die::MIN_SIDES = 2;

Die::Die() 
    : Die(6) {
}

Die::Die(unsigned int sides)
        : mSides(sides) {
    validateSides();
}

Die::~Die() {
}

void Die::setSides(unsigned int sides) {
    mSides = sides;
    validateSides();
}

unsigned int Die::roll() const {
    return (rand() % mSides) + 1;
}

void Die::validateSides() const {
    if (mSides < MIN_SIDES) {
        std::cerr << "A die cannot have less than " << MIN_SIDES << " sides; attempted: " << mSides << std::endl;
        throw std::exception();
    }
}
