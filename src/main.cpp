#include <fstream>
#include <iostream>
#include <sstream>

#include "headers/parser.hpp"
#include "headers/tokenizer.hpp"
#include "headers/executor.hpp"
int main(int argc, char** argv)
{

    if(argc  < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.masm>" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream file(argv[1], std::ios::in);
        contents_stream << file.rdbuf();
        contents = contents_stream.str();
    }
    // Tokenization
    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();
    // Parsing
    Parser parser(tokens);
    std::vector<stmt> stmts = parser.stmts();
    // Execution
    Execution execution(stmts);
    execution.execute();

    // for(const auto&[type, val] : tokens) {
    //     std::cout<< type <<  " ";
    // }
    //
    // std::cout << std::endl;
    // std::cout << "Working Fine" << std::endl;
    return 0;
}
