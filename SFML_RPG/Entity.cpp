#include "Entity.h"

// Initialization functions
void Entity::initVariables()
{
	this->texture = nullptr;
	this->sprite = nullptr;
	this->movementSpeed = 100.f;
}

// Constructors / Destructors
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{

}


// Component functions
void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}


// Functions
void Entity::move(const float dirX, const float dirY, const float& dt)
{
	if (this->sprite)
	{
		this->sprite->move(dirX * this->movementSpeed * dt, dirY * this->movementSpeed * dt);
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
}
