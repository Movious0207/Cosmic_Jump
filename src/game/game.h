#pragma once

namespace CosmicJump
{
	enum class Scenes
	{
		MainMenu,
		Gameplay,
		Multiplayer,
		Credits
	};

	extern Scenes currentScene;
	extern bool isRunning;

	void Play();
}