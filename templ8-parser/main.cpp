#include <iostream>
#include <antlr4-runtime.h>
#include "parser/templ8Lexer.h"
#include "parser/templ8Parser.h"
#include "Visitor.h"

using namespace std;
using namespace antlr4;
int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open("test.templ8");

    ANTLRInputStream input(stream);
    templ8Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    templ8Parser parser(&tokens);
    templ8Parser::FileContext* tree = parser.file();
    Visitor visitor;
    Templ8 templ8 = std::any_cast<Templ8>( visitor.visitFile(tree));
    templ8.print();
    return 0;
}