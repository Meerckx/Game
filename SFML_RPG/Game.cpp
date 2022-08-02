#include "Game.h"

// Static functions


// Initialization functions
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
}

void Game::initWindow()
{
	// Creating local variables to describe window's configuration
	// We get information from the file "window.ini"
	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned int framerateLimit = 120;
	bool verticalSyncEnabled = false;
	unsigned int antialiasingLevel = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> verticalSyncEnabled;
		ifs >> antialiasingLevel;
	}

	ifs.close();

	windowSettings.antialiasingLevel = antialiasingLevel;

	if (fullscreen)
		this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setFramerateLimit(framerateLimit);
	this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key("");
		int keyValue;
		while (ifs >> key >> keyValue)
			this->supportedKeys[key] = keyValue;
	}

	ifs.close();

	for (auto i : this->supportedKeys)
		std::cout << i.first << " " << i.second << "\n";
}

void Game::initStates()
{
	// Adding GameState in our stack of states
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}


// Constructors / Destructors
Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


// Functions
void Game::endApplication()
{
	std::cout << "End Application\n";
}

void Game::updateDt()
{
	// Update the dt variable each frame
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	// Updating SFML events
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	// Updating variables
	this->updateSFMLEvents();

	// If our stack of states is not empty update top (active) state
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		// If top state requires to quit
		// End it's state and delete it
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	// Else end application
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	// Render items
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	// Run application
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
