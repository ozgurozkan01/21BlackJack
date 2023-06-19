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

    DesignateUnknownStatePlayer();
    PrintPlayersState();
}

void GameManager::SetPlayerNumber()
{
    do {
        std::cout << " You can play with max 7 players !! " << std::endl;
        std::cout << " Enter how many players are gonna play : " << std::flush;
        std::cin >> playerNumber;
    }while(playerNumber > 7);

    playerNumber++;
    std::cout << std::endl;
}

void GameManager::SetPlayerName()
{
    for (int i = 0; i < playerNumber - 1; ++i)
    {
        std::string playerName;
        std::string player = "player's";
        std::cout << "Enter " << i+1 << ". " <<  player << " name : " << std::flush;
        std::cin >> playerName;
        playersName.push_back(playerName);
    }

    playersName.push_back("Croupier");
}

void GameManager::DealInitialCard()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < playerNumber; ++j)
        {
            int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
            std::string card = cardDeck->GetDeck()[cardIndex]->GetCardValue();
            playersInitialCards[j][i] = card;
            cardDeck->GetDeck().erase(cardDeck->GetDeck().begin() + cardIndex);
            cardDeck->DecreaseCardNumber();
        }
    }
}

void GameManager::DealHitCard()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        CalculatePlayerInitialHand(i);
        bool isCardDealing;

        std::cout << playersName[i] << " point is : " << playersPoint[i] << std::endl;
        do {
            std::cout << playersName[i] << ", do you wanna hit card : " << std::flush;
            std::cin >> isCardDealing;

            if (isCardDealing)
            {
                int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
                std::string card = cardDeck->GetDeck()[cardIndex]->GetCardValue();
                playersPoint[i] += ConvertCardToPoint(card);
                std::cout << "Your new point is : " << playersPoint[i] << std::endl;
                cardDeck->GetDeck().erase(cardDeck->GetDeck().begin() + cardIndex);
                cardDeck->DecreaseCardNumber();

                if(playersPoint[i] == 21)
                {
                    std::cout << "Congratulations! BLACKJACK !!" << std::endl;
                }

                else if (playersPoint[i] > 21)
                {
                    std::cout << "You Have Lost !! Better Luck Next Time." << std::endl;
                }
            }

        }while (isCardDealing && playersPoint[i] < 21);
    }
}

void GameManager::CalculatePlayerInitialHand(int index)
{
    int point;
    if (playersInitialCards[index][0] == "A" && playersInitialCards[index][1] == "A")
    {
        std::cout << playersName[index] << " have 2 AS. You can choose 2, 12" << std::endl;
        std::cout << "Enter your point choice : " << std::flush;
        std::cin >> point;
    }

    else if (playersInitialCards[index][0] != "A" && playersInitialCards[index][1] == "A")
    {
        std::cout << playersName[index] << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(playersInitialCards[index][0]) << " or "
        << 1 + ConvertCardToPoint(playersInitialCards[index][0]) << std::endl;
        std::cout << "Enter your point choice : " << std::flush;
        std::cin >> point;
    }

    else if (playersInitialCards[index][0] == "A" && playersInitialCards[index][1] != "A")
    {
        std::cout << playersName[index] << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(playersInitialCards[index][1]) << " or "
        << 1 + ConvertCardToPoint(playersInitialCards[index][1]) << std::endl;
        std::cout << "Enter your point choice : " << std::flush;
        std::cin >> point;
    }

    else
    {
        point = (ConvertCardToPoint(playersInitialCards[index][0]) + ConvertCardToPoint(playersInitialCards[index][1]));
    };

    playersPoint.push_back(point);
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

void GameManager::DesignateUnknownStatePlayer()
{
    int croupierValue = playersPoint[playerNumber-1];
    std::string croupier = playersName[playerNumber-1];
    playersName.erase(playersName.begin() + (playersName.size() -1));
    playersPoint.erase(playersPoint.begin() + (playersPoint.size() -1));
    playerNumber--;

    if (croupierValue > 21)
    {
        exactLoserList.push_back(croupier);
        for (int i = 0; i < playerNumber; ++i)
        {
            if (playersPoint[i] > 21)
            {
                exactLoserList.push_back(playersName[i]);
                continue;
            }

            else
            {
                exactWinnerList.push_back(playersName[i]);
            }
        }
    }

    else
    {
        for (int i = 0; i < playerNumber; ++i)
        {
            if (playersPoint[i] > 21 ||playersPoint[i] < croupierValue)
            {
                exactLoserList.push_back(playersName[i]);
                continue;
            }

            else if (playersPoint[i] > croupierValue)
            {
                exactWinnerList.push_back(playersName[i]);
                continue;
            }

            else if (playersPoint[i] == croupierValue)
            {
                tiedPlayerList.push_back(playersName[i]);
                continue;
            }
        }
    }

}

void GameManager::PrintPlayersState()
{
    std::cout << "WINNERS !" << std::endl;
    for (auto winner : exactWinnerList)
    {
        std::cout << winner << std::endl;
    }
    std::cout << std::endl;

    std::cout << "LOSERS !" << std::endl;
    for (auto loser : exactLoserList)
    {
        std::cout << loser << std::endl;
    }
    std::cout << std::endl;


    std::cout << "TIED !" << std::endl;
    for (auto tied : tiedPlayerList)
    {
        std::cout << tied << std::endl;
    }
    std::cout << std::endl;
}
