#include "Observer.h"
#include "Logger.h"
namespace strawberry {

Observer::Observer(const std::string& name)
: name_(name)
{
    LOG("");
}
Observer::~Observer()
{
    LOG("");
}
void Observer::Notify(std::shared_ptr<EventData> event_data)
{
    LOG("");
    NotifyImpl(event_data);
}
const std::string Observer::Name() const
{
    LOG("");
    return name_;
}    

}  // namespace strawberry