#include "Core.hpp"

#include <chrono>
#include <thread>
#include "sys/Time.hpp"
#include "sys/Utils.hpp"
#include "sys/Debug.hpp"
#include "Tank.hpp"
#include "NetworkManager.hpp"
#include "World.hpp"
#include "Map.hpp"
#include "sys/Polygon.hpp"
#if defined(_WIN32) || defined(__linux__) 
	#include "SFMLRenderer.hpp"
#endif

Core::Core()
: m_isRunning(false), m_renderer(nullptr), m_fpsLimit(60)
{
	#if defined(_WIN32) || defined(__linux__)
    	m_renderer = new SFMLRenderer();
	#endif
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
    
	try {
		m_world = new World(new Map("1"));
		Tank* t = new Tank(10, 5, new Polygon("tank_1"));
		t->setPos({40, 40});
		t->setRotDeg(15);
		m_world->addTank(t);
		
		if (m_renderer->isActive()) {
			m_renderer->requestFocus();
			m_renderer->setDrawTransform(true);
			m_renderer->setDrawTransform(m_world->getMap()->getWidth(), m_world->getMap()->getHeight());
		}
		
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

	while (m_isRunning && m_renderer->isActive()) {
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
            // m_world->getTanks()[0]->rotate(updateTime);
            
			if (m_renderer->isActive())
				m_renderer->update();			
			
            if (m_renderer->isActive()) {
                m_renderer->clear();   
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

void Core::sync() {
    
}