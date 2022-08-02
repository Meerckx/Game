#pragma once

#include "MainMenuState.h"

class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	// Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Functions
	void endApplication();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};

