#include "CoreCommands.h"
#include "Stack.h"
#include "UserInterface.h"
#include "CommandRepository.h"
#include "Exception.h"
#include "Logger.h"

namespace strawberry {

/**
 * @brief register a command to CommandRepository
 * 
 * @param ui the user interface for show error message
 * @param label the name of the command
 * @param c the command pointer
 */
static void RegisterCommand(UserInterface& ui, const std::string& label, CommandPtr c)
{
    try {
        CommandRepository::Instance().RegisterCommand(label, std::move(c));
    } catch (Exception& e) {
        ui.PostMessage(e.What());
    }
}

////////////////////////////////////////////////////////////////////////////////////////

EnterNumber::EnterNumber(double d)
: Command{}
, number_{d}
{

}
EnterNumber::EnterNumber(const EnterNumber& rhs)
: Command {rhs}
, number_ {rhs.number_}
{

}
EnterNumber::~EnterNumber()
{}
void EnterNumber::ExecuteImpl() noexcept
{
    LOG("");
    Stack::Instance().Push(number_);
}
void EnterNumber::UndoImpl() noexcept
{
    Stack::Instance().Pop();
}
EnterNumber* EnterNumber::CloneImpl() const
{
    return new EnterNumber {*this};
}
//////////////////////////////////////////////////////////////////////


Divide::Divide(const Divide& rhs)
: BinaryCommand(rhs)
{}

Divide::~Divide()
{}

void Divide::CheckPreconditionsImpl() const
{
    BinaryCommand::CheckPreconditionsImpl();
    auto v = Stack::Instance().GetElements(1);
    if (v.front() == 0. || v.front() == -0.)
        throw Exception {"Division by zero"};
}

double Divide::BinaryOperation(double next, double top) const noexcept
{
    return next / top;
}

Divide* Divide::CloneImpl() const
{
    return new Divide{*this};
}
//////////////////////////////////////////////////////////////////////



/**
 * @brief register core commands
 * 
 * @param ui the user interface
 */
void RegisterCoreCommands(UserInterface& ui)
{
    RegisterCommand(ui, "+", MakeCommandPtr<BinaryCommandAlternative>([](double d1, double d2){return d1+d2;}));
    RegisterCommand(ui, "-", MakeCommandPtr<BinaryCommandAlternative>([](double d1, double d2){return d1-d2;}));
    RegisterCommand(ui, "*", MakeCommandPtr<BinaryCommandAlternative>([](double d1, double d2){return d1*d2;}));
    RegisterCommand(ui, "/", MakeCommandPtr<Divide>());
}

}  // namespace strawberry

