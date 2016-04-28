#ifndef CORE_HPP
#define CORE_HPP

class Renderer;

class Core {
public:
    Core();
    ~Core();
    
    Renderer* getRenderer() const;
    bool isRunning() const { return m_isRunning; }
    
    void start();
    void stop();
protected:
private:
    bool m_isRunning;

    Renderer* m_renderer;
    int m_fpsLimit;
    
    void run();
};

#endif