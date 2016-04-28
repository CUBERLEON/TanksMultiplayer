#include "Map.hpp"

#include "System.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

Map::Map(float width, float height)
: m_width(width), m_height(height)
{}

Map::Map(const std::string& fileName)
{
    loadFromFile(fileName);
}

Map::~Map() {
    for (unsigned int i = 0; i < m_blocks.size(); ++i)
        delete m_blocks[i];
}

void Map::clear() {
    m_blocks.clear();
}

void Map::loadFromFile(const std::string& fileName) {
    //TODO Loading map
}

void Map::draw(Renderer* renderer) {
    
}