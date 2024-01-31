cmake_minimum_required(VERSION 3.3)
project(tetris CXX)
include(.cs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        src/player.cxx
        src/position_set.cxx
        src/board.cxx
        src/model.cxx)

add_program(tetris
        src/tetris.cxx
        src/controller.cxx
        src/view.cxx
        ${MODEL_SRC})
target_link_libraries(tetris ge211)



