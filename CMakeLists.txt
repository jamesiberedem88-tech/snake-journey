cmake_minimum_required(VERSION 3.23)

project(SnakeJourney)

include(Fetchcontent)

Fetchcontent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # or a specific version like v7.0.1)
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