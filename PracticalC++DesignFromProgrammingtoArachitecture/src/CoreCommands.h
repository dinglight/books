#ifndef CORE_COMMANDS_H
#define CORE_COMMANDS_H

#include "Command.h"

namespace strawberry {
/**
 * @brief accept a number from input and adds it to the stack.
 * 
 */
class EnterNumber : public Command {
public:
    explicit EnterNumber(double d);
    explicit EnterNumber(const EnterNumber&);
    ~EnterNumber();

private:
    EnterNumber(EnterNumber&&) = delete;
    EnterNumber& operator=(const EnterNumber&) = delete;
    EnterNumber& operator=(EnterNumber&&) = delete;

private:
    void ExecuteImpl() noexcept override;
    void UndoImpl() noexcept override;
    EnterNumber* CloneImpl() const override;
private:
    double number_;
};

/**
 * @brief divide two elements on the stack
 * 
 */
class Divide : public BinaryCommand {
public:
    Divide() {}
    explicit Divide(const Divide&);
    ~Divide();
private:
    Divide(Divide&&) = delete;
    Divide& operator=(const Divide&) = delete;
    Divide& operator=(Divide&&) = delete;

    void CheckPreconditionsImpl() const override;
    double BinaryOperation(double next, double top) const noexcept override;
    Divide* CloneImpl() const override;
};

class UserInterface;
void RegisterCoreCommands(UserInterface& ui);

}  // namespace strawberry
#endif  // CORE_COMMANDS_H
