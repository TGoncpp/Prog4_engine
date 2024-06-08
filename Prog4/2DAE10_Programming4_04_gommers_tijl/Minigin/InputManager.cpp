#include <SDL.h>
#include "InputManager.h"
#include<backends/imgui_impl_sdl2.h>
#include<iostream>
const Uint8* keyboardStatePtr =  SDL_GetKeyboardState(nullptr);

bool TG::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN && !m_IsButtonPressed) 
		{
			InputHandling(EInputType::pressed );
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			InputHandling(EInputType::completed);
		}
		if (e.type == SDL_KEYUP)
		{
			m_IsButtonPressed = false;
		}

		//ImGui_ImplSDL2_ProcessEvent(&e);
	}

	InputHandling(EInputType::hold);

	//After registering all inputs in queue -> execute them 
	if (m_vCommandPtrQueue.size()> 0)
	{
		for (auto input : m_vCommandPtrQueue)
		{
			input->commandActor->Execute();
		}
	}

	//CONTROLLER INPUT HANDELING
	//------------------------------------------	
	
	for (size_t index{}; index < static_cast<size_t>(m_NumOfPlayers); ++index)
	{
		m_vControllers[index]->InputHandling();
		HandleControllerInput(index);
	}

	m_vCommandPtrQueue.clear();
	return true;
}





//Binds all input in array to check during game if that binded input is used
void TG::InputManager::InputBinding(std::unique_ptr<Command>&& commandActorPtr, Uint32 input, EInputType type, int controller)
{
	//keyboard
	if (controller == -1)
	{
		m_vBindedCommandActorsPtrs.push_back(std::make_unique<Input>(Input{ std::move(commandActorPtr), input, type }));
		return;
	}

	//Controllers
	if (controller >= m_MaxNumOfPlayers)
	{
		std::cout << "amaunt off players is not allowed, max number is 2\n";
		return;
	}

	if (m_vControllers[controller] == nullptr)
	{
		m_vControllers[controller] = std::make_unique<Controller>();
		m_vControllers[controller]->SetControllerIndex(controller);
		++m_NumOfPlayers;
	}
	m_vvBindedControllerCommandActorsPtrs[controller].push_back(std::make_unique<Input>(Input{std::move(commandActorPtr), input, type}));

}

//for keyboard input only
void TG::InputManager::InputHandling(EInputType type)
{
	if (type == EInputType::pressed)
		m_IsButtonPressed = true;

	for (const auto& input : m_vBindedCommandActorsPtrs)
	{
		if  (input.get()->inputType == type && keyboardStatePtr[input.get()->inputEvent] )
		{
			m_vCommandPtrQueue.push_back(input.get());
		}
	}

}

void TG::InputManager::HandleControllerInput(size_t controllerIndex)
{
	for (const auto& inputAction : m_vvBindedControllerCommandActorsPtrs[controllerIndex])
	{
		switch (inputAction->inputType)
		{
		case EInputType::hold:
			if (m_vControllers[controllerIndex]->IsDown(inputAction->inputEvent))
			{
				inputAction->commandActor->Execute();
			}
			break;
		case EInputType::completed:
			if (m_vControllers[controllerIndex]->IsUpThisFrame(inputAction->inputEvent))
			{
				inputAction->commandActor->Execute();
			}
			break;
		case EInputType::pressed:
			if (m_vControllers[controllerIndex]->IsPressedThisFrame(inputAction->inputEvent))
			{
				inputAction->commandActor->Execute();
			}
			break;
		case EInputType::joyStick:
			if (m_vControllers[controllerIndex]->IsRightThumbsNotInDeadZone())
			{
				inputAction->commandActor->Execute();
			}
			if (m_vControllers[controllerIndex]->IsLeftThumbsNotInDeadZone())
			{
				inputAction->commandActor->Execute();
			}
			break;
		}
	}
}
