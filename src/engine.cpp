#include "engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <globals.h>
#include <iostream>
#include "player.h"
#include "platform.h"
#include "Candy.h"

Engine::Engine() : platformListener_(this)
{
	if (!backgroundTexture_.loadFromFile("data/Background.png"))
	{
		std::cerr << "[Error] Could not load background texture\n";
	}
	backgroundSprite_.setTexture(backgroundTexture_);
}


void Engine::Loop()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "PUMPKIN PLATFORMER");
	window.setVerticalSyncEnabled(true);

	if (!icon_.loadFromFile("data/Player.png"))
	{
		std::cerr << "[Error] Could not load icon texture\n";
	}
	window.setIcon(93, 92, icon_.getPixelsPtr());

	b2World world(b2Vec2(0.0f, 9.81f));
	world.SetContactListener(&platformListener_);

	std::vector<Platform> platforms = {
		{sf::Vector2f(150, 1000), sf::Vector2f(300, 50) },
		{sf::Vector2f(700, 750), sf::Vector2f(300, 50) },
		{sf::Vector2f(1770, 200), sf::Vector2f(300, 50) },
	};

	MovingPlatform movingPlatform = MovingPlatform(sf::Vector2f(1750, 450), sf::Vector2f(300, 50));


	playerCharacter_.Init(world);
	for (auto& platform : platforms)
	{
		platform.Init(world);
	}

	movingPlatform.Init(world);
	
	candy_.Init(world);
	
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

		}
		
		playerCharacter_.Update(deltaTime.asSeconds());
		movingPlatform.Moving();
		world.Step(deltaTime.asSeconds(), velocityIterations, positionIterations);
		// Clear screen
		window.clear(sf::Color::White);
		//Draw everything here
		DrawBackground(window);
		for (auto& platform : platforms)
		{
			platform.Draw(window);
		}

		movingPlatform.Draw(window);
		candy_.Draw(window);
		playerCharacter_.Draw(window);
		// Update the window
		window.display();
		
		if (playerCharacter_.CheckDeath() > 1095)
			window.close();

		if (win == true)
			window.close();
	}
}

void Engine::OnContactEnter(b2Fixture* c1, b2Fixture* c2)
{
	GameObject* g1 = (GameObject*)(c1->GetUserData());
	GameObject* g2 = (GameObject*)(c2->GetUserData());
	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::PLATFORM)
	{
		playerCharacter_.OnContactBegin();
	}

	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::CANDY)
	{
		win = true;
	}
}

void Engine::OnContactExit(b2Fixture* c1, b2Fixture* c2)
{
	GameObject* g1 = (GameObject*)(c1->GetUserData());
	GameObject* g2 = (GameObject*)(c2->GetUserData());
	if (g1->GetGameObjectType() == GameObjectType::PLAYER_CHARACTER ||
		g2->GetGameObjectType() == GameObjectType::PLATFORM)
	{
		playerCharacter_.OnContactEnd();
	}
}

void Engine::DrawBackground(sf::RenderWindow& window)
{
	window.draw(backgroundSprite_);
}

PlatformContactListener::PlatformContactListener(Engine* engine) : engine_(engine)
{
}

void PlatformContactListener::BeginContact(b2Contact* contact)
{
	engine_->OnContactEnter(contact->GetFixtureA(), contact->GetFixtureB());
}

void PlatformContactListener::EndContact(b2Contact* contact)
{
	engine_->OnContactExit(contact->GetFixtureA(), contact->GetFixtureB());
}