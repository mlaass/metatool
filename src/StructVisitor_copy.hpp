#pragma once

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>

#include "types.hpp"

using namespace metatool;

class StructVisitor : public clang::RecursiveASTVisitor<StructVisitor> {
  clang::SourceManager &sourceManager_;

public:
  static std::map<std::string, MemberStructTemplate> memberTemplates;
  static std::map<std::string, MemberStructTemplate> methodTemplates;
  static std::map<std::string, MemberStructTemplate> functionTemplates;
  static std::map<std::string, MemberStructTemplate> argumentTemplates;

  static std::vector<Struct> structData;

  explicit StructVisitor(clang::SourceManager &sm) : sourceManager_(sm) {}

  bool VisitCXXRecordDecl(clang::CXXRecordDecl *decl) {
    std::cout << "walk..." << std::endl;
    if (sourceManager_.isWrittenInMainFile(decl->getSourceRange().getBegin())) {
      std::cout << "step..." << std::endl;

      Struct s;
      s.name = decl->getQualifiedNameAsString();
      clang::ASTContext &ctx = decl->getASTContext();
      clang::SourceManager &sm = ctx.getSourceManager();
      const auto fields = decl->fields();
      const auto methods = decl->methods();

      bool ignoreStruct = false;
      auto *rc = decl->getASTContext().getRawCommentForDeclNoCache(decl);
      std::vector<std::string> ignoreMembers = {};
      if (rc) {
        // Found comment!
        std::string raw = rc->getRawText(sm).str();
        std::cout << "comment.." << std::endl;

        if (raw.find("@meta-ignore-struct") != std::string::npos ||
            raw.find("@meta-ignore-class") != std::string::npos) {
          std::cout << "ignoreStruct: " << std::endl;

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
          std::cout << "ignore: " << s << std::endl;
        }
      }

      if (!ignoreStruct) {
        std::cout << "struct.." << std::endl;

        for (auto &[tname, t] : memberTemplates) {
          std::string memberBuff;
          std::for_each(std::begin(fields), std::end(fields), [&](const auto &f) {
            const std::string smName = f->getNameAsString();
            const std::string mName = f->getQualifiedNameAsString();
            std::cout << tname << smName << std::endl;

            const clang::QualType qt = f->getType();
            std::string mType = qt.getAsString();

            if (mType == "_Bool")
              mType = "bool";

            if (std::find(ignoreMembers.begin(), ignoreMembers.end(), smName) == ignoreMembers.end()) {
              memberBuff += fill_template(t.template_data, {{"SHORT_NAME", smName}, {"NAME", mName}, {"TYPE", mType}});
              memberBuff += t.delim;
            }
          });
          if (t.removeLast) {
            memberBuff = memberBuff.substr(0, memberBuff.size() - t.delim.size());
          }
          s.memberTemplatesFilled[tname] = memberBuff;
        }

        for (auto &[tname, t] : methodTemplates) {
          std::string buf;
          std::for_each(std::begin(methods), std::end(methods),
                        [&](const auto &f) { buf += fillFunctionTemplate(tname, t, f, ignoreMembers); });
          if (t.removeLast) {
            buf = buf.substr(0, buf.size() - t.delim.size());
          }
          s.methodTemplatesFilled[tname] = buf;
        }
        structData.push_back(s);
      }
      return true;
    }
  }

  std::string fillFunctionTemplate(const std::string &tname, const MemberStructTemplate &t, clang::FunctionDecl *f,
                                   const std::vector<std::string> &ignoreMembers) {
    std::string buf;
    auto args_filled = parseMethodArgs(f);
    const std::string smName = f->getNameAsString();
    const std::string mName = f->getQualifiedNameAsString();

    const clang::QualType qt = f->getType();
    std::string mType = qt.getAsString();

    if (mType == "_Bool")
      mType = "bool";

    // if not in ignoreMembers
    if (ignoreMembers.end() == std::find(ignoreMembers.begin(), ignoreMembers.end(), smName)) {
      std::vector<std::pair<std::string, std::string>> args = {
          {"SHORT_NAME", smName},
          {"NAME", mName},
          {"TYPE", mType},
      };

      for (auto &[atname, at] : argumentTemplates) {
        args.push_back({"arguments." + atname, args_filled[atname]});
      };

      buf += fill_template(t.template_data, args);
      buf += t.delim;
    }

    return buf;
  }

  std::map<std::string, std::string> parseMethodArgs(clang::FunctionDecl *func) {
    std::map<std::string, std::string> result;

    auto parameters = func->parameters();
    clang::PrintingPolicy pp = clang::PrintingPolicy(clang::LangOptions());
    pp.Bool = false;

    for (auto &[tname, t] : argumentTemplates) {
      std::string paramBuf;
      std::for_each(std::begin(parameters), std::end(parameters), [&](const auto &p) {
        const clang::QualType qt = p->getType();
        std::string paramTypeRef = qt.getUnqualifiedType().getAsString(pp);
        std::string paramName = p->getNameAsString();

        if (paramName == "")
          paramName = "_input";

        // some cleanup seems to be needed here!
        if (paramTypeRef == "_Bool")
          paramTypeRef = "bool";

        std::vector<std::pair<std::string, std::string>> args = {
            {"NAME", paramName},
            {"TYPE", paramTypeRef},
        };
        paramBuf += fill_template(t.template_data, args);
        paramBuf += t.delim;
      });
      if (t.removeLast) {
        paramBuf = paramBuf.substr(0, paramBuf.size() - t.delim.size());
      }
      result[tname] = paramBuf;
    }

    return result;
  }

  bool VisitFunctionDecl(clang::FunctionDecl *func) {
    if (func->isGlobal())
      if (sourceManager_.isWrittenInMainFile(func->getSourceRange().getBegin())) {
        const clang::QualType rt = func->getReturnType();
        std::string fType = rt.getAsString();
        std::string fName = func->getNameAsString();

        std::cout << "global function " << fName << "(";
        auto parameters = func->parameters();
        std::for_each(std::begin(parameters), std::end(parameters), [&](const auto &p) {
          const clang::QualType qt = p->getType();
          std::string paramType = qt.getAsString();
          std::string paramName = p->getNameAsString();

          std::cout << paramName << " : " << paramType << ((p == *(std::end(parameters) - 1)) ? "" : ", ");
        });
        std::cout << ") -> " << fType << std::endl;
        return true;
      } else {
        // std::cout << "Skipping '" << func->getNameAsString()
        //           << "' not in main file\n";
      }
    return true;
  }
};

class StructASTConsumer : public clang::ASTConsumer {
  StructVisitor visitor_; // doesn't have to be private

public:
  // override the constructor in order to pass CI
  explicit StructASTConsumer(clang::CompilerInstance &ci) : visitor_(ci.getSourceManager()) {}

  virtual void HandleTranslationUnit(clang::ASTContext &astContext) {
    visitor_.TraverseDecl(astContext.getTranslationUnitDecl());
  }
};

class StructFrontendAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef file) {
    return std::make_unique<StructASTConsumer>(CI); // pass CI pointer to ASTConsumer
  }
};

std::map<std::string, metatool::MemberStructTemplate> StructVisitor::memberTemplates = {};
std::map<std::string, metatool::MemberStructTemplate> StructVisitor::methodTemplates = {};
std::map<std::string, metatool::MemberStructTemplate> StructVisitor::functionTemplates = {};
std::map<std::string, metatool::MemberStructTemplate> StructVisitor::argumentTemplates = {};

std::vector<metatool::Struct> StructDeclASTVisitor::structData = {};
