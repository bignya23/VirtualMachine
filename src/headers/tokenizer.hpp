#pragma once
#include <optional>
#include <utility>
#include <vector>

enum TokenType {
    ADD, SUB, MUL, DIV, PUSH, POP, PRINT, NUMBER, LOAD, STORE, JMP, JZ, JNZ, IDENTIFIER, STRING
};

struct Token {
    TokenType type;
    std::optional<std::string> val;
};
class Tokenizer {
public:
    explicit Tokenizer(std::string contents) : m_contents(std::move(contents)) {}

    std::vector<Token> tokenize();

private:
    std::string m_contents;
    int m_index{};
    // Function to get the character using m_index
    [[nodiscard]] inline std::optional<char> peek(const int offset = 0) {
        if (m_index + offset >= m_contents.size()) {
            return {};
        }
        else {
            return m_contents.at(m_index + offset);
        }
    }
    // Function to consume the character
    inline char consume() {
        return m_contents.at(m_index++);
    }
};
