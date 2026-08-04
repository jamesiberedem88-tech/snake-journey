#include <vector>
#include <atomic>
#include <future>

#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;

enum direction_t { UP, RIGHT, DOWN, LEFT };

const unsigned FIELD_WIDTH = 120;
const unsigned FIELD_HEIGHT = 120;
const unsigned SNAKE_THICKNESS = FIELD_WIDTH / 15;

std::atomic_bool is_game_active = false;
int snake_head_x = FIELD_WIDTH / 2;
int snake_head_y = FIELD_HEIGHT / 2;
unsigned snake_length = 16;
direction_t snake_dir = RIGHT;

Canvas game_canvas;
auto move_snake = [](App* app) {
  while(is_game_active.load()) {
    game_canvas = Canvas(FIELD_WIDTH, FIELD_HEIGHT);
    int snake_tail_x;
    int snake_tail_y;

    switch (snake_dir) {
      case UP: snake_tail_x = snake_head_x; snake_tail_y = snake_head_y + snake_length; break;
      case RIGHT: snake_tail_x = snake_head_x + snake_length; snake_tail_y = snake_head_y; break;
      case DOWN: snake_tail_x = snake_head_x; snake_tail_y = snake_head_y - snake_length; break;
      case LEFT: snake_tail_x = snake_head_x + snake_length; snake_tail_y = snake_head_y;
    }

    for (int i = -4; i + 4 < SNAKE_THICKNESS; ++i)
      switch (snake_dir) {
        case UP:
        case DOWN:
          game_canvas.DrawBlockLine(snake_head_x + i, snake_head_y, snake_tail_x + i, snake_tail_y);
          break;
        case RIGHT:
        case LEFT:
          game_canvas.DrawBlockLine(snake_head_x, snake_head_y + i, snake_tail_x, snake_tail_y + i);
      }

    ++snake_head_x;

    app->PostEvent(Event::Custom);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
};
std::future<void> game_task;

Component game_screen(App& app) {
  return Renderer([&] {
    return hbox({
      filler(),
      canvas(&game_canvas)
        | size(WIDTH, EQUAL, FIELD_WIDTH / 2)
        | size(HEIGHT, EQUAL, FIELD_HEIGHT / 4)
        | center
        | border,
      filler()
    });
  });
}

void start_game(App* app) {
  is_game_active.store(true);

  snake_head_x = FIELD_WIDTH / 2;
  snake_head_y = FIELD_HEIGHT / 2;
  snake_length = 16;
  snake_dir = RIGHT;

  game_task = std::async(std::launch::async, move_snake, app);
}

void stop_game() {
  is_game_active.store(false);
}
