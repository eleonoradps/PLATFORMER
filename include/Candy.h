#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D/Box2D.h>
#include "globals.h"

class Candy : public GameObject
{
public:
	Candy();
	void Init(b2World& world);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	//void OnContactBegin();
	//void OnContactEnd();
private:
	b2Body* candyBody_ = nullptr;
	sf::Texture candyTexture_; //candy
	sf::Sprite candySprite_;
	sf::Vector2f position_ = sf::Vector2f(1750, 135);
	const sf::Vector2f boxSize = sf::Vector2f(82, 39);
};

