#include <windows.h>
#include <Xinput.h>
#include <SDL_syswm.h>
#include <cmath>
#include "Controller.h"


class TG::Controller::ControllerImpl
{
public:
	ControllerImpl()   = default;
	~ControllerImpl()  = default;

	void InputHandling();
	void SetControllerIndex(int index);

	bool IsPressedThisFrame(Uint32 button) const;
	bool IsUpThisFrame(Uint32 button) const;
	bool IsDown(Uint32 button) const;
	bool IsLeftThumbsNotInDeadZone() const;
	bool IsRightThumbsNotInDeadZone() const;

private:
	DWORD m_ControllerIndex{};
	int m_ButtonsPressedThisFrame{};
	int m_ButtonsReleasedThisFrame{};

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	float m_DeadzonePercentage{ 15.f };
};

void TG::Controller::ControllerImpl::InputHandling()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto newButtons            = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame  = newButtons & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = newButtons & (~m_CurrentState.Gamepad.wButtons);
}

void TG::Controller::ControllerImpl::SetControllerIndex(int index)
{
	m_ControllerIndex = index;
}

bool TG::Controller::ControllerImpl::IsPressedThisFrame(Uint32 button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool TG::Controller::ControllerImpl::IsUpThisFrame(Uint32 button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool TG::Controller::ControllerImpl::IsDown(Uint32 button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

bool TG::Controller::ControllerImpl::IsLeftThumbsNotInDeadZone() const
{
	const SHORT thumbL{ m_CurrentState.Gamepad.sThumbLX };
	const float thumbLPercentage{ std::abs(thumbL / static_cast<float>(SHRT_MIN)) };

	return (thumbLPercentage > m_DeadzonePercentage);
}

bool TG::Controller::ControllerImpl::IsRightThumbsNotInDeadZone() const
{
	const SHORT thumbR{ m_CurrentState.Gamepad.sThumbRX };
	const float thumbRPercentage{ std::abs(thumbR / static_cast<float>(SHRT_MAX)) };

	return (thumbRPercentage > m_DeadzonePercentage);
}






TG::Controller::Controller() 
	: m_pPimpl{ std::make_unique<ControllerImpl>() }
{
}

TG::Controller::~Controller() = default;


void TG::Controller::SetControllerIndex(int index)
{
	m_pPimpl->SetControllerIndex(index);
}

void TG::Controller::InputHandling()
{
	m_pPimpl->InputHandling();
}

bool TG::Controller::IsPressedThisFrame(Uint32 button) const
{
	return m_pPimpl->IsPressedThisFrame(button);
}

bool TG::Controller::IsUpThisFrame(Uint32 button) const
{
	return m_pPimpl->IsUpThisFrame(button);
}

bool TG::Controller::IsDown(Uint32 button) const
{
	return m_pPimpl->IsDown(button);
}

bool TG::Controller::IsLeftThumbsNotInDeadZone() const
{
	return m_pPimpl->IsLeftThumbsNotInDeadZone();
}

bool TG::Controller::IsRightThumbsNotInDeadZone() const
{
	return m_pPimpl->IsLeftThumbsNotInDeadZone();
}