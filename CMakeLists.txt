cmake_minimum_required(VERSION 3.10)

# set the project name
project(CounterStrike2D)

find_package(box2d REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wunused -Wuninitialized -std=c++11 -pthread -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lyaml-cpp")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include_directories(${PROJECT_SOURCE_DIR}/client_src)
include_directories(${PROJECT_SOURCE_DIR}/client_src/Character)
include_directories(${PROJECT_SOURCE_DIR}/client_src/Events)
include_directories(${PROJECT_SOURCE_DIR}/server_src)
include_directories(${PROJECT_SOURCE_DIR}/server_src/game_model)
include_directories(${PROJECT_SOURCE_DIR}/common_src)
include_directories(${PROJECT_SOURCE_DIR}/common_src/Sdl)
include_directories(${PROJECT_SOURCE_DIR}/editor_src)


#CLIENT
file(GLOB CLIENT_SRC_FILES "client_src/*.cpp")
file(GLOB CHARACTER_SRC_FILES "client_src/Character/*.cpp")
file(GLOB EVENTS_SRC_FILES "client_src/Events/*.cpp")

#SERVER
file(GLOB SERVER_SRC_FILES "server_src/*.cpp")
file(GLOB GAME_MODEL_SRC_FILES "server_src/game_model/*.cpp")

#EDITOR
file(GLOB EDITOR_SRC_FILES "editor_src/*.cpp")

#COMMON
file(GLOB COMMON_SRC_FILES "common_src/*.cpp")
file(GLOB SDL_SRC_FILES "common_src/Sdl/*.cpp")

# add the executable
add_executable(Client client_src/main.cpp ${CLIENT_SRC_FILES} ${CHARACTER_SRC_FILES} ${EVENTS_SRC_FILES} ${COMMON_SRC_FILES} ${SDL_SRC_FILES})
target_link_libraries(Client SDL2 SDL2_image SDL2_ttf SDL2_mixer pthread)

add_executable(Server server_src/main.cpp ${SERVER_SRC_FILES}
        ${COMMON_SRC_FILES} ${GAME_MODEL_SRC_FILES})
target_link_libraries(Server box2d pthread yaml-cpp)

add_executable(Editor editor_src/main.cpp ${EDITOR_SRC_FILES} ${COMMON_SRC_FILES} ${SDL_SRC_FILES} "client_src/Character/camera.cpp")
target_link_libraries(Editor SDL2 SDL2_image SDL2_ttf SDL2_mixer yaml-cpp)