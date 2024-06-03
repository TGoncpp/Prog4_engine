#include "Audio.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

TG::GameAudio::~GameAudio()
{
	m_IsPlaying = false;
	for (auto& chunks : m_mAudio)
	{
		Mix_FreeChunk(chunks.second);
	}
	Mix_Quit();
}

TG::GameAudio::GameAudio()
{
	//Mix_Init(MIX_INIT_WAVPACK);
	//Mix_Volume(-1, 0);

	SDL_Init(SDL_INIT_AUDIO);

	int result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	if (result < 0)
	{
		std::cout << "audio init failed\n";
		return;
	}

	AddMusic("Qbert Hit.wav", "Hit");
	AddMusic("Qbert Fall.wav", "Fall");
	AddMusic("Qbert Jump.wav", "Jump");
	AddMusic("Round Complete Tune.wav", "Complete");
	AddMusic("Swearing.wav", "Swearing");
	AddMusic("Disk Lift.wav", "Disk Lift");
	AddMusic("Disk Land.wav", "Disk Land");
	AddMusic("Level Screen Tune.wav", "Level");

	m_Audiothread = std::jthread(&GameAudio::AudioPlaylist, this);
}

void TG::GameAudio::playSound(const std::string& music )
{
	//std::lock_guard
	m_qPlaylist.push(music);
}

void TG::GameAudio::MuteAllSounds(bool mute)
{
	m_Volume = mute? 0 : 100;
}

void TG::GameAudio::AddMusic(const std::string& musicPath, const std::string& keyName)
{
	if (m_mAudio.contains(keyName))
	{
		std::cout << "file already exists\n";
		return;
	}
	const std::string path{ "../Data/Sounds/" };
	const std::string fullPath{ path + musicPath };

	Mix_Chunk* chunk = Mix_LoadWAV(fullPath.c_str());

	if (!chunk)
	{
		std::cout << "file loading failed\n";
		return;
	}

	m_mAudio.insert(std::make_pair(keyName, chunk));
}

void TG::GameAudio::AudioPlaylist()
{
	while(m_IsPlaying)
	{
		//protect this queue as wel
		if (m_qPlaylist.size() > 0)
		{
			std::lock_guard lk(audioMutex);
			Mix_PlayChannel(-1, m_mAudio[m_qPlaylist.front()], 0);
			Mix_Volume(-1, m_Volume);

			m_qPlaylist.pop();
		}

	}
	
}
