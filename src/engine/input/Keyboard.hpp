#ifndef MACRO_INPUT_KEYBOARD_HPP_
# define MACRO_INPUT_KEYBOARD_HPP_

namespace macro {
  namespace input {
    class Keyboard {
      public:
        Keyboard() {}
        virtual ~Keyboard() {}

        static bool keyPressed(const int &key);
        static bool keyReleased(const int &key);
    };
  }
}

#endif // MACRO_INPUT_KEYBOARD_HPP_
