#include <memory>
#include "Singleton.h"


namespace TG
{
	class Controller final : public dae::Singleton<Controller>
	{
	public:
		Controller();
		~Controller();

		void InputHandling();

		bool IsPressedThisFrame(Uint32 button) const;
		bool IsUpThisFrame(Uint32 button) const;
		bool IsDown(Uint32 button) const;
		bool IsLeftThumbsNotInDeadZone() const;
		bool IsRightThumbsNotInDeadZone() const;

	private:
		
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pPimpl;
	};
}

