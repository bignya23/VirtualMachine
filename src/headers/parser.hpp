#pragma once
#include <variant>

#include "tokenizer.hpp"
// Grouping into statements
struct stmt {
    Token token;
    std::optional<std::string> value{};
};

// For whole Prg
struct Prg {
    std::vector<stmt> stmts;
};

class Parser {

public:
    explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}
    std::optional<stmt> parse();
    std::vector<stmt> stmts();

private:
    std::vector<Token> m_tokens;
    int m_index{};
    // Function to get the character using m_index
    [[nodiscard]] std::optional<Token> peek(const int offset = 0) {
        if (m_index + offset >= m_tokens.size()) {
            return {};
        }
        else {
            return m_tokens.at(m_index + offset);
        }
    }
    // Function to consume the tokens
    Token consume() {
        return m_tokens.at(m_index++);
    }

};