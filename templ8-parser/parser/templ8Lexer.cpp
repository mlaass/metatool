
// Generated from templ8.g4 by ANTLR 4.10.1


#include "templ8Lexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct Templ8LexerStaticData final {
  Templ8LexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Templ8LexerStaticData(const Templ8LexerStaticData&) = delete;
  Templ8LexerStaticData(Templ8LexerStaticData&&) = delete;
  Templ8LexerStaticData& operator=(const Templ8LexerStaticData&) = delete;
  Templ8LexerStaticData& operator=(Templ8LexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag templ8lexerLexerOnceFlag;
Templ8LexerStaticData *templ8lexerLexerStaticData = nullptr;

void templ8lexerLexerInitialize() {
  assert(templ8lexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<Templ8LexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "BEGIN", "END", "COMMA", "MEMBER", "STRUCT", "FUNCTION", 
      "FILE", "CODE", "CODE_ITEM", "LONG_STRING_CHAR", "STRING_ESCAPE_SEQ", 
      "STRING", "NAME", "NEWLINE", "COMMENT", "WHITESPACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "':'", "'='", "'def'", "", "','", "'member'", "'struct'", "'function'", 
      "'file'"
    },
    std::vector<std::string>{
      "", "", "", "BEGIN", "END", "COMMA", "MEMBER", "STRUCT", "FUNCTION", 
      "FILE", "CODE", "STRING", "NAME", "NEWLINE", "COMMENT", "WHITESPACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,15,150,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,
  	3,1,3,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,
  	9,1,9,1,9,1,9,5,9,85,8,9,10,9,12,9,88,9,9,1,9,1,9,1,10,1,10,3,10,94,8,
  	10,1,11,1,11,1,12,1,12,1,12,1,12,3,12,102,8,12,1,13,1,13,5,13,106,8,13,
  	10,13,12,13,109,9,13,1,13,1,13,1,13,5,13,114,8,13,10,13,12,13,117,9,13,
  	1,13,3,13,120,8,13,1,14,4,14,123,8,14,11,14,12,14,124,1,15,3,15,128,8,
  	15,1,15,1,15,4,15,132,8,15,11,15,12,15,133,1,16,1,16,5,16,138,8,16,10,
  	16,12,16,141,9,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,4,86,107,115,
  	139,0,18,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,0,23,0,25,0,
  	27,11,29,12,31,13,33,14,35,15,1,0,3,1,0,92,92,5,0,45,45,48,57,65,90,95,
  	95,97,122,2,0,9,9,32,32,157,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,
  	0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,
  	0,19,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,
  	1,0,0,0,1,37,1,0,0,0,3,39,1,0,0,0,5,41,1,0,0,0,7,45,1,0,0,0,9,50,1,0,
  	0,0,11,52,1,0,0,0,13,59,1,0,0,0,15,66,1,0,0,0,17,75,1,0,0,0,19,80,1,0,
  	0,0,21,93,1,0,0,0,23,95,1,0,0,0,25,101,1,0,0,0,27,119,1,0,0,0,29,122,
  	1,0,0,0,31,131,1,0,0,0,33,135,1,0,0,0,35,146,1,0,0,0,37,38,5,58,0,0,38,
  	2,1,0,0,0,39,40,5,61,0,0,40,4,1,0,0,0,41,42,5,100,0,0,42,43,5,101,0,0,
  	43,44,5,102,0,0,44,6,1,0,0,0,45,46,3,31,15,0,46,47,5,101,0,0,47,48,5,
  	110,0,0,48,49,5,100,0,0,49,8,1,0,0,0,50,51,5,44,0,0,51,10,1,0,0,0,52,
  	53,5,109,0,0,53,54,5,101,0,0,54,55,5,109,0,0,55,56,5,98,0,0,56,57,5,101,
  	0,0,57,58,5,114,0,0,58,12,1,0,0,0,59,60,5,115,0,0,60,61,5,116,0,0,61,
  	62,5,114,0,0,62,63,5,117,0,0,63,64,5,99,0,0,64,65,5,116,0,0,65,14,1,0,
  	0,0,66,67,5,102,0,0,67,68,5,117,0,0,68,69,5,110,0,0,69,70,5,99,0,0,70,
  	71,5,116,0,0,71,72,5,105,0,0,72,73,5,111,0,0,73,74,5,110,0,0,74,16,1,
  	0,0,0,75,76,5,102,0,0,76,77,5,105,0,0,77,78,5,108,0,0,78,79,5,101,0,0,
  	79,18,1,0,0,0,80,81,5,45,0,0,81,82,5,62,0,0,82,86,1,0,0,0,83,85,3,21,
  	10,0,84,83,1,0,0,0,85,88,1,0,0,0,86,87,1,0,0,0,86,84,1,0,0,0,87,89,1,
  	0,0,0,88,86,1,0,0,0,89,90,3,7,3,0,90,20,1,0,0,0,91,94,3,23,11,0,92,94,
  	3,25,12,0,93,91,1,0,0,0,93,92,1,0,0,0,94,22,1,0,0,0,95,96,8,0,0,0,96,
  	24,1,0,0,0,97,98,5,92,0,0,98,102,9,0,0,0,99,100,5,92,0,0,100,102,3,31,
  	15,0,101,97,1,0,0,0,101,99,1,0,0,0,102,26,1,0,0,0,103,107,5,39,0,0,104,
  	106,9,0,0,0,105,104,1,0,0,0,106,109,1,0,0,0,107,108,1,0,0,0,107,105,1,
  	0,0,0,108,110,1,0,0,0,109,107,1,0,0,0,110,120,5,39,0,0,111,115,5,34,0,
  	0,112,114,9,0,0,0,113,112,1,0,0,0,114,117,1,0,0,0,115,116,1,0,0,0,115,
  	113,1,0,0,0,116,118,1,0,0,0,117,115,1,0,0,0,118,120,5,34,0,0,119,103,
  	1,0,0,0,119,111,1,0,0,0,120,28,1,0,0,0,121,123,7,1,0,0,122,121,1,0,0,
  	0,123,124,1,0,0,0,124,122,1,0,0,0,124,125,1,0,0,0,125,30,1,0,0,0,126,
  	128,5,13,0,0,127,126,1,0,0,0,127,128,1,0,0,0,128,129,1,0,0,0,129,132,
  	5,10,0,0,130,132,5,13,0,0,131,127,1,0,0,0,131,130,1,0,0,0,132,133,1,0,
  	0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,32,1,0,0,0,135,139,5,35,0,0,136,
  	138,9,0,0,0,137,136,1,0,0,0,138,141,1,0,0,0,139,140,1,0,0,0,139,137,1,
  	0,0,0,140,142,1,0,0,0,141,139,1,0,0,0,142,143,3,31,15,0,143,144,1,0,0,
  	0,144,145,6,16,0,0,145,34,1,0,0,0,146,147,7,2,0,0,147,148,1,0,0,0,148,
  	149,6,17,0,0,149,36,1,0,0,0,12,0,86,93,101,107,115,119,124,127,131,133,
  	139,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  templ8lexerLexerStaticData = staticData.release();
}

}

templ8Lexer::templ8Lexer(CharStream *input) : Lexer(input) {
  templ8Lexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *templ8lexerLexerStaticData->atn, templ8lexerLexerStaticData->decisionToDFA, templ8lexerLexerStaticData->sharedContextCache);
}

templ8Lexer::~templ8Lexer() {
  delete _interpreter;
}

std::string templ8Lexer::getGrammarFileName() const {
  return "templ8.g4";
}

const std::vector<std::string>& templ8Lexer::getRuleNames() const {
  return templ8lexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& templ8Lexer::getChannelNames() const {
  return templ8lexerLexerStaticData->channelNames;
}

const std::vector<std::string>& templ8Lexer::getModeNames() const {
  return templ8lexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& templ8Lexer::getVocabulary() const {
  return templ8lexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView templ8Lexer::getSerializedATN() const {
  return templ8lexerLexerStaticData->serializedATN;
}

const atn::ATN& templ8Lexer::getATN() const {
  return *templ8lexerLexerStaticData->atn;
}




void templ8Lexer::initialize() {
  std::call_once(templ8lexerLexerOnceFlag, templ8lexerLexerInitialize);
}
