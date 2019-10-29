#include "globals.h"


meter pixel2meter(pixel pixel)
{
	return pixel / pixelPerMeter;
}
b2Vec2 pixel2meter(sf::Vector2f pixels)
{
	return b2Vec2(pixel2meter(pixels.x), pixel2meter(pixels.y));
}
pixel meter2pixel(meter meter)
{
	return meter * pixelPerMeter;
}
sf::Vector2f meter2pixel(b2Vec2 meters)
{
	return sf::Vector2f(meter2pixel(meters.x), meter2pixel(meters.y));
}