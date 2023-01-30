cmake_minimum_required(VERSION 3.20)
project(wggame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS FALSE)

add_compile_definitions(SFML_STATIC)

set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SFML)

file(GLOB GAME_HEADERS
     "${PROJECT_SOURCE_DIR}/include/**.hpp")

file(GLOB GAME_SOURCES
     "${PROJECT_SOURCE_DIR}/src/**.cpp")

add_executable(wggame ${GAME_SOURCES} ${GAME_HEADERS})
target_include_directories(wggame PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(wggame PRIVATE sfml-graphics sfml-window sfml-system)

set(TARGET_FOLDER ${PROJECT_SOURCE_DIR}/build)
add_custom_command(
        TARGET wggame
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:wggame>" "${TARGET_FOLDER}/$<TARGET_FILE_NAME:wggame>"
        COMMAND "${CMAKE_COMMAND}" -E copy "${PROJECT_SOURCE_DIR}/resources/Roboto.ttf" "${TARGET_FOLDER}/resources/Roboto.ttf"
)
