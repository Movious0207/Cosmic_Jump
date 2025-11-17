#pragma once

#include "raylib.h"

#include "geometry/rectangle.h"

namespace Player
{
	struct Player
	{
		Geometry::Rectangle rectangle;
		float speedX;
		float speedY;
		bool isActive;
		bool respawning;
	};

	void Update(Player& player, float deltaTime);
	void Draw(Player player, Player player2, Texture2D p1Texture, Texture2D p2Texture);

	Player Create();
	void Reset(Player& player);
	void Jump(Player& player);
}