#include "credits_screen.h"

#include "raylib.h"

#include "game/game.h"
#include "interface/button.h"
#include "game/game_constants.h"
#include "interface/ui_constants.h"

using namespace Game;
using namespace UIConstants;

namespace Credits
{
	static const std::string TITLE = "Credits";
	static const std::string LABEL = "Developed by:";
	static const std::string AUTHOR = "Jonas Canaza and Lucas Galli";

	static const int FONT_SIZE_TITLE = 64;
	static const int FONT_SIZE_TEXT = 32;

	static const float TITLE_TOP_OFFSET = 0.1f;
	static const float LABEL_Y_CENTER = 0.5f;
	static const int AUTHOR_LINE_SPACING = 40;

	static Button::Button button;
	static const std::string buttonName = "Back";

	static Sound buttonSound;

	static const int BUTTON_MARGIN_BOTTOM = 10;

	static void DrawInfo();
	static void InitButton();
	static void InitAudio();
	static void UpdateButton();
	static void DrawButton();

	void Init()
	{
		InitAudio();
		InitButton();
	}

	void Input()
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			CosmicJump::currentScene = CosmicJump::Scenes::MainMenu;
		}
	}

	void Update()
	{
		UpdateButton();
	}

	void Draw()
	{
		ClearBackground(BLACK);
		BeginDrawing();

		DrawInfo();
		DrawButton();

		EndDrawing();
	}

	void Close()
	{
		UnloadSound(buttonSound);
	}

	static void DrawInfo()
	{
		int titleX = (SCREEN_WIDTH - MeasureText(TITLE.c_str(), FONT_SIZE_TITLE)) / 2;
		int titleY = static_cast<int>(SCREEN_HEIGHT * TITLE_TOP_OFFSET);

		int labelX = (SCREEN_WIDTH - MeasureText(LABEL.c_str(), FONT_SIZE_TEXT)) / 2;
		int labelY = static_cast<int>(SCREEN_HEIGHT * LABEL_Y_CENTER);

		int authorX = (SCREEN_WIDTH - MeasureText(AUTHOR.c_str(), FONT_SIZE_TEXT)) / 2;
		int authorY = labelY + AUTHOR_LINE_SPACING;

		DrawText(TITLE.c_str(), titleX, titleY, FONT_SIZE_TITLE, WHITE);
		DrawText(LABEL.c_str(), labelX, labelY, FONT_SIZE_TEXT, WHITE);
		DrawText(AUTHOR.c_str(), authorX, authorY, FONT_SIZE_TEXT, WHITE);
	}

	static void InitButton()
	{
		float x = static_cast<float>(SCREEN_WIDTH) / 2.0f - BUTTON_WIDTH / 2.0f;
		float y = static_cast<float>(SCREEN_HEIGHT) - BUTTON_HEIGHT - BUTTON_MARGIN_BOTTOM;

		button = Button::Create(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, buttonName);
	}

	static void InitAudio()
	{
		buttonSound = LoadSound("res/sounds/buttonClick.mp3");
	}

	static void UpdateButton()
	{
		Button::Update(button);

		if (button.clicked)
		{
			PlaySound(buttonSound);
			CosmicJump::currentScene = CosmicJump::Scenes::MainMenu;
		}
	}

	static void DrawButton()
	{
		Button::Draw(button);
	}
}