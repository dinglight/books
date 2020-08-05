#include "StackUpdatedObserver.h"
#include "UserInterface.h"
#include "Exception.h"

#include "Logger.h"

namespace strawberry {
StackUpdatedObserver::StackUpdatedObserver(UserInterface& ui)
: Observer("StackUpdated")
, ui_(ui)
{
    LOG("");
}

void StackUpdatedObserver::NotifyImpl(std::shared_ptr<EventData> event_data)
{
    LOG("");
    ui_.StackChanged();
}

}  // namespace strawberry