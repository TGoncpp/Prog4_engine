#include <memory>
#include "Singleton.h"


namespace TG
{
	class Controller final 
	{
	public:
		Controller();
		~Controller();

		void SetControllerIndex(int index);
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

