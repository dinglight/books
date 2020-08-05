#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <memory>

namespace strawberry {
class EventData;

/**
 * @brief The Observer class.
 * 
 */
class Observer {
public:
    explicit Observer(const std::string& name);
    virtual ~Observer();
    /**
     * @brief observer got a notice from publisher.
     * 
     * @param event_data The share point of event data
     */
    void Notify(std::shared_ptr<EventData> event_data);
    /**
     * @brief return the name of the observer.
     * 
     * @return the name of the observer
     */
    const std::string Name() const;

private:
    virtual void NotifyImpl(std::shared_ptr<EventData> event_data) = 0;
    std::string name_;
};
}  // namespace strawberry

#endif  // OBSERVER_H
