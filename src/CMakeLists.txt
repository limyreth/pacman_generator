cmake_minimum_required (VERSION 2.8)
project (pacman_sdl)

############################################
# find libs
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_ttf REQUIRED)

if ( NOT SDL_FOUND )
    message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

if ( NOT SDL_IMAGE_FOUND )
    set(SDL_IMAGE_LIBRARIES "SDL_image")
    message ( "SDL image not found, making a guess" )
endif ( NOT SDL_IMAGE_FOUND )

if ( NOT SDL_MIXER_FOUND )
    set(SDL_MIXER_LIBRARIES "SDL_mixer")
    message ( "SDL mixer not found, making a guess" )
endif ( NOT SDL_MIXER_FOUND )

if ( NOT SDL_TTF_FOUND )
    set(SDL_TTF_LIBRARIES "SDL_ttf")
    message ( "SDL ttf not found, making a guess" )
endif ( NOT SDL_TTF_FOUND )

set(SDL_GFX_LIBRARIES "SDL_gfx")

execute_process(
    COMMAND sdl-config --cflags
    OUTPUT_VARIABLE SDL_FLAGS
)
############################################

set(CMAKE_CXX_FLAGS "-g -std=c++11 ${SDL_CFLAGS}")

file(GLOB_RECURSE Sources pacman/*.cpp)
add_executable(pacman_sdl ${Sources})

target_link_libraries(pacman_sdl 
    ${SDL_LIBRARY} 
    ${SDL_IMAGE_LIBRARIES} 
    ${SDL_MIXER_LIBRARIES} 
    ${SDL_TTF_LIBRARIES}
    ${SDL_GFX_LIBRARIES} 
    ${LIBS} 
)


######## Testing ############

enable_testing()

add_test(
    NAME start_foods
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 9
)

add_test(
    NAME initial_game_state
    COMMAND pacman_sdl --test 1
)

add_test(
    NAME ghosts_remain_normal_when_not_eating_energizer
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 2
)

add_test(
    NAME pacman_movement_regular_speed_not_cornering
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 3
)

add_test(
    NAME dot_eating_no_cornering
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 4
)

add_test(
    NAME minimax_1
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 5
)

add_test(
    NAME generator_1
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 6
)

add_test(
    NAME generator_save_load
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 7
)

add_test(
    NAME generator_save_load_of_running_instance
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 8
)

