
// Generated from templ8.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "templ8Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by templ8Parser.
 */
class  templ8Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by templ8Parser.
   */
    virtual std::any visitFile(templ8Parser::FileContext *context) = 0;

    virtual std::any visitName(templ8Parser::NameContext *context) = 0;

    virtual std::any visitDefinition(templ8Parser::DefinitionContext *context) = 0;

    virtual std::any visitAttribute(templ8Parser::AttributeContext *context) = 0;

    virtual std::any visitDeftype(templ8Parser::DeftypeContext *context) = 0;

    virtual std::any visitCodeblock(templ8Parser::CodeblockContext *context) = 0;


};

