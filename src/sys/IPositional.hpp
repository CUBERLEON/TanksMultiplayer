#ifndef I_POSITIONAL_HPP
#define I_POSITIONAL_HPP

#include <utility>

class IPositional {
public:
    const std::pair<float, float>& getPos() const { return m_pos; }
    float getPosX() const { return m_pos.first; }
    float getPosY() const { return m_pos.second; }
    float getRotation() const { return m_rotation; }
    void setPos(const std::pair<float, float>& pos) { m_pos = pos; }
    void setPosX(float posX) { m_pos.first = posX; }
    void setPosY(float posY) { m_pos.second = posY; }
    void setRotation(float angle) { m_rotation = angle; }
protected:
    IPositional(const std::pair<float, float> pos, float angle) : m_pos(pos), m_rotation(angle) {}
    ~IPositional() {}
private:
    std::pair<float, float> m_pos;
    float m_rotation;
};

#endif