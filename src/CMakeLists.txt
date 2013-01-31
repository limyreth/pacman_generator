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

include_directories(BEFORE ${CMAKE_SOURCE_DIR})

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

# initial state
add_test(
    NAME MODEL::test_start_foods
    COMMAND pacman_sdl --test MODEL::test_start_foods
)

add_test(
    NAME MODEL::test_initial_game_state
    COMMAND pacman_sdl --test MODEL::test_initial_game_state
)

add_test(
    NAME MODEL::test_ghosts_remain_normal_when_not_eating_energizer
    COMMAND pacman_sdl --test MODEL::test_ghosts_remain_normal_when_not_eating_energizer
)

# movement
add_test(
    NAME MODEL::test_pacman_movement_regular_speed_not_cornering
    COMMAND pacman_sdl --test MODEL::test_pacman_movement_regular_speed_not_cornering
)

add_test(
    NAME MODEL::test_pacman_movement_regular_speed_cornering
    COMMAND pacman_sdl --test MODEL::test_pacman_movement_regular_speed_cornering
)

add_test(
    NAME MODEL::test_dot_eating_no_cornering
    COMMAND pacman_sdl --test MODEL::test_dot_eating_no_cornering
)

# ghost pen leaving
add_test(
    NAME MODEL::GhostLeavingTests::test_blinky_pinky_immediately_leave
    COMMAND pacman_sdl --test MODEL::GhostLeavingTests::test_blinky_pinky_immediately_leave
)

# vulnerability
add_test(
    NAME MODEL::VulnerabilityTests::test_energizer_time
    COMMAND pacman_sdl --test MODEL::VulnerabilityTests::test_energizer_time
)

add_test(
    NAME MODEL::VulnerabilityTests::test_2_energizers_time
    COMMAND pacman_sdl --test MODEL::VulnerabilityTests::test_2_energizers_time
)

# fruit spawning
add_test(
    NAME MODEL::FruitTests::test_fruit_timing
    COMMAND pacman_sdl --test MODEL::FruitTests::test_fruit_timing
)

# scoring
add_test(
    NAME MODEL::test_eat_2_dots
    COMMAND pacman_sdl --test MODEL::test_eat_2_dots
)

add_test(
    NAME MODEL::test_eat_energizer
    COMMAND pacman_sdl --test MODEL::test_eat_energizer
)

add_test(
    NAME MODEL::test_eat_fruit
    COMMAND pacman_sdl --test MODEL::test_eat_fruit
)

add_test(
    NAME MODEL::test_eat_1_ghost
    COMMAND pacman_sdl --test MODEL::test_eat_1_ghost
)

add_test(
    NAME MODEL::test_eat_2_ghosts
    COMMAND pacman_sdl --test MODEL::test_eat_2_ghosts
)

add_test(
    NAME MODEL::test_eat_3_ghosts
    COMMAND pacman_sdl --test MODEL::test_eat_3_ghosts
)

add_test(
    NAME MODEL::test_eat_4_ghosts
    COMMAND pacman_sdl --test MODEL::test_eat_4_ghosts
)

add_test(
    NAME MODEL::test_eat_ghost_energizer_ghost
    COMMAND pacman_sdl --test MODEL::test_eat_ghost_energizer_ghost
)

add_test(
    NAME MODEL::test_eat_fruit_ghost
    COMMAND pacman_sdl --test MODEL::test_eat_fruit_ghost
)

# generator
add_test(
    NAME MinimaxTests::test_1
    COMMAND pacman_sdl --test MinimaxTests::test_1
)

add_test(
    NAME GeneratorTests::test_1
    COMMAND pacman_sdl --test GeneratorTests::test_1
)

add_test(
    NAME GeneratorTests::test_save_load
    COMMAND pacman_sdl --test GeneratorTests::test_save_load
)

add_test(
    NAME GeneratorTests::test_save_load_of_running_instance
    COMMAND pacman_sdl --test GeneratorTests::test_save_load_of_running_instance
)

