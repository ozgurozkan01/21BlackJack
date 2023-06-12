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
    // Initial Part
    DealInitialCard();
    CalculatePlayerInitialHand();

    // Hit Part
    DealHitCard();

}

void GameManager::SetPlayerNumber()
{
    std::cout << " Enter how many players are gonna play : " << std::flush;
    std::cin >> playerNumber;

    playerNumber++; // For adding croupier
}

void GameManager::SetPlayerName()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        std::string playerName;

        if (i == playerNumber-1)
        {
            std::cout << "You are croupier! Never forget." << std::endl;
        }

        std::cout << "Enter " << i+1 << ". player's name : " << std::flush;
        std::cin >> playerName;
        playersName.push_back(playerName);
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
            playersInitialCards[j][i] = card;
        }
    }
}

void GameManager::DealHitCard()
{

    for (int i = 0; i < playerNumber; ++i)
    {
        bool isCardDealing;

        std::cout << "Your point is : " << playersPoint[i] << std::endl;
        do {
            std::cout << playersName[i] << ", do you wanna hit card : " << std::flush;
            std::cin >> isCardDealing;

            if (isCardDealing)
            {
                int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
                std::string card = cardDeck->GetDeck()[cardIndex]->GetCardValue();
                playersPoint[i] += ConvertCardToPoint(card);
                std::cout << "Your new point is : " << playersPoint[i] << std::endl;
                cardDeck->DecreaseCardNumber();

                if(playersPoint[i] == 21)
                {
                    std::cout << "Congratulations! BLACKJACK !!" << std::endl;
                    continue;
                }

                else if (playersPoint[i] > 21)
                {
                    std::cout << "You Have Lost !! Better Luck Next Time." << std::endl;
                    playersName.erase(playersName.begin() + i);
                    exactLosers.push_back(playersName[i]);
                    continue;
                }
            }

        }while (isCardDealing && playersPoint[i] < 21);
    }
}

void GameManager::CalculatePlayerInitialHand()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        if (playersInitialCards[i][0] == "A" && playersInitialCards[i][1] == "A")
        {
            std::cout << playersName[i] << " have 2 AS. You can choose 2, 12, 22" << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> playersPoint[i];
            continue;
        }

        else if (playersInitialCards[i][0] != "A" && playersInitialCards[i][1] == "A")
        {
            std::cout << playersName[i] << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(playersInitialCards[i][0]) << " or " << 1 + ConvertCardToPoint(playersInitialCards[i][0]) << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> playersPoint[i];
            continue;
        }

        else if (playersInitialCards[i][0] == "A" && playersInitialCards[i][1] != "A")
        {
            std::cout << playersName[i] << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(playersInitialCards[i][1]) << " or " << 1 + ConvertCardToPoint(playersInitialCards[i][1]) << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> playersPoint[i];
            continue;
        }

        playersPoint[i] = ConvertCardToPoint(playersInitialCards[i][1]) + ConvertCardToPoint(playersInitialCards[i][0]);
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

void GameManager::DesignatePlayersWinOrLose()
{


}