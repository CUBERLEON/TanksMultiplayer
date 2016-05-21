#ifndef CORE_HPP
#define CORE_HPP

class Renderer;
class NetworkMgr;
class World;

class Core {
public:
    virtual ~Core();
    
    bool isRunning() const { return m_isRunning; }
    Renderer* getRenderer() const;
    
    void start();
    void stop();
protected:
    Core();
    
    bool m_isRunning;

    Renderer* m_renderer;
    int m_fpsLimit;
    
    NetworkMgr* m_network;
    
    World* m_world;
    // Interface* m_interface;
    
    virtual void update(float updateTime) = 0;
private:
    void init();
    void run();
};

#endif