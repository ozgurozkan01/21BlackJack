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

    // Hit Part
    DealHitCard();
}

void GameManager::SetPlayerNumber()
{
    std::cout << " Enter how many players are gonna play : " << std::flush;
    std::cin >> playerNumber;

    playerNumber++;
}

void GameManager::SetPlayerName()
{
    for (int i = 0; i < playerNumber -1; ++i)
    {
        std::string playerName;
        std::string player = "player's";
        std::cout << "Enter " << i+1 << ". " <<  player << " name : " << std::flush;
        std::cin >> playerName;
        playersName.push_back(playerName);
    }

    playersName[playerNumber-1] = "Croupier";
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
        std::cout << std::endl;
        CalculatePlayerInitialHand(playersInitialCards[i], playersName[i], playersPoint[i]);

        bool isCardDealing;

        std::cout << playersName[i] << " point is : " << playersPoint[i] << std::endl;
        do {
            std::cout << playersName[i] << ", do you wanna hit card : " << std::flush;
            std::cin >> isCardDealing;

            if (isCardDealing)
            {
                int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
                std::string card = cardDeck->GetDeck()[cardIndex]->GetCardValue();
                playersPoint.push_back(ConvertCardToPoint(card));
                std::cout << "Your new point is : " << playersPoint[i] << std::endl;
                cardDeck->DecreaseCardNumber();

                if(playersPoint[i] == 21)
                {
                    std::cout << "Congratulations! BLACKJACK !!" << std::endl;
                }

                else if (playersPoint[i] > 21)
                {
                    std::cout << "You Have Lost !! Better Luck Next Time." << std::endl;
                    playersName.erase(playersName.begin() + i);
                    exactLosers.push_back(playersName[i]);
                }
            }

        }while (isCardDealing && playersPoint[i] < 21);
    }
}

int GameManager::CalculatePlayerInitialHand(std::string* card, std::string& name, int& point)
{
        if (card[0] == "A" && card[1] == "A")
        {
            std::cout << name << " have 2 AS. You can choose 2, 12" << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> point;
        }

        else if (card[0] != "A" && card[1] == "A")
        {
            std::cout << name << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(card[0]) << " or " << 1 + ConvertCardToPoint(card[0]) << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> point;
        }

        else if (card[0] == "A" && card[1] != "A")
        {
            std::cout << name << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(card[1]) << " or " << 1 + ConvertCardToPoint(card[1]) << std::endl;
            std::cout << "Enter your point choice : " << std::flush;
            std::cin >> point;
        }

        else
        {
            point = ConvertCardToPoint(card[1]) + ConvertCardToPoint(card[0]);
        }

        return point;
}

int GameManager::ConvertCardToPoint(std::string& card)
{
    if (card == "A") return 1;
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

void GameManager::DesignatePlayersWinState()
{
    if (exactLosers[exactLosers.size() -1] == "Croupier")
    {
        for (auto player: playersName)
        {
            exactWinners.push_back(player);
        }
        return;
    }

    else {

        for (int i = 0; i < playersName.size() - 1; ++i)
        {
        }

    }
}