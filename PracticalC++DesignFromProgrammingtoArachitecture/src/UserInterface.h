#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Publisher.h"

namespace strawberry {

class CommandData : public EventData {
public:
    explicit CommandData(const std::string& command) : command_(command) {}
    /**
     * @brief return the name of command.
     * 
     * @return the name of command
     */
    const std::string& Command() const { return command_; }
private:
    std::string command_;
};

class UserInterface : protected Publisher {
public:
    UserInterface();
    virtual ~UserInterface();

    /**
     * @brief post a message to the user.
     * 
     * @param msg The post message
     */
    virtual void PostMessage(const std::string& msg) = 0;
    /**
     * @brief notifies the interface that the stack has changed.
     * 
     */
    virtual void StackChanged() = 0;

    using Publisher::Attach;
    using Publisher::Detach;

    // defines the event this publisher can raise
    // note that the string is defined in main.cpp of the application since
    // class UserInterface has no implementation file (in test driver for same
    // reason)
    static const std::string CommandEntered;
};
}  // namespace strawberry
#endif  // USERINTERFACE_H
