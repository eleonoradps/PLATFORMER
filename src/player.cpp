#include "player.h"
#include "globals.h"
#include "platform.h"
#include <iostream>

PlayerCharacter::PlayerCharacter()
{
	if (!playerTexture_.loadFromFile("data/Player.png"))
	{
		std::cerr << "[Error] Could not load Player texture\n";
	}
	playerSprite_.setTexture(playerTexture_);

}

void PlayerCharacter::Init(b2World& world)
{

	const auto playerSize = sf::Vector2f(playerSprite_.getLocalBounds().width, playerSprite_.getLocalBounds().height);
	playerSprite_.setOrigin(playerSize / 2.0f);
	b2BodyDef bodyDef;
	bodyDef.position = pixel2meter(playerPosition_);
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	playerBody_ = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(pixel2meter(boxSize.x) / 2.0f, pixel2meter(boxSize.y) / 2.0f);

	/*boxRectDebug_.setSize(boxSize);
	boxRectDebug_.setOrigin(boxSize / 2.0f);
	boxRectDebug_.setFillColor(sf::Color(0,255,0,120));
	boxRectDebug_.setOutlineColor(sf::Color::Green);
	boxRectDebug_.setOutlineThickness(2.0f);*/

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.0f;
	fixtureDef.userData = this;

	playerBody_->CreateFixture(&fixtureDef);
}

void PlayerCharacter::Update(float dt)
{
	float jump = playerBody_->GetLinearVelocity().y;
	bool jumpButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	if (jumpButton && !previousJumpButton_ && contactNmb_ > 0)
	{
		jump = jumpVelocity_;
	}

	float move = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		move -= 1.0f;
		playerSprite_.setScale(-1, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move += 1.0f;
		playerSprite_.setScale(1, 1);
	}
	
	const float deltaVx = move * pixel2meter(playerSpeed_) - playerBody_->GetLinearVelocity().x;
	const float fx = movementFactor_ * playerBody_->GetMass() * deltaVx / dt;

	const float deltaVy = jump - playerBody_->GetLinearVelocity().y;
	const float fy = playerBody_->GetMass() * deltaVy / dt;
	playerBody_->ApplyForce(b2Vec2(fx, fy), playerBody_->GetWorldCenter(), true);
	
	previousJumpButton_ = jumpButton;

}

void PlayerCharacter::Draw(sf::RenderWindow& window)
{

	/*boxRectDebug_.setPosition(meter2pixel(playerBody_->GetPosition()));*/
	playerPosition_ = meter2pixel(playerBody_->GetPosition());
	playerSprite_.setPosition(playerPosition_);
	window.draw(playerSprite_);
	/*window.draw(boxRectDebug_);*/
}

void PlayerCharacter::OnContactBegin()
{
	contactNmb_++;
}

void PlayerCharacter::OnContactEnd()
{
	contactNmb_--;
}

int PlayerCharacter::CheckDeath()
{
	return playerPosition_.y;
}