#include "obstacle.h"

#include "raylib.h"

#include "game/game_constants.h"
#include "utilities/math_utils.h"

using namespace Game;
using namespace MathUtils;

namespace Obstacle
{
	static const float WIDTH = 80.0f;
	static const float GAP_MIN = 250.0f;
	static const float GAP_MAX = 350.0f;
	static const float SPEED_X = 500.0f;
	static const float SPAWN_X_OFFSET = 50.0f;
	static const float MARGIN_TOP = 50.0f;
	static const float MARGIN_BOTTOM = 50.0f;

	static void Move(Obstacle& obstacle, float deltaTime);
	static void Recycle(Obstacle& obstacle);
	static void RandomizeVerticalPosition(Obstacle& obstacle);

	void Update(Obstacle& obstacle, float deltaTime)
	{
		Move(obstacle, deltaTime);
		Recycle(obstacle);
	}

	void Draw(Obstacle obstacle)
	{
		int obstacleTopX = static_cast<int>(obstacle.rectangleTop.x);
		int obstacleTopY = static_cast<int>(obstacle.rectangleTop.y);
		int obstacleTopWidth = static_cast<int>(obstacle.rectangleTop.width);
		int obstacleTopHeight = static_cast<int>(obstacle.rectangleTop.height);

		int obstacleBottomX = static_cast<int>(obstacle.rectangleBottom.x);
		int obstacleBottomY = static_cast<int>(obstacle.rectangleBottom.y);
		int obstacleBottomWidth = static_cast<int>(obstacle.rectangleBottom.width);
		int obstacleBottomHeight = static_cast<int>(obstacle.rectangleBottom.height);

		int obstacleMidX = static_cast<int>(obstacle.rectangleMid.x);
		int obstacleMidY = static_cast<int>(obstacle.rectangleMid.y);
		int obstacleMidWidth = static_cast<int>(obstacle.rectangleMid.width);
		int obstacleMidHeight = static_cast<int>(obstacle.rectangleMid.height);

		DrawRectangle(obstacleTopX, obstacleTopY, obstacleTopWidth, obstacleTopHeight, RED);
		DrawRectangle(obstacleBottomX, obstacleBottomY, obstacleBottomWidth, obstacleBottomHeight, RED);
		DrawRectangleLines(obstacleMidX, obstacleMidY, obstacleMidWidth, obstacleMidHeight, BLACK);
	}

	Obstacle Create()
	{
		Obstacle newObstacle = {};

		RandomizeVerticalPosition(newObstacle);
		newObstacle.speedX = SPEED_X;
		newObstacle.isActive = true;

		return newObstacle;
	}

	void Reset(Obstacle& obstacle)
	{
		RandomizeVerticalPosition(obstacle);
	}

	static void Move(Obstacle& obstacle, float deltaTime)
	{
		obstacle.rectangleTop.x -= obstacle.speedX * deltaTime;
		obstacle.rectangleMid.x -= obstacle.speedX * deltaTime;
		obstacle.rectangleBottom.x -= obstacle.speedX * deltaTime;
	}

	static void Recycle(Obstacle& obstacle)
	{
		if (obstacle.rectangleTop.x + obstacle.rectangleTop.width < 0)
		{
			RandomizeVerticalPosition(obstacle);
		}
	}

	static void RandomizeVerticalPosition(Obstacle& obstacle)
	{
		float gap = GetFloatRandomBetween(GAP_MIN, GAP_MAX);
		float maxY = static_cast<float>(SCREEN_HEIGHT) - MARGIN_BOTTOM - gap;
		float gapY = GetFloatRandomBetween(MARGIN_TOP, maxY);

		float x = static_cast<float>(SCREEN_WIDTH) + SPAWN_X_OFFSET;

		float topHeight = gapY;
		float bottomY = gapY + gap;
		float bottomHeight = static_cast<float>(SCREEN_HEIGHT) - bottomY;

		obstacle.rectangleTop.x = x;
		obstacle.rectangleTop.y = 0.0f;
		obstacle.rectangleTop.width = WIDTH;
		obstacle.rectangleTop.height = topHeight;

		obstacle.rectangleBottom.x = x;
		obstacle.rectangleBottom.y = bottomY;
		obstacle.rectangleBottom.width = WIDTH;
		obstacle.rectangleBottom.height = bottomHeight;

		obstacle.rectangleMid.x = x;
		obstacle.rectangleMid.y = gapY;
		obstacle.rectangleMid.width = WIDTH;
		obstacle.rectangleMid.height = gap;
	}
}