
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
      "T__0", "T__1", "BEGIN", "END", "COMMA", "MEMBER", "METHOD", "ARGUMENT", 
      "STRUCT", "FUNCTION", "FILE", "CODE", "CODE_ITEM", "LONG_STRING_CHAR", 
      "STRING_ESCAPE_SEQ", "STRING", "NAME", "NEWLINE", "COMMENT", "WHITESPACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,17,170,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,
  	10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,5,11,105,8,11,10,11,12,11,108,9,
  	11,1,11,1,11,1,12,1,12,3,12,114,8,12,1,13,1,13,1,14,1,14,1,14,1,14,3,
  	14,122,8,14,1,15,1,15,5,15,126,8,15,10,15,12,15,129,9,15,1,15,1,15,1,
  	15,5,15,134,8,15,10,15,12,15,137,9,15,1,15,3,15,140,8,15,1,16,4,16,143,
  	8,16,11,16,12,16,144,1,17,3,17,148,8,17,1,17,1,17,4,17,152,8,17,11,17,
  	12,17,153,1,18,1,18,5,18,158,8,18,10,18,12,18,161,9,18,1,18,1,18,1,18,
  	1,18,1,19,1,19,1,19,1,19,4,106,127,135,159,0,20,1,1,3,2,5,3,7,4,9,5,11,
  	6,13,7,15,8,17,9,19,10,21,11,23,12,25,0,27,0,29,0,31,13,33,14,35,15,37,
  	16,39,17,1,0,3,1,0,92,92,5,0,45,45,48,57,65,90,95,95,97,122,2,0,9,9,32,
  	32,177,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,
  	11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,
  	0,0,0,0,23,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,
  	0,0,39,1,0,0,0,1,41,1,0,0,0,3,43,1,0,0,0,5,45,1,0,0,0,7,49,1,0,0,0,9,
  	54,1,0,0,0,11,56,1,0,0,0,13,63,1,0,0,0,15,70,1,0,0,0,17,79,1,0,0,0,19,
  	86,1,0,0,0,21,95,1,0,0,0,23,100,1,0,0,0,25,113,1,0,0,0,27,115,1,0,0,0,
  	29,121,1,0,0,0,31,139,1,0,0,0,33,142,1,0,0,0,35,151,1,0,0,0,37,155,1,
  	0,0,0,39,166,1,0,0,0,41,42,5,58,0,0,42,2,1,0,0,0,43,44,5,61,0,0,44,4,
  	1,0,0,0,45,46,5,100,0,0,46,47,5,101,0,0,47,48,5,102,0,0,48,6,1,0,0,0,
  	49,50,3,35,17,0,50,51,5,101,0,0,51,52,5,110,0,0,52,53,5,100,0,0,53,8,
  	1,0,0,0,54,55,5,44,0,0,55,10,1,0,0,0,56,57,5,109,0,0,57,58,5,101,0,0,
  	58,59,5,109,0,0,59,60,5,98,0,0,60,61,5,101,0,0,61,62,5,114,0,0,62,12,
  	1,0,0,0,63,64,5,109,0,0,64,65,5,101,0,0,65,66,5,116,0,0,66,67,5,104,0,
  	0,67,68,5,111,0,0,68,69,5,100,0,0,69,14,1,0,0,0,70,71,5,97,0,0,71,72,
  	5,114,0,0,72,73,5,103,0,0,73,74,5,117,0,0,74,75,5,109,0,0,75,76,5,101,
  	0,0,76,77,5,110,0,0,77,78,5,116,0,0,78,16,1,0,0,0,79,80,5,115,0,0,80,
  	81,5,116,0,0,81,82,5,114,0,0,82,83,5,117,0,0,83,84,5,99,0,0,84,85,5,116,
  	0,0,85,18,1,0,0,0,86,87,5,102,0,0,87,88,5,117,0,0,88,89,5,110,0,0,89,
  	90,5,99,0,0,90,91,5,116,0,0,91,92,5,105,0,0,92,93,5,111,0,0,93,94,5,110,
  	0,0,94,20,1,0,0,0,95,96,5,102,0,0,96,97,5,105,0,0,97,98,5,108,0,0,98,
  	99,5,101,0,0,99,22,1,0,0,0,100,101,5,45,0,0,101,102,5,62,0,0,102,106,
  	1,0,0,0,103,105,3,25,12,0,104,103,1,0,0,0,105,108,1,0,0,0,106,107,1,0,
  	0,0,106,104,1,0,0,0,107,109,1,0,0,0,108,106,1,0,0,0,109,110,3,7,3,0,110,
  	24,1,0,0,0,111,114,3,27,13,0,112,114,3,29,14,0,113,111,1,0,0,0,113,112,
  	1,0,0,0,114,26,1,0,0,0,115,116,8,0,0,0,116,28,1,0,0,0,117,118,5,92,0,
  	0,118,122,9,0,0,0,119,120,5,92,0,0,120,122,3,35,17,0,121,117,1,0,0,0,
  	121,119,1,0,0,0,122,30,1,0,0,0,123,127,5,39,0,0,124,126,9,0,0,0,125,124,
  	1,0,0,0,126,129,1,0,0,0,127,128,1,0,0,0,127,125,1,0,0,0,128,130,1,0,0,
  	0,129,127,1,0,0,0,130,140,5,39,0,0,131,135,5,34,0,0,132,134,9,0,0,0,133,
  	132,1,0,0,0,134,137,1,0,0,0,135,136,1,0,0,0,135,133,1,0,0,0,136,138,1,
  	0,0,0,137,135,1,0,0,0,138,140,5,34,0,0,139,123,1,0,0,0,139,131,1,0,0,
  	0,140,32,1,0,0,0,141,143,7,1,0,0,142,141,1,0,0,0,143,144,1,0,0,0,144,
  	142,1,0,0,0,144,145,1,0,0,0,145,34,1,0,0,0,146,148,5,13,0,0,147,146,1,
  	0,0,0,147,148,1,0,0,0,148,149,1,0,0,0,149,152,5,10,0,0,150,152,5,13,0,
  	0,151,147,1,0,0,0,151,150,1,0,0,0,152,153,1,0,0,0,153,151,1,0,0,0,153,
  	154,1,0,0,0,154,36,1,0,0,0,155,159,5,35,0,0,156,158,9,0,0,0,157,156,1,
  	0,0,0,158,161,1,0,0,0,159,160,1,0,0,0,159,157,1,0,0,0,160,162,1,0,0,0,
  	161,159,1,0,0,0,162,163,3,35,17,0,163,164,1,0,0,0,164,165,6,18,0,0,165,
  	38,1,0,0,0,166,167,7,2,0,0,167,168,1,0,0,0,168,169,6,19,0,0,169,40,1,
  	0,0,0,12,0,106,113,121,127,135,139,144,147,151,153,159,1,6,0,0
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
