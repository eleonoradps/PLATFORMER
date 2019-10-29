#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

const float framerate = 60.f;
//For pixel to meter conversion
const float pixelPerMeter = 100.0f;

using meter = float;
using pixel = float;

//For b2World step
const int velocityIterations = 8;
const int positionIterations = 8;


meter pixel2meter(pixel pixel);
b2Vec2 pixel2meter(sf::Vector2f pixels);
pixel meter2pixel(pixel meter);
sf::Vector2f meter2pixel(b2Vec2 meters);


enum class GameObjectType
{
	PLAYER_CHARACTER,
	PLATFORM,
	CANDY
};

class GameObject
{
public:
	GameObjectType GetGameObjectType() const { return gameObjectType_; };
protected:
	GameObjectType gameObjectType_;

};

#endif