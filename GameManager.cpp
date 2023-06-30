//
// Created by ozgur on 6/5/2023.
//
#include "GameManager.h"
#include "CardDeck.h"
#include "Card.h"
#include "Player.h"
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
    FillUpWallet();
    PlaceBets();

    // Initial Part
    DealInitialCard();

    // Hit Part
    DealHitCard();

    DesignatePlayersLastState();
    BetsPayOut();
    PrintPlayersState();
}

void GameManager::SetPlayerNumber()
{
    bool isPlayerNumberCorrect;
    std::string playerAmount;
    do {

        isPlayerNumberCorrect = true;

        std::cout << std::endl;
        std::cout << " You can play with MIN 1 - MAX 7 players !! " << std::endl;
        std::cout << " Enter how many players are gonna play : " << std::flush;
        std::cin >> playerAmount;

        for (auto c : playerAmount)
        {
            if(!isdigit(c))
            {
                isPlayerNumberCorrect = false;
                break;
            }
        }

        if (isPlayerNumberCorrect)
        {
            playerNumber = std::stoi(playerAmount);
        }

    }while(playerNumber < 1 || playerNumber > 7 || !isPlayerNumberCorrect);

    playerNumber++;
    std::cout << std::endl;
}

void GameManager::SetPlayerName()
{

    std::cout << "PLEASE DO NOT USE CHAR IN NAME !" << std::endl;
    for (int i = 0; i < playerNumber - 1; ++i)
    {
        players[i] = new Player();
        bool isPlayerNameCorrect;

        do {
            isPlayerNameCorrect = true;
            std::string playerName;
            std::cout << "Enter " << i+1 << ". player's name : " << std::flush;
            std::cin >> playerName;

            for (auto c : playerName)
            {
                if (isdigit(c))
                {
                    std::cout << "You cannot use char in name!" << std::endl;
                    std::cout << std::endl;
                    isPlayerNameCorrect = false;
                    break;
                }
            }

            if(isPlayerNameCorrect)
            {
                players[i]->nickName = playerName;
            }

        } while (!isPlayerNameCorrect);
    }

    players[playerNumber-1] = new Player();
    players[playerNumber-1]->nickName = "Croupier";
}


void GameManager::FillUpWallet()
{
    bool isAcceptableMoney;
    std::cout << "You should enter minimum bet amount (10 Dolar) to take a seat at the table in Blackjack!" << std::endl;
    for(int i = 0; i < playerNumber-1; i++)
    {
        do
        {
            isAcceptableMoney = true;
            std::cout << players[i]->nickName << ", how much do you want to fill up the wallet : " << std::flush;
            std::cin >> players[i]->wallet;

            if (players[i]->wallet < minBet)
            {
                std::cout << "You have entered wrong amount of money! TRY AGAIN!" << std::endl;
                isAcceptableMoney = false;
            }

        }while(!isAcceptableMoney);
    }
}


void GameManager::PlaceBets()
{
    bool isBetAcceptable;

    for (auto player : players)
    {
        do
        {
            isBetAcceptable = true;
            std::cout << player->nickName << ", how much do you want to place as bet : " << std::flush;
            std::cin >> player->bet;

            if (player->bet >= minBet && player->bet <= maxBet)
            {
                std::cout << "Sorry, your bet amount is not acceptable!" << std::endl;
                std::cout << "You should place bet between 10 and 100.000!" << std::endl;
                isBetAcceptable = false;
                continue;
            }

            if (player->bet > player->wallet)
            {
                std::cout << "Sorry, you does not have enough money in your wallet!!" << std::endl;
                isBetAcceptable = false;
            }

        } while (!isBetAcceptable);
    }
}

void GameManager::DealInitialCard()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < playerNumber; ++j)
        {
            int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
            Card* cardHolder = cardDeck->GetDeck()[cardIndex];
            std::string cardValue = cardHolder->GetCardValue();
            players[j]->initialCardValues[i] = cardValue;
            cardDeck->GetDeck().erase(cardDeck->GetDeck().begin() + cardIndex);
            cardDeck->GetDeck().push_back(cardHolder);
            cardDeck->DecreaseCardNumber();
        }
    }
}

