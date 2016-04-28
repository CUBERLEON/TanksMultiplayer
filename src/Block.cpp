#include "Block.hpp"

#include "Polygon.hpp"

Block::Block(Polygon* shape, bool isBulletProof, bool isPassable)
: IPositional({0, 0}, 0), m_shape(shape), m_isBulletProof(isBulletProof), m_isPassable(isPassable)
{}

Block::~Block() {
    delete m_shape;
}