#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>

class IDrawable;

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void setWindow(sf::RenderWindow* window);
    sf::RenderWindow* getWindow() const { return m_window; };
    
    void refresh();
    void draw(IDrawable* r);
protected:
private:
    sf::RenderWindow* m_window;
    
    void init();
};

#endif