#pragma once

#include <tinyxml2.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include "StructVisitor.hpp"
#include "types.hpp"

namespace metatool {

std::string replace_all(std::string str, const std::string &remove, const std::string &insert) {
  std::string::size_type pos = 0;
  while ((pos = str.find(remove, pos)) != std::string::npos) {
    str.replace(pos, remove.size(), insert);
    pos++;
  }

  return str;
}

std::string fill_template(std::string templ, const std::vector<str_pair> &args) {
  for (const auto &arg : args) {
    templ = replace_all(templ, std::string("{") + arg.first + std::string("}"), arg.second);
  }
  return templ;
}

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
  std::generate_n(std::back_inserter(v), len, [&] { return syllables[dist(gen)]; });
  std::string ret;
  ret = std::accumulate(v.begin(), v.end(), ret);
  ;
  ret += "_HPP";
  return ret;
}

tinyxml2::XMLDocument *parseXMLDoc(std::string xml) {
  auto doc = new tinyxml2::XMLDocument();

  int err = doc->Parse(xml.c_str());
  if (err) {
    std::cerr << "Error parsing xml: " << err << std::endl;
  }
  return doc;
}

void parseXMLMemberStructTemplate(tinyxml2::XMLElement *root, const std::string &type,
                                  std::map<std::string, metatool::MemberStructTemplate> &target) {
  for (auto *e = root->FirstChildElement(type.c_str()); e != NULL; e = e->NextSiblingElement(type.c_str())) {
    std::string name = e->Attribute("name");
    std::string delim = e->Attribute("delim");
    bool removeLast = e->BoolAttribute("remove_last_delim");
    std::string txt = "";
    if (e->GetText())
      txt = e->GetText();
    target[name] = {delim, removeLast, txt};
  }
}

void parseXMLTemplates(std::istream &stream, auto &structTemplates, auto &fileTemplates,
                       const std::string &outputFilename = "") {
  std::ostringstream os;
  os << stream.rdbuf();

  auto doc = parseXMLDoc(os.str());
  try {
    auto root = doc->FirstChildElement();

    for (auto *e = root->FirstChildElement("file"); e != NULL; e = e->NextSiblingElement("file")) {
      std::string name = e->Attribute("name");
      std::string ext = e->Attribute("ext");

      std::string fn = ((outputFilename == "") ? name : outputFilename);
      fn += (std::string(".") + ext);
      std::string txt = "";
      if (e->GetText())
        txt = e->GetText();
      fileTemplates[name] = {ext, fn, txt};
    }

    parseXMLMemberStructTemplate(root, "struct", structTemplates);
    parseXMLMemberStructTemplate(root, "member", StructDeclASTVisitor::memberTemplates);
    parseXMLMemberStructTemplate(root, "method", StructDeclASTVisitor::methodTemplates);
    parseXMLMemberStructTemplate(root, "function", StructDeclASTVisitor::functionTemplates);
    parseXMLMemberStructTemplate(root, "argument", StructDeclASTVisitor::argumentTemplates);

  } catch (const std::exception &e) {
    std::cerr << "Error parsing template" << e.what() << '\n';
  }

  delete doc;
}

bool parseBool(std::string str) {
  static const std::string TRUE_VALS[] = {"true", "True", "TRUE"};
  static const std::string FALSE_VALS[] = {"false", "False", "FALSE"};

  for (const auto &v : TRUE_VALS) {
    if (v == str) {
      return true;
    }
  }

  for (const auto &v : FALSE_VALS) {
    if (v == str) {
      return false;
    }
  }
  return false;
}

void parseT8MemberStructTemplate(Definition &d, std::map<std::string, metatool::MemberStructTemplate> &target) {
  std::string name = d.attributes["name"];
  std::string delim = d.attributes["delim"];
  bool removeLast = parseBool(d.attributes["remove_last_delim"]);
  target[name] = {delim, removeLast, d.code};
}

