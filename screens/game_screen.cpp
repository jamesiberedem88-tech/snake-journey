#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>

using namespace ftxui;

auto game = Renderer([] {
  return vbox({ text("The game will be played here.") });
});

Component game_screen(App& app) {
  return game | xflex | size(WIDTH, GREATER_THAN, 100) | border;
}
