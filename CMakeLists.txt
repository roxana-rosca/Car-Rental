cmake_minimum_required(VERSION 3.24)
project(inchiriere_masini)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.5.0\\mingw_64\\lib\\cmake")

find_package(Qt6Widgets REQUIRED)
find_package(Qt6Core REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")

add_executable(inchiriere_masini main.cpp Car.cpp UI.cpp Repository.cpp Service.cpp Validator.h VectorDinamicTemplate.cpp ListaDeLucru.cpp ListaDeLucru.h DTO.cpp DTO.h Export.cpp Export.h Undo.h Undo.h GUI.cpp GUI.h ListaDeLucruGUI.cpp ListaDeLucruGUI.h Observer.h Observer.h MyTableModel.h GUIModel.cpp GUIModel.h)

target_link_libraries(inchiriere_masini Qt6::Widgets Qt6::Core)