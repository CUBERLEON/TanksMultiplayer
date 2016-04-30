#include "Core.hpp"

#include <chrono>
#include <thread>
#include "Renderer.hpp"
#include "sys/Time.hpp"
#include "sys/Utils.hpp"
#include "sys/Debug.hpp"
#include "Tank.hpp"
#include "NetworkManager.hpp"
#include "World.hpp"
#include "Map.hpp"
#include "sys/Polygon.hpp"

Core::Core()
: m_isRunning(false), m_renderer(nullptr), m_fpsLimit(60)
{
    m_renderer = new Renderer();
}

Core::~Core() {
    delete m_renderer;
}

Renderer* Core::getRenderer() const {
    return m_renderer;
}

void Core::start() {
    if (m_isRunning)
        return;
        
    m_world = new World(new Map(100, 70));
    Tank* t = new Tank(new Polygon({{-10, -10}, {10, -10}, {10, 10}, {-10, 10}}), 10, 5);
    t->setPos({40, 40});
    m_world->addTank(t);
    
    
    run();
}

void Core::stop() {
    if (!m_isRunning)
        return;
    
    m_isRunning = false;
    
    if (m_renderer->isActive())
        m_renderer->getWindow()->close();
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
			Debug::info("%.1f fps", frames / fpsTime);
			fpsTime -= fpsRefreshTime;
			frames = 0;
		}

		if (needUpdate) {
            m_world->getTanks()[0]->setRotation(m_world->getTanks()[0]->getRotation() + updateTime);
            
            if (m_renderer->isActive()) {
                sf::Event event;
                while (m_renderer->getWindow()->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        stop();
                }
                
                m_renderer->clear();
                
                m_renderer->draw(m_world);
                // m_renderer->draw(m_interface);
                
                m_renderer->display();
            }
            
			frames++;
		}
		else {
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		}
        
		prevTime = curTime;
	}
}

void Core::sync() {
    
}