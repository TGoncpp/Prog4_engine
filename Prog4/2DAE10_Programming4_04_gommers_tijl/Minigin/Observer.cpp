#include "Observer.h"
#include "Subject.h"



Watcher::Watcher(ISubject& subject, const std::string& name, int message)
	:IObserver(),
	m_Name{ name },
	m_Subject{ subject },
	m_Message{message}
{
	m_Subject.AddObserver(m_Message, this);
}

Watcher::~Watcher()
{
	m_Subject.RemoveObserver(m_Message, this);
}


void Watcher::Notify()
{
}
