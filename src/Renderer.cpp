#include "Renderer.hpp"

#include "Input.hpp"

Renderer::Renderer()
: m_active(false), m_width(0), m_height(0), m_title(""), m_antialiasing(0), m_activeDT(false), m_widthDT(1), m_heightDT(1),
  m_input(nullptr)
{}

Renderer::~Renderer()
{
    delete m_input;
}

Input* Renderer::getInput() const {
    return m_input;
}