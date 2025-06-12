#ifndef MACRO_UTILS_INI_H_
# define MACRO_UTILS_INI_H_

# include <unordered_map>
# include <vector>
# include <string>

class Ini {
  struct Value {
    std::vector<std::string> lines;
    std::string value;
  };

  struct Section {
    std::vector<std::string> content;
    std::unordered_map<std::string, std::string> keyValues;
  };

  private:
    std::string const &_path;
    std::unordered_map<std::string, Section> _data;

  public:
    Ini(std::string const &path) : _path { path } { parse(); }
    virtual ~Ini() {}

    Section const &operator[](std::string const &key) { return _data[key]; }

  private:
    void parse();
    std::vector<std::string> getLines();

    void parseSection(std::string const &name, std::vector<std::string> const &lines);

    std::string trim(std::string const &str);

    bool isSection(std::string const &line) { return line[0] == '[' && line[line.size() - 1] == ']'; }
};

#endif //MACRO_UTILS_INI_H_
