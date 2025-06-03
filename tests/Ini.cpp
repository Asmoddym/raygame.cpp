#include "Ini.h"
#include "raylib.h"
#include <iostream>
#include <sstream>

void Ini::parse() {
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
    std::cout << "Section name: <" << section.first << ">" << std::endl;

    std::cout << "  Content: " << section.second.content.size() << " lines" << std::endl;
    for (auto &&line: section.second.content) {
      std::cout << "    <" << line << ">" << std::endl;
    }
    for (auto &&kv: section.second.keyValues) {
      std::cout << "  <" << kv.first << ">: <" << kv.second << ">" << std::endl;
    }
  }
}

void Ini::parseSection(std::string const &name, std::vector<std::string> const &lines) {
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

std::vector<std::string> Ini::getLines() {
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

std::string Ini::trim(std::string const &raw) {
  std::string str = raw;

  str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));

  str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), str.end());

  return str;
}
