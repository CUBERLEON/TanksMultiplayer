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
    const std::vector<Block*>& getBlocks() const { return m_blocks; }
    const std::vector< std::pair<float, float> >& getSpawns() const { return m_spawns; }
    
    void addBlock(Block* block) { m_blocks.push_back(block); }
    void addSpawn(const std::pair<float, float>& spawn) { m_spawns.push_back(spawn); }
    void setBlocks(const std::vector<Block*>& blocks) { m_blocks = blocks; }
    void setSpawns(const std::vector< std::pair<float, float> >& spawns) { m_spawns = spawns; }
    
    void clear();
    
    void draw(Renderer* renderer);
protected:
private:
    float m_width;
    float m_height;
    
    std::vector<Block*> m_blocks;
    std::vector< std::pair<float, float> > m_spawns;
    
    void loadFromFile(const std::string& filePath);
};

#endif