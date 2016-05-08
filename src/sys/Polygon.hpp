#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>
#include <map>
#include <utility>

class Polygon {
public:
    Polygon(const Polygon& r);
    Polygon(std::string fileName);
    Polygon(const std::vector< std::pair<float, float> >& points);
    ~Polygon();
    
    bool isIntersecting(const std::pair<float, float>& a, const std::pair<float, float>& b) const;
    
    const std::vector< std::pair<float, float> >& getPoints() const { return m_points; }
    const std::string& getFileName() const { return m_fileName; }
    
    static void freeLoaded();
protected:
    std::vector< std::pair<float, float> > m_points;
private:
    void loadFromFile(std::string fileName);
    void copy(const Polygon& r);
    
    std::string m_fileName;
    static std::map<std::string, Polygon*> m_loaded;
};

#endif