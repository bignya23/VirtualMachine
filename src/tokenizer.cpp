#include <iostream>
#include <optional>
#include "headers/tokenizer.hpp"


std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    std::string buffer{};
    while(peek().has_value()) {
        // For alphabets
        if(isalpha(peek().value())) {
            buffer.push_back(consume());
            // For further char
            while(isalpha(peek().value())) {
                buffer.push_back(consume());
            }
            // Compare the string and map to the TokenType
            if(buffer == "push" || buffer == "PUSH") {
                tokens.push_back({.type = PUSH});
            }
            else if(buffer == "pop" || buffer == "POP") {
                tokens.push_back({.type = POP});
            }
            else if(buffer == "load" || buffer == "LOAD") {
                tokens.push_back({.type = LOAD});
            }
            else if(buffer == "store" || buffer == "STORE") {
                tokens.push_back({.type = STORE});
            }
            else if (buffer == "print" || buffer == "PRINT") {
                tokens.push_back({.type = PRINT});
            }
            else {
                tokens.push_back({.type = IDENTIFIER, .val = buffer});
            }
            buffer.clear(); // Clearing for further use
        }
        // For recognition of digits
        else if(isdigit(peek().value()) && peek(-1).value() != '\n') {
            buffer.push_back(consume());
            while(isdigit(peek().value())) {
                buffer.push_back(consume());
            }
            tokens.push_back({.type = NUMBER, .val = buffer});
            buffer.clear();
        }
        else if (peek().value() == '"') {
            consume();
            while (peek().has_value() && peek().value() != '"') {
                buffer.push_back(consume());
            }

            tokens.push_back({.type = STRING, .val = buffer});
            consume();
            buffer.clear();
        }
        else if(isspace(peek().value())) {
            consume();
        }
        else {
            std::cerr << "Invalid Syntax" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}



