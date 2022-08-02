#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

enum class buttonStates
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

class Button
{
private:
	// Variables
	buttonStates buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	// Constructors / Destructors
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, sf::Color idleColor,
		sf::Color hoverColor, sf::Color activeColor);
	~Button();

	// Functions
	const bool isPressed() const;

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

