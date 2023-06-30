cmake_minimum_required(VERSION 3.25)
project(21BlackJack)

set(CMAKE_CXX_STANDARD 17)

add_executable(21BlackJack main.cpp GameManager.cpp GameManager.h Card.cpp Card.h CardDeck.cpp CardDeck.h Player.cpp Player.h Croupier.cpp Croupier.h)
