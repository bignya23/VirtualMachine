#include <fstream>
#include <iostream>
#include <sstream>

#include "headers/parser.hpp"
#include "headers/tokenizer.hpp"
#include "headers/executor.hpp"
#include "headers/labelsprocess.hpp"
int main(int argc, char** argv)
{

    if(argc  < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.masm>" << std::endl;
        exit(EXIT_FAILURE);
    }

    // std::string contents;
    // {
    //     std::stringstream contents_stream;
    //     std::fstream file(argv[1], std::ios::in);
    //     contents_stream << file.rdbuf();
    //     contents = contents_stream.str();
    // }
    Labels lb;
    //
    std::unordered_map<std::string, std::string> program = lb.labels(argv[1]);
    //
    // for (auto& it : program) {
    //     std::cout << it.first << "\n" << it.second << std::endl;
    // }

    // Tokenization
    std::unordered_map<std::string, std::vector<Token>> tokens;
    for (auto& contents : program) {
        Tokenizer tokenizer(contents.second);
        std::vector<Token> token = tokenizer.tokenize();
        tokens[contents.first] = token;
    }

    // Parsing
    std::unordered_map<std::string, std::vector<stmt>> stmts;
    for (auto& it : tokens) {
        Parser parser(it.second);
        std::vector<stmt> stmt = parser.stmts();
        stmts[it.first] = stmt;
    }
    // Execution
    Execution execution(stmts);
    execution.execute(stmts["start:"]);

    return 0;
}
