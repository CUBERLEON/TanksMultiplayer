#include "SFMLRenderer.hpp"

#include "sys/IDrawable.hpp"
#include "sys/IPositionable.hpp"
#include "sys/Polygon.hpp"
#include "sys/Utils.hpp"
#include "sys/Debug.hpp"

SFMLRenderer::SFMLRenderer()
: m_window(nullptr)
{}

SFMLRenderer::~SFMLRenderer() {
    delete m_window;
}

void SFMLRenderer::createWindow(int width, int height, std::string title) {
    m_width = width;
    m_height = height;
    m_title = title;

    sf::ContextSettings settings;
    settings.antialiasingLevel = m_antialiasing;
    if (m_window == nullptr)
        m_window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close, settings);
    else
        m_window->create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close, settings);

    m_active = true;
}

void SFMLRenderer::recreateWindow() {
    createWindow(m_width, m_height, m_title);
}

void SFMLRenderer::update() {
    sf::Event event;
    while (m_active && m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            destroyWindow();
    	if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                destroyWindow();
    		// if (event.key.code == sf::Keyboard::A)
    		// 	m_world->getTanks()[0]->rotate(5*updateTime);
    		// if (event.key.code == sf::Keyboard::D)
    		// 	m_world->getTanks()[0]->rotate(-5*updateTime);
    	}
    }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    // 	m_world->getTanks()[0]->rotate(5*updateTime);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    // 	m_world->getTanks()[0]->rotate(-5*updateTime);
}

void SFMLRenderer::destroyWindow() {
    if (!m_active)
        return;
        
    m_active = false;
    if (m_window != nullptr) {
        m_window->close();
        m_window = nullptr;
    }
}

void SFMLRenderer::setSettings(short antialiasing) {
    m_active = false;
    m_antialiasing = antialiasing;

    recreateWindow();
}

void SFMLRenderer::requestFocus() {
    m_window->requestFocus();
}

void SFMLRenderer::clear() {
    m_window->clear(sf::Color::Black);
}

void SFMLRenderer::display() {
    m_window->display();
}

void SFMLRenderer::draw(IDrawable* r) {
    if (r != nullptr)
        r->draw(this);
}

void SFMLRenderer::draw(Polygon* p, const IPositionable& t) {
    std::vector<sf::Vertex> vertices;
    for (unsigned int i = 0; i <= p->getPoints().size(); ++i) {
        std::pair<float, float> a1 = p->getPoints()[i % p->getPoints().size()];

        a1 = scale(a1, t.getScale());
        float k = 1.;
        if (isActiveDrawTransform()) {
            k = std::min((float)m_width/m_widthDT, (float)m_height/m_heightDT);
            a1 = scale(a1, k);
        }
        a1 = rotate(a1, t.getRot());

        vertices.push_back(sf::Vertex(sf::Vector2f(a1.first + t.getPosX() * k, a1.second + t.getPosY() * k)));
    }
    m_window->draw(&vertices[0], vertices.size(), sf::LinesStrip);

    // sf::ConvexShape convex;
    // convex.setPointCount(p->getPoints().size());
    // for (unsigned int i = 0; i < p->getPoints().size(); ++i) {
    //     std::pair<float, float> a1 = p->getPoints()[i];
    //     convex.setPoint(i, sf::Vector2f(a1.first, a1.second));
    // }
    // convex.setRotation(getRotDeg());
    // convex.setPosition({t.getPosX(), t.getPosY()});
    // m_window->draw(convex);
}