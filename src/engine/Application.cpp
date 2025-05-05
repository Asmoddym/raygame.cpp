#include "Application.hpp"
#include "utils/Log.hpp"

template<typename... Args>
void a(Args&&... args) {
  (coucou(args), ...);
}

Application::Application() {
  Log::d("Constructing Application");
}

Application::~Application() {
  Log::d("Destroying Application");
}

