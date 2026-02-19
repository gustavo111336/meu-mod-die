cmake_minimum_required(VERSION 3.21)

# Força o desligamento do PCH que gerou aquele erro "cmake_pch.hxx"
set(GEODE_DISABLE_PCH ON CACHE INTERNAL "Disable PCH" FORCE)

project(meu-mod-die VERSION 1.0.3)

# C++20: A versão que seu arquivo de sucesso usou
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Bloqueio de FMT para evitar o erro de consteval
add_compile_definitions(FMT_USE_CONSTEVAL=0)
add_compile_definitions(FMT_USE_CONSTEXPR=0)

if(ANDROID)
    add_compile_options(-Wno-error=invalid-constexpr)
    add_compile_options(-Wno-format-security)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Garante que o alvo não use PCH
set_target_properties(${PROJECT_NAME} PROPERTIES DISABLE_PRECOMPILED_HEADERS ON)

setup_geode_mod(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} geode.loader)
