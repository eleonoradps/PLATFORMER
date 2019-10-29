#include "platform.h"
#include "globals.h"

Platform::Platform(sf::Vector2f position, sf::Vector2f size) : position_(position), size_(size)
{
	gameObjectType_ = GameObjectType::PLATFORM;
}
void Platform::Init(b2World& world)
{
	rectShape_.setPosition(position_);
	rectShape_.setSize(size_);
	rectShape_.setOrigin(size_ / 2.0f);
	rectShape_.setFillColor(sf::Color(47, 40, 103));
	rectShape_.setOutlineColor(sf::Color(24, 18, 73));
	rectShape_.setOutlineThickness(2.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position = pixel2meter(position_);
	platformBody_ = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(size_.x / 2.0f), pixel2meter(size_.y / 2.0f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.userData = this;
	fixtureDef.friction = 0.0f;
	platformBody_->CreateFixture(&fixtureDef);
}
void Platform::Draw(sf::RenderWindow& window)
{
	position_ = meter2pixel(platformBody_->GetPosition());
	rectShape_.setPosition(position_);
	window.draw(rectShape_);
}

MovingPlatform::MovingPlatform(sf::Vector2f position, sf::Vector2f size) : Platform(position, size)
{

}

void MovingPlatform::Moving()
{
	// platformBody_->SetLinearVelocity(b2Vec2(0.5, 0));
	// platformBody_->SetLinearVelocity(b2Vec2(-0.5, 0));

	// nombre magique, changer code

	b2Vec2 position = platformBody_->GetPosition();

	if (position.x > 16)
	{
		platformBody_->SetLinearVelocity(b2Vec2(-3, 0));
	}
	if (position.x < 10)
	{
		platformBody_->SetLinearVelocity(b2Vec2(3, 0));
	}

}
