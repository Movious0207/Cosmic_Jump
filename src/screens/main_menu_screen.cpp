#include "main_menu_screen.h"

#include "raylib.h"

#include "game/game.h"
#include "geometry/rectangle.h"
#include "interface/button.h"
#include "game/game_constants.h"
#include "interface/ui_constants.h"

using namespace Game;
using namespace UIConstants;

namespace MainMenu
{
	static Geometry::Rectangle logo;

	static const int MAX_BUTTONS = 4;
	static Button::Button buttons[MAX_BUTTONS];
	static const std::string buttonNames[MAX_BUTTONS] = { "Play", "Multiplayer" ,"Credits", "Exit"};

	enum ButtonID
	{
		Play,
		Multiplayer,
		Credits,
		Exit,
	};

	static void InitLogo();
	static void InitButtons();
	static void UpdateButtons();
	static void DrawLogo();
	static void DrawButtons();
	static void DrawVersion();
	static float GetTotalMenuHeight();

	void Init()
	{
		InitLogo();
		InitButtons();
	}

	void Input()
	{

	}

	void Update()
	{
		UpdateButtons();
	}

	void Draw()
	{
		ClearBackground(BLACK);
		BeginDrawing();

		DrawLogo();
		DrawButtons();
		DrawVersion();

		EndDrawing();
	}

	void Close()
	{

	}

	static void InitLogo()
	{
		float totalMenuHeight = GetTotalMenuHeight();
		float logoStartY = (SCREEN_HEIGHT - totalMenuHeight) / 2.0f;

		logo.x = static_cast<float>(SCREEN_WIDTH) / 2.0f - LOGO_WIDTH / 2.0f;
		logo.y = logoStartY;
		logo.width = LOGO_WIDTH;
		logo.height = LOGO_HEIGHT;
	}

	static void InitButtons()
	{
		float totalMenuHeight = GetTotalMenuHeight();
		float logoStartY = (SCREEN_HEIGHT - totalMenuHeight) / 2.0f;
		float buttonsStartY = logoStartY + LOGO_HEIGHT + LOGO_TO_BUTTONS_MARGIN;

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			float buttonCenterX = logo.x + LOGO_WIDTH / 2.0f;
			float buttonX = buttonCenterX - BUTTON_WIDTH / 2.0f;
			float buttonY = buttonsStartY + (BUTTON_HEIGHT + BUTTON_MARGIN_Y) * i;

			buttons[i] = Button::Create(buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, buttonNames[i]);
		}
	}

	static void DrawLogo()
	{
		int x = static_cast<int>(logo.x);
		int y = static_cast<int>(logo.y);
		int width = static_cast<int>(logo.width);
		int height = static_cast<int>(logo.height);

		DrawRectangle(x, y, width, height, WHITE);
	}

	static void DrawButtons()
	{
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			Button::Draw(buttons[i]);
		}
	}

	static void UpdateButtons()
	{
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			Button::Update(buttons[i]);
		}

		if (buttons[Play].clicked)
		{
			CosmicJump::currentScene = CosmicJump::Scenes::Gameplay;
		}

		if (buttons[Multiplayer].clicked)
		{
			CosmicJump::currentScene = CosmicJump::Scenes::Multiplayer;
		}

		if (buttons[Credits].clicked)
		{
			CosmicJump::currentScene = CosmicJump::Scenes::Credits;
		}

		if (buttons[Exit].clicked)
		{
			CosmicJump::isRunning = false;
		}
	}

	static void DrawVersion()
	{
		int textWidth = MeasureText(PROGRAM_VERSION.c_str(), VERSION_TEXT_SIZE);
		int margin = 10;

		int x = SCREEN_WIDTH - textWidth - margin;
		int y = SCREEN_HEIGHT - VERSION_TEXT_SIZE;

		DrawText(PROGRAM_VERSION.c_str(), x, y, VERSION_TEXT_SIZE, WHITE);
	}

	static float GetTotalMenuHeight()
	{
		return LOGO_HEIGHT + LOGO_TO_BUTTONS_MARGIN + (BUTTON_HEIGHT * MAX_BUTTONS) + (BUTTON_MARGIN_Y * (MAX_BUTTONS - 1));
	}
}
