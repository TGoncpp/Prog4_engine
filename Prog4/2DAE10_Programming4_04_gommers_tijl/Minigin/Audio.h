#pragma once
#include <map>
#include <string>
#include <memory>
#include <sdl_mixer.h>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace TG
{
	

	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual void playSound(const std::string& musicKey) = 0;
		virtual void MuteAllSounds(bool mute)  = 0;
		virtual void AddMusic(const std::string& musicPath, const std::string& keyName) = 0;
		virtual void AudioPlaylist() = 0;

	protected:
		std::condition_variable cv;
		std::mutex audioMutex;
	};

	class GameAudio : public Audio
	{
	public:
		virtual ~GameAudio();
		GameAudio();
		virtual void playSound(const std::string& musicKey) override;
		virtual void MuteAllSounds(bool mute) override;
		virtual void AddMusic(const std::string& musicPath, const std::string& keyName) override;
		virtual void AudioPlaylist()override;

	private:
		std::map<std::string, Mix_Chunk*> m_mAudio;
		std::queue<std::string>m_qPlaylist{};
		std::jthread m_Audiothread;
		int m_Volume{ 100 };
		bool m_IsPlaying{ true };
	};


	class NullAudio : public Audio
	{
	public:
		virtual void playSound(const std::string& ) {  }
		virtual void stopSound(const std::string& ) {  }
		virtual void MuteAllSounds(bool ) {  }
		virtual void AddMusic(const std::string& , const std::string& ) override{}
		virtual void AudioPlaylist()override {};

	};


	class LoggedAudio : public GameAudio
	{
	public:
		LoggedAudio(Audio& wrapped)
			: wrapped_(wrapped)
		{}

		virtual void playSound(const std::string& musicKey)
		{
			log("play sound");
			wrapped_.playSound(musicKey);
		}

		virtual void MuteAllSounds(bool mute)
		{
			log("stop all sounds");
			wrapped_.MuteAllSounds(mute);
		}
		virtual void AddMusic(const std::string& musicPath, const std::string& keyName) override
		{
			log("stop all sounds");
			wrapped_.AddMusic(musicPath, keyName);
		}
		virtual void AudioPlaylist()override {};

	private:
		void log(const char* )
		{
			// Code to log message...
		}

		Audio& wrapped_;
	};

}