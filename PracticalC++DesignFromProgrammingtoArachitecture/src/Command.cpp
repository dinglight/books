#include "Command.h"

#include "Stack.h"
#include "Exception.h"
#include "Logger.h"

namespace strawberry {
Command::~Command()
{

}
void Command::Execute()
{
    LOG("");
    CheckPreconditionsImpl();
    ExecuteImpl();
}
void Command::Undo()
{
    LOG("");
    UndoImpl();
}
Command* Command::Clone() const
{
    return CloneImpl();
}

void Command::Deallocate()
{
    delete this;
}

void Command::CheckPreconditionsImpl() const
{
    LOG("");
}

//////////////////////////////////////////////////////////////////
BinaryCommand::BinaryCommand(const BinaryCommand& rhs)
: Command(rhs)
, top_{rhs.top_}
, next_{rhs.next_}
{ }

BinaryCommand::~BinaryCommand()
{ }

void BinaryCommand::CheckPreconditionsImpl() const
{
    if( Stack::Instance().Size() < 2 )
        throw Exception{"Stack must have 2 elements"};
}

void BinaryCommand::ExecuteImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    top_ = Stack::Instance().Pop();
    next_ = Stack::Instance().Pop();
    Stack::Instance().Push( BinaryOperation(next_, top_) );
}

void BinaryCommand::UndoImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    Stack::Instance().Pop();
    Stack::Instance().Push(next_);
    Stack::Instance().Push(top_);
}

////////////////////////////////////////////////////////////////////////
BinaryCommandAlternative::BinaryCommandAlternative(const std::function<BinaryCommandAlternative::BinaryCommandOp> f)
: command_(f)
{}

BinaryCommandAlternative::BinaryCommandAlternative(const BinaryCommandAlternative& rhs)
: Command(rhs)
, top_(rhs.top_)
, next_(rhs.next_)
, command_(rhs.command_)
{}

void BinaryCommandAlternative::CheckPreconditionsImpl() const
{
    LOG("");
    if (Stack::Instance().Size() < 2) {
        throw Exception {"Stack must have 2 elements"};
    }
}

void BinaryCommandAlternative::ExecuteImpl() noexcept
{
    LOG("");
    top_ = Stack::Instance().Pop();
    next_ = Stack::Instance().Pop();
    Stack::Instance().Push(command_(next_, top_));
}

void BinaryCommandAlternative::UndoImpl() noexcept
{
    Stack::Instance().Pop();
    Stack::Instance().Push(next_);
    Stack::Instance().Push(top_);
}

BinaryCommandAlternative* BinaryCommandAlternative::CloneImpl() const
{
    LOG("");
    return new BinaryCommandAlternative{*this};
}


}  // namespace strawberry