void GameManager::DealHitCard()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        CalculatePlayerInitialHand(i);
        bool isCardDealing = true;

        std::cout << std::endl;
        std::cout << players[i]->nickName << " point is : " << players[i]->point << std::endl;
        while (isCardDealing && players[i]->point < blackjack)
        {
            std::cout << players[i]->nickName << ", do you wanna hit card (1-> yes, 0-> no) : " << std::flush;
            std::cin >> isCardDealing;

            if (isCardDealing)
            {
                int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
                std::string card = cardDeck->GetDeck()[cardIndex]->GetCardValue();
                players[i]->point += ConvertCardToPoint(card);
                std::cout << "Your new point is : " << players[i]->point << std::endl;
                cardDeck->GetDeck().erase(cardDeck->GetDeck().begin() + cardIndex);
                cardDeck->DecreaseCardNumber();

                if(players[i]->point == blackjack)
                {
                    std::cout << "Congratulations! BLACKJACK !!" << std::endl;
                }

                else if (players[i]->point > blackjack)
                {
                    std::cout << "You Have Lost !! Better Luck Next Time." << std::endl;
                }
            }

        }
    }
}

void GameManager::CalculatePlayerInitialHand(int index)
{
    int point;
    if (players[index]->initialCardValues[0] == "A" && players[index]->initialCardValues[1] == "A")
    {
        std::cout << players[index]->nickName << " have 2 AS. You can choose 2, 12" << std::endl;
        std::cout << "Enter your point choice : " << std::flush;
        std::cin >> point;
    }

    else if (players[index]->initialCardValues[0] != "A" && players[index]->initialCardValues[1] == "A")
    {
        std::cout << players[index]->nickName << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(players[index]->initialCardValues[0]) << " or "
                  << 1 + ConvertCardToPoint(players[index]->initialCardValues[0]) << std::endl;
        std::cout << "Enter your point choice : " << std::flush;
        std::cin >> point;
    }

    else if (players[index]->initialCardValues[0] == "A" && players[index]->initialCardValues[1] != "A")
    {
        std::cout << players[index]->nickName << " have 1 AS. You can choose " << 11 + ConvertCardToPoint(players[index]->initialCardValues[1]) << " or "
                  << 1 + ConvertCardToPoint(players[index]->initialCardValues[1]) << std::endl;
        std::cout << "Enter your point choice : " << std::flush;
        std::cin >> point;
    }

    else
    {
        point = (ConvertCardToPoint(players[index]->initialCardValues[0]) + ConvertCardToPoint(players[index]->initialCardValues[1]));
    };

    players[index]->point = point;
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

void GameManager::DesignatePlayersLastState()
{
    int croupierValue = players[playerNumber-1]->point;
    std::string croupier = players[playerNumber-1]->nickName;
    playerNumber--;

    if (croupierValue > blackjack)
    {
        for (int i = 0; i < playerNumber; ++i)
        {
            if (players[i]->point > blackjack)
            {
                loserList.push_back(players[i]);
                continue;
            }

            else
            {
                winnerList.push_back(players[i]);
            }
        }
    }

    else
    {
        for (int i = 0; i < playerNumber; ++i)
        {
            if (players[i]->point > blackjack || players[i]->point < croupierValue)
            {
                loserList.push_back(players[i]);
            }

            else if (players[i]->point > croupierValue)
            {
                winnerList.push_back(players[i]);
            }

            else if (players[i]->point == croupierValue)
            {
                tiedPlayerList.push_back(players[i]);
            }
        }
    }
}

void GameManager::BetsPayOut()
{
    for (auto loser : loserList)
    {
        loser->wallet -= loser->bet;
    }

    for (auto winner : winnerList)
    {
        if (winner->point == blackjack)
        {
            winner->wallet += (winner->bet * (3/2));
        }

        else
        {
            winner->wallet += winner->bet;
        }
    }
}

void GameManager::PrintPlayersState()
{
    std::cout << "***** WINNER *****" << std::endl;
    for (auto winner : winnerList)
    {
        std::cout << winner->nickName << "  ";
    }

    std::cout << std::endl << "***** LOSER *****" << std::endl;
    for (auto loser : loserList)
    {
        std::cout << loser->nickName << "  ";
    }

    std::cout << std::endl << "***** TIED *****" << std::endl;
    for (auto tied : tiedPlayerList)
    {
        std::cout << tied->nickName << "  ";
    }

    std::cout << std::endl << std::endl;
}