#include "Log.hpp"
#include "Ini.hpp"
#include "raylib.h"
#include <cctype>
#include <sstream>
#include <unordered_map>

macro::utils::Ini::Ini(std::string const &path) : _path { path } {
  parse();
}

bool macro::utils::Ini::isSection(std::string const &line) {
  return line[0] == '[' && line[line.size() - 1] == ']';
}

void macro::utils::Ini::parse() {
  std::vector<std::string> lines = getLines();
  std::string section_name;
  std::unordered_map<std::string, std::vector<std::string>> section_lines;

  for (auto &&line: lines) {
    line = line.substr(0, line.size() - 1);

    if (line.size() == 0) {
      continue;
    }

    if (isSection(line)) {
      section_name = trim(line.substr(1, line.size() - 2));
    } else {
      section_lines[section_name].emplace_back(line);
    }
  }

  for (auto &&section_data: section_lines) {
    parseSection(section_data.first, section_data.second);
  }

  for (auto &&section: _data) {
    Log::d("Section name: <", section.first, ">");

    Log::d("  Content: ", section.second.content.size(), " lines");
    for (auto &&line: section.second.content) {
      Log::d("    <", line, ">");
    }
    for (auto &&kv: section.second.keyValues) {
      Log::d("  <", kv.first, ">: <", kv.second, ">");
    }
  }
}

void macro::utils::Ini::parseSection(std::string const &name, std::vector<std::string> const &lines) {
  for (auto &line: lines) {
    auto idx = line.find("=");

    if (idx != std::string::npos) {
      std::string const &&key = trim(line.substr(0, idx));
      std::string const &&value = trim(line.substr(idx + 1, line.size() - idx - 1));

      _data[name].keyValues[key] = value;
    } else {
      _data[name].content.emplace_back(trim(line));
    }
  }
}

std::vector<std::string> macro::utils::Ini::getLines() {
  std::vector<std::string> lines;
  int size;
  unsigned char *data = LoadFileData(_path.c_str(), &size);
  data[size] = 0;

  std::istringstream stream((char *)data);

  for (std::string line; std::getline(stream, line, '\n');) {
    if (line.size() > 0) {
      lines.emplace_back(line);
    }
  }

  return lines;
}

std::string macro::utils::Ini::trim(std::string const &raw) {
  std::string str = raw;

  str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));

  str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), str.end());

  return str;
}
