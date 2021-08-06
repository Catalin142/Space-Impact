#include "SoundPlayer.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")

void SoundPlayer::Play(const std::string& filepath)
{
	PlaySoundA(filepath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}