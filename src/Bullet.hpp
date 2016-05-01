#ifndef BULLET_HPP
#define BULLET_HPP

#include "sys/IMovable.hpp"
#include "sys/IDrawable.hpp"
#include "sys/ICollidable.hpp"

class Renderer;

class Bullet : public IMovable, public IDrawable, public ICollidable {
public:
    Bullet(float penetration, Polygon* shape);
    virtual ~Bullet(); 
    
    float getPenetration() const { return m_penetration; }
    
    void draw(Renderer* renderer);
protected:
private:
    float m_penetration;
};

#endif