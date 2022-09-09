#include "Visitor.h"
#include "Templ8.hpp"
#include <any>
#include <regex>


  antlrcpp::Any Visitor::visitFile(templ8Parser::FileContext *ctx)
  {
    std::vector<Definition> definitions;
    for (auto def : ctx->definition()) {
		  Definition d = std::any_cast<Definition>(visitDefinition(def));

      definitions.push_back(d);
    }

    auto name = ctx->name()->NAME()->getText();

    antlrcpp::Any result = Templ8{name, definitions};

    return result;
  }

  antlrcpp::Any Visitor::visitDefinition(templ8Parser::DefinitionContext *ctx)
  {
    std::string type = ctx->deftype()->getText();
    std::string code = ctx->codeblock()->CODE()->getText();

    std::regex s ("\\->[ \n\r]*");
    std::regex e ("[ \n\r]end");

    code = std::regex_replace(code,s, "");
    code = std::regex_replace(code,e, "");

    std::map<std::string,std::string> attributes;
    for (auto attr : ctx->attribute()) {
		  auto a = std::any_cast<std::pair<std::string, std::string>>(visitAttribute(attr));
      attributes.emplace(a);
     }

    antlrcpp::Any result = Definition{ type, attributes, code};
    return result;
  }

  antlrcpp::Any Visitor::visitAttribute(templ8Parser::AttributeContext *ctx)
  {
    auto key = ctx->NAME()->getText();
    auto val = ctx->STRING()->getText();
    val = val.substr(1, val.size()-2);
    // std:: cout << "attr: " << key << " = " << val << std::endl;
    antlrcpp::Any result = std::pair<std::string, std::string>(key, val);
    return result;
  }