#pragma once
#include "AGameObject.h"
class BGObject : public AGameObject
{
	public: 
		BGObject(String name, String textureName, float spd);
		void initialize();
		void processInput(sf::Event event);
		void update(sf::Time deltaTime);
	private:
		float SPEED_MULTIPLIER = 3000.0f;
		String textName;
};

