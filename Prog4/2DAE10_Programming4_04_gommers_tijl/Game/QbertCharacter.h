#pragma once
#include "Character.h"

namespace Game
{

	class QbertCharacter final: public Character, public TG::IObserver<bool>
	{
	public:
		QbertCharacter(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, std::shared_ptr<TG::Texture2D> curseTex);
		QbertCharacter()                                 = default;
		~QbertCharacter()                                = default;
		QbertCharacter& operator=(const QbertCharacter&) = delete;
		QbertCharacter& operator=(QbertCharacter&&)      = delete;
		QbertCharacter(const QbertCharacter&)            = delete;
		QbertCharacter(QbertCharacter&&)                 = delete;


	private:
		//IObserver
		virtual void Notify(bool)override;
		virtual void OnSubjectDestroy()override {};

		TG::RenderComponent* m_RenderCurseCompRefrence{ nullptr };
		void SetCurseVisibility(bool isVisible);
	};

}