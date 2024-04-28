#pragma once
#include <map>
#include <string>
#include <memory>
#include <sdl_mixer.h>


namespace TG
{
	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual void playSound(const std::string& musicKey) = 0;
		virtual void stopSound(const std::string& musicKey) = 0;
		virtual void stopAllSounds() = 0;
		virtual void AddMusic(const std::string& musicPath, const std::string& keyName) = 0;
	};

	class GameAudio : public Audio
	{
	public:
		virtual ~GameAudio();
		virtual void playSound(const std::string& musicKey) override;
		virtual void stopSound(const std::string& musicKey) override;
		virtual void stopAllSounds() override;
		virtual void AddMusic(const std::string& musicPath, const std::string& keyName) override;

	private:
		std::map<std::string, Mix_Chunk*> m_mAudio;
	};


	class NullAudio : public Audio
	{
	public:
		virtual void playSound(const std::string& ) {  }
		virtual void stopSound(const std::string& ) {  }
		virtual void stopAllSounds() {  }
		virtual void AddMusic(const std::string& , const std::string& ) override{}

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

		virtual void stopSound(const std::string& musicKey)
		{
			log("stop sound");
			wrapped_.stopSound(musicKey);
		}

		virtual void stopAllSounds()
		{
			log("stop all sounds");
			wrapped_.stopAllSounds();
		}
		virtual void AddMusic(const std::string& musicPath, const std::string& keyName) override
		{
			log("stop all sounds");
			wrapped_.AddMusic(musicPath, keyName);
		}

	private:
		void log(const char* )
		{
			// Code to log message...
		}

		Audio& wrapped_;
	};

}