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
    
    virtual void draw(Renderer* renderer) override;
protected:
    float m_penetration;
private:
};

#endif