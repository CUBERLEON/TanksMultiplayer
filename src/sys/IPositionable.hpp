#ifndef I_POSITIONABLE_HPP
#define I_POSITIONABLE_HPP

#include "Utils.hpp"

class IPositionable {
public:
    const std::pair<float, float>& getPos() const { return m_pos; }
    float getPosX() const { return m_pos.first; }
    float getPosY() const { return m_pos.second; }
    float getRot() const { return m_rotation; }
    float getRotDeg() const { return 180. * m_rotation / PI; }
    const std::pair<float, float>& getScale() const { return m_scale; }
    float getScaleX() const { return m_scale.first; }
    float getScaleY() const { return m_scale.second; }
    
    void setPos(const std::pair<float, float>& pos) { m_pos = pos; }
    void setPosX(float posX) { m_pos.first = posX; }
    void setPosY(float posY) { m_pos.second = posY; }
    void move(const std::pair<float, float>& d) { m_pos += d; }
    void setRot(float angle) { m_rotation = angle; }
    void setRotDeg(float angle) { m_rotation = PI * angle / 180.; }
    void rotate(float angle) { m_rotation += angle; }
    void setScale(const std::pair<float, float>& scale) { m_scale = scale; }
    void setScaleX(float scaleX) { m_scale.first = scaleX; }
    void setScaleY(float scaleY) { m_scale.second = scaleY; }
protected:
    IPositionable(const std::pair<float, float> pos = {0, 0}, float angle = 0, const std::pair<float, float>& scale = {1, 1}) : m_pos(pos), m_rotation(angle), m_scale(scale) {}
    ~IPositionable() {}
    
    std::pair<float, float> m_pos;
    float m_rotation;
    std::pair<float, float> m_scale;
private:
};

#endif