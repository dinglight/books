#include "CommandIssuedObserver.h"
#include "UserInterface.h"
#include "CommandDispatcher.h"
#include "Exception.h"

#include "Logger.h"

namespace strawberry {
CommandIssuedObserver::CommandIssuedObserver(CommandDispatcher& dispatcher)
: Observer("CommandIssued")
, dispatcher_(dispatcher)
{
    LOG("");
}

void CommandIssuedObserver::NotifyImpl(std::shared_ptr<EventData> event_data)
{
    LOG("");
    auto data = std::dynamic_pointer_cast<CommandData>(event_data);
    if (!data) {
        throw Exception("Could not convert EventData to a CommandData");
    } else {
        dispatcher_.CommandEntered(data->Command());
    }
}

}  // namespace strawberry