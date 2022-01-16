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
namespace metastuff {
struct Struct {
  std::string name;
  std::string memberTemplatesFilled;
};

std::string randomHeaderName() {
  std::vector<std::string> const syllables = {"QU",
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
  std::uniform_int_distribution<size_t> dist{0, syllables.size() - 1};
  std::vector<std::string> v;
  std::generate_n(std::back_inserter(v), len,
                  [&] { return syllables[dist(gen)]; });
  std::string ret;
  ret = std::accumulate(v.begin(), v.end(), ret);
  ;
  ret += "_HPP";
  return ret;
}

} // namespace metastuff

class StructDeclASTVisitor
    : public clang::RecursiveASTVisitor<StructDeclASTVisitor> {
  clang::SourceManager &sourceManager_;

public:
  static std::string MemberTemplate;
  static std::vector<metastuff::Struct> Data;

  explicit StructDeclASTVisitor(clang::SourceManager &sm)
      : sourceManager_(sm) {}

  bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
    if (sourceManager_.isWrittenInMainFile(decl->getSourceRange().getBegin())) {
      using namespace metastuff;
      Struct s;
      s.name = decl->getQualifiedNameAsString();
      clang::ASTContext &ctx = decl->getASTContext();
      clang::SourceManager &sm = ctx.getSourceManager();
      const auto fields = decl->fields();

      bool ignoreStruct = false;
      auto *rc = decl->getASTContext().getRawCommentForDeclNoCache(decl);
      std::vector<std::string> ignoreMembers = {};
      if (rc) {
        // Found comment!
        std::string raw = rc->getRawText(sm);
        std::cout << "raw:\n" << raw << std::endl;

        if (raw.find("@meta-ignore-struct") != std::string::npos ||
            raw.find("@meta-ignore-class") != std::string::npos) {
          ignoreStruct = true;
          std::cout << "ignoreStruct: " << ignoreStruct << std::endl;
        }
        auto ignoreMPos = raw.find("@meta-ignore-members");
        if (ignoreMPos != std::string::npos) {
          std::string delim = ",";

          auto start = raw.find(":", ignoreMPos);
          std::string s;
          auto end = raw.find(delim, start);

          while (end != std::string::npos) {
            s = raw.substr(start, end - start);
            s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
            ignoreMembers.push_back(s);
            std::cout << "ignore: \"" << s << "\"" << std::endl;

            start = end + delim.length();
            end = raw.find(delim, start);
          }
          end = raw.find(";", start);

          s = raw.substr(start, end - start);
          s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
          ignoreMembers.push_back(s);
          std::cout << "ignore: \"" << s << "\"" << std::endl;
        }
      }

      if (!ignoreStruct) {
        std::string memberBuff;
        std::for_each(
            std::begin(fields), std::end(fields),
            [&memberBuff, &ignoreMembers](const auto &f) {
              using namespace fmt::literals;
              const std::string shortMemberName = f->getNameAsString();
              const std::string memberName = f->getQualifiedNameAsString();
              if (std::find(ignoreMembers.begin(), ignoreMembers.end(),
                            shortMemberName) == ignoreMembers.end()) {

                memberBuff += fmt::format(
                    MemberTemplate, "SHORT_MEMBER_NAME"_a = shortMemberName,
                    "MEMBER_NAME"_a = memberName);
                memberBuff += ",\n";
              }
            });
        memberBuff = memberBuff.substr(0, memberBuff.size() - 2);
        s.memberTemplatesFilled = memberBuff;
        Data.push_back(s);
      }
    }
    return true;
  }
};
std::string StructDeclASTVisitor::MemberTemplate = "";
std::vector<metastuff::Struct> StructDeclASTVisitor::Data = {};

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

  // FIXME could not get his to work
  // tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster(
  //     {"-fparse-all-comments"},
  //     clang::tooling::ArgumentInsertPosition::BEGIN));

  auto ec = tool.run(
      clang::tooling::newFrontendActionFactory<StructDeclFrontendAction>()
          .get());
  std::string specializationBuff, includeBuff;

  for (const auto &structEntry : StructDeclASTVisitor::Data) {
    using namespace fmt;
    specializationBuff +=
        fmt::format(SpecializationTemplate, "TYPE"_a = structEntry.name,
                    "MEMBERS"_a = structEntry.memberTemplatesFilled);
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
      FileTemplate, "INCLUDE_GUARD_NAME"_a = metastuff::randomHeaderName(),
      "SPECIALIZATIONS"_a = specializationBuff, "INCLUDES"_a = includeBuff);
  std::ofstream outfile(OutputFilename.c_str());
  if (outfile.good()) {
    outfile << output << std::endl;
    outfile.close();
  } else
    std::cout << output << std::endl;

  return ec;
}
