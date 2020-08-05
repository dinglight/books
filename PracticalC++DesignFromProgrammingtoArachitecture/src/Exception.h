#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

namespace strawberry {

/**
 * @brief The Publisher class is a class capable of receiving observers.
 * Note that it is assumed that a real publisher may publish multiple separate events.
 * These are stored by string name in a table. Since each event may have multiple observers,
 * the table stores a collection of observers. 
 * Important: Publishers own the memory for their observers (enforced by std::unique_ptr)
 * @code
 *     throw Exception{"exception message"};
 * try {
 *
 * } catch (Exception e) {
 *     std::cout << e.What();
 * }
 * @endcode
 */
class Exception {
public:
    explicit Exception(const std::string& msg) : msg_(msg) {}
    const std::string& What() const { return msg_;}
private:
    std::string msg_;
};
}  // namespace strawberry

#endif  // EXCEPTION_H
