/**
 * @file Stack.cpp
 * @author Ding Liang (dinglight@163.com)
 * @brief 
 * @version 0.1
 * @date 2020-05-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Stack.h"
#include <deque>

#include "Exception.h"

namespace strawberry {

const char* StackEventData::Message(StackEventData::ErrorType e)
{
    switch (e) {
        case ErrorType::Empty: return "Attempting to pop empty stack";
        case ErrorType::TooFewArguments: return "Need at least two stack elements to swap top";
        default: return "Unknown error";
    }
}

const std::string Stack::StackChanged = "StackChanged";
const std::string Stack::StackError = "StackError";

class Stack::StackImpl {
public:
    explicit StackImpl(const Stack&);
    void Push(double d);
    double Pop();
    size_t Size() const;
    std::vector<double> GetElements(size_t n) const;
    void GetElements(size_t n, std::vector<double>& v) const;
private:
    const Stack& parent_;
    std::deque<double> stack_;
};

Stack::StackImpl::StackImpl(const Stack& s)
: parent_(s)
{}
void Stack::StackImpl::Push(double d)
{
    stack_.push_back(d);
    parent_.Raise(Stack::StackChanged, nullptr);
}
double Stack::StackImpl::Pop()
{
    if (stack_.empty()) {
        parent_.Raise(Stack::StackError, std::make_shared<StackEventData>(StackEventData::ErrorType::Empty));
        throw Exception {StackEventData::Message(StackEventData::ErrorType::Empty)};
    } else {
        auto val = stack_.back();
        stack_.pop_back();
        parent_.Raise(Stack::StackChanged, nullptr);
        return val;
    }
}
size_t Stack::StackImpl::Size() const
{
    return stack_.size();
}
std::vector<double> Stack::StackImpl::GetElements(size_t n) const
{
    std::vector<double> v;
    GetElements(n, v);
    return v;
}
void Stack::StackImpl::GetElements(size_t n, std::vector<double>& v) const
{
    if (n > stack_.size()) n = stack_.size();

    v.insert(v.end(), stack_.rbegin(), stack_.rbegin()+n);
}
/////////////////////////////////////////////////////////////////////////////
Stack& Stack::Instance()
{
    static Stack instance;
    return instance;
}

void Stack::Push(double d)
{
    impl_->Push(d);
}

double Stack::Pop()
{
    return impl_->Pop();
}

size_t Stack::Size() const
{
    return impl_->Size();
}

std::vector<double> Stack::GetElements(size_t n) const
{
    return impl_->GetElements(n);
}

Stack::Stack()
{
    impl_ = std::make_unique<StackImpl>(*this);
    RegisterEvent(StackChanged);
    RegisterEvent(StackError);
}

Stack::~Stack()
{}

}  // namespace strawberry
