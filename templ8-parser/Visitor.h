#pragma once

#include <antlr4-runtime.h>
#include "parser/templ8BaseVisitor.h"
#include <string>

class Visitor : templ8BaseVisitor {
public:
  antlrcpp::Any visitFile(templ8Parser::FileContext *ctx);
  antlrcpp::Any visitDefinition(templ8Parser::DefinitionContext *ctx);
  antlrcpp::Any visitAttribute(templ8Parser::AttributeContext *ctx);
};