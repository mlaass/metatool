#include <iostream>

#include "Templ8.hpp"
#include "Visitor.h"

using namespace std;
using namespace antlr4;
Templ8 loadTempl8(std::string fn) {

  std::ifstream stream;
  stream.open(fn);

  ANTLRInputStream input(stream);
  templ8Lexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  templ8Parser parser(&tokens);
  templ8Parser::FileContext *tree = parser.file();
  Visitor visitor;
  return std::any_cast<Templ8>(visitor.visitFile(tree));
}