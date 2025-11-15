#include "audio/audio_manager.h"

#include "raylib.h"

namespace Audio
{
	static Sound buttonSound;

	void Init()
	{
		InitAudioDevice();
		buttonSound = LoadSound("res/sounds/buttonClick.mp3");
	}
	void Close()
	{
		UnloadSound(buttonSound);
		CloseAudioDevice();
	}
}