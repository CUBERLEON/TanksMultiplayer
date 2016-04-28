#include "Bullet.hpp"

#include "Renderer.hpp"

Bullet::Bullet(float penetration)
: IMovable({0, 0}, {0, 0}, 0), m_penetration(penetration)
{}

Bullet::~Bullet() {
    
}

void Bullet::draw(Renderer* renderer) {
    
}