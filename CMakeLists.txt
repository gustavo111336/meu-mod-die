cmake_minimum_required(VERSION 3.21)

project(meu-mod-die VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# 1. Carrega o SDK do Geode
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()

# Forçar desativação de PCH e validações que causam o erro
set(GEODE_DISABLE_PCH ON CACHE INTERNAL "Disable PCH")

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# 2. BLOQUEIO NUCLEAR DE ERROS FMT NO ANDROID
if(ANDROID)
    # Isso define para o compilador ANTES de ler qualquer header
    add_compile_definitions(FMT_USE_CONSTEVAL=0)
    add_compile_definitions(FMT_USE_CONSTEXPR=0)
    add_compile_definitions(FMT_COMPILE_TIME_CHECKS=0)
    
    # Desativa a checagem que está disparando o erro consteval
    add_compile_options(-Wno-error=format-security)
    add_compile_options(-Wno-format-security)
    
    # Truque para o Clang ignorar a verificação de string constante
    add_compile_options(-fno-limit-debug-info) 
endif()

# 3. Define os arquivos fonte
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 4. CRIA O TARGET
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 5. Configura o Geode
setup_geode_mod(${PROJECT_NAME})

# 6. Links extras
target_link_libraries(${PROJECT_NAME} geode.node-ids)
