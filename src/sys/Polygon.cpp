#include "Polygon.hpp"

#include <fstream>
#include <sstream>
#include "Utils.hpp"
#include "System.hpp"
#include "Debug.hpp"

std::map<std::string, Polygon*> Polygon::m_loaded;

Polygon::Polygon(const Polygon& r) {
    copy(r);
}

Polygon::Polygon(std::string fileName)
: m_fileName(fileName)
{
    if (m_loaded.count(fileName)) {
        copy(*m_loaded.at(fileName));
    } else {
        loadFromFile(SHAPES_PATH + fileName + ".sp");
        m_loaded[fileName] = new Polygon(*this);
    }
} 

Polygon::Polygon(const std::vector< std::pair<float, float> >& points)
: m_points(points), m_fileName("")
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

void Polygon::freeLoaded() {
    Polygon* tmp;
    for (auto i = m_loaded.begin(); i != m_loaded.end(); ++i) {
        tmp = i->second;
        m_loaded.erase(i->first);
        delete tmp;
    }
}

void Polygon::loadFromFile(std::string filePath) {
    m_points.clear();
    std::ifstream s;
    s.open(filePath);
    if (!s)
        throw std::runtime_error("Couldn't open shape file " + filePath);
    std::string line, type;
    while (std::getline(s, line)) {
        std::stringstream buf(line);
        buf >> type;
        if (!type.size()) continue;
        
        if (type == "v") {
            float x, y;
            buf >> x >> y;
            m_points.push_back(std::make_pair(x, y));
        }
    }
}

void Polygon::copy(const Polygon& r) {
    m_fileName = r.getFileName();
    m_points = r.getPoints(); 
}