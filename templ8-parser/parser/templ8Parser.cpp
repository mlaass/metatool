
// Generated from templ8.g4 by ANTLR 4.10.1


#include "templ8Visitor.h"

#include "templ8Parser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct Templ8ParserStaticData final {
  Templ8ParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Templ8ParserStaticData(const Templ8ParserStaticData&) = delete;
  Templ8ParserStaticData(Templ8ParserStaticData&&) = delete;
  Templ8ParserStaticData& operator=(const Templ8ParserStaticData&) = delete;
  Templ8ParserStaticData& operator=(Templ8ParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag templ8ParserOnceFlag;
Templ8ParserStaticData *templ8ParserStaticData = nullptr;

void templ8ParserInitialize() {
  assert(templ8ParserStaticData == nullptr);
  auto staticData = std::make_unique<Templ8ParserStaticData>(
    std::vector<std::string>{
      "file", "name", "definition", "attribute", "deftype", "codeblock"
    },
    std::vector<std::string>{
      "", "':'", "'='", "'def'", "", "','", "'member'", "'method'", "'argument'", 
      "'struct'", "'function'", "'file'"
    },
    std::vector<std::string>{
      "", "", "", "BEGIN", "END", "COMMA", "MEMBER", "METHOD", "ARGUMENT", 
      "STRUCT", "FUNCTION", "FILE", "CODE", "STRING", "NAME", "NEWLINE", 
      "COMMENT", "WHITESPACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,17,50,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,0,1,0,1,0,
  	1,0,3,0,17,8,0,5,0,19,8,0,10,0,12,0,22,9,0,1,0,1,0,1,1,1,1,1,1,1,2,1,
  	2,1,2,1,2,3,2,33,8,2,5,2,35,8,2,10,2,12,2,38,9,2,1,2,1,2,1,3,1,3,1,3,
  	1,3,1,4,1,4,1,5,1,5,1,5,0,0,6,0,2,4,6,8,10,0,1,1,0,6,11,47,0,12,1,0,0,
  	0,2,25,1,0,0,0,4,28,1,0,0,0,6,41,1,0,0,0,8,45,1,0,0,0,10,47,1,0,0,0,12,
  	13,3,2,1,0,13,20,5,15,0,0,14,16,3,4,2,0,15,17,5,15,0,0,16,15,1,0,0,0,
  	16,17,1,0,0,0,17,19,1,0,0,0,18,14,1,0,0,0,19,22,1,0,0,0,20,18,1,0,0,0,
  	20,21,1,0,0,0,21,23,1,0,0,0,22,20,1,0,0,0,23,24,5,0,0,1,24,1,1,0,0,0,
  	25,26,5,14,0,0,26,27,5,1,0,0,27,3,1,0,0,0,28,29,5,3,0,0,29,36,3,8,4,0,
  	30,32,3,6,3,0,31,33,5,5,0,0,32,31,1,0,0,0,32,33,1,0,0,0,33,35,1,0,0,0,
  	34,30,1,0,0,0,35,38,1,0,0,0,36,34,1,0,0,0,36,37,1,0,0,0,37,39,1,0,0,0,
  	38,36,1,0,0,0,39,40,3,10,5,0,40,5,1,0,0,0,41,42,5,14,0,0,42,43,5,2,0,
  	0,43,44,5,13,0,0,44,7,1,0,0,0,45,46,7,0,0,0,46,9,1,0,0,0,47,48,5,12,0,
  	0,48,11,1,0,0,0,4,16,20,32,36
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  templ8ParserStaticData = staticData.release();
}

}

templ8Parser::templ8Parser(TokenStream *input) : templ8Parser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

templ8Parser::templ8Parser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  templ8Parser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *templ8ParserStaticData->atn, templ8ParserStaticData->decisionToDFA, templ8ParserStaticData->sharedContextCache, options);
}

templ8Parser::~templ8Parser() {
  delete _interpreter;
}

const atn::ATN& templ8Parser::getATN() const {
  return *templ8ParserStaticData->atn;
}

