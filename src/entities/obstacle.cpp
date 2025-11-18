#include "obstacle.h"

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

	void Draw(Obstacle obstacle, Texture2D texture)
	{
		float obstacleTopX = obstacle.rectangleTop.x;
		float obstacleTopY = obstacle.rectangleTop.y;
		float obstacleTopWidth = obstacle.rectangleTop.width + 10.0f;
		float obstacleTopHeight = obstacle.rectangleTop.height;

		float obstacleBottomX = obstacle.rectangleBottom.x;
		float obstacleBottomY = obstacle.rectangleBottom.y;
		float obstacleBottomWidth = obstacle.rectangleBottom.width + 10.0f;
		float obstacleBottomHeight = obstacle.rectangleBottom.height;


		DrawTexturePro(texture, { 0, 0 , 511, 1396 }, { obstacleTopX,obstacleTopY , obstacleTopWidth, obstacleTopHeight }, {0,0} , 0, WHITE);
		DrawTexturePro(texture, { 0, 0, 511, 1396 }, { obstacleBottomX, obstacleBottomY, obstacleBottomWidth, obstacleBottomHeight}, {0, 0}, 0, WHITE);

		#ifdef _DEBUG
		int obstacleMidX = static_cast<int>(obstacle.rectangleMid.x);
		int obstacleMidY = static_cast<int>(obstacle.rectangleMid.y);
		int obstacleMidWidth = static_cast<int>(obstacle.rectangleMid.width);
		int obstacleMidHeight = static_cast<int>(obstacle.rectangleMid.height);

		DrawRectangleLines(obstacleMidX, obstacleMidY, obstacleMidWidth, obstacleMidHeight, BLACK);
		#endif
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