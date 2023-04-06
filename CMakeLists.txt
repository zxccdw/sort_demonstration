cmake_minimum_required(VERSION 3.0.0)
project(kursach VERSION 0.1.0)


add_executable(kursach kurs.cpp)

find_package(imgui REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(kursach PRIVATE sfml-system sfml-network sfml-graphics sfml-window imgui::imgui ImGui-SFML::ImGui-SFML)

#target_link_libraries(kursach imgui::imgui)


