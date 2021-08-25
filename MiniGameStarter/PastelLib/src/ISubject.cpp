#include "ISubject.h"

ISubject::ISubject()
{
}

void ISubject::Attach(IObserver* observer)
{
	this->list_observer_.push_back(observer);
}

void ISubject::Detach(IObserver* observer)
{
	this->list_observer_.remove(observer);
}

void ISubject::Notify(const std::string& message)
{
    for (auto const& observer : this->list_observer_) {
        observer->Update(message);
    }
}

