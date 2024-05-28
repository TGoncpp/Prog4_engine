#pragma once
#include "QbertCharacter.h"
#include "Npc.h"
#include "subject.h"
#include <map>
#include "TextComponent.h"

namespace Game
{
	class Hud final : public TG::GameObject
	{
	public:
		Hud(std::vector<Character*> vCharacters, std::vector<Character*> vCharactersPlayer2
			, std::vector<std::shared_ptr<TG::Texture2D>> vTextures, std::shared_ptr<TG::Font> font);
		~Hud()                     = default;
		Hud(const Hud&)            = delete;
		Hud(Hud&&)                 = delete;
		Hud& operator=(const Hud&) = delete;
		Hud& operator=(Hud&&)      = delete;

		virtual void ApplyGameMode(int gameMode)override;

	private:
		std::map<std::string, TG::RenderComponent*> m_mTextureRenderRefrences
		{
			std::make_pair("background", nullptr),
			std::make_pair("health", nullptr),
			std::make_pair("health2", nullptr),
			std::make_pair("health3", nullptr),
			std::make_pair("healthPlayer2-1", nullptr),
			std::make_pair("healthPlayer2-2", nullptr),
			std::make_pair("healthPlayer2-3", nullptr),
			std::make_pair("targetCube", nullptr)
		};
		std::map<std::string, TG::TextComponent*> m_mTextRenderRefrences
		{
			std::make_pair("level", nullptr),
			std::make_pair("Player 1", nullptr),
			std::make_pair("round", nullptr),
			std::make_pair("Score", nullptr)
		};

		void SetTextComponent(const glm::vec2& offset, const std::string& key, std::shared_ptr<TG::Font> font, std::string text = "");

		int m_Level{ 2 };
		int m_Round{ 1 };
		bool m_ShowPlayer2{ false };
	};
}
