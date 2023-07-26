#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include <iostream>


/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

//a singleton class
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner* BaseRunner::getInstance()
{
	if (sharedInstance == NULL)
	{
		//initialize
		sharedInstance = new BaseRunner();
	}

	return sharedInstance;
}
BaseRunner::BaseRunner() :window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Barrage of Threads", sf::Style::Close)
{
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load BG objects
	BGObject* bgObject = new BGObject("BGObject", "PixelSky_BG", 250);
	GameObjectManager::getInstance()->addObject(bgObject);

	BGObject* mgObject = new BGObject("BGObject", "PixelSky_MG", 500);
	GameObjectManager::getInstance()->addObject(mgObject);

	BGObject* fgObject = new BGObject("BGObject", "PixelSky_FG", 750);
	GameObjectManager::getInstance()->addObject(fgObject);


	/*TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);*/

	fpsCounter = new FPSCounter();
	fpsCounter->initialize();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run()
{
	sf::Clock clock;
	window.setFramerateLimit(60);
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (this->window.isOpen())
	{
		sf::Time currentTime = clock.restart();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		FPS = 1 / currentTime.asSeconds();

		std::cout << "FPS: " << deltaTime << "\n ";
		processEvents();
		update(sf::seconds(deltaTime));


		render();
	}
}

float BaseRunner::getFPS()
{
	return this->FPS;
}

void BaseRunner::setFPS(float value)
{
	FPS = value;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {

		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time deltaTime)
{
	GameObjectManager::getInstance()->update(deltaTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	fpsCounter->draw(&this->window);
	this->window.display();
}