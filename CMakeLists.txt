cmake_minimum_required(VERSION 3.16)
project(enm_learning_aid)
add_executable(enm_learning_aid src/main.cpp)
target_link_libraries(enm_learning_aid PRIVATE sfml-graphics sfml-window sfml-system)