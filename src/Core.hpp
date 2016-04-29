#ifndef CORE_HPP
#define CORE_HPP

class Renderer;
class NetworkManager;
class World;

class Core {
public:
    Core();
    ~Core();
    
    Renderer* getRenderer() const;
    bool isRunning() const { return m_isRunning; }
    
    void start();
    void stop();
    
    void sync();
protected:
private:
    bool m_isRunning;
    bool m_isHost;

    Renderer* m_renderer;
    int m_fpsLimit;
    
    NetworkManager* m_nManager;
    
    World* m_world;
    // Interface* m_interface;
    
    void run();
};

#endif