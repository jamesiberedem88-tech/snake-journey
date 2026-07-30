#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>

using namespace ftxui;
 
std::vector<std::string> entries = {
  "New Game",
  "Continue",
  "High Score",
  "Instructions",
  "Exit"
};
int selected = 0;
MenuOption option;
auto menu = Menu(&entries, &selected, option);

Component menu_screen(App& app, int* current_screen) {
  return menu | border | CatchEvent([&](Event event) {
    if (selected == 4 && event == Event::Return) {
      app.Exit();
      return true;
    }

    if ((selected == 0 || selected == 1) && event == Event::Return) {
      *current_screen = 1;
      return true;
    }

    return false;
  });
}
