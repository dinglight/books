#include "Cli.h"

#include "Tokenizer.h"
#include "Stack.h"

#include "Logger.h"

namespace strawberry {
class Cli::CliImpl {
public:
    CliImpl(Cli&, std::istream& in, std::ostream& out);
    void Execute();
    void PostMessage(const std::string& msg);
    void StackChanged();
private:
    void StartupMessage();
private:
    Cli& parent_;
    std::istream& in_;
    std::ostream& out_;
};

Cli::CliImpl::CliImpl(Cli& p, std::istream& in, std::ostream& out)
: parent_(p)
, in_(in)
, out_(out)
{

}

void Cli::CliImpl::Execute()
{
    StartupMessage();
    for (std::string line; std::getline(in_, line, '\n');) {
        Tokenizer tokenizer{line};
        for (const auto& token : tokenizer) {
            if (token == "exit") {
                return;
            } else {
                parent_.Raise(UserInterface::CommandEntered, std::make_shared<CommandData>(token));
            }
        }
    }
}
void Cli::CliImpl::PostMessage(const std::string& msg)
{
    out_ << msg << std::endl;
}

/**
 * @brief show the top4 numbers on the stack
 * 
 */
void Cli::CliImpl::StackChanged()
{
    size_t nElements{4};
    auto v = Stack::Instance().GetElements(nElements);
    std::ostringstream oss;
    oss.precision(12);
    size_t size = Stack::Instance().Size();
    oss << "\n";
    if (size == 0) {
        oss << "Stack currently empty. \n";
    } else if (size == 1) {
        oss << "Top element of stack (size = " << size << "):\n";
    } else if (size > 1 && size <= nElements) {
        oss << "Top " << size << " elements of stack (size = " << size << "):\n";
    } else {
        oss << "Top " << nElements << " elements of stack (size = " << size << "):\n";
    }

    size_t j {v.size()};
    for (auto i = v.rbegin(); i != v.rend(); ++i) {
        oss << j << ":\t" << *i << "\n";
        --j;
    }
    PostMessage(oss.str());
}
void Cli::CliImpl::StartupMessage()
{
    out_ << "calc\n"
         << "type 'exit' to end program\n" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
Cli::Cli(std::istream& in, std::ostream& out)
{
    LOG("");
    cli_impl_ = std::make_unique<CliImpl>(*this, in, out);
}
Cli::~Cli()
{
    LOG("");
}
void Cli::Execute()
{
    LOG("");
    cli_impl_->Execute();
}
void Cli::PostMessage(const std::string& msg)
{
    LOG("");
    cli_impl_->PostMessage(msg);
}
void Cli::StackChanged()
{
    LOG("");
    cli_impl_->StackChanged();
}

}  // namespace strawberry