#pragma once

#include "BaseComponent.h"

namespace TG
{
	class AudioComponent final: public BaseComponent
	{
	public:
		virtual void Update(float dt) { (void)dt; };
		virtual void FixedUpdate(float dt) { dt = 0.f; };
		virtual void Render()const override {};

		//void PlaySound(const SoundId& id, int volume);

		AudioComponent(dae::GameObject* owner) : BaseComponent( owner ) {};
		virtual ~AudioComponent() = default;
		AudioComponent& operator=(const AudioComponent&) = delete;
		AudioComponent& operator=(AudioComponent&&) = delete;
		AudioComponent(const AudioComponent&) = delete;
		AudioComponent(AudioComponent&&) = delete;

	private:
		static const int MAX_PENDING = 16;

		//static PlayMessage pending_[MAX_PENDING];
		static int numPending_;
	};
}