std::string templ8Parser::getGrammarFileName() const {
  return "templ8.g4";
}

const std::vector<std::string>& templ8Parser::getRuleNames() const {
  return templ8ParserStaticData->ruleNames;
}

const dfa::Vocabulary& templ8Parser::getVocabulary() const {
  return templ8ParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView templ8Parser::getSerializedATN() const {
  return templ8ParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

templ8Parser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* templ8Parser::FileContext::EOF() {
  return getToken(templ8Parser::EOF, 0);
}

templ8Parser::NameContext* templ8Parser::FileContext::name() {
  return getRuleContext<templ8Parser::NameContext>(0);
}

std::vector<tree::TerminalNode *> templ8Parser::FileContext::NEWLINE() {
  return getTokens(templ8Parser::NEWLINE);
}

tree::TerminalNode* templ8Parser::FileContext::NEWLINE(size_t i) {
  return getToken(templ8Parser::NEWLINE, i);
}

std::vector<templ8Parser::DefinitionContext *> templ8Parser::FileContext::definition() {
  return getRuleContexts<templ8Parser::DefinitionContext>();
}

templ8Parser::DefinitionContext* templ8Parser::FileContext::definition(size_t i) {
  return getRuleContext<templ8Parser::DefinitionContext>(i);
}


size_t templ8Parser::FileContext::getRuleIndex() const {
  return templ8Parser::RuleFile;
}


std::any templ8Parser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<templ8Visitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

templ8Parser::FileContext* templ8Parser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, templ8Parser::RuleFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(12);
    name();
    setState(13);
    match(templ8Parser::NEWLINE);
    setState(20);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == templ8Parser::BEGIN) {
      setState(14);
      definition();
      setState(16);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == templ8Parser::NEWLINE) {
        setState(15);
        match(templ8Parser::NEWLINE);
      }
      setState(22);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(23);
    match(templ8Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameContext ------------------------------------------------------------------

templ8Parser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* templ8Parser::NameContext::NAME() {
  return getToken(templ8Parser::NAME, 0);
}


size_t templ8Parser::NameContext::getRuleIndex() const {
  return templ8Parser::RuleName;
}


std::any templ8Parser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<templ8Visitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}

templ8Parser::NameContext* templ8Parser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 2, templ8Parser::RuleName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25);
    match(templ8Parser::NAME);
    setState(26);
    match(templ8Parser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefinitionContext ------------------------------------------------------------------

templ8Parser::DefinitionContext::DefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* templ8Parser::DefinitionContext::BEGIN() {
  return getToken(templ8Parser::BEGIN, 0);
}

templ8Parser::DeftypeContext* templ8Parser::DefinitionContext::deftype() {
  return getRuleContext<templ8Parser::DeftypeContext>(0);
}

templ8Parser::CodeblockContext* templ8Parser::DefinitionContext::codeblock() {
  return getRuleContext<templ8Parser::CodeblockContext>(0);
}

std::vector<templ8Parser::AttributeContext *> templ8Parser::DefinitionContext::attribute() {
  return getRuleContexts<templ8Parser::AttributeContext>();
}

templ8Parser::AttributeContext* templ8Parser::DefinitionContext::attribute(size_t i) {
  return getRuleContext<templ8Parser::AttributeContext>(i);
}

std::vector<tree::TerminalNode *> templ8Parser::DefinitionContext::COMMA() {
  return getTokens(templ8Parser::COMMA);
}

tree::TerminalNode* templ8Parser::DefinitionContext::COMMA(size_t i) {
  return getToken(templ8Parser::COMMA, i);
}


size_t templ8Parser::DefinitionContext::getRuleIndex() const {
  return templ8Parser::RuleDefinition;
}


std::any templ8Parser::DefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<templ8Visitor*>(visitor))
    return parserVisitor->visitDefinition(this);
  else
    return visitor->visitChildren(this);
}

