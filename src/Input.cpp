#include "Input.hpp"

#include <SFML/Window.hpp>

Input::Input()
{
    m_keyboard = new int[Keyboard::KEYS_CNT];
    m_mouse = new int[Mouse::KEYS_CNT];
    memset(m_keyboard, 0, sizeof(m_keyboard) * Keyboard::KEYS_CNT);
    memset(m_mouse, 0, sizeof(m_mouse) * Mouse::KEYS_CNT);
}

Input::~Input() {
    delete[] m_keyboard;
    delete[] m_mouse;
}

int toSFMLKey(int key) {
    int v = -1;
    switch(key) {
        case Keyboard::A: v = sf::Keyboard::A; break;
        case Keyboard::W: v = sf::Keyboard::W; break;
        case Keyboard::S: v = sf::Keyboard::S; break;
        case Keyboard::D: v = sf::Keyboard::D; break;
        case Keyboard::Escape: v = sf::Keyboard::Escape; break;
        case Mouse::Left: v = sf::Mouse::Escape; break;
        case Mouse::Right: v = sf::Mouse::Escape; break;
    }
    return v;
}

void Input::update() {
    for (unsigned int i = 0; i < Keyboard::KEYS_CNT; ++i)
        m_keyboard[i] = sf::Keyboard::isKeyPressed(toSFMLKey(i));
    for (unsigned int i = 0; i < Mouse::KEYS_CNT; ++i)
        m_mouse[i] = sf::Mouse::isKeyPressed(toSFMLKey(i));
}