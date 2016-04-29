#include "World.hpp"

#include "Map.hpp"
#include "Tank.hpp"
#include "Bullet.hpp"
#include "Renderer.hpp"

World::World(Map* map)
: m_map(map), m_updateTime(1.), m_curTime(0.)
{}

World::~World() {
    delete m_map;
    for (unsigned int i = 0; i < m_tanks.size(); ++i)
        delete m_tanks[i];
    for (unsigned int i = 0; i < m_bullets.size(); ++i)
        delete m_bullets[i];
}

const std::vector<Tank*>& World::getTanks() const {
    return m_tanks;
}

const std::vector<Bullet*>& World::getBullets() const {
    return m_bullets;
}

Map* World::getMap() const {
    return m_map;
}

void World::addTank(Tank* tank) {
    m_tanks.push_back(tank);
}

void World::addBullet(Bullet* bullet) {
    m_bullets.push_back(bullet);
}

void World::update(float time) {
    
}

void World::draw(Renderer* renderer) {
    renderer->draw(m_map);
    for (unsigned int i = 0; i < m_tanks.size(); ++i)
        renderer->draw(m_tanks[i]);
    for (unsigned int i = 0; i < m_bullets.size(); ++i)
        renderer->draw(m_bullets[i]);
}