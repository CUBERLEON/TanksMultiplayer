#ifndef SFML_RENDERER_HPP
#define SFML_RENDERER_HPP

#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

class SFMLrenderer : public Renderer {
public:
    SFMLrenderer();
    virtual ~SFMLrenderer();

    void createWindow(int width, int height, std::string title) override;
    void recreateWindow() override;
    void destroyWindow() override;
    void setSettings(short antialiasing, bool apply = false) override;
    
    void requestFocus() override;
    void update() override;
    void input() override;
    
    void clear() override;
    void display() override;
    void draw(IDrawable* r) override;
    
    void draw(const Polygon& p, const IPositionable& t) override;
protected:
private:
    sf::RenderWindow* m_window;
};

#endif