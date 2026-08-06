#include <vector>
#include <atomic>
#include <future>
#include <tuple>

#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;

enum direction_t { UP, RIGHT, DOWN, LEFT };

typedef std::tuple<unsigned, direction_t> bend;

const unsigned FIELD_WIDTH = 120;
const unsigned FIELD_HEIGHT = 120;
const unsigned SNAKE_THICKNESS = FIELD_WIDTH / 15;

std::atomic_bool is_game_active = false;
int snake_head_x = FIELD_WIDTH / 2;
int snake_head_y = FIELD_HEIGHT / 2;
unsigned snake_length = 16;
std::vector<bend> snake_bends = {
  bend(0, RIGHT), bend(snake_length, RIGHT)
}; // first element is the perceived snake_dir


Canvas game_canvas;
auto move_snake = [](App* app) {
  while(is_game_active.load()) {
    game_canvas = Canvas(FIELD_WIDTH, FIELD_HEIGHT);

    int seg_start_x = snake_head_x;
    int seg_start_y = snake_head_y;
    int seg_end_x;
    int seg_end_y;

    // draw the snake as is
    std::vector<bend>::iterator bend_it;
    for (bend_it = snake_bends.begin(); bend_it < snake_bends.end() - 1; ++bend_it) {
      unsigned segment_length = std::get<0>(*(bend_it + 1)) - std::get<0>(*bend_it);

      switch (std::get<1>(*bend_it)) {
        case UP: seg_end_x = seg_start_x; seg_end_y = seg_start_y + segment_length; break;
        case RIGHT: seg_end_x = seg_start_x - segment_length; seg_end_y = seg_start_y; break;
        case DOWN: seg_end_x = seg_start_x; seg_end_y = seg_start_y - segment_length; break;
        case LEFT: seg_end_x = seg_start_x + segment_length; seg_end_y = seg_start_y;
      }

      for (int i = -4; i + 4 < SNAKE_THICKNESS; ++i)
        switch (std::get<1>(*bend_it)) {
          case UP:
          case DOWN:
            game_canvas.DrawBlockLine(seg_start_x + i, seg_start_y, seg_end_x + i, seg_end_y);
            break;
          case RIGHT:
          case LEFT:
            game_canvas.DrawBlockLine(seg_start_x, seg_start_y + i, seg_end_x, seg_end_y + i);
        }

      seg_start_x = seg_end_x;
      seg_start_y = seg_end_y;
    }

    // move the snake for the next drawing
    bend_it = snake_bends.begin();
    switch (std::get<1>(*bend_it)) {
      case UP: --snake_head_y; break;
      case RIGHT: ++snake_head_x; break;
      case DOWN: ++snake_head_y; break;
      case LEFT: --snake_head_x;
    }
    for (++bend_it; bend_it < snake_bends.end() - 1; ++bend_it) ++std::get<0>(*bend_it);
    if (std::get<0>(*(bend_it - 1)) == std::get<0>(*bend_it)) snake_bends.pop_back();

    app->PostEvent(Event::Custom);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
};
std::future<void> game_task;

Component game_screen(App& app) {
  return CatchEvent(Renderer([&](bool focused) {
    return hbox({
      filler(),
      canvas(&game_canvas)
        | size(WIDTH, EQUAL, FIELD_WIDTH / 2)
        | size(HEIGHT, EQUAL, FIELD_HEIGHT / 4)
        | center
        | border,
      filler()
    });
  }), [&](Event event) {
    if (event == Event::ArrowUp) {
      switch (std::get<1>(snake_bends[0])) {
        // undo snake movement
        case RIGHT: --snake_head_x; break;
        case LEFT: ++snake_head_x; break;
        default: return false;
      }
      --snake_head_y; // turn up
      ++std::get<0>(snake_bends[0]);
      snake_bends.emplace(snake_bends.begin(), 0, UP);
      return true;
    }

    if (event == Event::ArrowRight) {
      switch (std::get<1>(snake_bends[0])) {
        case UP: ++snake_head_y; break;
        case DOWN: --snake_head_y; break;
        default: return false;
      }
      ++snake_head_x;
      ++std::get<0>(snake_bends[0]);
      snake_bends.emplace(snake_bends.begin(), 0, RIGHT);
      return true;
    }

    if (event == Event::ArrowDown) {
      switch (std::get<1>(snake_bends[0])) {
        case RIGHT: --snake_head_x; break;
        case LEFT: ++snake_head_x; break;
        default: return false;
      }
      ++snake_head_y;
      ++std::get<0>(snake_bends[0]);
      snake_bends.emplace(snake_bends.begin(), 0, DOWN);
      return true;
    }

    if (event == Event::ArrowLeft) {
      switch (std::get<1>(snake_bends[0])) {
        case UP: ++snake_head_y; break;
        case DOWN: --snake_head_y; break;
        default: return false;
      }
      --snake_head_x;
      ++std::get<0>(snake_bends[0]);
      snake_bends.emplace(snake_bends.begin(), 0, LEFT);
      return true;
    }

    return false;
  });
}

void start_game(App* app) {
  is_game_active.store(true);

  snake_head_x = FIELD_WIDTH / 2;
  snake_head_y = FIELD_HEIGHT / 2;
  snake_length = 16;
  snake_bends = {
    { 0, RIGHT }, { snake_length, RIGHT }
  }; // first element is the perceived snake_dir

  game_task = std::async(std::launch::async, move_snake, app);
}

void stop_game() {
  is_game_active.store(false);
}
