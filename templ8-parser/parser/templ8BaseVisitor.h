
// Generated from templ8.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "templ8Visitor.h"


/**
 * This class provides an empty implementation of templ8Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  templ8BaseVisitor : public templ8Visitor {
public:

  virtual std::any visitFile(templ8Parser::FileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitName(templ8Parser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition(templ8Parser::DefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute(templ8Parser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeftype(templ8Parser::DeftypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCodeblock(templ8Parser::CodeblockContext *ctx) override {
    return visitChildren(ctx);
  }


};

