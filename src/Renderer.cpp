#include "Renderer.hpp"

#include "IDrawable.hpp"

Renderer::Renderer()
{
    
}

Renderer::~Renderer() {
    delete m_window;
}

void Renderer::setWindow(sf::RenderWindow* window) {
    
    init();
    
}

void Renderer::refresh() {
    
}

void Renderer::draw(IDrawable* r) {
    r->draw(this);
}

void Renderer::init() {
    
}