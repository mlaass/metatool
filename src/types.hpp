#pragma once

#include <string>
#include <map>

namespace metatool {
typedef std::pair<std::string, std::string> str_pair ;

struct Struct {
  std::string name;
  std::map<std::string, std::string> memberTemplatesFilled;
  std::map<std::string, std::string> methodTemplatesFilled;
};

struct FileTemplate {
  std::string ext;
  std::string filename;
  std::string template_data;
};

struct MemberStructTemplate {
  std::string delim;
  bool removeLast;
  std::string template_data;
};



std::string fill_template(std::string, const std::vector<str_pair> &);

} // namespace metatool