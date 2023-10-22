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

static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

static llvm::cl::opt<std::string> TemplateOption{"t",
                                                 llvm::cl::desc("Name or path of template .t8/.xml ending necessary"),
                                                 llvm::cl::value_desc("path"), llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string> OutputFilename{"o", cl::desc("Specify output filename"),
                                                 llvm::cl::value_desc("filename"), llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                                                llvm::cl::init("../test/test.cpp"));
bool endsWith(const std::string &value, const std::string &ending) {
  if (ending.size() > value.size())
    return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main(int argc, const char *argv[]) {
  using namespace metatool;

  auto opts = clang::tooling::CommonOptionsParser::create(argc, argv, ms_generator);

  std::string template_fn = TemplateOption;
  bool t8 = true;

  if (endsWith(template_fn, ".xml")) {
    t8 = false;
  }
  std::ifstream stream;
  stream.open(template_fn);

  const auto files = opts->getSourcePathList();
  return generate(opts->getCompilations(), files, stream, t8, OutputFilename);
}
