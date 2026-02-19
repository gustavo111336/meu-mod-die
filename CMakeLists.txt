cmake_minimum_required(VERSION 3.21)

project(meu-mod-die VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# 1. Carrega o SDK do Geode
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. Correção para o erro de strings no Android
if(ANDROID)
    add_definitions(-DFMT_USE_CONSTEXPR=0)
    add_definitions(-DFMT_COMPILE_TIME_CHECKS=0)
endif()

# 3. Define os arquivos fonte
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 4. CRIA O TARGET (Isso resolve o erro atual!)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 5. Configura o Geode no Target criado
setup_geode_mod(${PROJECT_NAME})

# 6. Links extras
target_link_libraries(${PROJECT_NAME} geode.node-ids)