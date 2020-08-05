#include "Publisher.h"
#include "Observer.h"
#include "Exception.h"

#include <sstream>
#include <unordered_map>

#include "Logger.h"

namespace strawberry {

EventData::~EventData()
{
}

class Publisher::PublisherImpl {
    using ObserversList = std::unordered_map<std::string, std::unique_ptr<Observer>>;
    using Events = std::unordered_map<std::string, ObserversList>;
public:
    PublisherImpl();
    ~PublisherImpl();
    void Attach(const std::string& event_name, std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> Detach(const std::string& event_name, const std::string& observer_name);
    void Notify(const std::string& event_name, std::shared_ptr<EventData> event_data) const;
    void RegisterEvent(const std::string& event_name);
private:
    Events::const_iterator FindRegistedEvent(const std::string& event_name) const;
    Events::iterator FindRegistedEvent(const std::string& event_name);
private:
    Events events_;
};

Publisher::PublisherImpl::PublisherImpl()
{
}
Publisher::PublisherImpl::~PublisherImpl()
{
}

void Publisher::PublisherImpl::Attach(const std::string& event_name, std::unique_ptr<Observer> observer)
{
    auto ev = FindRegistedEvent(event_name);
    auto& obs_list = ev->second;

    auto obs = obs_list.find(observer->Name());
    if (obs != obs_list.end()) {
        std::ostringstream oss;
        oss << "Observer '" << observer->Name() << "' already attached to publisher";
        throw Exception{ oss.str() };
    }
    obs_list.insert(std::make_pair(observer->Name(), std::move(observer)));
}
std::unique_ptr<Observer> Publisher::PublisherImpl::Detach(const std::string& event_name, const std::string& observer_name)
{
    auto ev = FindRegistedEvent(event_name);
    auto& obs_list = ev->second;

    auto obs = obs_list.find(observer_name);
    if (obs == obs_list.end()) {
        std::ostringstream oss;
        oss << "Can not detach observer because '" << observer_name << "' not found";
        throw Exception{ oss.str() };
    }
    auto tmp = std::move(obs->second);
    obs_list.erase(obs);

    return tmp;
}

void Publisher::PublisherImpl::Notify(const std::string& event_name, std::shared_ptr<EventData> event_data) const
{
    auto ev = FindRegistedEvent(event_name);
    const auto& obs_list = ev->second;
    for (const auto& obs : obs_list) {
        obs.second->Notify(event_data);
    }
}

void Publisher::PublisherImpl::RegisterEvent(const std::string& event_name)
{
    auto p = events_.find(event_name);
    if (p != events_.end()) {
        std::ostringstream oss;
        oss << "Event '" << event_name << "' already registered";
        throw Exception{ oss.str() };
    }
    events_[event_name] = ObserversList{};
}

Publisher::PublisherImpl::Events::const_iterator Publisher::PublisherImpl::FindRegistedEvent(const std::string& event_name) const
{
    auto ev = events_.find(event_name);
    if (ev == events_.end()) {
        std::ostringstream oss;
        oss << "Publisher does not support event '" << event_name << "'";
        throw Exception{ oss.str() };
    }
    return ev;
}
Publisher::PublisherImpl::Events::iterator Publisher::PublisherImpl::FindRegistedEvent(const std::string& event_name)
{
    auto ev = events_.find(event_name);
    if (ev == events_.end()) {
        std::ostringstream oss;
        oss << "Publisher does not support event '" << event_name << "'";
        throw Exception{ oss.str() };
    }
    return ev;
}

///////////////////////////////////////////////////////////////////////////////
Publisher::Publisher()
{
    LOG("");
    publisher_impl_ = std::make_unique<PublisherImpl>();
}

Publisher::~Publisher()
{
    LOG("");
    // std::unique_ptr requires a definition of the destructor instead
    // of using the default because the destructor must appear in a scope
    // in which the complete definition of the template argument for
    // std::unique_ptr is known
}

void Publisher::Attach(const std::string& event_name, std::unique_ptr<Observer> observer)
{
    LOG("");
    publisher_impl_->Attach(event_name, std::move(observer));
}

std::unique_ptr<Observer> Publisher::Detach(const std::string& event_name, const std::string& observer_name)
{
    LOG("");
    return publisher_impl_->Detach(event_name, observer_name);
}

void Publisher::Raise(const std::string& event_name, std::shared_ptr<EventData> event_data) const
{
    LOG("");
    publisher_impl_->Notify(event_name, event_data);
}

void Publisher::RegisterEvent(const std::string& event_name)
{
    LOG("");
    publisher_impl_->RegisterEvent(event_name);
}

}  // namespace strawberry
