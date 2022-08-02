#include "GameState.h"

// Private functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key("");
		std::string keyValue("");
		while (ifs >> key >> keyValue)
			this->keybind[key] = this->supportedKeys->at(keyValue);
	}

	ifs.close();
}

// Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
}

GameState::~GameState()
{

}


// Functions
void GameState::updateInput(const float& dt)
{
	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybind.at("MOVE_LEFT"))))
		this->player.move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybind.at("MOVE_RIGHT"))))
		this->player.move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybind.at("MOVE_UP"))))
		this->player.move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybind.at("MOVE_DOWN"))))
		this->player.move(0.f, 1.f, dt);

	// Check for "Escape" input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybind.at("CLOSE"))))
		this->endState();
}

void GameState::update(const float& dt)
{
	// Updating GameState data
	this->updateMousePositions();
	this->updateInput(dt);

	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	// Rendering GameState data
	if (!target)
		target = this->window;

	this->player.render(this->window);
}
