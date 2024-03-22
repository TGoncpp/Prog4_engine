#include "Subject.h"

void ISubject::AddObserver(int message, IObserver* observer)
{
	auto it = m_mObservers.find(message);
	//if not found
	if (it == m_mObservers.cend())
	{
		m_mObservers[message] = Observers();
	}
	m_mObservers[message].push_front(observer);
}
void ISubject::RemoveObserver(int message, IObserver* observer)
{
	auto it = m_mObservers.find(message);
	if (it != m_mObservers.end())
	{
		for (auto& it2 : m_mObservers[message])
		{
			if (it2 == observer)
			{
				m_mObservers[message].remove(observer);
			}
		}
	}

}

void ISubject::OnNotify(int message)
{
	if (!m_mObservers.contains(message))
	{
		std::cout << "subject does not contain this message\n";
		return;
	}
	for (const auto& observers : m_mObservers[message])
	{
		observers->Notify();
	}
}

void ISubject::OnNotifyAll()
{
	for (const auto& it : m_mObservers)
	{
		for (const auto& observer : m_mObservers[it.first])
		{
			observer->Notify();
		}
	}
}
;