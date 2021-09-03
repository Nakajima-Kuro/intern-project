#include "ISubject.h"

ISubject::ISubject()
{
}

ISubject::~ISubject()
{
    list_observer_.clear();
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
        if (observer != nullptr) {
            observer->Update(message);
        }
        else {
            Detach(observer);
        }
    }
}

