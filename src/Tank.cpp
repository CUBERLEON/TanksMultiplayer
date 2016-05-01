#include "Tank.hpp"

#include "Renderer.hpp"
#include "sys/Polygon.hpp"

Tank::Tank(float enginePower, float maxSpeed, Polygon* shape)
: IMovable({0, 0}, {0, 0}, 0), ICollidable(shape), m_enginePower(enginePower), m_maxSpeed(maxSpeed), m_health(100), m_level(1)
{}

Tank::~Tank() {
    
}

void Tank::draw(Renderer* renderer) {
    renderer->draw(m_shape, getPos(), getRotation());
}