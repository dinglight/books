#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <vector>
#include <memory>
#include <set>

namespace strawberry {
class Observer;

class EventData {
public:
    virtual ~EventData();
};

/**
 * @brief The Publisher class is a class capable of receiving observers.
 * Note that it is assumed that a real publisher may publish multiple separate events.
 * These are stored by string name in a table. Since each event may have multiple observers,
 * the table stores a collection of observers. 
 * Important: Publishers own the memory for their observers (enforced by std::unique_ptr)
 */
class Publisher {
    class PublisherImpl;
public:
    Publisher();
    /**
     * @brief attach a observer that intrested in the event.
     * 
     * @param event_name The name of the event
     * @param observer The observer which intrested in event_name
     * @exception
     *     -: "Publisher does not support the event"
     *     -: "Observer already attached to publisher"
     */
    void Attach(const std::string& event_name, std::unique_ptr<Observer> observer);
    /**
     * @brief detach a observer with the event.
     * 
     * @param event_name The name of the event
     * @param observer_name The name of the observer which attached with the event_name
     * @exception
     *     -: "Publisher does not support the event"
     *     -: "Can not found the observer"
     */
    std::unique_ptr<Observer> Detach(const std::string& event_name, const std::string& observer_name);

protected:
    ~Publisher();
    /**
     * @brief raise a event to the observer.
     * 
     * @param event_name The name of the event
     * @param event_data The share point of event data
     * @exception
     *     -: "Publisher does not support the event"
     */
    void Raise(const std::string& event_name, std::shared_ptr<EventData> event_data) const;

    /**
     * @brief registe a event to the publisher.
     * 
     * @param event_name The name of the event
     * @exception
     *     -: "Event already registered"
     */
    void RegisterEvent(const std::string& event_name);

private:
    std::unique_ptr<PublisherImpl> publisher_impl_;
};
}  // namespace strawberry
#endif  // PUBLISHER_H
