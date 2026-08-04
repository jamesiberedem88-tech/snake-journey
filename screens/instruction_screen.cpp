#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>

namespace screens {
    using namespace ftxui;

    Component InstructionScreen(int* current_screen) {

    	auto renderer = Renderer([=] {
        	return vbox({

           		text(" ?? SNAKE XENZIA - HOW TO PLAY ") | bold | color(Color::Green) | border,
            	separator(),

            	vbox({
                	text("?? OBJECTIVE") | bold | color(Color::Yellow),
            	    text(" Guide the snake to eat food, grow longer, and achieve high scores."),
            	}),
            	separator(),

            	vbox({
                	text("?? CONTROLS") | bold | color(Color::Cyan),
                	hbox({ text("  • Move Snake  : "), text("Arrow Keys (Up, Down, Left, Right)") | bold }),
                	hbox({ text("  • Back / Menu : "), text("Q") | bold }),
                	hbox({ text("  • Exit Game   : "), text("Q (on Main Menu)") | bold }),
            	}),
            	separator(),

            	vbox({
                	text("?? GAME RULES") | bold | color(Color::Red),
                	text("  • Do not crash into the outer walls."),
                	text("  • Do not run into your own body."),
                	text("  • Each food item increases your speed and score."),
            	}),
            	separator(),

            	text("Press [Q] to Return to Menu") | dim | center
        	}) | borderDouble | center;
    	});

	    return CatchEvent(renderer, [=](Event event) {
	        if (event == Event::Character('q') || event == Event::Character('Q')) {
	            if (current_screen) {
	                *current_screen = 0; 
	            }
	            return true;
	        }
	        return false;
	    });
	}

}  

