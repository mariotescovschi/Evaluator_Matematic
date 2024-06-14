cmake_minimum_required(VERSION 3.26)
project(ProiectIP_EvaluatorMatematic)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProiectIP_EvaluatorMatematic main.cpp
        parsing/verificareParanteze.cpp
        setup/preprocesare.cpp
        parsing/parsareExpresie.cpp
        parsing/parsareExpresie.h
        graphics/meniuCalculator.cpp
        graphics/meniuCalculator.h
        graphics/graficaArbore.cpp
        graphics/graficaArbore.h
        parsing/verificareSintaxaExpresiei.cpp
        parsing/verificareSintaxaExpresiei.h
        setup/structuriDeDate.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(ProiectIP_EvaluatorMatematic sfml-system sfml-window sfml-graphics sfml-audio sfml-network)