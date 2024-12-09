#pragma once
#include <stack>
#include <unordered_map>

#include "parser.hpp"
class Execution {
public:
    explicit Execution(std::vector<stmt> stmts) : m_stmts(std::move(stmts)) {}

    void execute();

private:
    std::vector<stmt> m_stmts;
    std::stack<int> m_stack;
    std::unordered_map<std::string, int> m_map;
};