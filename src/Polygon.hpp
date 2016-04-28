#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <utility>

class Polygon {
public:
    Polygon(const std::vector< std::pair<float, float> > points);
    ~Polygon();
    
    bool isIntersecting(const std::pair<float, float>& a, const std::pair<float, float>& b) const;
    const std::vector< std::pair<float, float> > getPoints() const { return m_points; }
protected:
private:
    std::vector< std::pair<float, float> > m_points;
};

#endif