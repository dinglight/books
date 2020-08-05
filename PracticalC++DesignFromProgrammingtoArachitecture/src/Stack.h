/**
 * @file Stack.h
 * @author Ding Liang (dinglight@163.com)
 * @brief 
 * @version 0.1
 * @date 2020-05-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef STACK_H
#define STACK_H

#include "Publisher.h"

#include <vector>

namespace strawberry {

class StackEventData : public EventData {
public:
    enum class ErrorType { Empty, TooFewArguments };
    explicit StackEventData(ErrorType e) : err_(e) {}
    static const char* Message(ErrorType e);
    const char* message() const;
    ErrorType error() const {return err_;}
private:
    ErrorType err_;
};

class Stack : private Publisher {
    class StackImpl;

public:
    static Stack& Instance();
    void Push(double);
    double Pop();
    size_t Size() const;

    /**
     * @brief Get the first min(n, stackSize) elements of the stack
     * with the top of stack at position 0
     * 
     * @param n how many elements you want
     * @return std::vector<double> the n elements from the top of the stack
     */
    std::vector<double> GetElements(size_t n) const;

    using Publisher::Attach;
    using Publisher::Detach;

    static const std::string StackChanged;
    static const std::string StackError;
private:
    Stack();
    ~Stack();
    Stack(const Stack&) = delete;
    Stack(Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack& operator=(Stack&&) = delete;
private:
    std::unique_ptr<StackImpl> impl_;
};

}  // namespace strawberry

#endif  // STACK_H