void parseT8Templates(std::istream &stream, auto &structTemplates, auto &fileTemplates,
                      const std::string &outputFilename = "") {
  Templ8 t8 = streamTempl8(stream);

  for (auto d : t8.definitions) {
    if (d.type == "file") {
      std::string name = d.attributes["name"];
      std::string ext = d.attributes["ext"];

      std::string fn = ((outputFilename == "") ? name : outputFilename);
      fn += (std::string(".") + ext);
      fileTemplates[name] = {ext, fn, d.code};
    }

    if (d.type == "struct") {
      parseT8MemberStructTemplate(d, structTemplates);
    }
    if (d.type == "member") {
      parseT8MemberStructTemplate(d, StructDeclASTVisitor::memberTemplates);
    }
    if (d.type == "method") {
      parseT8MemberStructTemplate(d, StructDeclASTVisitor::methodTemplates);
    }
    if (d.type == "function") {
      parseT8MemberStructTemplate(d, StructDeclASTVisitor::functionTemplates);
    }
    if (d.type == "argument") {
      parseT8MemberStructTemplate(d, StructDeclASTVisitor::argumentTemplates);
    }
  }
}

int generate(const clang::tooling::CompilationDatabase &compilations, const llvm::ArrayRef<std::__cxx11::string> &files,
             std::istream &stream, bool t8 = true, const std::string &outputFilename = "") {
  std::map<std::string, MemberStructTemplate> structTemplates;
  std::map<std::string, FileTemplate> fileTemplates;

  if (t8) {
    parseT8Templates(stream, structTemplates, fileTemplates, outputFilename);
  } else {
    parseXMLTemplates(stream, structTemplates, fileTemplates, outputFilename);
  }

  clang::tooling::ClangTool tool{compilations, files};

  auto ec = tool.run(clang::tooling::newFrontendActionFactory<StructDeclFrontendAction>().get());

  // struct templates buffer
  std::map<std::string, std::string> structBuf;

  for (const auto &[struct_templ_name, struct_templ] : structTemplates) {
    structBuf[struct_templ_name] = "";
    for (auto &structEntry : StructDeclASTVisitor::structData) {
      // collect member + method args
      std::vector<std::pair<std::string, std::string>> args;
      for (auto &[mem_templ_name, mem_templ] : StructDeclASTVisitor::memberTemplates) {
        auto members = structEntry.memberTemplatesFilled[mem_templ_name];
        args.push_back({(std::string("members.") + mem_templ_name), members});
      }

      for (auto &[mem_templ_name, mem_templ] : StructDeclASTVisitor::methodTemplates) {
        auto members = structEntry.methodTemplatesFilled[mem_templ_name];
        args.push_back({(std::string("methods.") + mem_templ_name), members});
      }

      args.push_back({"TYPE", structEntry.name});

      structBuf[struct_templ_name] += fill_template(struct_templ.template_data, args);
      structBuf[struct_templ_name] += struct_templ.delim;
    }

    if (struct_templ.removeLast) {
      structBuf[struct_templ_name] =
          structBuf[struct_templ_name].substr(0, structBuf[struct_templ_name].size() - struct_templ.delim.size());
    }
  }

  // add files include buffer
  std::string includeBuff;
  {
    for (const auto &f : files) {
      includeBuff += fill_template("#include <{FILE}>\n", {{"FILE", f}});
    }
  }

  // collect args for struct templates
  std::vector<std::pair<std::string, std::string>> args;
  for (const auto &[struct_templ_name, struct_templ] : structTemplates) {
    args.push_back({(std::string("structs.") + struct_templ_name), structBuf[struct_templ_name]});
  }

  // collect args for file templates
  for (const auto &[file_templ_name, file_templ] : fileTemplates) {
    args.push_back({(std::string("filename.") + file_templ_name), file_templ.filename});
  }

  args.push_back({"INCLUDE_GUARD_NAME", randomHeaderName()});
  args.push_back({"INCLUDES", includeBuff});

  // generate and fill files
  for (const auto &[file_templ_name, file_templ] : fileTemplates) {
    auto output = fill_template(file_templ.template_data, args);
    if (outputFilename != "") {
      std::ofstream outfile((file_templ.filename).c_str());
      if (outfile.good()) {
        outfile << output << std::endl;
        outfile.close();
      }
    } else {
      std::cout << file_templ_name << ":" << std::endl;
      std::cout << output << std::endl;
    }
  }

  return ec;
}

} // namespace metatool