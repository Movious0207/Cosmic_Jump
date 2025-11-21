#include "main_menu_screen.h"

#include "raylib.h"

#include "game/game.h"
#include "geometry/rectangle.h"
#include "interface/button.h"
#include "game/game_constants.h"
#include "interface/ui_constants.h"
#include "audio/audio_manager.h"

using namespace Game;
using namespace UIConstants;

namespace MainMenu
{
	static Geometry::Rectangle logo;

	static Sound buttonSound;
	static Music menuMusic;
	static Texture2D logoTexture;
	static Texture2D background;

	static const int MAX_BUTTONS = 4;
	static Button::Button buttons[MAX_BUTTONS];
	static Button::Button muteButton;
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
	static void InitAudio();
	static void UpdateButtons();
	static void DrawLogo();
	static void DrawButtons();
	static void DrawVersion();
	static float GetTotalMenuHeight();

	void Init()
	{
		logoTexture = LoadTexture("res/textures/logo.png");
		background = LoadTexture("res/textures/backgrounds/gameplay/back.png");
		InitLogo();
		InitButtons();
		InitAudio();
	}

	void Input()
	{

	}

	void Update()
	{
		if(!IsMusicStreamPlaying(menuMusic))
		{
			PlayMusicStream(menuMusic);
		}
		UpdateMusicStream(menuMusic);
		UpdateButtons();
	}

	void Draw()
	{
		DrawTexturePro(background, { 0,0,1919,1080 }, { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, { 0,0 }, 0, WHITE);
		BeginDrawing();

		DrawLogo();
		DrawButtons();
		DrawVersion();

		EndDrawing();
	}

	void Close()
	{
		UnloadTexture(logoTexture);
		UnloadSound(buttonSound);
		UnloadMusicStream(menuMusic);
	}

	static void InitLogo()
	{
		float totalMenuHeight = GetTotalMenuHeight();
		float logoStartY = (SCREEN_HEIGHT - totalMenuHeight) / 2.2f;

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
		muteButton = Button::Create(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.1f, 100, 100, "Mute");
	}

	static void InitAudio()
	{
		buttonSound = LoadSound("res/sounds/buttonClick.mp3");
		menuMusic = LoadMusicStream("res/music/Menu.mp3");
	}

	static void DrawLogo()
	{
		DrawTexturePro(logoTexture, { 0,0,1760,1214 }, {logo.x,logo.y,logo.width,logo.height} , {0,0}, 0, WHITE);
	}

	static void DrawButtons()
	{
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			Button::Draw(buttons[i]);
		}
		Button::Draw(muteButton);
	}

	static void UpdateButtons()
	{
		static bool CloseGame = false;

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			Button::Update(buttons[i]);
		}
		Button::Update(muteButton);

		if (buttons[Play].clicked)
		{
			StopMusicStream(menuMusic);
			PlaySound(buttonSound);
			CosmicJump::currentScene = CosmicJump::Scenes::Gameplay;
		}

		if (buttons[Multiplayer].clicked)
		{
			StopMusicStream(menuMusic);
			PlaySound(buttonSound);
			CosmicJump::currentScene = CosmicJump::Scenes::Multiplayer;
		}

		if (buttons[Credits].clicked)
		{
			StopMusicStream(menuMusic);
			PlaySound(buttonSound);
			CosmicJump::currentScene = CosmicJump::Scenes::Credits;
		}

		if (buttons[Exit].clicked)
		{
			PlaySound(buttonSound);
			CloseGame = true;
		}

		if (muteButton.clicked)
		{
			PlaySound(buttonSound);
			if (GetMasterVolume() > 0.0f)
			{
				muteButton.text = "unmute";
				SetMasterVolume(0.0f);
			}
			else
			{
				muteButton.text = "mute";
				SetMasterVolume(0.1f);
			}
		}

		if (CloseGame && !IsSoundPlaying(buttonSound))
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