templ8Parser::DefinitionContext* templ8Parser::definition() {
  DefinitionContext *_localctx = _tracker.createInstance<DefinitionContext>(_ctx, getState());
  enterRule(_localctx, 4, templ8Parser::RuleDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    match(templ8Parser::BEGIN);
    setState(29);
    deftype();
    setState(36);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == templ8Parser::NAME) {
      setState(30);
      attribute();
      setState(32);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == templ8Parser::COMMA) {
        setState(31);
        match(templ8Parser::COMMA);
      }
      setState(38);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(39);
    codeblock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeContext ------------------------------------------------------------------

templ8Parser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* templ8Parser::AttributeContext::NAME() {
  return getToken(templ8Parser::NAME, 0);
}

tree::TerminalNode* templ8Parser::AttributeContext::STRING() {
  return getToken(templ8Parser::STRING, 0);
}


size_t templ8Parser::AttributeContext::getRuleIndex() const {
  return templ8Parser::RuleAttribute;
}


std::any templ8Parser::AttributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<templ8Visitor*>(visitor))
    return parserVisitor->visitAttribute(this);
  else
    return visitor->visitChildren(this);
}

templ8Parser::AttributeContext* templ8Parser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 6, templ8Parser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(41);
    match(templ8Parser::NAME);
    setState(42);
    match(templ8Parser::T__1);
    setState(43);
    match(templ8Parser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeftypeContext ------------------------------------------------------------------

templ8Parser::DeftypeContext::DeftypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* templ8Parser::DeftypeContext::MEMBER() {
  return getToken(templ8Parser::MEMBER, 0);
}

tree::TerminalNode* templ8Parser::DeftypeContext::METHOD() {
  return getToken(templ8Parser::METHOD, 0);
}

tree::TerminalNode* templ8Parser::DeftypeContext::ARGUMENT() {
  return getToken(templ8Parser::ARGUMENT, 0);
}

tree::TerminalNode* templ8Parser::DeftypeContext::STRUCT() {
  return getToken(templ8Parser::STRUCT, 0);
}

tree::TerminalNode* templ8Parser::DeftypeContext::FUNCTION() {
  return getToken(templ8Parser::FUNCTION, 0);
}

tree::TerminalNode* templ8Parser::DeftypeContext::FILE() {
  return getToken(templ8Parser::FILE, 0);
}


size_t templ8Parser::DeftypeContext::getRuleIndex() const {
  return templ8Parser::RuleDeftype;
}


std::any templ8Parser::DeftypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<templ8Visitor*>(visitor))
    return parserVisitor->visitDeftype(this);
  else
    return visitor->visitChildren(this);
}

templ8Parser::DeftypeContext* templ8Parser::deftype() {
  DeftypeContext *_localctx = _tracker.createInstance<DeftypeContext>(_ctx, getState());
  enterRule(_localctx, 8, templ8Parser::RuleDeftype);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << templ8Parser::MEMBER)
      | (1ULL << templ8Parser::METHOD)
      | (1ULL << templ8Parser::ARGUMENT)
      | (1ULL << templ8Parser::STRUCT)
      | (1ULL << templ8Parser::FUNCTION)
      | (1ULL << templ8Parser::FILE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CodeblockContext ------------------------------------------------------------------

templ8Parser::CodeblockContext::CodeblockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* templ8Parser::CodeblockContext::CODE() {
  return getToken(templ8Parser::CODE, 0);
}


size_t templ8Parser::CodeblockContext::getRuleIndex() const {
  return templ8Parser::RuleCodeblock;
}


std::any templ8Parser::CodeblockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<templ8Visitor*>(visitor))
    return parserVisitor->visitCodeblock(this);
  else
    return visitor->visitChildren(this);
}

templ8Parser::CodeblockContext* templ8Parser::codeblock() {
  CodeblockContext *_localctx = _tracker.createInstance<CodeblockContext>(_ctx, getState());
  enterRule(_localctx, 10, templ8Parser::RuleCodeblock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    match(templ8Parser::CODE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void templ8Parser::initialize() {
  std::call_once(templ8ParserOnceFlag, templ8ParserInitialize);
}
