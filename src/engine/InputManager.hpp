#ifndef MACRO_INPUTMANAGER_HPP_
# define MACRO_INPUTMANAGER_HPP_

# include "input/Keyboard.hpp"

namespace macro {
  class InputManager {
    private:
      input::Keyboard _keyboard;

    public:
      InputManager() {}
      virtual ~InputManager() {}
  };
}

#endif // MACRO_INPUTMANAGER_HPP_
