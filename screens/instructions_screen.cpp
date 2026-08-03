#include "instructions_screen.hpp"
#include <ftxui/dom/elements.hpp>

Component instructions_screen(App& app, int* current_screen) {
    auto renderer = Renderer([] {
        Element title = text("HOW TO PLAY") | bold | color(Color::Green) | center;

        Element objective = vbox({
            text("Objective:") | bold | underlined,
            text("Guide the snake to eat food and grow as long as possible"),
            text("without hitting the walls or yourself."),
        });

        Element controls = vbox({
            text("Controls:") | bold | underlined,
            hbox({ text(" ↑ ") | bold | color(Color::Yellow), text("  Move Up") }),
            hbox({ text(" ↓ ") | bold | color(Color::Yellow), text("  Move Down") }),
            hbox({ text(" ← ") | bold | color(Color::Yellow), text("  Move Left") }),
            hbox({ text(" → ") | bold | color(Color::Yellow), text("  Move Right") }),
            hbox({ text(" P ") | bold | color(Color::Yellow), text("  Pause Game") }),
            hbox({ text(" Q ") | bold | color(Color::Yellow), text("  Quit to Menu") }),
        });

        Element rules = vbox({
            text("Rules:") | bold | underlined,
            text("• Each food eaten increases your score and snake length"),
            text("• The game ends if you hit a wall or your own tail"),
            text("• Speed increases slightly as your score grows"),
        });

        Element footer = text("Press [Enter] or [Esc] to return to Menu") | dim | center;

        Element content = vbox({
            title, separator(),
            objective, separator(),
            controls, separator(),
            rules, separator(),
            footer,
        }) | border | size(WIDTH, EQUAL, 60);

        return content | center;
    });

    return CatchEvent(renderer, [current_screen](Event event) {
        if (event == Event::Return || event == Event::Escape) {
            *current_screen = 0;
            return true;
        }
        return false;
    });
}