#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utility>
#include <SFML/Graphics.hpp>

class IDrawable;
class Polygon;

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool isActive() const { return m_isActive; }
    void setWindow(sf::RenderWindow* window);
    sf::RenderWindow* getWindow() const { return m_window; };
    
    void clear();
    void display();
    void draw(IDrawable* r);
    
    void draw(Polygon* p, const std::pair<float, float>& pos, float angle);
protected:
private:
    bool m_isActive;

    sf::RenderWindow* m_window;
};

#endif