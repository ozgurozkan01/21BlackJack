cmake_minimum_required(VERSION 3.25)
project(21BlackJack)

set(CMAKE_CXX_STANDARD 17)

add_executable(21BlackJack main.cpp Card.cpp Card.h GameManager.cpp GameManager.h)
