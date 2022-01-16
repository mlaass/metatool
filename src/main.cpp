#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <fmt/format.h>
#include <llvm/Support/CommandLine.h>

namespace fs = std::filesystem;
namespace {
struct Struct {
  std::string name;
  std::string memberTemplatesFilled;
};

std::string randomHeaderName() {
  std::vector<std::string> const silables = {"QU",
                                             "OK"
                                             "AE",
                                             "IE",
                                             "KH",
                                             "PO",
                                             "FL",
                                             "OO"
                                             "DA",
                                             "IZ",
                                             "NI",
                                             "UH",
                                             "OU",
                                             "FF",
                                             "SR"
                                             "TI",
                                             "KA",
                                             "KI",
                                             "LL",
                                             "DA",
                                             "SZ",
                                             "AA"
                                             "MA",
                                             "MO"};

  const auto len = 5;
  std::mt19937_64 gen{std::random_device()()};
  std::uniform_int_distribution<size_t> dist{0, silables.size() - 1};
  std::vector<std::string> v;
  std::generate_n(std::back_inserter(v), len,
                  [&] { return silables[dist(gen)]; });
  std::string ret;
  ret = std::accumulate(v.begin(), v.end(), ret);
  ;
  ret += "_HPP";
  return ret;
}

std::vector<Struct> data;
} // namespace

class StructDeclASTVisitor
    : public clang::RecursiveASTVisitor<StructDeclASTVisitor> {
  clang::SourceManager &sourceManager_;

public:
  static std::string MemberTemplate;

  explicit StructDeclASTVisitor(clang::SourceManager &sm)
      : sourceManager_(sm) {}

  bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
    if (sourceManager_.isWrittenInMainFile(decl->getSourceRange().getBegin())) {
      Struct s;
      s.name = decl->getQualifiedNameAsString();

      const auto fields = decl->fields();
      std::string memberBuff;

      std::for_each(
          std::begin(fields), std::end(fields), [&memberBuff](const auto &f) {
            using namespace fmt::literals;
            const auto shortMemberName = f->getNameAsString();
            const auto memberName = f->getQualifiedNameAsString();
            memberBuff += "        ";
            memberBuff += fmt::format(MemberTemplate,
                                      "SHORT_MEMBER_NAME"_a = shortMemberName,
                                      "MEMBER_NAME"_a = memberName);
            memberBuff += ",\n";
          });

      memberBuff = memberBuff.substr(0, memberBuff.size() - 2);
      s.memberTemplatesFilled = memberBuff;
      data.push_back(s);
    }
    return true;
  }
};
std::string StructDeclASTVisitor::MemberTemplate = "";

class StructDeclASTConsumer : public clang::ASTConsumer {
  StructDeclASTVisitor visitor_; // doesn't have to be private

public:
  // override the constructor in order to pass CI
  explicit StructDeclASTConsumer(clang::CompilerInstance &ci)
      : visitor_(ci.getSourceManager()) {}

  virtual void HandleTranslationUnit(clang::ASTContext &astContext) {
    visitor_.TraverseDecl(astContext.getTranslationUnitDecl());
  }
};

class StructDeclFrontendAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef file) {
    return std::make_unique<StructDeclASTConsumer>(
        CI); // pass CI pointer to ASTConsumer
  }
};
using namespace llvm;

static llvm::cl::OptionCategory ms_generator{"metastuff-gen options"};
static llvm::cl::extrahelp
    MoreHelp("\n-t is a pth to directory with 3 template files: 'file', "
             "'member', 'specialization'\n");
static llvm::cl::extrahelp
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
static llvm::cl::opt<std::string> TemplateOption{
    "t", llvm::cl::desc("Name or path of template"),
    llvm::cl::value_desc("path"), llvm::cl::cat(ms_generator)};
static llvm::cl::opt<std::string> OutputFilename{
    "o", cl::desc("Specify output filename"), llvm::cl::value_desc("filename"),
    llvm::cl::cat(ms_generator)};

std::string readFile(fs::path fn) {
  std::ifstream infile{fn};
  if (infile.good()) {
    std::stringstream ss;
    ss << infile.rdbuf(); // read the file
    return ss.str();
  }
}
int main(int argc, const char *argv[]) {

  clang::tooling::CommonOptionsParser opts{argc, argv, ms_generator};
  std::cout << OutputFilename << TemplateOption << std::endl;

  std::string SpecializationTemplate;
  std::string FileTemplate;
  const fs::path templ{TemplateOption.c_str()};
  if (fs::exists(templ)) {
    SpecializationTemplate = readFile(templ / "specialization");
    FileTemplate = readFile(templ / "file");
    StructDeclASTVisitor::MemberTemplate = readFile(templ / "member");
  }

  const auto files = opts.getSourcePathList();

  clang::tooling::ClangTool tool{opts.getCompilations(), files};

  auto ec = tool.run(
      clang::tooling::newFrontendActionFactory<StructDeclFrontendAction>()
          .get());
  std::string specializationBuff, includeBuff;
  for (const auto &oneEntry : data) {
    using namespace fmt;
    specializationBuff +=
        fmt::format(SpecializationTemplate, "TYPE"_a = oneEntry.name,
                    "MEMBERS"_a = oneEntry.memberTemplatesFilled);
    specializationBuff += "\n";
  }

  using namespace fmt;
  // includes
  {
    for (const auto &f : files) {
      includeBuff += fmt::format("#include <{}>\n", f);
    }
  }
  auto output = fmt::format(
      FileTemplate, "INCLUDE_GUARD_NAME"_a = randomHeaderName(),
      "SPECIALIZATIONS"_a = specializationBuff, "INCLUDES"_a = includeBuff);
  std::ofstream outfile(OutputFilename.c_str());
  if (outfile.good()) {
    outfile << output << std::endl;
    outfile.close();
  } else
    std::cout << output << std::endl;

  return ec;
}
