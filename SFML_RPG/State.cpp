#include "State.h"

// Constructors / Destructors
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: window(window), supportedKeys(supportedKeys), quit(false), states(states)
{
	
}

State::~State()
{

}


// Functions
const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
