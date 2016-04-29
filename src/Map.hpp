#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "sys/IDrawable.hpp"

class Block;
class Renderer;

class Map : public IDrawable {
public:
    Map(float width, float height);
    Map(const std::string& fileName);
    virtual ~Map();
    
    float getWidth() const { return m_width; }
    float getHeight() const { return m_height; }
    void addBlock(Block* block) { m_blocks.push_back(block); }
    void setBlocks(const std::vector<Block*>& blocks) { m_blocks = blocks; }
    const std::vector<Block*>& getBlocks() const { return m_blocks; }
    
    void clear();
    void loadFromFile(const std::string& fileName);
    
    void draw(Renderer* renderer);
protected:
private:
    float m_width;
    float m_height;
    
    std::vector<Block*> m_blocks;
};

#endif