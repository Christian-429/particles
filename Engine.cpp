#include "Engine.h"

using namespace std;
using namespace sf;

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles");
}

void Engine::run()
{
	Clock timer;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		float dt = timer.restart().asSeconds();
		input();
		update(dt);
		draw();

	}
}
void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_Window.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				for (int i = 0; i < 5; i++)
				{
					Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
					int numPoints = rand() % (50 - 25 + 1) + 25;
					Particle p(m_Window, numPoints, mousePos);
					m_particles.push_back(p);
				}
			}
		}
		

	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}
}
void Engine::update(float dtAsSeconds)
{
	for (size_t i = 0; i < m_particles.size();) {
		if (m_particles[i].getTTL() > 0.0f)
		{
			m_particles[i].update(dtAsSeconds);
			i++;
		}
		else
		{
			m_particles.erase(m_particles.begin() + i);

		}
	}
}
void Engine::draw()
{
	m_Window.clear();
	for (const auto& particle : m_particles)
	{
		m_Window.draw(particle);
	}
	m_Window.display();
}