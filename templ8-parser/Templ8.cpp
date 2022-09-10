#include <iostream>

#include "Templ8.hpp"
#include "Visitor.h"

using namespace antlr4;

Templ8 streamTempl8(std::istream &stream) {
  ANTLRInputStream input(stream);
  templ8Lexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  templ8Parser parser(&tokens);
  templ8Parser::FileContext *tree = parser.file();
  Visitor visitor;
  return std::any_cast<Templ8>(visitor.visitFile(tree));
}

Templ8 loadTempl8(const std::string &fn) {

  std::ifstream stream;
  stream.open(fn);
  return streamTempl8(stream);
}