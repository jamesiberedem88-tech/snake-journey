#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component_options.hpp>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	using namespace ftxui;
 
  std::vector<std::string> entries = {
      "Start",
      "Continue",
      "HighScore",
      "Instructions",
      "Exit",
         
  };
  int selected = 0;
 
  auto app = App::TerminalOutput();
  MenuOption option;
  option.on_enter = app.ExitLoopClosure();
  auto menu = Menu(&entries, &selected, option);
 
  // You can decorate components using the pipe operator.
  auto component = menu | border;
 
  // Start the main loop
  app.Loop(component);
	
	return 0;
}
