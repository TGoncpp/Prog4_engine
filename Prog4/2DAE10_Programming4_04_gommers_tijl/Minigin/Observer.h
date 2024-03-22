#pragma once
#include <iostream>

class ISubject;

class IObserver
{
public:
	IObserver() = default;
	virtual ~IObserver() = default;

	virtual void Notify() = 0;

private:
};

class Watcher : public IObserver
{
public:
	explicit Watcher(ISubject& subject, const std::string& name, int message);
	virtual ~Watcher();

	virtual void Notify() override;
private:
	std::string m_Name;
	ISubject& m_Subject;
	int m_Message;
};

// --------------------------------------
//SUBJECT
//----------------------------------------
