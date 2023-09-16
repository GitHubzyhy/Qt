cmake_minimum_required(VERSION 3.14)

project(chapter2signal LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(chapter2signal
  main.cpp
  sender.h sender.cpp
  receiver.h receiver.cpp
)
target_link_libraries(chapter2signal Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS chapter2signal
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
