#include <iostream>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>

#include "game_screen.hpp"

using namespace ftxui;
 
std::vector<std::string> entries = {
  "New Game",
  "Continue",
  "High Score",
  "Instructions",
  "Exit"
};
int selected = 0;
auto menu = Menu(&entries, &selected);

Component menu_screen(App& app, int* current_screen) {
  return menu | border | CatchEvent([&app, current_screen](Event event) {
    if (selected == 4 && event == Event::Return) {
      app.Exit();
      return true;
    }

    if ((selected == 0 || selected == 1) && event == Event::Return) {
      *current_screen = 1;
      start_game(&app);
      return true;
    }

    return false;
  });
}
