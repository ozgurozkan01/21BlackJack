//
// Created by ozgur on 6/5/2023.
//

#include "GameManager.h"
#include "CardDeck.h"
#include "Card.h"
#include <iostream>
#include <vector>

GameManager::GameManager()
{
    srand(time(nullptr));
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
    DealInitialCard();
    CalculatePlayerInitialHand();

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

void GameManager::DealInitialCard()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < playerNumber; ++j)
        {
            int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
            std::string card = cardDeck->GetDeck()[cardIndex]->GetCardValue();
            cardDeck->GetDeck().erase(cardDeck->GetDeck().begin() + cardIndex);
            playersCards[j][i] = card;
            cardDeck->DecreaseCardNumber();
            std::cout << cardDeck->GetDeck().size() << std::endl;
        }
    }
}

void GameManager::CalculatePlayerInitialHand()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        if (playersCards[i][0] == "A" && playersCards[i][1] == "A")
        {
            std::cout << "You have 2 AS. You can choose 2, 12, 22" << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> playersPoints[i];
            continue;
        }

        else if (playersCards[i][0] != "A" && playersCards[i][1] == "A")
        {
            std::cout << "You have 1 AS. You can choose " << 11 + ConvertCardToPoint(playersCards[i][0]) << " or " << 1 + ConvertCardToPoint(playersCards[i][0]) << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> playersPoints[i];
            continue;
        }

        else if (playersCards[i][0] == "A" && playersCards[i][1] != "A")
        {
            std::cout << "You have 1 AS. You can choose " << 11 + ConvertCardToPoint(playersCards[i][1]) << " or " << 1 + ConvertCardToPoint(playersCards[i][1]) << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> playersPoints[i];
            continue;
        }

        playersPoints[i] = ConvertCardToPoint(playersCards[i][1]) + ConvertCardToPoint(playersCards[i][0]);
    }
}

int GameManager::ConvertCardToPoint(std::string& card)
{
    if (card == "A") return 11;
    else if (card == "2") return 2;
    else if (card == "3") return 3;
    else if (card == "4") return 4;
    else if (card == "5") return 5;
    else if (card == "6") return 6;
    else if (card == "7") return 7;
    else if (card == "8") return 8;
    else if (card == "9") return 9;
    return 10; // J, K, Q, 10
}