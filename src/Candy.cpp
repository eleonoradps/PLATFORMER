#include <iostream>
#include "Candy.h"

Candy::Candy()
{
	if (!candyTexture_.loadFromFile("data/Victory.png"))
	{
		std::cerr << "[Error] Could not load Player texture\n";
	}
	candySprite_.setTexture(candyTexture_);

	gameObjectType_ = GameObjectType::CANDY;

}

void Candy::Init(b2World& world)
{

	const auto playerSize = sf::Vector2f(candySprite_.getLocalBounds().width, candySprite_.getLocalBounds().height);
	candySprite_.setOrigin(playerSize / 2.0f);
	b2BodyDef bodyDef;
	bodyDef.position = pixel2meter(position_);
	bodyDef.fixedRotation = true;
	candyBody_ = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(boxSize.x) / 2.0f, pixel2meter(boxSize.y) / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.0f;
	fixtureDef.userData = this;

	candyBody_->CreateFixture(&fixtureDef);
}

void Candy::Draw(sf::RenderWindow& window)
{
	position_ = meter2pixel(candyBody_->GetPosition());
	candySprite_.setPosition(position_);
	window.draw(candySprite_);
}