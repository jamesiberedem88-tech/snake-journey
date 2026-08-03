#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>

#include "screens/menu_screen.hpp"
#include "screens/game_screen.hpp"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	using namespace ftxui;
 
  auto app = App::TerminalOutput();

  int selected = 0;
  auto container = Container::Tab({
    menu_screen(app, &selected),
    game_screen(app)
  }, &selected);

  auto component = CatchEvent(container, [&](Event event) {
    if (event == Event::q) {
      if (selected > 0) {
        if (selected < 2) stop_game();
        selected = 0;
      }
      else app.Exit();
      return true;
    }
    return false;
  });

  // Start the main loop
  app.Loop(component);
	
	return 0;
}
