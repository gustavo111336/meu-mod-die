cmake_minimum_required(VERSION 3.21)

# 1. ISSO AQUI MATA O PCH ANTES DELE NASCER
set(GEODE_DISABLE_PCH ON CACHE INTERNAL "Disable PCH" FORCE)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES OFF)

project(meu-mod-die VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Carrega o SDK
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 3. SE O ARQUIVO AINDA TENTAR EXISTIR, IGNORAMOS OS ERROS DELE
if(ANDROID)
    add_compile_definitions(FMT_USE_CONSTEVAL=0)
    add_compile_definitions(FMT_USE_CONSTEXPR=0)
    add_compile_options(-Wno-invalid-constexpr)
    add_compile_options(-Wno-error=invalid-constexpr)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 4. FORÇA O SEU PROJETO A NÃO USAR PCH DE JEITO NENHUM
set_target_properties(${PROJECT_NAME} PROPERTIES DISABLE_PRECOMPILED_HEADERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_ENABLE_PRECOMPILED_HEADER OFF)

setup_geode_mod(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} geode.loader)
