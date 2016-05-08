#ifndef CORE_HPP
#define CORE_HPP

class Renderer;
// class NetworkManager;
class World;

class Core {
public:
    virtual ~Core();
    
    bool isRunning() const { return m_isRunning; }
    Renderer* getRenderer() const;
    
    void start();
    void stop();
    
    virtual void sync() = 0;
protected:
    Core();
    
    bool m_isRunning;

    Renderer* m_renderer;
    int m_fpsLimit;
    
    // NetworkManager* m_nManager;
    
    World* m_world;
    // Interface* m_interface;
private:
    void run();
};

#endif