#ifndef I_COLLIDABLE_HPP
#define I_COLLIDABLE_HPP

#include "Polygon.hpp"

class ICollidable {
public:
    
protected:
    ICollidable() {}
    ~ICollidable() { delete m_shape; }
    
    Polygon* m_shape;
private:
};

#endif