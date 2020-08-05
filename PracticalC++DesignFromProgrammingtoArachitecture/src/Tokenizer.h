#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

namespace strawberry {

/**
 * @brief Tokenizer class is responsible for taking a string of text and
 * splitting this string into individual space-separated tokens.
 * 
 */

class Tokenizer {
public:
    using Token = std::string;
    using Tokens = std::vector<Token>;
    using const_iterator = Tokens::const_iterator;
    explicit Tokenizer(const std::string &s);
    ~Tokenizer();
    const_iterator begin() const { return tokens_.begin(); }
    const_iterator end() const { return tokens_.end(); }
    const Token& operator[](size_t i) const { return tokens_[i]; }
private:
    void Tokenize(std::istream& is);
private:
    Tokenizer() = delete;
    Tokenizer(const Tokenizer&) = delete;
    Tokenizer& operator=(const Tokenizer&) = delete;
    Tokenizer(Tokenizer&&) = delete;
    Tokenizer& operator=(Tokenizer&&) = delete;
private:
    Tokens tokens_;
};
}  // namespace strawberry
#endif  // TOKENIZER_H
