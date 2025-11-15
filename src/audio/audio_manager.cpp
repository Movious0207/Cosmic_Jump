#include "audio/audio_manager.h"

namespace Audio
{

	void Init()
	{
		InitAudioDevice();
		SetMasterVolume(100.0f);
	}
	void Close()
	{
		CloseAudioDevice();
	}
}