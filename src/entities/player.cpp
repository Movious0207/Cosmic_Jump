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

	void Draw(Player player,Player player2,Texture2D p1Texture, Texture2D p2Texture)
	{
		if (player.isActive)
		{
			float x = player.rectangle.x + player.rectangle.height;
			float y = player.rectangle.y;

			DrawTextureEx(p1Texture, { x, y }, 90, 0.4f, WHITE);
		}
		else if (player.respawning)
		{
			int x = static_cast<int>(player.rectangle.x + player.rectangle.height);
			int y = SCREEN_HEIGHT / 2 - static_cast<int>(DEFAULT_WIDTH) / 2;

			DrawTextureEx(p1Texture, { static_cast<float> (x), static_cast<float>(y) }, 90, 0.4f, GRAY);
		}

		if (player2.isActive)
		{
			float x = player2.rectangle.x + player2.rectangle.height;
			float y = player2.rectangle.y;

			DrawTextureEx(p2Texture, { x, y }, 90, 0.4f, WHITE);
		}
		else if (player2.respawning)
		{
			int x = static_cast<int>(player2.rectangle.x + player2.rectangle.height);
			int y = SCREEN_HEIGHT / 2 - static_cast<int>(DEFAULT_WIDTH) / 2;

			DrawTextureEx(p2Texture, { static_cast<float> (x), static_cast<float>(y) }, 90, 0.4f, GRAY);
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
		player.respawning = false;
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