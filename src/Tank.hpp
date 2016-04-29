#ifndef TANK_HPP
#define TANK_HPP

#include "sys/IMovable.hpp"
#include "sys/IDrawable.hpp"

class Renderer;
class Polygon;

class Tank : public IMovable, public IDrawable {
public:
    Tank(Polygon* shape, float enginePower, float maxSpeed);
    virtual ~Tank();
    
    Polygon* getShape() const { return m_shape; }
    void setShape(Polygon* shape) { m_shape = shape; }
    float getEnginePower() const { return m_enginePower; }
    float getMaxSpeed() const { return m_maxSpeed; }
    int getLevel() const { return m_level; }
    
    void draw(Renderer* renderer);
protected:
private:
    Polygon* m_shape;

    float m_enginePower;
    float m_maxSpeed;
    
    float m_health;
    
    int m_level;
    //std::vector<Bonus*> m_bonuses;
};

#endif