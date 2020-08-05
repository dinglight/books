#include "CommandDispatcher.h"

#include <regex>

#include "UserInterface.h"
#include "CommandRepository.h"
#include "CoreCommands.h"
#include "Exception.h"
#include "Logger.h"
namespace strawberry {

class CommandDispatcher::CommandDispatcherImpl {
public:
    explicit CommandDispatcherImpl(UserInterface& ui);
    void ExecuteCommand(const std::string& command);
private:
    bool IsNumber(const std::string& s, double &d) const;
private:
    UserInterface& ui_;
};
CommandDispatcher::CommandDispatcherImpl::CommandDispatcherImpl(UserInterface& ui)
: ui_(ui)
{

}
void CommandDispatcher::CommandDispatcherImpl::ExecuteCommand(const std::string& command)
{
    double d;
    if (IsNumber(command, d)) {
        auto c = MakeCommandPtr<EnterNumber>(d);
        c->Execute();
    } else {
        auto c = CommandRepository::Instance().AllocateCommand(command);
        if (!c) {
            std::ostringstream oss;
            oss << "Command " << command << " is not a known command";
            ui_.PostMessage(oss.str());
        } else {
            try {
                c->Execute();
            } catch (Exception& e) {
                ui_.PostMessage(e.What());
            }
        }
    }
}

bool CommandDispatcher::CommandDispatcherImpl::IsNumber(const std::string& s, double &d) const
{
    if (s == "+" || s == "-") return false;
    std::regex pattern("((\\+|-)?[[:digit:]]*)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    bool is_number {std::regex_match(s, pattern)};
    if (is_number) {
        d = std::stod(s);
    }
    return is_number;
}
///////////////////////////////////////////////////////////////
CommandDispatcher::CommandDispatcher(UserInterface& ui)
{
    LOG("");
    impl_ = std::make_unique<CommandDispatcherImpl>(ui);
}
CommandDispatcher::~CommandDispatcher()
{
    LOG("");
}

void CommandDispatcher::CommandEntered(const std::string& command)
{
    LOG("");
    impl_->ExecuteCommand(command);
}

}  // namespace strawberry
