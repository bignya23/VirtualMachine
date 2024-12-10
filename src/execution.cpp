#include <algorithm>
#include <iostream>
#include "headers/executor.hpp"
#include <cctype>


void Execution::execute() {

    for (auto& smt : m_stmts) {
        //PUSH
        if (smt.token.type == TokenType::PUSH) {
            m_stack.push(stoi(smt.value.value()));
            // std::cout << "Pushed"<< std::endl;
        }
        //POP
        if (smt.token.type == TokenType::POP) {
            m_stack.pop();
            // std::cout << "Popped" << std::endl;
        }
        //LOAD
        if (smt.token.type == TokenType::LOAD) {

            if (std::all_of(smt.value.value().begin(), smt.value.value().end(), ::isdigit)) {
                m_stack.push(stoi(smt.value.value()));
                // std::cout << "Pushed"<< std::endl;
            }
            else {
                bool isFound = false;
                for (auto& m : m_map) {
                    if (m.first == smt.value.value()) {
                        m_stack.push(m.second);
                        isFound = true;
                        // std::cout << "Loaded" << std::endl;
                        break;
                    }
                }
                if (isFound == false) {
                    std::cerr << smt.value.value() << " not defined" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

        }
        //STORE
        if (smt.token.type == TokenType::STORE) {
            m_map[smt.value.value()] = m_stack.top();
            // std::cout << "STORED" << std::endl;
        }
        //PRINT
        if (smt.token.type == TokenType::PRINT) {
            if (smt.value.has_value()) {
                // For identifier
                if (smt.value.value()[0] == '<' && smt.value.value()[1] == '>' ) {
                    std::string identifier{};
                    for (int i = 2; i < smt.value.value().size(); i++) {
                        identifier.push_back(smt.value.value()[i]);
                    }
                    int found = false;
                    for (auto& m : m_map) {
                        if (m.first == identifier) {
                            std::cout << m.second << std::endl;
                            found = true;
                        }
                    }
                    if (!found) {
                        std::cerr << identifier << " not defined" << std::endl;
                    }
                }
                // For strings
                else {
                    std::cout << smt.value.value() << std::endl;
                }
            }
            // Just printing the stack for empty
            else {
                std::stack<int> s = m_stack;
                int i = 0;
                if (s.empty()) {
                    std::cout << "Stack is empty" << std::endl;
                }
                std::cout << "Printing stack : " << std::endl;
                while (!s.empty()) {
                    std::cout << i++ << " " << s.top() << std::endl;
                    s.pop();
                }
            }

        }
        // INPUT
        if (smt.token.type == TokenType::INPUT) {
            int val;
            std::cin >> val;
            m_map[smt.value.value()] = val;
        }
        // OPERATIONS
        if (smt.token.type == TokenType::ADD || smt.token.type == TokenType::SUB || smt.token.type == TokenType::MUL || smt.token.type == TokenType::DIV) {
            if (smt.value.has_value()) {
                std::stack<int> s;
                std::string buffer{};
                std::string st = smt.value.value();
                for (int i = 0; i < st.length(); i++) {
                    if (st[i] == ' ') {
                        continue;
                    }
                    else if (st[i] ==',') {
                        continue;
                    }
                    else if (isalpha(st[i])) {
                        while (isalpha(st[i])) {
                            buffer.push_back(st[i]);
                            i++;
                        }
                        bool found = false;
                        for (auto& m : m_map) {
                            if (m.first == buffer) {
                                s.push(m.second);
                                found = true;
                            }
                        }
                        if (!found) {
                            std::cerr << buffer << " not defined" << std::endl;
                        }
                        buffer.clear();
                    }
                    else if (isdigit(st[i])) {
                        while (isdigit(st[i])) {
                            buffer.push_back(st[i]);
                            i++;
                        }
                        int val = std::stoi(buffer);
                        s.push(val);
                        buffer.clear();
                    }
                    else {
                        std::cerr << "Invalid Character" << std::endl;
                    }

                }
                if (smt.token.type == TokenType::ADD) {
                    int result{};
                    while (!s.empty()) {
                        result += s.top();
                        s.pop();
                    }
                    m_stack.push(result);
                }
                if (smt.token.type == TokenType::SUB) {
                    int result = s.top();
                    s.pop();
                    while (!s.empty()) {
                        result -= s.top();
                        s.pop();
                    }
                    m_stack.push(result);
                }
                if (smt.token.type == TokenType::MUL) {
                    int result = 1;
                    while (!s.empty()) {
                        result *= s.top();
                        s.pop();
                    }
                    m_stack.push(result);
                }
                if (smt.token.type == TokenType::DIV) {
                    int val1 = s.top();
                    s.pop();
                    int val2 = s.top();
                    s.pop();
                    m_stack.push(val1 / val2);
                }


            }

            else {
                if (m_stack.empty()) {
                    std::cerr << "Less values in stack" << std::endl;
                    exit(EXIT_FAILURE);
                }
                int val1 = m_stack.top();
                m_stack.pop();
                if (m_stack.empty()) {
                    std::cerr << "Less values in stack" << std::endl;
                    exit(EXIT_FAILURE);
                }
                int val2 = m_stack.top();
                m_stack.pop();
                int result = val1 + val2;
                m_stack.push(result);
            }
        }


    }
}
