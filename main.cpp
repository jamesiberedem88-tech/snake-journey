#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	using namespace ftxui;
 
  std::vector<std::string> entries = {
      "Entry 1",
      "Entry 2",
      "Entry 3",
  };
  int selected = 0;
 
  // Create a menu component
  auto menu = Menu(&entries, &selected);
 
  // You can decorate components using the pipe operator.
  auto component = menu | border;
 
  // Start the main loop
  auto app = App::TerminalOutput();
  app.Loop(component);
	
	return 0;
}
