#include "BGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

BGObject::BGObject(string name, string textureName, float spd) : AGameObject(name)
{
	this->textName = textureName;
	this->SPEED_MULTIPLIER = spd;
}

void BGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(this->textName, 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	//set sprite size based on texture size
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	// scale to screen
	setScale(8, 8.64);

	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0,0,BaseRunner::WINDOW_WIDTH*8, BaseRunner::WINDOW_HEIGHT)); 
	this->setPosition(0, 0);
}

void BGObject::processInput(sf::Event event)
{
}

void BGObject::update(sf::Time deltaTime)
{
	//make BG scroll slowly
	sf::Vector2f position = this->getPosition();
	position.x -= this->SPEED_MULTIPLIER * deltaTime.asSeconds();

	this->setPosition(position.x, position.y);

	sf::Vector2f localPos = this->sprite->getPosition();
	if (localPos.x < -BaseRunner::WINDOW_WIDTH*7) {
		//reset position
	this->setPosition(0, 0);
	}
	else {
		
	}

}
