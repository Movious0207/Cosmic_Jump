#include "screens/gameplay_screen.h"

#include <string>
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

	static Sound jumpSound;
	static Sound scoreSound;
	static Sound hitSound;
	static Sound fallingSound;
	static Music gameMusic;

	static const float BUTTON_WIDTH = 60.0f;
	static const float BUTTON_HEIGHT = 60.0f;
	static const float BUTTON_MARGIN = 10.0f;

	static const std::string TEXT_CONTROLS = "Controls: SPACE to jump";
	static const std::string TEXT_MULTCONTROLS = "Controls: P1: SPACE to jump  P2: UP to Jump";
	static const std::string TEXT_START_GAME = "Press SPACE to start the game";

	static const int TUTORIAL_FONT_SIZE = 36;
	static const int TUTORIAL_TEXT_SPACING = 90;

	static const Color TUTORIAL_BACKGROUND = { 0, 0, 0, 150 };

	static float deltaTime;
	static bool isGameStarted;
	static bool isGameOver;
	static int score;
	static float respawnTimer;

	static void InitButton();
	static void InitAudio();
	static void UpdateButton();
	static void DrawButton();
	static void DrawTutorial();
	static void DrawGameEnd();
	static void DrawScore();
	static void HandleCollisionBetweenPlayerAndObstacle();
	static void HandlePlayerFloorCollision();
	static void PlayerScoreCheck();
	static void PlayerRespawn();
	static void Reset();

	void Init()
	{
		static const float DEFAULT_X = 200.0f;

		player = Player::Create();
		player2 = Player::Create();
		obstacle = Obstacle::Create();

		player.rectangle.x = DEFAULT_X - 50.0f;
		player2.rectangle.x = DEFAULT_X + 50.0f;


		InitAudio();
		InitButton();

		deltaTime = GetFrameTime();
		isGameStarted = false;
	}

	void Input()
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			StopMusicStream(gameMusic);

			CosmicJump::currentScene = CosmicJump::Scenes::MainMenu;

			isGameStarted = false;
			isGameOver = false;
		}

		if (player.isActive)
		{
			if (IsKeyPressed(KEY_SPACE) && isGameStarted)
			{
				Player::Jump(player);
				PlaySound(jumpSound);
			}
		}

		if (player2.isActive)
		{
			if (IsKeyPressed(KEY_UP) && isGameStarted)
			{
				Player::Jump(player2);
				PlaySound(jumpSound);
			}
		}

		if (IsKeyPressed(KEY_SPACE) && !isGameStarted && !isGameOver)
		{
			isGameStarted = true;
			Player::Jump(player);

			if (CosmicJump::currentScene == CosmicJump::Scenes::Multiplayer)
			{
				Player::Jump(player2);
			}
			PlaySound(jumpSound);
		}
		else if (IsKeyPressed(KEY_SPACE) && !isGameStarted)
		{
			isGameOver = false;
		}
	}

	void Update()
	{
		if (!IsMusicStreamPlaying(gameMusic))
		{
			PlayMusicStream(gameMusic);
		}
		UpdateMusicStream(gameMusic);

		deltaTime = GetFrameTime();

		if (isGameStarted)
		{
			Background::Update(deltaTime);

			if (CosmicJump::currentScene == CosmicJump::Scenes::Gameplay)
			{
				Player::Update(player, deltaTime);
			}
			else if (CosmicJump::currentScene == CosmicJump::Scenes::Multiplayer)
			{
				Player::Update(player, deltaTime);
				Player::Update(player2, deltaTime);

				if (!player.isActive && player2.isActive)
				{
					PlayerRespawn();
				}
				else if (player.isActive && !player2.isActive)
				{
					PlayerRespawn();
				}
			}

			Obstacle::Update(obstacle, deltaTime);

			HandleCollisionBetweenPlayerAndObstacle();
			HandlePlayerFloorCollision();
			PlayerScoreCheck();
		}

		UpdateButton();
	}

	void Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		Background::Draw();


		Player::Draw(player,player2);


		Obstacle::Draw(obstacle);

		if (!isGameStarted && !isGameOver)
		{
			Reset();

			Player::Draw(player,player2);

			DrawTutorial();
		}
		else if (isGameOver)
		{
			DrawGameEnd();
		}

		if (isGameStarted)
		{
			DrawScore();
		}

		DrawButton();

		EndDrawing();
	}

	void Close()
	{
		UnloadSound(jumpSound);
		UnloadSound(scoreSound);
		UnloadSound(hitSound);
		UnloadSound(fallingSound);
	}

	static void InitButton()
	{
		float x = static_cast<float>(SCREEN_WIDTH) - BUTTON_WIDTH - BUTTON_MARGIN;
		float y = BUTTON_MARGIN;

		button = Button::Create(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, buttonName);
	}

	static void InitAudio()
	{
		jumpSound = LoadSound("res/sounds/Jump.wav");
		scoreSound = LoadSound("res/sounds/Score.wav");
		hitSound = LoadSound("res/sounds/Hit.mp3");
		fallingSound = LoadSound("res/sounds/Falling.wav");
		gameMusic = LoadMusicStream("res/music/Game.mp3");
	}

	static void UpdateButton()
	{
		Button::Update(button);

		if (button.clicked)
		{
			StopMusicStream(gameMusic);
			CosmicJump::currentScene = CosmicJump::Scenes::MainMenu;
			isGameStarted = false;
			isGameOver = false;
		}
	}

	static void DrawButton()
	{
		Button::Draw(button);
	}

	static void DrawTutorial()
	{
		int textControlsWidth = 0;

		if (CosmicJump::currentScene == CosmicJump::Scenes::Multiplayer)
		{
			textControlsWidth = MeasureText(TEXT_MULTCONTROLS.c_str(), TUTORIAL_FONT_SIZE);
		}
		else
		{
			textControlsWidth = MeasureText(TEXT_CONTROLS.c_str(), TUTORIAL_FONT_SIZE);
		}

		int textStartGameWidth = MeasureText(TEXT_START_GAME.c_str(), TUTORIAL_FONT_SIZE);

		int textControlsX = (SCREEN_WIDTH - textControlsWidth) / 2;
		int textStartGameX = (SCREEN_WIDTH - textStartGameWidth) / 2;

		int totalBlockHeight = TUTORIAL_FONT_SIZE + TUTORIAL_TEXT_SPACING + TUTORIAL_FONT_SIZE;

		int blockTopY = (SCREEN_HEIGHT - totalBlockHeight) / 2;

		int textControlsY = blockTopY;
		int textStartGameY = textControlsY + TUTORIAL_FONT_SIZE + TUTORIAL_TEXT_SPACING;

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TUTORIAL_BACKGROUND);

		if (CosmicJump::currentScene == CosmicJump::Scenes::Multiplayer)
		{
			DrawText(TEXT_MULTCONTROLS.c_str(), textControlsX, textControlsY, TUTORIAL_FONT_SIZE, WHITE);
		}
		else
		{
			DrawText(TEXT_CONTROLS.c_str(), textControlsX, textControlsY, TUTORIAL_FONT_SIZE, WHITE);
		}

		DrawText(TEXT_START_GAME.c_str(), textStartGameX, textStartGameY, TUTORIAL_FONT_SIZE, WHITE);
	}

	static void DrawGameEnd()
	{
		int textGameOverWidth = 0;


		textGameOverWidth = MeasureText("GAME OVER!", TUTORIAL_FONT_SIZE);


		int textScoreWidth = MeasureText(std::to_string(score).c_str(), TUTORIAL_FONT_SIZE);
		textScoreWidth += MeasureText("Final Score: ", TUTORIAL_FONT_SIZE);

		int textGameOverX = (SCREEN_WIDTH - textGameOverWidth) / 2;
		int textScoreX = (SCREEN_WIDTH - textScoreWidth) / 2;

		int totalBlockHeight = TUTORIAL_FONT_SIZE + TUTORIAL_TEXT_SPACING + TUTORIAL_FONT_SIZE;
		int blockTopY = (SCREEN_HEIGHT - totalBlockHeight) / 2;

		int textGameOverY = blockTopY;
		int textScoreY = textGameOverY + TUTORIAL_FONT_SIZE + TUTORIAL_TEXT_SPACING;

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TUTORIAL_BACKGROUND);

		DrawText("GAME OVER!", textGameOverX, textGameOverY, TUTORIAL_FONT_SIZE, WHITE);

		DrawText("Final Score: ", textScoreX, textScoreY, TUTORIAL_FONT_SIZE, WHITE);

		textScoreWidth = MeasureText("Final Score: ", TUTORIAL_FONT_SIZE);

		textScoreX = (SCREEN_WIDTH + textScoreWidth) / 2;

		DrawText(std::to_string(score).c_str(), textScoreX, textScoreY, TUTORIAL_FONT_SIZE, WHITE);
	}

	static void DrawScore()
	{
		int scoreYPos = SCREEN_HEIGHT / 6;
		int scoreXPos = { SCREEN_WIDTH / 2 };

		DrawText(std::to_string(score).c_str(), scoreXPos, scoreYPos, 50, WHITE);

	}

	static void HandleCollisionBetweenPlayerAndObstacle()
	{
		if (player.isActive)
		{
			if (CheckCollisionRectangle(player.rectangle, obstacle.rectangleTop) ||
				CheckCollisionRectangle(player.rectangle, obstacle.rectangleBottom))
			{
				PlaySound(hitSound);
				player.isActive = false;
				respawnTimer = 3.0f;
			}
		}
		if (player2.isActive)
		{
			if (CheckCollisionRectangle(player2.rectangle, obstacle.rectangleTop) ||
				CheckCollisionRectangle(player2.rectangle, obstacle.rectangleBottom))
			{
				PlaySound(hitSound);
				player2.isActive = false;
				respawnTimer = 3.0f;
			}
		}

		if (!player.isActive && !player2.isActive)
		{
			isGameStarted = false;
			isGameOver = true;
		}

	}

	static void PlayerScoreCheck()
	{
		static bool isColliding = { false };
		static bool wasColliding = { false };

		if (player.isActive && CheckCollisionRectangle(player.rectangle, obstacle.rectangleMid))
		{
			isColliding = true;
			wasColliding = true;
		}
		else
		{
			isColliding = false;
		}
		
		if (!player.isActive && player2.isActive && CheckCollisionRectangle(player2.rectangle, obstacle.rectangleMid))
		{
			isColliding = true;
			wasColliding = true;
		}
		else if (!player.isActive)
		{
			isColliding = false;
		}

		if (!isColliding && wasColliding)
		{
			PlaySound(scoreSound);
			score++;
			wasColliding = false;
		}
	}

	static void HandlePlayerFloorCollision()
	{
		if (player.rectangle.y + player.rectangle.height >= SCREEN_HEIGHT && player.isActive)
		{
			PlaySound(fallingSound);
			player.isActive = false;
			respawnTimer = 3.0f;
		}
		if (player2.rectangle.y + player2.rectangle.height >= SCREEN_HEIGHT && player2.isActive)
		{
			PlaySound(fallingSound);
			player2.isActive = false;
			respawnTimer = 3.0f;
		}
		if (!player.isActive && !player2.isActive)
		{
			isGameStarted = false;
			isGameOver = true;
		}

	}

	static void PlayerRespawn()
	{
		respawnTimer -= GetFrameTime();
		if (!player.isActive && respawnTimer < 1)
		{
			player.respawning = true;
		}
		if (!player.isActive&& respawnTimer < 0)
		{
			player.respawning = false;
			Player::Reset(player);
		}
		if (!player2.isActive && respawnTimer < 1)
		{
			player2.respawning = true;
		}
		if (!player2.isActive && respawnTimer < 0)
		{
			player2.respawning = false;
			Player::Reset(player2);
		}
	}

	static void Reset()
	{
		score = 0;

		Player::Reset(player);

		Player::Reset(player2);

		if (CosmicJump::currentScene != CosmicJump::Scenes::Multiplayer)
		{
			player2.isActive = false;
		}

		Obstacle::Reset(obstacle);
	}
}