#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include <Templ8.hpp>

#include "metatool.hpp"

namespace fs = std::filesystem;

using namespace llvm;

static llvm::cl::OptionCategory ms_generator{"metatool-gen options"};

static llvm::cl::extrahelp
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

static llvm::cl::opt<std::string> TemplateT8Option{
    "t", llvm::cl::desc("Name or path of t8 template"),
    llvm::cl::value_desc("path"), llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string> TemplateXMLOption{
    "x", llvm::cl::desc("Name or path of XML template"),
    llvm::cl::value_desc("path"), llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string> OutputFilename{
    "o", cl::desc("Specify output filename"), llvm::cl::value_desc("filename"),
    llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string>
    InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                  llvm::cl::init("../test/test.cpp"));


int main(int argc, const char *argv[]) {
  using namespace metatool;

  clang::tooling::CommonOptionsParser opts = {argc, argv, ms_generator};

  std::string fn = TemplateT8Option;
  bool t8 = true;

  if(TemplateT8Option == "" && TemplateXMLOption != ""){
    fn = TemplateXMLOption;
    t8 = false;
  }
  std::ifstream stream;
  stream.open(fn);

  const auto files = opts.getSourcePathList();
  return generate(opts.getCompilations(), files, stream, t8, OutputFilename);

}
