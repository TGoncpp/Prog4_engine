#include "Audio.h"
#include <iostream>


TG::GameAudio::~GameAudio()
{
	for (auto& chunks : m_mAudio)
	{
		Mix_FreeChunk(chunks.second);
	}
	Mix_Quit();
}

void TG::GameAudio::playSound(const std::string& musicKey  )
{
	Mix_PlayChannel(-1, m_mAudio[musicKey], 0);
}

void TG::GameAudio::stopSound(const std::string& )
{

}

void TG::GameAudio::stopAllSounds()
{
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
