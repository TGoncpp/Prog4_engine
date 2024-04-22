#include <SDL.h>
#include "InputManager.h"
#include<backends/imgui_impl_sdl2.h>
const Uint8* keyboardStatePtr =  SDL_GetKeyboardState(nullptr);

bool TG::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			InputHandling(EInputType::pressed);
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			InputHandling(EInputType::completed);
			
		}
		
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	InputHandling(EInputType::hold);

	if (m_vCommandPtrQueue.size()> 0)
	{
		for (auto input : m_vCommandPtrQueue)
		{
			input->commandActor->Execute();
		}
		
	}

	auto& controller = TG::Controller::GetInstance();
	controller.InputHandling();

	for (const auto& inputAction : m_vBindedControllerCommandActorsPtrs)
	{
		switch (inputAction->inputType)
		{
		case EInputType::hold:
			if (controller.IsDown(inputAction->inputEvent))
			{
				inputAction->commandActor->Execute();
			}
			break;
		case EInputType::completed:
			if (controller.IsUpThisFrame(inputAction->inputEvent))
			{
				inputAction->commandActor->Execute();
			}
			break;
		case EInputType::pressed:
			if (controller.IsPressedThisFrame(inputAction->inputEvent))
			{
				inputAction->commandActor->Execute();
			}
			break;
		case EInputType::joyStick:
			if (controller.IsRightThumbsNotInDeadZone())
			{
				inputAction->commandActor->Execute();
			}
			if (controller.IsLeftThumbsNotInDeadZone())
			{
				inputAction->commandActor->Execute();
			}
			break;
		}

		
	}
	m_vCommandPtrQueue.clear();
	return true;
}






void TG::InputManager::InputBinding(std::unique_ptr<CommandActor>&& commandActorPtr, Uint32 input, EInputType type, bool controller)
{
	if(controller)
		m_vBindedControllerCommandActorsPtrs.push_back(std::make_unique<Input>(Input{ std::move(commandActorPtr), input, type }));
	else
		m_vBindedCommandActorsPtrs.push_back(std::make_unique<Input>(Input{ std::move(commandActorPtr), input, type}));
}

void TG::InputManager::InputHandling(EInputType type)
{
	for (const auto& input : m_vBindedCommandActorsPtrs)
	{
		if  (input.get()->inputType == type && keyboardStatePtr[input.get()->inputEvent] )
		{
			m_vCommandPtrQueue.push_back(input.get());
		}
	}

}
