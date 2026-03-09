cmake_minimum_required(VERSION 3.15)

# Nom du projet et version
project(AI_Library VERSION 1.0 LANGUAGES CXX)

# Force l'utilisation du C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenMP REQUIRED)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -O3 -march=native)
endif()

# Définir où se trouvent les fichiers .hpp
include_directories(headers)

file(GLOB SOURCES "src/*.cpp")

# Créer l'exécutable
add_executable(ai_lib ${SOURCES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(ai_lib PUBLIC OpenMP::OpenMP_CXX)
endif()