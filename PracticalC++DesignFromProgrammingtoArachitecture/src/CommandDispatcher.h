#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H

#include <string>
#include <memory>

namespace strawberry {

class UserInterface;

class CommandDispatcher {
    class CommandDispatcherImpl;
public:
    explicit CommandDispatcher(UserInterface& ui);
    ~CommandDispatcher();

    /**
     * @brief a command is entered from user interface.
     * 
     * @param command The command
     */
    void CommandEntered(const std::string& command);
private:
    CommandDispatcher(const CommandDispatcher&) = delete;
    CommandDispatcher& operator=(const CommandDispatcher&) = delete;
    CommandDispatcher(CommandDispatcher&&) = delete;
    CommandDispatcher& operator=(CommandDispatcher&&) = delete;
private:
    std::unique_ptr<CommandDispatcherImpl> impl_;
};
}  // namespace strawberry

#endif  // COMMANDDISPATCHER_H
