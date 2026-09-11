cmake_minimum_required(VERSION 4.3)
project(stoneandsoil)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG master
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG master
)

FetchContent_MakeAvailable(glfw glm)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.hpp
)

set(VENDOR_SOURCES ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c)

add_executable(stoneandsoil ${SOURCES} ${VENDOR_SOURCES})

add_custom_command(TARGET stoneandsoil POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:stoneandsoil>/res"
)

target_include_directories(stoneandsoil PRIVATE ${CMAKE_SOURCE_DIR}/vendor/glad/include ${CMAKE_SOURCE_DIR}/vendor)

target_link_libraries(stoneandsoil PRIVATE glfw glm::glm)