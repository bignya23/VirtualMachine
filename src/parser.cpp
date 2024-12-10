#include <iostream>
#include "headers/parser.hpp"


std::optional<stmt> Parser::parse() {
    // PUSH
    if (peek(0).has_value() && peek().value().type == TokenType::PUSH && peek(1).has_value() && peek(1).value().type == TokenType::NUMBER) {
        stmt s;

        s.token = peek().value();
        consume();
        s.value = peek().value().val.value();
        consume();
        return s;
    }
    // POP
    if (peek(0).has_value() && peek().value().type == TokenType::POP) {
        stmt s;
        s.token = peek().value();
        consume();
        return s;
    }

    // LOAD
    if (peek(0).has_value() && peek().value().type == TokenType::LOAD && peek(1).value().type == TokenType::IDENTIFIER || peek(1).has_value() && peek(1).value().type == TokenType::NUMBER) {
        stmt s;
        s.token = peek().value();
        consume();
        s.value = peek().value().val.value();
        consume();
        return s;
    }
    // STORE
    if (peek(0).has_value() && peek().value().type == TokenType::STORE && peek(1).value().type == TokenType::IDENTIFIER) {
        stmt s;
        s.token = peek().value();
        consume();
        s.value = peek().value().val.value();
        consume();
        return s;
    }
    // PRINT
    if (peek(0).has_value() && peek().value().type == TokenType::PRINT) {

        stmt s;
        s.token = peek().value();
        consume();

        if (peek().has_value() && peek().value().type == TokenType::STRING) {
            s.value = peek().value().val.value();
            consume();
        }
        if (peek().has_value() && peek().value().type == TokenType::IDENTIFIER) {
            s.value =  "<>" + peek().value().val.value() ;
            consume();
        }
        return s;
    }
    // INPUT
    if (peek(0).has_value() && peek().value().type == TokenType::INPUT && peek(1).has_value() && peek(1).value().type == TokenType::IDENTIFIER) {
        stmt s;
        s.token = peek().value();
        consume();
        s.value = peek().value().val.value();
        consume();
        return s;
    }
    // ADD, SUB, DIV, MUL
    if (peek(0).has_value() && peek().value().type == TokenType::ADD || peek().value().type == TokenType::SUB || peek().value().type == TokenType::MUL || peek().value().type == TokenType::DIV) {
        stmt s;
        s.token = peek().value();
        consume();
        if (peek().has_value() && peek().value().type == TokenType::EXPRESSION) {
            s.value = peek().value().val.value();
            consume();
        }

        return s;

    }
    return {};

}

std::vector<stmt> Parser::stmts() {
    Prg p;
    while (peek().has_value()) {
        if (auto s1 = parse()) {
            p.stmts.push_back(s1.value());
        }
        else {
            std::cerr << "ERROR in Parsing" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return p.stmts;
}

