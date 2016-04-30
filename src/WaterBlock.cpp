#include "WaterBlock.hpp"

#include "Renderer.hpp"

WaterBlock::WaterBlock(Polygon* shape)
: Block(shape, false, false)
{
}

WaterBlock::~WaterBlock() {
    
}

void WaterBlock::draw(Renderer* renderer) {
    renderer->draw(getShape(), getPos(), getRotation());
}