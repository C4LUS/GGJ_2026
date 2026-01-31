cmake_minimum_required(VERSION 3.22)
project(ggj_2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/Users/sebastiennourry/tek/SFML-3.0.2/lib/cmake/SFML" CACHE PATH "Path to SFMLConfig.cmake")
set(SFML_LIB_DIR "/Users/sebastiennourry/tek/SFML-3.0.2/lib" CACHE PATH "Path to SFML libraries")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(game
  src/Game.cpp
  src/StateStack.cpp
  src/main.cpp
  src/State.cpp
  src/InputManager.cpp
  src/InsideCarState.cpp
  src/MenuState.cpp
)

target_include_directories(game PRIVATE include)
target_link_libraries(game PRIVATE SFML::Graphics)

set_target_properties(game PROPERTIES
  BUILD_RPATH "${SFML_LIB_DIR}"
  INSTALL_RPATH "${SFML_LIB_DIR}"
)
