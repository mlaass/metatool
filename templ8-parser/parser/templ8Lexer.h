
// Generated from templ8.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  templ8Lexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, BEGIN = 3, END = 4, COMMA = 5, MEMBER = 6, METHOD = 7, 
    ARGUMENT = 8, STRUCT = 9, FUNCTION = 10, FILE = 11, CODE = 12, STRING = 13, 
    NAME = 14, NEWLINE = 15, COMMENT = 16, WHITESPACE = 17
  };

  explicit templ8Lexer(antlr4::CharStream *input);

  ~templ8Lexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

