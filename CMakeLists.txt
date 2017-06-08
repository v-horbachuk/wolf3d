cmake_minimum_required(VERSION 3.6)
project(wolf3d)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

include_directories(./../i) # headers
link_directories(libft minilibx) # libraries

set(SOURCE_FILES
        main.c wolf3d.c) # sources

add_executable(wolf3d ${SOURCE_FILES}) # compilation

target_link_libraries(wolf3d libft.a libmlx.a "-framework OpenGL" "-framework AppKit") # linkage