cmake_minimum_required(VERSION 3.21)

# Desativa o PCH de forma absoluta
set(GEODE_DISABLE_PCH ON CACHE BOOL "Force Disable PCH" FORCE)

project(meu-mod-die VERSION 1.0.0)

# C++23 
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# 1. Carrega o Geode
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. Definições de Pré-processador (O "Cala a boca" pro compilador)
add_compile_definitions(FMT_USE_CONSTEVAL=0)
add_compile_definitions(FMT_USE_CONSTEXPR=0)
add_compile_definitions(FMT_COMPILE_TIME_CHECKS=0)

if(ANDROID)
    add_compile_options(-Wno-format-security)
    add_compile_options(-Wno-error=format-security)
    add_compile_options(-Wno-everything) # A "Marreta": Silencia TODOS os avisos no Android
endif()

# 3. Arquivos fonte
file(GLOB_RECURSE SOURCES src/*.cpp)

# 4. Target
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 5. Configura Geode
setup_geode_mod(${PROJECT_NAME})

# 6. Link Simples (Removi o node-ids para isolar o erro)
target_link_libraries(${PROJECT_NAME} geode.loader)
