#include "Input.hpp"

#include "sys/Debug.hpp"
#include <SFML/Window.hpp>
#include <cstring>

Input::Input()
{
    m_keyboard = new int[Keyboard::KEYBOARD_CNT];
    m_mouse = new int[Mouse::MOUSE_CNT];
    memset(m_keyboard, 0, sizeof(int) * Keyboard::KEYBOARD_CNT);
    memset(m_mouse, 0, sizeof(int) * Mouse::MOUSE_CNT);
}

Input::~Input() {
    delete[] m_keyboard;
    delete[] m_mouse;
}