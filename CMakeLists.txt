cmake_minimum_required(VERSION 3.21)

# 1. Mata o PCH e o FMT Consteval antes de qualquer coisa
set(GEODE_DISABLE_PCH ON CACHE INTERNAL "Disable PCH" FORCE)
add_compile_definitions(FMT_USE_CONSTEVAL=0)
add_compile_definitions(FMT_USE_CONSTEXPR=0)
add_compile_definitions(FMT_COMPILE_TIME_CHECKS=0)
add_compile_definitions(FMT_HEADER_ONLY=1)

project(meu-mod-die VERSION 1.0.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. SEGUNDA ONDA DE ATAQUE: Força o compilador a ignorar o erro de vez
if(ANDROID)
    add_compile_options(-Wno-error=invalid-constexpr)
    add_compile_options(-Wno-invalid-constexpr)
    add_compile_options(-fcommon)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 3. Força o alvo a não usar PCH
set_target_properties(${PROJECT_NAME} PROPERTIES DISABLE_PRECOMPILED_HEADERS ON)

setup_geode_mod(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} geode.loader)
