#ifndef MAINSCENE_HPP_
# define MAINSCENE_HPP_

# include "engine/Scene.hpp"

class MainScene : public Scene {
  public:
    MainScene() : Scene { "MainScene" } {}
    virtual ~MainScene() override {}
};

#endif
