#include "Core.hpp"

#include <chrono>
#include <thread>
#include "sys/Time.hpp"
#include "sys/Utils.hpp"
#include "sys/Debug.hpp"
#include "Tank.hpp"
// #include "NetworkManager.hpp"
#include "World.hpp"
#include "Map.hpp"
#include "Input.hpp"
#include "sys/Polygon.hpp"
#ifdef SFML
    #include "sfml/SFMLrenderer.hpp"
    #include "sfml/SFMLnetworkMgr.hpp"
#endif

Core::Core()
: m_isRunning(false), m_renderer(nullptr), m_fpsLimit(60), m_world(nullptr)
{
#ifdef SFML
    m_renderer = new SFMLrenderer();
    m_network = new SFMLnetworkMgr();
#endif
}

Core::~Core() {
    delete m_renderer;
}

Renderer* Core::getRenderer() const {
    if (m_renderer == nullptr)
        Debug::warning("Returning nullptr in Core.getRenderer()");
    return m_renderer;
}

void Core::init() {
    if (m_renderer->isActive()) {
        m_renderer->requestFocus();
        
        if (m_world) {
            m_renderer->setDrawTransform(true);
            m_renderer->setDrawTransform(m_world->getMap()->getWidth(), m_world->getMap()->getHeight());
        }
    }    
}

void Core::start() {
    if (m_isRunning)
        return;
    
    try {		
        init();
        run();
    } catch (const std::exception& e) {
        Debug::error(e.what());
        stop();
    }
}

void Core::stop() {
    m_isRunning = false;
    
    if (m_renderer->isActive())
        m_renderer->destroyWindow();
}

void Core::run() {
    m_isRunning = true;

    int frames = 0;
    double fpsTime = 0;
    double fpsRefreshTime = 1.0;

    double prevTime = Time::getTime();
    double frameTime = 1.0 / (double)m_fpsLimit;
    double unprocessedTime = 0;

    while (m_isRunning) {
        double curTime = Time::getTime();
        double passedTime = curTime - prevTime;

        unprocessedTime += passedTime;
        fpsTime += passedTime;

        bool needUpdate = false;
        double updateTime = 0.;

        if (unprocessedTime >= frameTime) {
            updateTime = frameTime * (int)floor(unprocessedTime / frameTime);
            unprocessedTime -= updateTime;

            needUpdate = true;
        }

        if (fpsTime >= fpsRefreshTime) {
            // Debug::info("%.1f fps", frames / fpsTime);
            fpsTime -= fpsRefreshTime;
            frames = 0;
        }

        if (needUpdate) {
            if (m_renderer->isActive()) {
                m_renderer->input();
                m_renderer->update();
            }
            
            update(updateTime);
            
            if (m_renderer->isActive()) {
                m_renderer->clear();
                
                if (m_world)
                    m_renderer->draw(m_world);
                // m_renderer->draw(m_interface);
                
                m_renderer->display();
            }
            
            frames++;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        
        prevTime = curTime;
    }
    
    m_isRunning = false;
}