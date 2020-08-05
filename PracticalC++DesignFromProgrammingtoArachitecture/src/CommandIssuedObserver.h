#ifndef COMMANDISSUEDOBSERVER_H
#define COMMANDISSUEDOBSERVER_H

#include "Observer.h"

namespace strawberry {
class CommandDispatcher;

/**
 * @brief The CommandIssuedObserver class is a proxy between
 * CommandDispatcher and UserInterface, this make use of proxy pattern.
 * 
 */
class CommandIssuedObserver : public Observer {
public:
    explicit CommandIssuedObserver(CommandDispatcher& dispatcher);
private:
    void NotifyImpl(std::shared_ptr<EventData> event_data) override;
private:
    CommandDispatcher& dispatcher_;
};
}  // namespace strawberry

#endif  // COMMANDISSUEDOBSERVER_H
