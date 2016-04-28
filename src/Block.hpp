#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "IDrawable.hpp"
#include "IPositional.hpp"

class Polygon;

class Block : public IDrawable, public IPositional {
public:
    enum TYPE {
        BRICK,
        WATER,
        TYPES_CNT
    };
    
    virtual ~Block();
        
    Polygon* getShape() const { return m_shape; }
    void setShape(Polygon* shape) { m_shape = shape; }
    bool isBulletProof() const { return m_isBulletProof; }
    bool isPassable() const { return m_isPassable; }
    
    virtual int getType() const = 0;
protected:
    Block(Polygon* shape, bool isBulletProof, bool isPassable);
private:
    Polygon* m_shape;
    
    bool m_isBulletProof;
    bool m_isPassable;
};

#endif