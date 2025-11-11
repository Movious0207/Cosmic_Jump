#include "screens/gameplay_screen.h"

#include "raylib.h"

#include "game/game.h"
#include "game/game_constants.h"
#include "entities/player.h"
#include "entities/obstacle.h"
#include "collision/collision_manager.h"
#include "interface/button.h"
#include "background/background_manager.h"

using namespace Game;
using namespace Collision;

namespace Gameplay
{
	static Player::Player player;
	
	static Player::Player player2;

	static Obstacle::Obstacle obstacle;

	static Button::Button button;
	static const std::string buttonName = " | | ";

	static const float BUTTON_WIDTH = 60.0f;
	static const float BUTTON_HEIGHT = 60.0f;
	static const float BUTTON_MARGIN = 10.0f;

	static const std::string TEXT_CONTROLS = "Controls: SPACE to jump";
	static const std::string TEXT_START_GAME = "Press SPACE to start the game";

	static const int TUTORIAL_FONT_SIZE = 36;
	static const int TUTORIAL_TEXT_SPACING = 90;

	static const Color TUTORIAL_BACKGROUND = { 0, 0, 0, 150 };

	static float deltaTime;
	static bool isGameStarted;

	static void InitButton();
	static void UpdateButton();
	static void DrawButton();
	static void DrawTutorial();
	static void HandleCollisionBetweenPlayerAndObstacle();
	static void HandlePlayerFloorCollision();
	static void Reset();

	void Init()
	{
		player = Player::Create();
		player2 = Player::Create();
		obstacle = Obstacle::Create();

		InitButton();

		deltaTime = GetFrameTime();
		isGameStarted = false;
	}

	void Input()
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			CosmicJump::currentScene = CosmicJump::Scenes::MainMenu;
		}

		if (player.isActive)
		{
			if (IsKeyPressed(KEY_SPACE) && isGameStarted)
			{
				Player::Jump(player);
			}
		}

		if (player2.isActive)
		{
			if (IsKeyPressed(KEY_UP) && isGameStarted)
			{
				Player::Jump(player2);
			}
		}
		if (IsKeyPressed(KEY_SPACE) && !isGameStarted)
		{
			isGameStarted = true;
			Player::Jump(player);
		}
	}

	void Update()
	{
		deltaTime = GetFrameTime();

		if (isGameStarted)
		{
			Background::Update(deltaTime);

			if (player.isActive)
			{
				Player::Update(player, deltaTime);
			}
			if (player2.isActive)
			{
				Player::Update(player2, deltaTime);
			}
			Obstacle::Update(obstacle, deltaTime);

			HandleCollisionBetweenPlayerAndObstacle();
			HandlePlayerFloorCollision();
		}

		UpdateButton();
	}

	void Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		Background::Draw();

		if (player.isActive)
		{
			Player::Draw(player);
		}
		if (player2.isActive)
		{
			Player::Draw(player2);
		}
		Obstacle::Draw(obstacle);

		if (!isGameStarted)
		{
			DrawTutorial();
		}

		DrawButton();

		EndDrawing();
	}

	void Close()
	{

	}

	static void InitButton()
	{
		float x = static_cast<float>(SCREEN_WIDTH) - BUTTON_WIDTH - BUTTON_MARGIN;
		float y = BUTTON_MARGIN;

		button = Button::Create(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, buttonName);
	}

	static void UpdateButton()
	{
		Button::Update(button);

		if (button.clicked)
		{
			CosmicJump::currentScene = CosmicJump::Scenes::MainMenu;
		}
	}

	static void DrawButton()
	{
		Button::Draw(button);
	}

	static void DrawTutorial()
	{
		int textControlsWidth = MeasureText(TEXT_CONTROLS.c_str(), TUTORIAL_FONT_SIZE);
		int textStartGameWidth = MeasureText(TEXT_START_GAME.c_str(), TUTORIAL_FONT_SIZE);

		int textControlsX = (SCREEN_WIDTH - textControlsWidth) / 2;
		int textStartGameX = (SCREEN_WIDTH - textStartGameWidth) / 2;

		int totalBlockHeight = TUTORIAL_FONT_SIZE + TUTORIAL_TEXT_SPACING + TUTORIAL_FONT_SIZE;

		int blockTopY = (SCREEN_HEIGHT - totalBlockHeight) / 2;

		int textControlsY = blockTopY;
		int textStartGameY = textControlsY + TUTORIAL_FONT_SIZE + TUTORIAL_TEXT_SPACING;

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TUTORIAL_BACKGROUND);
		DrawText(TEXT_CONTROLS.c_str(), textControlsX, textControlsY, TUTORIAL_FONT_SIZE, WHITE);
		DrawText(TEXT_START_GAME.c_str(), textStartGameX, textStartGameY, TUTORIAL_FONT_SIZE, WHITE);
	}

	static void HandleCollisionBetweenPlayerAndObstacle()
	{

		if (CheckCollisionRectangle(player.rectangle, obstacle.rectangleTop) ||
			CheckCollisionRectangle(player.rectangle, obstacle.rectangleBottom))
		{
			player.isActive = false;
		}
		if (CheckCollisionRectangle(player2.rectangle, obstacle.rectangleTop) ||
			CheckCollisionRectangle(player2.rectangle, obstacle.rectangleBottom))
		{
			player2.isActive = false;
		}

		if (!player.isActive && !player2.isActive)
		{
			Reset();
			isGameStarted = false;
		}

	}

	static void HandlePlayerFloorCollision()
	{
		if (player.rectangle.y + player.rectangle.height >= SCREEN_HEIGHT)
		{
			player.isActive = false;
		}
		if (player2.rectangle.y + player2.rectangle.height >= SCREEN_HEIGHT)
		{
			player2.isActive = false;
		}
		if (!player.isActive && !player2.isActive)
		{
			Reset();
			isGameStarted = false;
		}

	}

	static void Reset()
	{
		Player::Reset(player);
		Player::Reset(player2);
		Obstacle::Reset(obstacle);
	}
}