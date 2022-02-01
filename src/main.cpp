#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include <tinyxml2.h>

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

namespace fs = std::filesystem;

std::string replace_all(std::string str, const std::string &remove,
                        const std::string &insert) {
  std::string::size_type pos = 0;
  while ((pos = str.find(remove, pos)) != std::string::npos) {
    str.replace(pos, remove.size(), insert);
    pos++;
  }

  return str;
}

std::string
fill_template(std::string templ,
              const std::vector<std::pair<std::string, std::string>> &args) {

  for (const auto &arg : args) {
    templ = replace_all(templ, std::string("{") + arg.first + std::string("}"),
                        arg.second);
  }
  // std::cout << templ << std::endl;
  return templ;
}
namespace metastuff {
struct Struct {
  std::string name;
  std::map<std::string, std::string> memberTemplatesFilled;
};

struct FileTemplate {
  std::string ext;
  std::string filename;
  std::string templ8;
};
struct MemberStructTemplate {
  std::string delim;
  bool removeLast;
  std::string templ8;
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
  static std::map<std::string, metastuff::MemberStructTemplate> memberTemplates;

  static std::vector<metastuff::Struct> structData;

  explicit StructDeclASTVisitor(clang::SourceManager &sm)
      : sourceManager_(sm) {}

  bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
    if (sourceManager_.isWrittenInMainFile(decl->getSourceRange().getBegin())) {
      using namespace metastuff;
      metastuff::Struct s;
      s.name = decl->getQualifiedNameAsString();
      clang::ASTContext &ctx = decl->getASTContext();
      clang::SourceManager &sm = ctx.getSourceManager();
      const auto fields = decl->fields();

      bool ignoreStruct = false;
      auto *rc = decl->getASTContext().getRawCommentForDeclNoCache(decl);
      std::vector<std::string> ignoreMembers = {};
      if (rc) {
        // Found comment!
        std::string raw = rc->getRawText(sm).str();

        if (raw.find("@meta-ignore-struct") != std::string::npos ||
            raw.find("@meta-ignore-class") != std::string::npos) {
          ignoreStruct = true;
        }
        auto ignoreMPos = raw.find("@meta-ignore-members");
        if (ignoreMPos != std::string::npos) {
          std::string delim = ",";

          auto start = raw.find(":", ignoreMPos) + 1;
          std::string s;
          auto end = raw.find(delim, start);

          while (end != std::string::npos) {
            s = raw.substr(start, end - start);
            s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
            ignoreMembers.push_back(s);

            start = end + delim.length();
            end = raw.find(delim, start);
          }
          end = raw.find(";", start);

          s = raw.substr(start, end - start);
          s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
          ignoreMembers.push_back(s);
        }
      }

      if (!ignoreStruct) {
        for (auto &[tname, templ8] : memberTemplates) {

          std::string memberBuff;
          std::for_each(
              std::begin(fields), std::end(fields), [&](const auto &f) {
                const std::string shortMemberName = f->getNameAsString();
                const std::string memberName = f->getQualifiedNameAsString();

                const clang::QualType qt = f->getType();
                std::string memberType = qt.getAsString();
                // some cleanup seems to be needed here!
                if (memberType == "_Bool")
                  memberType = "bool";

                if (std::find(ignoreMembers.begin(), ignoreMembers.end(),
                              shortMemberName) == ignoreMembers.end()) {

                  memberBuff += fill_template(
                      templ8.templ8, {{"SHORT_MEMBER_NAME", shortMemberName},
                                      {"MEMBER_NAME", memberName},
                                      {"MEMBER_TYPE", memberType}});
                  memberBuff += templ8.delim;
                }
              });
          if (templ8.removeLast) {
            memberBuff =
                memberBuff.substr(0, memberBuff.size() - templ8.delim.size());
          }
          s.memberTemplatesFilled[tname] = memberBuff;
        }
        structData.push_back(s);
      }
    }
    return true;
  }
};
std::map<std::string, metastuff::MemberStructTemplate>
    StructDeclASTVisitor::memberTemplates = {};
std::vector<metastuff::Struct> StructDeclASTVisitor::structData = {};

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
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

static llvm::cl::opt<std::string> TemplateXMLOption{
    "t", llvm::cl::desc("Name or path of XML template"),
    llvm::cl::value_desc("path"), llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string> OutputFilename{
    "o", cl::desc("Specify output filename"), llvm::cl::value_desc("filename"),
    llvm::cl::cat(ms_generator)};

static llvm::cl::opt<std::string>
    InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                  llvm::cl::init("../test/test.cpp"));

