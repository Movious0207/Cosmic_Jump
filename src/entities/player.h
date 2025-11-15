#pragma once

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
	void Draw(Player player, Player player2);

	Player Create();
	void Reset(Player& player);
	void Jump(Player& player);
}