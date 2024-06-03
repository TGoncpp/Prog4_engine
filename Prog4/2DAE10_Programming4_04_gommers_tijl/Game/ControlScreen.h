#pragma once
#include "GameObject.h"

namespace Game
{
	class controlScreen final : public TG::GameObject
	{
	public:
		controlScreen(std::vector<std::shared_ptr<TG::Texture2D>> vTextures);
		virtual~controlScreen() = default;
		controlScreen(controlScreen&&) = delete;
		controlScreen(const controlScreen&) = delete;
		controlScreen& operator=(const controlScreen&) = delete;
		controlScreen& operator=(controlScreen&&) = delete;

		virtual void ApplyGameMode(int gameModeValue, int)override;
	private:
		std::vector<std::shared_ptr<TG::Texture2D>> m_vTextureSPtr;
		
	};
}