int main(int argc, const char *argv[]) {

  clang::tooling::CommonOptionsParser opts = {argc, argv, ms_generator};

  std::map<std::string, metastuff::MemberStructTemplate> structTemplates;
  std::map<std::string, metastuff::FileTemplate> fileTemplates;
  const fs::path templ{TemplateXMLOption.c_str()};
  if (fs::exists(templ)) {
    using namespace tinyxml2;
    XMLDocument doc;
    int err = doc.LoadFile(templ.c_str());
    if (err)
      std::cerr << "Error loading File " << templ << ": " << err << std::endl;

    auto root = doc.FirstChildElement();

    for (auto *e = root->FirstChildElement("struct"); e != NULL;
         e = e->NextSiblingElement("struct")) {
      std::string name = e->Attribute("name");
      std::string delim = e->Attribute("delim");
      bool removeLast = e->BoolAttribute("remove_last_delim");
      std::string txt = "";
      if (e->GetText())
        txt = e->GetText();
      structTemplates[name] = {delim, removeLast, txt};
    }
    for (auto *e = root->FirstChildElement("file"); e != NULL;
         e = e->NextSiblingElement("file")) {
      std::string name = e->Attribute("name");
      std::string ext = e->Attribute("ext");

      std::string fn = ((OutputFilename == "") ? name : OutputFilename);
      fn += (std::string(".") + ext);
      std::string txt = "";
      if (e->GetText())
        txt = e->GetText();
      fileTemplates[name] = {ext, fn, txt};
    }
    for (auto *e = root->FirstChildElement("member"); e != NULL;
         e = e->NextSiblingElement("member")) {
      std::string name = e->Attribute("name");
      std::string delim = e->Attribute("delim");
      bool removeLast = e->BoolAttribute("remove_last_delim");
      std::string txt = "";
      if (e->GetText())
        txt = e->GetText();
      StructDeclASTVisitor::memberTemplates[name] = {delim, removeLast, txt};
    }
  }

  const auto files = opts.getSourcePathList();
  clang::tooling::ClangTool tool{opts.getCompilations(), files};

  auto ec = tool.run(
      clang::tooling::newFrontendActionFactory<StructDeclFrontendAction>()
          .get());

  std::string includeBuff;
  std::map<std::string, std::string> structBuf;
  for (const auto &[structtname, structt] : structTemplates) {
    structBuf[structtname] = "";
    for (auto &structEntry : StructDeclASTVisitor::structData) {
      std::vector<std::pair<std::string, std::string>> args;
      for (auto &[memtname, memt] : StructDeclASTVisitor::memberTemplates) {
        auto members = structEntry.memberTemplatesFilled[memtname];
        args.push_back({(std::string("members.") + memtname), members});
      }
      args.push_back({"TYPE", structEntry.name});
      structBuf[structtname] += fill_template(structt.templ8, args);
      structBuf[structtname] += structt.delim;
    }
    if (structt.removeLast) {
      structBuf[structtname] = structBuf[structtname].substr(
          0, structBuf[structtname].size() - structt.delim.size());
    }
  }

  // includes
  {
    for (const auto &f : files) {
      includeBuff += fill_template("#include <{FILE}>\n", {{"FILE", f}});
    }
  }
  std::vector<std::pair<std::string, std::string>> args;

  for (const auto &[structtname, structt] : structTemplates) {
    args.push_back(
        {(std::string("structs.") + structtname), structBuf[structtname]});
  }
  for (const auto &[filetname, filet] : fileTemplates) {
    args.push_back({(std::string("filename.") + filetname), filet.filename});
  }

  args.push_back({"INCLUDE_GUARD_NAME", metastuff::randomHeaderName()});
  args.push_back({"INCLUDES", includeBuff});
  for (const auto &[filetname, filet] : fileTemplates) {
    auto output = fill_template(filet.templ8, args);
    if (OutputFilename != "") {
      std::ofstream outfile((filet.filename).c_str());
      if (outfile.good()) {
        outfile << output << std::endl;
        outfile.close();
      }
    } else {
      std::cout << filetname << ":" << std::endl;
      std::cout << output << std::endl;
    }
  }

  return ec;
}
