#pragma once
#include <string>
#include <iostream>
#include <utility>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "executor.hpp"
class Labels {
public:
    explicit Labels() {};

    std::unordered_map<std::string, std::string> labels(std::string filename);

private:
    std::string m_prg{};

};
