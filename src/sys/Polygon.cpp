#include "Polygon.hpp"

#include "Utils.hpp"

Polygon::Polygon(const std::vector< std::pair<float, float> >& points)
: m_points(points)
{}

Polygon::~Polygon() {
    
}

bool Polygon::isIntersecting(const std::pair<float, float>& a, const std::pair<float, float>& b) const {
    for (unsigned i = 0; i < m_points.size(); ++i) {
        unsigned j = (i+1) % m_points.size();
        
        if (intersecting(m_points[i], m_points[j], a, b) == 2)
            return true;
    }
    return false;
}