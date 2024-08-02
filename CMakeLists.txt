cmake_minimum_required(VERSION 3.20)

project(TermUI)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(win)
add_subdirectory(scintilla)
add_subdirectory(lexilla)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT termui-win64)

