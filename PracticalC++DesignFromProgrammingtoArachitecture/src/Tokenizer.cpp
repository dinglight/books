#include "Tokenizer.h"

#include <sstream>
#include <iterator>
#include <algorithm>

namespace strawberry {

Tokenizer::Tokenizer(const std::string &s)
{
    std::istringstream iss{s};
    Tokenize(iss);
}
Tokenizer::~Tokenizer()
{

}
void Tokenizer::Tokenize(std::istream& is)
{
    tokens_.assign( std::istream_iterator<std::string>{is}, std::istream_iterator<std::string>{});
    for (auto& i : tokens_) {
        std::transform(i.begin(), i.end(), i.begin(), ::tolower);
    }
}
}  // namespace strawberry

