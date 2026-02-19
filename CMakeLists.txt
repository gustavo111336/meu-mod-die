cmake_minimum_required(VERSION 3.21)

# Desativa o PCH antes de qualquer coisa
set(GEODE_DISABLE_PCH ON CACHE INTERNAL "Disable PCH" FORCE)

project(meu-mod-die VERSION 1.0.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Força o FMT a ser o mais simples possível ANTES de carregar o Geode
add_definitions(-DFMT_USE_CONSTEVAL=0)
add_definitions(-DFMT_USE_CONSTEXPR=0)
add_definitions(-DFMT_COMPILE_TIME_CHECKS=0)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. Silencia o erro específico do log: compile_string_to_view
if(ANDROID)
    add_compile_options(-Wno-invalid-constexpr)
    add_compile_options(-Wno-error=invalid-constexpr)
    add_compile_options(-Wno-unused-local-typedef)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} geode.loader)
