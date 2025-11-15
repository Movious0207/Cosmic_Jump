#include "player.h"

#include "raylib.h"

#include "game/game_constants.h"

using namespace Game;

namespace Player
{
	static const float DEFAULT_X = 200.0f;
	static const float DEFAULT_WIDTH = 75.0f;
	static const float DEFAULT_HEIGHT = 75.0f;

	static const float GRAVITY = 1800.0f;
	const float JUMP_STRENGTH = -650.0f;

	static void UpdateGravity(Player& player, float deltaTime);
	static void LimitWithBorders(Player& player);

	void Update(Player& player, float deltaTime)
	{
		if (player.isActive)
		{
			UpdateGravity(player, deltaTime);
		}

		player.rectangle.y += player.speedY * deltaTime;

		LimitWithBorders(player);
	}

	void Draw(Player player,Player player2)
	{
		if (player.isActive)
		{
			int x = static_cast<int>(player.rectangle.x);
			int y = static_cast<int>(player.rectangle.y);
			int width = static_cast<int>(player.rectangle.width);
			int height = static_cast<int>(player.rectangle.height);

			DrawRectangle(x, y, width, height, GREEN);
		}
		else if (player.respawning)
		{
			int x = static_cast<int>(player.rectangle.x);
			int y = SCREEN_HEIGHT / 2 - static_cast<int>(DEFAULT_WIDTH) / 2;
			int width = static_cast<int>(player.rectangle.width);
			int height = static_cast<int>(player.rectangle.height);

			DrawRectangle(x, y, width, height, WHITE);
		}

		if (player2.isActive)
		{
			int x = static_cast<int>(player2.rectangle.x);
			int y = static_cast<int>(player2.rectangle.y);
			int width = static_cast<int>(player2.rectangle.width);
			int height = static_cast<int>(player2.rectangle.height);

			DrawRectangle(x, y, width, height, RED);
		}
		else if (player2.respawning)
		{
			int x = static_cast<int>(player2.rectangle.x);
			int y = SCREEN_HEIGHT / 2 - static_cast<int>(DEFAULT_WIDTH) / 2;
			int width = static_cast<int>(player2.rectangle.width);
			int height = static_cast<int>(player2.rectangle.height);

			DrawRectangle(x, y, width, height, WHITE);
		}

	}

	Player Create()
	{
		Player newPlayer = {};

		newPlayer.rectangle.x = DEFAULT_X - 50.0f;
		newPlayer.rectangle.y = static_cast<float>(SCREEN_HEIGHT) / 2.0f - DEFAULT_WIDTH / 2.0f;
		newPlayer.rectangle.width = DEFAULT_WIDTH;
		newPlayer.rectangle.height = DEFAULT_HEIGHT;
		newPlayer.speedX = 0.0f;
		newPlayer.speedY = 0.0f;
		newPlayer.isActive = true;

		return newPlayer;
	}

	void Reset(Player& player)
	{
		player.isActive = true;
		player.rectangle.y = static_cast<float>(SCREEN_HEIGHT) / 2.0f - DEFAULT_WIDTH / 2.0f;
		player.speedY = 0.0f;
	}

	void Jump(Player& player)
	{
		player.speedY = JUMP_STRENGTH;
	}

	static void UpdateGravity(Player& player, float deltaTime)
	{
		player.speedY += GRAVITY * deltaTime;
	}

	static void LimitWithBorders(Player& player)
	{
		if (player.rectangle.y < 0.0f)
		{
			player.rectangle.y = 0.0f;
			player.speedY = 0.0f;
		}

		if (player.rectangle.y + DEFAULT_HEIGHT > SCREEN_HEIGHT)
		{
			player.rectangle.y = SCREEN_HEIGHT - DEFAULT_HEIGHT;
			player.speedY = 0.0f;
		}
	}
}