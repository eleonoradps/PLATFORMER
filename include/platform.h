#pragma once
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "globals.h"

class Engine;

class Platform : public GameObject
{
public:
	Platform(sf::Vector2f position, sf::Vector2f size);
	void Init(b2World& world);
	void Draw(sf::RenderWindow& window);

protected:
	b2Body* platformBody_ = nullptr;
	sf::RectangleShape rectShape_;
	sf::Vector2f position_;

private:
	sf::Vector2f size_;
};

class MovingPlatform : public Platform
{
public:
	MovingPlatform(sf::Vector2f position, sf::Vector2f size);
	void Moving();


private:



};