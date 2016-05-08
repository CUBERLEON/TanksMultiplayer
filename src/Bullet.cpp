#include "Bullet.hpp"

#include "Renderer.hpp"

Bullet::Bullet(float penetration, Polygon* shape)
: IMovable({0, 0}, {0, 0}, 0), ICollidable(shape), m_penetration(penetration)
{}

Bullet::~Bullet()
{}

void Bullet::draw(Renderer* renderer) {
    renderer->draw(*m_shape, *this);
}