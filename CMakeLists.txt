project(mandelbrot)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/SDL2.lib ${CMAKE_SOURCE_DIR}/lib/SDL2main.lib)
