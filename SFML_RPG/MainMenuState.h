#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	// Variables
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	// Initialization functions
	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initButtons();

public:
	// Constructors / Destructors
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	// Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

