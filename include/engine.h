#pragma once
#include <Box2D/Box2D.h>
#include "player.h"
#include "Candy.h"
#include "platform.h"

class Engine;

class PlatformContactListener : public b2ContactListener
{
public:
	PlatformContactListener(Engine* engine);
	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) override;

	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) override;
private:
	Engine* engine_ = nullptr;
};

class Engine
{
public:
	Engine();
	void Loop();

	void OnContactEnter(b2Fixture* c1, b2Fixture* c2);
	void OnContactExit(b2Fixture* c1, b2Fixture* c2);
	void DrawBackground(sf::RenderWindow& window);
private:
	PlayerCharacter playerCharacter_;
	PlatformContactListener platformListener_;
	sf::Texture backgroundTexture_; //background
	sf::Sprite backgroundSprite_;
	sf::Image icon_;
	Candy candy_;
	bool win = false;
};

