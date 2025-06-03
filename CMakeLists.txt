cmake_minimum_required(VERSION 3.26)


set(PLATFORM_DESKTOP_HEADLESS ON CACHE BOOL "Use headless (no window) platform")

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


        Code/include/defineuri.h

        Code/include/entities/Entity.h
        Code/include/entities/Enemy.h
        Code/include/entities/includeAll.h
        Code/include/entities/Living.h
        Code/include/entities/Player.h
        Code/include/entities/Turtle.h
        Code/include/Entities/environment/Environment.h
        Code/include/Entities/environment/GroundBlock.h
        Code/include/Exception/BaseException.h
        Code/include/Exception/FileException.h
        Code/include/Exception/TextureException.h
        Code/include/Exception/FpsException.h
        Code/include/Exception/Exception.h
        Code/include/entities/Animation.h
        Code/include/Entities/environment/QuestionBlock.h
        Code/include/Entities/environment/MovebleEnvironment.h
        Code/include/Entities/environment/BrickBlock.h
        Code/include/Template/ResourceManager.h
        Code/include/entities/Audio.h

        Code/src/Enemy.cpp
        Code/src/Entity.cpp
        Code/src/game/gameFunction.cpp
        Code/src/includeAll.cpp
        Code/src/Player.cpp
        Code/src/Turtle.cpp
        Code/src/Living.cpp
        Code/src/environment/Environment.cpp
        Code/src/environment/GroundBlock.cpp
        Code/src/Exception/BaseException.cpp
        Code/src/Exception/FileException.cpp
        Code/src/Exception/TextureException.cpp
        Code/src/Exception/FpsException.cpp
        Code/src/game/collision.cpp
        Code/src/game/gameUtilities.cpp
        Code/src/game/setLevel.cpp
        Code/src/Animation.cpp
        Code/src/environment/QuestionBlock.cpp
        Code/src/environment/MovebleEnvironment.cpp
        Code/src/environment/BrickBlock.cpp
        Code/src/Audio.cpp

        Code/Levels/level1.txt
        Code/include/Template/templateFunction.h
        Code/include/Template/ResourceAudio.h
        Code/src/EntityInitialization.cpp
        Code/include/entities/EntityFactory.h
        Code/include/Observer/IObserver.h
        Code/src/Observer/IObserver.cpp
        Code/include/Observer/ISubject.h
        Code/include/Observer/ScoreManager.h
        Code/src/Observer/ScoreManager.cpp
        Code/include/entities/Coin.h
        Code/src/Coin.cpp

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
