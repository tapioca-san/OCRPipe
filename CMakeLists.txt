#todo erro de configuração do cmake

cmake_minimum_required(VERSION 3.16)
project(GAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios
set(SRC_DIR ./src)

# Adiciona arquivos do projeto
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

# Compila executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Instalação
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
