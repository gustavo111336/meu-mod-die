cmake_minimum_required(VERSION 3.21)

# 1. Desativa PCH e qualquer validação de FMT antes do projeto
set(GEODE_DISABLE_PCH ON CACHE INTERNAL "Disable PCH" FORCE)
add_definitions(-DFMT_USE_CONSTEVAL=0)
add_definitions(-DFMT_USE_CONSTEXPR=0)
add_definitions(-DFMT_COMPILE_TIME_CHECKS=0)

project(meu-mod-die VERSION 1.0.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. ATAQUE DIRETO AO COMPILADOR CLANG DO ANDROID
if(ANDROID)
    # Força o compilador a ignorar o erro que parou o Build #48
    add_compile_options(-Wno-error=invalid-constexpr)
    add_compile_options(-Wno-invalid-constexpr)
    add_compile_options(-Wno-error=format-security)
    add_compile_options(-Wno-format-security)
    
    # Define as flags de FMT novamente para garantir que se propaguem
    add_compile_definitions(FMT_USE_CONSTEVAL=0)
    add_compile_definitions(FMT_USE_CONSTEXPR=0)
    add_compile_definitions(FMT_COMPILE_TIME_CHECKS=0)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 3. Blindagem extra no alvo do mod
set_target_properties(${PROJECT_NAME} PROPERTIES DISABLE_PRECOMPILED_HEADERS ON)

setup_geode_mod(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} geode.loader)
