cmake_minimum_required(VERSION 3.21)

project(meu-mod-die VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# CORREÇÃO: Em vez de find_package, usamos o caminho direto do ambiente
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()

# Adiciona o SDK do Geode ao projeto
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# CORREÇÃO DO ERRO FMT (Isso precisa continuar aqui para o Android não quebrar depois)
if(ANDROID)
    add_definitions(-DFMT_USE_CONSTEXPR=0)
    add_definitions(-DFMT_COMPILE_TIME_CHECKS=0)
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Configura o mod usando a função interna do SDK que acabamos de carregar
setup_geode_mod(
    ${PROJECT_NAME}
    SOURCES ${SOURCES}
)

# Adiciona a dependência do Node IDs que você queria
target_link_libraries(${PROJECT_NAME} INTERFACE geode.node-ids)
