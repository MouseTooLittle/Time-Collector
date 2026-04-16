cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

# Download FTXUI automatically
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG        v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# Your executable
add_executable(my_project main.cpp)

# Link FTXUI to your project
target_link_libraries(my_project
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)