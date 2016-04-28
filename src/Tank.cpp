#include "Tank.hpp"

#include "Renderer.hpp"

Tank::Tank(float enginePower, float maxSpeed)
: IMovable({0, 0}, {0, 0}, 0), m_enginePower(enginePower), m_maxSpeed(maxSpeed), m_health(100), m_level(1)
{}

Tank::~Tank() {
    
}

void Tank::draw(Renderer* renderer) {
    
}