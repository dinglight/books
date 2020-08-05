#ifndef STACK_UPDATED_OBSERVER_H
#define STACK_UPDATED_OBSERVER_H

#include "Observer.h"

namespace strawberry {
class UserInterface;

/**
 * @brief The StackUpdatedObserver class is a proxy between
 * Stack and UserInterface, this make use of proxy pattern.
 * 
 */
class StackUpdatedObserver : public Observer {
public:
    explicit StackUpdatedObserver(UserInterface& ui);
private:
    void NotifyImpl(std::shared_ptr<EventData> event_data) override;
private:
    UserInterface& ui_;
};
}  // namespace strawberry

#endif  // STACK_UPDATED_OBSERVER_H
