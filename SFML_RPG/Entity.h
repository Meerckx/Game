#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"

class Entity
{
private:
	// Initialization functions
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	float movementSpeed;

public:
	// Constructors / Destructors
	Entity();
	virtual ~Entity();

	// Component functions
	void createSprite(sf::Texture* texture);

	// Functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

