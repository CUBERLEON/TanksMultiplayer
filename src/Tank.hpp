#ifndef TANK_HPP
#define TANK_HPP

#include "IMovable.hpp"
#include "IDrawable.hpp"

class Renderer;

class Tank : public IMovable, public IDrawable {
public:
    Tank(float enginePower, float maxSpeed);
    virtual ~Tank();
    
    float getEnginePower() const { return m_enginePower; }
    float getMaxSpeed() const { return m_maxSpeed; }
    int getLevel() const { return m_level; }
    
    void draw(Renderer* renderer);
protected:
private:
    float m_enginePower;
    float m_maxSpeed;
    
    float m_health;
    
    int m_level;
    //std::vector<Bonus*> m_bonuses;
};

#endif