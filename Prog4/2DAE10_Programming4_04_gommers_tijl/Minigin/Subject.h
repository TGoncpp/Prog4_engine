#pragma once
#include <forward_list>
#include <map>
#include "Observer.h"

enum class MessageType
{
	physics,
	sound,
	score,
	hud
};

class ISubject
{
public:
	virtual ~ISubject() = default;

	virtual void AddObserver(int message, IObserver* observer);
	
	virtual void RemoveObserver(int message, IObserver* observer);
	
	virtual void OnNotify(int message);
	virtual void OnNotifyAll();

private:
	using Observers = std::forward_list<IObserver*>;
	std::map<int, Observers> m_mObservers;

};

class SomeSubject : public ISubject
{
public:


};

