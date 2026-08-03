cmake_minimum_required(VERSION 3.23)

project(SnakeJourney)

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v7.0.1
)
FetchContent_MakeAvailable(ftxui)

add_executable(SnakeJourney)
target_sources(SnakeJourney
  PRIVATE
    main.cpp
    screens/menu_screen.cpp
    screens/game_screen.cpp
    screens/menu_screen.hpp
    screens/game_screen.hpp
    screens/instructions_screen.cpp
    screens/instructions_screen.hpp
)
target_link_libraries(SnakeJourney
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
