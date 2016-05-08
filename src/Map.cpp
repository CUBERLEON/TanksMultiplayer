#include "Map.hpp"

#include <fstream>
#include <sstream>
#include "sys/System.hpp"
#include "Block.hpp"
#include "Renderer.hpp"

Map::Map(float width, float height)
: m_width(width), m_height(height)
{}

Map::Map(const std::string& fileName)
{
    loadFromFile(MAPS_PATH + fileName + ".mp");
}

Map::~Map() {
    for (unsigned int i = 0; i < m_blocks.size(); ++i)
        delete m_blocks[i];
}

void Map::clear() {
    m_blocks.clear();
}

void Map::draw(Renderer* renderer) {
    for (unsigned int i = 0; i < m_blocks.size(); ++i)
        renderer->draw(m_blocks[i]);
}

void Map::loadFromFile(const std::string& filePath) {
    m_blocks.clear();
    std::ifstream s;
    s.open(filePath);
    if (!s)
        throw std::runtime_error("Couldn't open map file " + filePath);
    std::string line, type;
    while (std::getline(s, line)) {
        std::stringstream buf(line);
        buf >> type;
        if (!type.size()) continue;
        
        if (type == "d") {
            float w, h;
            buf >> w >> h;
            m_width = w;
            m_height = h;
        } else if (type == "b") {
            std::string shape;
            bool bulletproof, passable;
            float posx, posy, rotdeg, scalex, scaley;
            buf >> bulletproof >> passable >> shape >> posx >> posy >> rotdeg >> scalex >> scaley;
            
            Block* b = new Block(bulletproof, passable, new Polygon(shape));
            b->setPos({posx, posy});
            b->setRotDeg(rotdeg);
            b->setScale({scalex, scaley});
            m_blocks.push_back(b);
        } else if (type == "s") {
            float x, y;
            buf >> x >> y;
            m_spawns.push_back({x, y});
        }
    }
}