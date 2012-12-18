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

file(GLOB Sources *.cpp)
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
    NAME DummyTest 
    COMMAND pacman_sdl --test 1
)

add_test(
    NAME DummyTest2
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/pacman_sdl --test 2
)

