#include "Log.hpp"
#include "Ini.hpp"
#include "raylib.h"
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
      section_name = line.substr(1, line.size() - 2);
    } else {
      section_lines[section_name].emplace_back(line);
    }
  }

  for (auto &&section_data: section_lines) {
    parseSection(section_data.first, section_data.second);
  }

  for (auto &&section: _data) {
    Log::d("Section name: ", section.first);
    for (auto &&kv: section.second) {
      Log::d(">> ", kv.first, ": ", kv.second.lines.size(), ", ", kv.second.value);
    }
  }
}

void macro::utils::Ini::parseSection(std::string const &name, std::vector<std::string> const &lines) {
  for (auto &line: lines) {
    auto idx = line.find(" = \"");

    if (idx != std::string::npos) {
      std::string const &&key = line.substr(0, idx);
      std::string const && value = line.substr(idx + 4, line.size() - 4 - key.size() - 1);

      _data[name][key].value = value;
    } else {
      _data[name][""].lines.emplace_back(line);
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
