#pragma once
#include <vector>
#include "Observer.h"

namespace TG
{
	template <typename... Args>
	class Subject final
	{
	public:
		virtual ~Subject()
		{
			for (auto& observer : m_mObservers)
			{
				if (observer)
					observer->OnSubjectDestroy();
			}
		}

		virtual void AddObserver(IObserver<Args...>* observer)
		{
			m_mObservers.push_back(observer);
		}

		virtual void RemoveObserver(IObserver<Args...>* observer)
		{
			m_mObservers.erase(std::remove(m_mObservers.begin(), m_mObservers.end(), observer), m_mObservers.end());
		}

		virtual void OnNotifyAll(Args... args)
		{
			for (const auto& it : m_mObservers)
			{
				it->Notify(args...);
			}
		}

	private:
		std::vector<IObserver<Args... >*> m_mObservers;

	};
}

