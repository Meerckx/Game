#include "MainMenuState.h"

// Initialization functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key("");
		std::string keyValue("");
		while (ifs >> key >> keyValue)
			this->keybind[key] = this->supportedKeys->at(keyValue);
	}

	ifs.close();
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Poppins-ExtraLight.ttf"))
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD FONT";
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(300, 480, 250, 50,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS"] = new Button(300, 580, 250, 50,
		&this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(300, 680, 250, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}


// Constructors / Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}


// Functions
void MainMenuState::updateInput(const float& dt)
{
	// Check for "Escape" input
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	// Updating MainMenuState data
	this->updateMousePositions();
	this->updateInput(dt);
	
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	// Rendering MainMenuState data
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}