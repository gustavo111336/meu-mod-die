cmake_minimum_required(VERSION 3.21)

# Desativa o PCH para evitar que o erro aconteça no cabeçalho pré-compilado
set(GEODE_DISABLE_PCH ON CACHE BOOL "Force Disable PCH" FORCE)

project(meu-mod-die VERSION 1.0.0)

# C++23 como você sugeriu
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# 1. Carrega o SDK do Geode
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. ATAQUE DIRETO AO COMPILADOR
if(ANDROID)
    # Define flags globais para silenciar o FMT de uma vez por todas
    add_compile_definitions(FMT_USE_CONSTEVAL=0)
    add_compile_definitions(FMT_USE_CONSTEXPR=0)
    add_compile_definitions(FMT_COMPILE_TIME_CHECKS=0)
    
    # Isso aqui é a "marreta": obriga o compilador a ignorar erros de segurança de formato
    add_compile_options(-Wno-format-security)
    add_compile_options(-Wno-error=format-security)
    add_compile_options(-Wno-implicit-consteval) # Tenta ignorar a chamada consteval
endif()

# 3. Define os arquivos fonte
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 4. CRIA O TARGET
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 5. Configura o Geode
setup_geode_mod(${PROJECT_NAME})

# 6. Links extras
target_link_libraries(${PROJECT_NAME} geode.node-ids)
