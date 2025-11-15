#include "game/game.h"

#include <ctime>

#include "raylib.h"

#include "game/game_constants.h"
#include "screens/main_menu_screen.h"
#include "screens/gameplay_screen.h"
#include "screens/credits_screen.h"
#include "background/background_manager.h"
#include "audio/audio_manager.h"

using namespace Game;

namespace CosmicJump
{
	Scenes currentScene = Scenes::MainMenu;
	bool isRunning = true;

	static void Init();
	static void Input();
	static void Update();
	static void Draw();
	static void Close();

	void Play()
	{
		srand(static_cast<unsigned int>(time(0)));

		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROGRAM_NAME.c_str());
		Init();
		SetExitKey(KEY_NULL);

		while (!WindowShouldClose() && isRunning)
		{
			Input();
			Update();
			Draw();
		}

		Close();
	}

	static void Init()
	{
		Audio::Init();
		MainMenu::Init();
		Gameplay::Init();
		Credits::Init();

		Background::Init();
	}

	static void Input()
	{
		switch (currentScene)
		{
		case CosmicJump::Scenes::MainMenu:

			MainMenu::Input();

			break;
		case CosmicJump::Scenes::Gameplay:

			Gameplay::Input();

			break;
		case CosmicJump::Scenes::Multiplayer:

			Gameplay::Input();

			break;
		case CosmicJump::Scenes::Credits:

			Credits::Input();

			break;
		default:

			// THERE ARE NO OTHER SCENES

			break;
		}
	}

	static void Update()
	{
		switch (currentScene)
		{
		case CosmicJump::Scenes::MainMenu:

			MainMenu::Update();

			break;
		case CosmicJump::Scenes::Gameplay:

			Gameplay::Update();

			break;
		case CosmicJump::Scenes::Multiplayer:

			Gameplay::Update();

			break;
		case CosmicJump::Scenes::Credits:

			Credits::Update();

			break;
		default:

			// THERE ARE NO OTHER SCENES

			break;
		}
	}

	static void Draw()
	{
		switch (currentScene)
		{
		case CosmicJump::Scenes::MainMenu:

			MainMenu::Draw();

			break;
		case CosmicJump::Scenes::Gameplay:

			Gameplay::Draw();

			break;
		case CosmicJump::Scenes::Multiplayer:

			Gameplay::Draw();

			break;
		case CosmicJump::Scenes::Credits:

			Credits::Draw();

			break;
		default:

			// THERE ARE NO OTHER SCENES

			break;
		}
	}

	static void Close()
	{
		MainMenu::Close();
		Gameplay::Close();
		Credits::Close();

		Background::Close();
		Audio::Close();
	}
}