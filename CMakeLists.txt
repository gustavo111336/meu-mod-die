cmake_minimum_required(VERSION 3.21)

project(meu-mod-die VERSION 1.0.0)

# 1. Configurações Globais
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# 2. Encontrar o Geode (Jeito moderno)
find_package(Geode REQUIRED)

# 3. CORREÇÃO DO ERRO FMT (Deve ficar aqui, fora de outros comandos)
if(ANDROID)
    add_definitions(-DFMT_USE_CONSTEXPR=0)
    add_definitions(-DFMT_COMPILE_TIME_CHECKS=0)
endif()

# 4. Adicionar arquivos fonte
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 5. Configurar o Mod
setup_geode_mod(
    ${PROJECT_NAME}
    SOURCES ${SOURCES}
)

# 6. Adicionar dependências (Node IDs)
target_link_libraries(${PROJECT_NAME} INTERFACE geode.node-ids)
