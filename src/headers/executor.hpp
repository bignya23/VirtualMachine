#pragma once
#include <stack>
#include <unordered_map>

#include "parser.hpp"
class Execution {
public:
    explicit Execution(    std::unordered_map<std::string, std::vector<stmt>> stmts) : allStmts(std::move(stmts)) {}

    void execute(std::vector<stmt> m_stmts);

private:
    std::unordered_map<std::string, std::vector<stmt>> allStmts;
    std::stack<int> m_stack;
    std::unordered_map<std::string, int> m_map;
};