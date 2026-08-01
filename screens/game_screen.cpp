#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component game_screen(App& app) {
  return Renderer([] {
    return vbox({ 
      filler(),
      hbox({
        filler(),
        text("The game will be played here."),
        filler()
      }),
      filler()
    }) | border;
  });
}
