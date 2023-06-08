//
// Created by ozgur on 6/5/2023.
//

#include "GameManager.h"
#include "Card.h"
#include "CardDeck.h"
#include <iostream>

GameManager::GameManager()
{
    srand(time(NULL));
    cardDeck = new CardDeck();
    playerNumber = 0.f;

    std::cout << " WELCOME TO 21 BLACKJAKE GAME " << std::endl;
    std::cout << " BEST OF LUCK !! " << std::endl;
}

void GameManager::BeginPlay()
{
    SetPlayerNumber();
    SetPlayerName();
}

void GameManager::Tick()
{
    DealFirstPartCard();
}

void GameManager::SetPlayerNumber()
{
    std::cout << " Enter how many players are gonna play : " << std::flush;
    std::cin >> playerNumber;
}

void GameManager::SetPlayerName()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        std::cout << "Enter " << i+1 << ". player's name : " << std::flush;
        std::cin >> playersName[i];
    }
}

void GameManager::DealFirstPartCard()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            std::string card = cardDeck->GetDeck()[rand() % 52]->GetCardValue();
            playersCards[i][j] = card;
        }
    }
}
