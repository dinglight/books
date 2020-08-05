#ifndef CLI_H
#define CLI_H

#include "UserInterface.h"

#include <iostream>

namespace strawberry {
class Cli : public UserInterface {
    class CliImpl;
public:
    Cli(std::istream& in, std::ostream& out);
    ~Cli();

    /**
     * @brief start the cli run loop.
     * 
     */
    void Execute();

private:
    /**
     * @brief post a text message to the output.
     * 
     * @param msg The post message
     */
    void PostMessage(const std::string& msg) override;
    /**
     * @brief updates the output when the stack is changed.
     * 
     */
    void StackChanged() override;

private:
    Cli(const Cli&) = delete;
    Cli& operator=(const Cli&) = delete;
    Cli(Cli&&) = delete;
    Cli&& operator=(Cli&&) = delete;

private:
    std::unique_ptr<CliImpl> cli_impl_;
};
}  // namespace strawberry

#endif  // CLI_H
