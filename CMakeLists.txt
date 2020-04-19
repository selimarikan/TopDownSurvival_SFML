cmake_minimum_required(VERSION 3.14)
project(TDDEF VERSION 1.0 DESCRIPTION "Top-Down Defence" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp AnimationHandler.cpp Character.cpp CharacterTopDown.cpp Game.cpp GameManager.cpp ITile.cpp Map.cpp TextureManager.cpp Tile.cpp Utils.cpp)
add_executable(TDDEF ${SOURCES})

# Enable -flto
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(TDDEF PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()


target_include_directories(TDDEF PUBLIC C:\\Users\\Selim\\Source\\Repos\\SFML\\Include\\)
target_include_directories(TDDEF PUBLIC Extern)
target_link_directories(TDDEF PUBLIC C:\\Users\\Selim\\Source\\Repos\\SFML\\lib\\Debug\\)
target_link_libraries(TDDEF sfml-main-d.lib sfml-system-d.lib sfml-window-d.lib sfml-graphics-d.lib)

add_custom_command(TARGET TDDEF PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:TDDEF>/Assets)