#ifndef SFML_RENDERER_HPP
#define SFML_RENDERER_HPP

#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

class SFMLRenderer : public Renderer {
public:
    SFMLRenderer();
    ~SFMLRenderer();

    void createWindow(int width, int height, std::string title);
    void recreateWindow();
    void destroyWindow();
    void setSettings(short antialiasing);
    
    void requestFocus();
    void update();
    
    void clear();
    void display();
    void draw(IDrawable* r);
    
    void draw(Polygon* p, const IPositionable& t);
protected:
private:
    sf::RenderWindow* m_window;
};

#endif