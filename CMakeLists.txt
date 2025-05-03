cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################
# Adăugarea dependenței pentru Raylib

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    endif()
endif()

###############################################################################
# Definirea executabilului

add_executable(${MAIN_EXECUTABLE_NAME}
        Code/src/main.cpp
       # Code/statemachine.cpp
        generated/src/Helper.cpp
        Code/Entitati1.h


        Code/include/defineuri.h

        Code/include/entitati/Entity.h
        Code/include/entitati/Enemy.h
        Code/include/entitati/includeAll.h
        Code/include/entitati/Living.h
        Code/include/entitati/Player.h
        Code/include/entitati/Turtle.h
        Code/include/entitati/Environment.h
        Code/include/entitati/Brick.h
        Code/include/exceptii/BaseException.h
        Code/include/exceptii/FileException.h

        Code/src/Enemy.cpp
        Code/src/Entity.cpp
        Code/src/game/gameFunction.cpp
        Code/src/includeAll.cpp
        Code/src/Player.cpp
        Code/src/Turtle.cpp
        Code/src/Living.cpp
        Code/src/Environment.cpp
        Code/src/Brick.cpp
        Code/Levels/level1.txt
        Code/src/exceptii/BaseException.cpp
        Code/src/exceptii/FileException.cpp
        Code/include/Exceptii/TextureException.h
        Code/src/exceptii/TextureException.cpp
        Code/include/Exceptii/FpsException.h
        Code/src/exceptii/FpsException.cpp
        Code/src/game/collision.cpp
        Code/src/game/gameUtilities.cpp
        Code/src/game/setLevel.cpp
        Code/include/Exceptii/exceptii.h

)
target_compile_features(oop PUBLIC cxx_std_17)
target_compile_definitions(${MAIN_EXECUTABLE_NAME} PRIVATE RAYLIB_STATIC)
target_link_libraries(${MAIN_EXECUTABLE_NAME} raylib)
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)

# Legarea Raylib la executabil
target_link_libraries(${MAIN_EXECUTABLE_NAME} raylib)

###############################################################################
# Configurații suplimentare (instalare, copiere fișiere, etc.)

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
    target_link_libraries(${MAIN_EXECUTABLE_NAME} "-framework IOKit")
    target_link_libraries(${MAIN_EXECUTABLE_NAME} "-framework Cocoa")
    target_link_libraries(${MAIN_EXECUTABLE_NAME} "-framework OpenGL")
endif()
if (WIN32)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} opengl32 gdi32 winmm)
endif()
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
