#ifndef COMMAND_REPOSITORY_H
#define COMMAND_REPOSITORY_H

#include "Command.h"

#include <string>

namespace strawberry {

/**
 * @brief this class is used to storing and retrieving commands.
 */
class CommandRepository {
    class CommandRepositoryImpl;
public:
    static CommandRepository& Instance();
    /**
     * @brief register a new command for the repository.
     * 
     * @param name The name of the command
     * @param c The pointer of the command
     * @exception
     *     -: "command already registed to the repository"
     */
    void RegisterCommand(const std::string& name, CommandPtr c);
    /**
     * @brief deregister a command from the repository.
     * returns the pointer to a command and subsequently remove it from
     * the internal deatabase of commands.
     * @param name The name of the command
     * @return
     *    @retval the pointer to a command
     *    @retval nullptr if the command not exist
     */
    CommandPtr DeregisterCommand(const std::string& name);
    /**
     * @brief allocate a command from the repository.
     * returns the pointer to a command without deregistering the command
     * @param name The name of the command
     * @return
     *    @retval the pointer to a command
     *    @retval nullptr if the command not exist
     */
    CommandPtr AllocateCommand(const std::string& name) const;

private:
    CommandRepository();
    ~CommandRepository();

    CommandRepository(const CommandRepository&) = delete;
    CommandRepository& operator=(const CommandRepository&) = delete;
    CommandRepository(CommandRepository&&) = delete;
    CommandRepository&& operator=(CommandRepository&&) = delete;

private:
    std::unique_ptr<CommandRepositoryImpl> impl_;
};

}  // namespace strawberry

#endif  // COMMAND_REPOSITORY_H
