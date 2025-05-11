cmake_minimum_required(VERSION 3.27)
project(xineramaGetCurrentMonitor)

find_package(X11 REQUIRED)

#Main binary
add_executable(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/srcs/main.c)
target_link_libraries(${PROJECT_NAME} X11::X11 X11::Xinerama)
set_target_properties(${PROJECT_NAME} PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)