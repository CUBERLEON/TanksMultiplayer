#include "Block.hpp"

#include "sys/Polygon.hpp"
#include "Renderer.hpp"

Block::Block(bool isBulletProof, bool isPassable, Polygon* shape)
: IPositionable({0, 0}, 0), ICollidable(shape), m_isBulletProof(isBulletProof), m_isPassable(isPassable)
{}

Block::~Block() {
}

void Block::draw(Renderer* renderer) {
    renderer->draw(*m_shape, *this);
}