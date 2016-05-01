#include "Block.hpp"

#include "sys/Polygon.hpp"

Block::Block(bool isBulletProof, bool isPassable, Polygon* shape)
: IPositionable({0, 0}, 0), ICollidable(shape), m_isBulletProof(isBulletProof), m_isPassable(isPassable)
{}

Block::~Block() {
}