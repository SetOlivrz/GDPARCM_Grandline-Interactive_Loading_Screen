#include <SFML/Graphics.hpp>
#include <vector>
#include "FPSCounter.h"

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static BaseRunner* getInstance();
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time deltaTime;

	void run();
	float getFPS();
	void setFPS(float value);


private:

	BaseRunner(BaseRunner const&) {};             // copy constructor is private
	BaseRunner& operator=(BaseRunner const&) {};  // assignment operator is private
	static BaseRunner* sharedInstance;

	BaseRunner();

	sf::RenderWindow window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

private:
	sf::Clock clock;
	FPSCounter* fpsCounter;
	float FPS = 0;

};


