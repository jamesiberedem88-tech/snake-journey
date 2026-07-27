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
)
target_link_libraries(SnakeJourney
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
