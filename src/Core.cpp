#include "Core.hpp"

#include <chrono>
#include <thread>
#include "Renderer.hpp"
#include "Time.hpp"
#include "Debug.hpp"
#include "Tank.hpp"

Core::Core()
: m_isRunning(false), m_fpsLimit(60)
{}

Core::~Core() {
    delete m_renderer;
}

Renderer* Core::getRenderer() const {
    return m_renderer;
}

void Core::start() {
    if (m_isRunning)
        return;
    
    run();
}

void Core::stop() {
    if (!m_isRunning)
        return;
    
    m_isRunning = false;
}

void Core::run() {
    m_isRunning = true;

	int frames = 0;
	double fpsTime = 0;
	double fpsRefreshTime = 1.0;

	double prevTime = Time::getTime();
	double frameTime = 1.0 / (double)m_fpsLimit;
	double unprocessedTime = 0;
    
    // Tank a(10., 20.);
    // Debug::info("%.2f\n", a.getPosX());

	while (m_isRunning) {
		// if (m_window->isCloseRequested())
		// 	stop();

		double curTime = Time::getTime();
		double passedTime = curTime - prevTime;

		unprocessedTime += passedTime;
		fpsTime += passedTime;

		bool render = false;

		if (unprocessedTime >= frameTime) {
			double updateTime = frameTime * (int)floor(unprocessedTime / frameTime);
			unprocessedTime -= updateTime;

			render = true;

			// m_scene->input((float)updateTime);
			// m_scene->update((float)updateTime);
		}

		if (fpsTime >= fpsRefreshTime) {
			Debug::info("%.1f fps", frames / fpsTime);
			fpsTime -= fpsRefreshTime;
			frames = 0;
		}

		if (render) {
			// m_renderer->refresh(m_renderingEngine);
			frames++;
		}
		else {
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		}
        
		prevTime = curTime;
	}
}