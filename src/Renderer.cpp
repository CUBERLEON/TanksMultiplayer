#include "Renderer.hpp"

#include "sys/IDrawable.hpp"
#include "sys/Polygon.hpp"
#include "sys/Debug.hpp"

Renderer::Renderer()
: m_isActive(false), m_window(nullptr)
{}

Renderer::~Renderer() {
    delete m_window;
}

void Renderer::setWindow(sf::RenderWindow* window) {
    m_window = window;
    m_isActive = m_window != nullptr;
}

void Renderer::clear() {
    m_window->clear(sf::Color::Black);
}

void Renderer::display() {
    m_window->display();
}

void Renderer::draw(IDrawable* r) {
    if (r != nullptr)
        r->draw(this);
}

void Renderer::draw(Polygon* p, const std::pair<float, float>& pos, float rotation) {
    sf::RectangleShape line(sf::Vector2f(150, 5));
    line.rotate(45);
    line.setFillColor(sf::Color(0, 0, 0));
    m_window->draw(line);
}