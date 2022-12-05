cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -g ")
include(cmake/CPM.cmake)


project(silentValley)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS  src/*.cpp)

add_library(silentValleyLib SHARED ${SRC_FILES})

CPMAddPackage(
    NAME magic_enum
    GITHUB_REPOSITORY Neargye/magic_enum
    GIT_TAG v0.8.0
)

set(TGUI_BUILD_FRAMEWORK FALSE)
FetchContent_Declare(
  tgui
  GIT_REPOSITORY https://github.com/texus/TGUI/
  GIT_TAG 2b7610f251937cf854a362127a47a13f027457a1
)

FetchContent_MakeAvailable(tgui)

target_link_libraries(silentValleyLib
    /Library/Frameworks/SFML.framework
    /Library/Frameworks/sfml-system.framework/sfml-system
    /Library/Frameworks/sfml-window.framework/sfml-window
    /Library/Frameworks/sfml-graphics.framework/sfml-graphics
    /Library/Frameworks/sfml-audio.framework/sfml-audio
    /usr/local/lib/libtmxlite.a
    magic_enum
    tgui

)

target_include_directories(silentValleyLib PUBLIC
    ./external/tmxlite/tmxlite/include
    ./external/entt/src/entt/
    ./external/pugixml-1.13/src/
    /usr/local/Cellar/entt/3.11.1/include
)

add_executable(silentValley src/main.cpp)
target_link_libraries(silentValley PRIVATE
    silentValleyLib
)