#pragma once
#include<list>
#include"IObserver.h"
class ISubject
{
public:
	virtual ~ISubject() {};
	void Attach(IObserver* observer);
	void Detach(IObserver* observer);
	void Notify(const std::string& message = "");
private:
	std::list<IObserver*> list_observer_;
};

