#pragma once
#include "Singleton.h"
#include "Command.h"
#include <vector>
#include <memory>
#include "Controller.h"


enum class EInputType
{
	pressed,
	hold,
	completed,
	joyStick
};

struct Input
{
	std::unique_ptr<dae::CommandActor> commandActor;
	Uint32 inputEvent;
	EInputType inputType;

	Input(std::unique_ptr<dae::CommandActor>  commandActor, Uint32 inputEvent, EInputType inputType)
		:commandActor{ std::move(commandActor) }, inputEvent{ inputEvent }, inputType{ inputType }
	{
	}
};


namespace dae
{
	class InputManager final : public dae::Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void InputBinding(std::unique_ptr<CommandActor> &&commandActorPtr, Uint32 input, EInputType type, bool controller = false);

		void InputHandling(EInputType type);
	private:
		std::vector < std::unique_ptr< Input >> m_vBindedCommandActorsPtrs;
		std::vector < std::unique_ptr< Input >> m_vBindedControllerCommandActorsPtrs;
		std::vector<Input*> m_vCommandPtrQueue;
	};

}
