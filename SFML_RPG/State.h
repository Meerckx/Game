#pragma once

#include "Entity.h"

class State
{
private:

protected:
	// Variables
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybind;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resourses
	std::vector<sf::Texture> textures;
	
	// Functions
	virtual void initKeybinds() = 0;

public:
	// Constructors / Destructors
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	// Functions
	const bool& getQuit() const;
	void endState();

	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

