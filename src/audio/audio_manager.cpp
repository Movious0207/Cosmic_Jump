#include "audio/audio_manager.h"

namespace Audio
{

	void Init()
	{
		InitAudioDevice();
		SetMasterVolume(0.1f);
	}
	void Close()
	{
		CloseAudioDevice();
	}
}