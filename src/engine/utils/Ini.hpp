#ifndef MACRO_UTILS_INI_HPP_
# define MACRO_UTILS_INI_HPP_

# include <unordered_map>
# include <vector>
# include <string>

namespace macro {
  namespace utils {
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
        Ini(std::string const &path);
        virtual ~Ini() {}

        Section const &operator[](std::string const &key);

      private:
        void parse();
        std::vector<std::string> getLines();

        bool isSection(std::string const &line);
        void parseSection(std::string const &name, std::vector<std::string> const &lines);

        std::string trim(std::string const &str);
    };
  }
}

#endif //MACRO_UTILS_INI_HPP_
