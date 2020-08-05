#include "Cli.h"
#include "CommandDispatcher.h"
#include "CommandIssuedObserver.h"
#include "CoreCommands.h"
#include "Stack.h"
#include "StackUpdatedObserver.h"


using namespace strawberry;

int main(int argc, char** argv)
{
    // user interface
    Cli cli(std::cin, std::cout);

    // 
    CommandDispatcher command_dispatcher(cli);

    // 
    RegisterCoreCommands(cli);

    cli.Attach(UserInterface::CommandEntered, std::make_unique<CommandIssuedObserver>(command_dispatcher));

    Stack::Instance().Attach(Stack::StackChanged, std::make_unique<StackUpdatedObserver>(cli));

    cli.Execute();
    return 0;
}