#pragma once
#include "GameObject.h"

namespace Game
{
	class IntermedateScreen final : public TG::GameObject
	{
	public:
		IntermedateScreen(std::vector<std::shared_ptr<TG::Texture2D>> vTextures, std::shared_ptr<TG::Font> font);
		virtual~IntermedateScreen() = default;
		IntermedateScreen(IntermedateScreen&&) = delete;
		IntermedateScreen(const IntermedateScreen&) = delete;
		IntermedateScreen& operator=(const IntermedateScreen&) = delete;
		IntermedateScreen& operator=(IntermedateScreen&&) = delete;

		virtual void ApplyGameMode(int gameModeValue)override;
	private:
		std::vector<std::shared_ptr<TG::Texture2D>> m_vTextureSPtr;
		std::vector<std::string> m_vMessages{
			"Single Player", 
			"        VS",
			"      COOP"};
	};
}