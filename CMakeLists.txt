cmake_minimum_required(VERSION 3.15)

# Nom du projet et version
project(AI_Library VERSION 1.0 LANGUAGES CXX)

# Force l'utilisation du C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options de compilation (Alertes maximales et optimisation)
if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -pedantic -O3)
endif()

# Définir où se trouvent les fichiers .hpp
include_directories(headers)

file(GLOB SOURCES "src/*.cpp")

# Créer l'exécutable
add_executable(ai_lib ${SOURCES})