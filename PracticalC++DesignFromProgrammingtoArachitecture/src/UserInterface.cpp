#include "UserInterface.h"
#include "Logger.h"

namespace strawberry {
const std::string UserInterface::CommandEntered{"CommandEntered"};

UserInterface::UserInterface()
{
    LOG("");
    RegisterEvent(CommandEntered);
}
UserInterface::~UserInterface()
{
    LOG("");
}

}  // namespace strawberry
