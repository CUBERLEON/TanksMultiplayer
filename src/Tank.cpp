#include "Tank.hpp"

#include "Renderer.hpp"
#include "sys/Polygon.hpp"

Tank::Tank(Polygon* shape, float enginePower, float maxSpeed)
: IMovable({0, 0}, {0, 0}, 0), m_shape(shape), m_enginePower(enginePower), m_maxSpeed(maxSpeed), m_health(100), m_level(1)
{}

Tank::~Tank() {
    
}

void Tank::draw(Renderer* renderer) {
    renderer->draw(m_shape, getPos(), getRotation());
}