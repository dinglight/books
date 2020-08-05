#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <functional>

namespace strawberry {

class Command {
public:
    virtual ~Command();

    /**
     * @brief execute the command.
     */
    void Execute();
    /**
     * @brief undo the command.
     */
    void Undo();

    /**
     * @brief create a polymorphic copy of the command.
     * 
     * @return a copy pointer of the command
     */
    Command* Clone() const;

    /**
     * @brief Deletes commands. this should only be overridden in plugins.
     * By default, simply deletes command.
     * In plugins, delete must happen in the plugin.
     * 
     */
    virtual void Deallocate();

protected:
    Command() {}
    Command(const Command&) {}

private:
    /**
     * @brief this function is not pure virtual because a command that need no
     * preconditions shouldn't be forced to check for any...thus, this default
     * to not throwing.
     */
    virtual void CheckPreconditionsImpl() const;
    /**
     * @brief derived class are enforced to be override.
     * and this function not throw a exception
     */
    virtual void ExecuteImpl() noexcept = 0;
    /**
     * @brief derived class are enforced to be override.
     * and this function not throw a exception
     */
    virtual void UndoImpl() noexcept = 0;

    /**
     * @brief derived class are enforced to be override.
     * 
     */
    virtual Command* CloneImpl() const = 0;
private:
    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;
    Command& operator=(Command&&) = delete;
};

/**
 * @brief base class for binary operations.
 * 
 */
class BinaryCommand : public Command {
public:
    virtual ~BinaryCommand();
protected:
    void CheckPreconditionsImpl() const override;

    BinaryCommand() {}
    BinaryCommand(const BinaryCommand&);
private:
    BinaryCommand(BinaryCommand&&) = delete;
    BinaryCommand& operator=(const BinaryCommand&) = delete;
    BinaryCommand& operator=(BinaryCommand&&) = delete;

    void ExecuteImpl() noexcept override;
    void UndoImpl() noexcept override;
    virtual double BinaryOperation(double next, double top) const noexcept = 0;
private:
    double top_;
    double next_;
};

/**
 * @brief base class for binary operations.
 * 
 */
class BinaryCommandAlternative final : public Command {
    using BinaryCommandOp = double(double, double);
public:
    BinaryCommandAlternative(const std::function<BinaryCommandOp> f);
    ~BinaryCommandAlternative() = default;

private:
    BinaryCommandAlternative(BinaryCommandAlternative&&) = delete;
    BinaryCommandAlternative& operator=(const BinaryCommandAlternative&) = delete;
    BinaryCommandAlternative& operator=(BinaryCommandAlternative&&) = delete;
private:
    BinaryCommandAlternative(const BinaryCommandAlternative&);

    void CheckPreconditionsImpl() const override;
    void ExecuteImpl() noexcept override;
    void UndoImpl() noexcept override;
    BinaryCommandAlternative* CloneImpl() const override;

private:
    double top_;
    double next_;
    std::function<BinaryCommandOp> command_;
};

inline void CommandDeleter(Command* p)
{
    p->Deallocate();
}

using CommandPtr = std::unique_ptr<Command, decltype(&CommandDeleter)>;
template<typename T, typename... Args>
auto MakeCommandPtr(Args&&... args)
{
    return CommandPtr{new T{std::forward<Args>(args)...}, &CommandDeleter};
}
inline auto MakeCommandPtr(Command* p)
{
    return CommandPtr{p, &CommandDeleter};
}
}  // namespace strawberry
#endif  // COMMAND_H
