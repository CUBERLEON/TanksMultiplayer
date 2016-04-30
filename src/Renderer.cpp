#include "Renderer.hpp"

#include "sys/IDrawable.hpp"
#include "sys/Polygon.hpp"
#include "sys/Utils.hpp"

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

void Renderer::draw(Polygon* p, const std::pair<float, float>& pos, float angle) {
    std::vector<sf::Vertex> vertices;
    for (unsigned int i = 0; i <= p->getPoints().size(); ++i) {
        std::pair<float, float> a1 = p->getPoints()[i % p->getPoints().size()];
        a1 = rotate(a1, angle);
        vertices.push_back(sf::Vertex(sf::Vector2f(a1.first + pos.first, a1.second + pos.second)));
    }
    m_window->draw(&vertices[0], vertices.size(), sf::LinesStrip);
    
    // sf::ConvexShape convex;
    // convex.setPointCount(p->getPoints().size());
    // for (unsigned int i = 0; i < p->getPoints().size(); ++i) {
    //     std::pair<float, float> a1 = p->getPoints()[i];
    //     convex.setPoint(i, sf::Vector2f(a1.first, a1.second));
    // }
    // convex.setRotation(180.*angle/M_PI);
    // convex.setPosition({pos.first, pos.second});
    // m_window->draw(convex);
}