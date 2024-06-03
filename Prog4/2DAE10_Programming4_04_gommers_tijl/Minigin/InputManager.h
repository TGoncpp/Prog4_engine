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
	std::unique_ptr<TG::Command> commandActor;
	Uint32     inputEvent;
	EInputType inputType;

	Input(std::unique_ptr<TG::Command>  commandActor, Uint32 inputEvent, EInputType inputType)
		:commandActor{ std::move(commandActor) },
		inputEvent{ inputEvent },
		inputType { inputType }
	{
	}
};


namespace TG
{
	class InputManager final : public TG::Singleton<InputManager>
	{
	public:

		bool ProcessInput();

		void InputBinding(std::unique_ptr<Command> &&commandActorPtr, Uint32 input, EInputType type, int controller = -1);

		void InputHandling(EInputType type);
	private:
		static const int m_MaxNumOfPlayers{ 2 };
		std::vector < std::unique_ptr< Input >> m_vBindedCommandActorsPtrs;
		std::vector < std::unique_ptr< Input >> m_vvBindedControllerCommandActorsPtrs[m_MaxNumOfPlayers];
		std::vector<Input*> m_vCommandPtrQueue;
		int m_NumOfPlayers{ 0 };
		bool m_IsButtonPressed{ false };

		std::unique_ptr<Controller> m_vControllers[2];

		void HandleControllerInput(size_t controllerIndex);
	};

}
