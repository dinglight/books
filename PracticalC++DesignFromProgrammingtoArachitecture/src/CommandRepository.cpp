#include "CommandRepository.h"

#include <unordered_map>

#include "Exception.h"
#include "Logger.h"

namespace strawberry {

class CommandRepository::CommandRepositoryImpl {
public:
    CommandRepositoryImpl();
    void RegisterCommand(const std::string& name, CommandPtr c);
    CommandPtr DeregisterCommand(const std::string& name);
    CommandPtr AllocateCommand(const std::string& name) const;
private:
    using Repository = std::unordered_map<std::string, CommandPtr>;
    Repository repository_;
};

CommandRepository::CommandRepositoryImpl::CommandRepositoryImpl()
{

}
void CommandRepository::CommandRepositoryImpl::RegisterCommand(const std::string& name, CommandPtr c)
{
    auto it = repository_.find(name);
    if (it != repository_.end()) {
        std::ostringstream oss;
        oss << "Command " << name << "already registered";
        throw Exception{ oss.str() };
    } else {
        repository_.emplace(name, std::move(c));
    }
}
CommandPtr CommandRepository::CommandRepositoryImpl::DeregisterCommand(const std::string& name)
{
    auto it = repository_.find(name);
    if (it != repository_.end()) {
        auto tmp = MakeCommandPtr(it->second.release());
        repository_.erase(it);
        return tmp;
    } else {
        return MakeCommandPtr(nullptr);
    }
}
CommandPtr CommandRepository::CommandRepositoryImpl::AllocateCommand(const std::string& name) const
{
    auto it = repository_.find(name);
    if (it != repository_.end()) {
        const auto& command = it->second;
        return MakeCommandPtr(command->Clone());
    } else {
        return MakeCommandPtr(nullptr);
    }
}
//////////////////////////////////////////////////////////////////////////////////
CommandRepository::CommandRepository()
{
    impl_ = std::make_unique<CommandRepositoryImpl>();
}

CommandRepository::~CommandRepository()
{

}
CommandRepository& CommandRepository::Instance()
{
    static CommandRepository instance;
    return instance;
}
void CommandRepository::RegisterCommand(const std::string& name, CommandPtr c)
{
    LOG("");
    impl_->RegisterCommand(name, std::move(c));
}

CommandPtr CommandRepository::DeregisterCommand(const std::string& name)
{
    LOG("");
    return impl_->DeregisterCommand(name);
}

CommandPtr CommandRepository::AllocateCommand(const std::string& name) const
{
    LOG("");
    return impl_->AllocateCommand(name);
}
}  // namespace strawberry
