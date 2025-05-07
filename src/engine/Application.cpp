#include "Application.hpp"
#include "utils/Log.hpp"

macro::Application::Application() {
  Log::d("Constructing Application");
}

macro::Application::~Application() {
  Log::d("Destroying Application");
}

