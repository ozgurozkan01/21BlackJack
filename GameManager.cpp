#include "GameManager.h"
#include "CardDeck.h"
#include "Card.h"
#include "Player.h"
#include "Croupier.h"
#include <iostream>
#include <vector>
#include <unistd.h>

GameManager::GameManager()
{
    srand(time(nullptr));

    cardDeck = new CardDeck();
    playerNumber = 0.f;

    for (int i = 0; i < deckAmountToPlay; ++i)
    {
        for (auto card : cardDeck->GetDeck())
        {
            cardAmountToPlay.push_back(card);
        }
    }

    std::cout << "********** WELCOME TO 21 BLACKJAKE GAME **********" << std::endl;
    std::cout << "***************** BEST OF LUCK! ******************" << std::endl;
}

void GameManager::BeginPlay()
{
    SetPlayerNumber();
    SetPlayerName();
    FillUpWallet();
}

void GameManager::Tick()
{
    PlaceBets();
    DealInitialCard();
    DealHitCard();
    DesignatePlayersLastState();
    PrintPlayersState();
    GameRoundEnd();
    NewRoundTimer();

    if(cardDeck->ShouldDeckShuffle())
    {
        cardDeck->ShuffleCardDeck();
    }
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
                std::cout << "You cannot enter anything but number!" << std::endl;
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

    std::cout << "PLEASE DO NOT USE DIGIT IN NAME !" << std::endl;
    for (int i = 0; i < mainPlayerNumber; ++i)
    {
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
                mainPlayers[i] = new Player();
                mainPlayers[i]->nickName = playerName;
                players[i] = mainPlayers[i];
            }

        } while (!isPlayerNameCorrect);
    }

    croupier = new Croupier();
    players[playerNumber-1] = croupier;
    players[playerNumber-1]->nickName = "Croupier";
}


void GameManager::FillUpWallet()
{
    bool isAcceptableMoney;
    std::cout << "You should enter minimum bet amount (10 Dolar) to take a seat at the table in Blackjack!" << std::endl;

    for(int i = 0; i < mainPlayerNumber; i++)
    {
        do
        {
            isAcceptableMoney = true;
            std::cout << mainPlayers[i]->nickName << ", how much do you want to fill up the wallet : " << std::flush;
            std::cin >> mainPlayers[i]->wallet;

            if (mainPlayers[i]->wallet < minBet)
            {
                std::cout << "You have entered wrong amount of money! TRY AGAIN!" << std::endl;
                isAcceptableMoney = false;
            }

        }while(!isAcceptableMoney);
    }

    std::cout << std::endl;
}


void GameManager::PlaceBets()
{
    bool isBetAcceptable;

    for (int i = 0; i < mainPlayerNumber; ++i)
    {
        do
        {
            isBetAcceptable = true;
            std::cout << mainPlayers[i]->nickName << ", how much do you want to place as bet : ";
            std::cin >> mainPlayers[i]->bet;

            if (mainPlayers[i]->bet < minBet || mainPlayers[i]->bet > maxBet)
            {
                std::cout << "Sorry, your bet amount is not acceptable!" << std::endl;
                std::cout << "You should place bet between 10 and 100.000!" << std::endl;
                isBetAcceptable = false;
                continue;
            }

            if (mainPlayers[i]->bet > mainPlayers[i]->wallet)
            {
                std::cout << "Sorry, you does not have enough money in your wallet!!" << std::endl;
                std::cout << "Current Wallet : " << mainPlayers[i]->wallet << std::endl;
                isBetAcceptable = false;
            }

        } while (!isBetAcceptable);
    }
}


std::string GameManager::GetDealCard()
{
    int cardIndex = rand() % cardDeck->GetRestOfCardNumber();
    Card* cardHolder = cardDeck->GetDeck()[cardIndex];
    std::string cardValue = cardHolder->GetCardValue();
    cardDeck->GetDeck().erase(cardDeck->GetDeck().begin() + cardIndex);
    cardDeck->GetDeck().push_back(cardHolder);
    cardDeck->DecreaseCardNumber();
    return cardValue;
}

void GameManager::DealInitialCard()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < playerNumber; ++j)
        {
            std::string cardValue = GetDealCard();
            players[j]->initialCardValues[i] = cardValue;
        }
    }
}

void GameManager::DealHitCard()
{
    for (int i = 0; i < playerNumber; ++i)
    {
        CalculatePlayerInitialHand(i);
        bool isCardDealing = false;

        std::cout << std::endl;
        std::cout << players[i]->nickName << " point is : " << players[i]->point << std::endl;

        do {

            std::cout << players[i]->nickName << ", do you wanna hit card (1-> yes, 0-> no) : " << std::flush;
            std::cin >> isCardDealing;

            if (isCardDealing)
            {
                std::string cardValue = GetDealCard();
                players[i]->point += ConvertCardToPoint(cardValue);
                std::cout << "Your new point is : " << players[i]->point << std::endl;

                if (players[i]->point == blackjack)
                {
                    std::cout << "Congratulations! BLACKJACK !!" << std::endl;
                }

                else if (players[i]->point > blackjack)
                {
                    std::cout << "You Have Lost !! Better Luck Next Time." << std::endl;
                }
            }

            if (players[i]->nickName == croupier->nickName && players[i]->point < 17 && !isCardDealing)
            {
                isCardDealing = true;
                std::cout << "You are CROUPIER and your point is less than 17" << std::endl;
                std::cout << "You have to want to card to get through 17 point !!" << std::endl;
            }

            std::cout << std::endl;

        }while (isCardDealing && players[i]->point < blackjack);
    }
}

bool GameManager::DoesHandHaveACE(int index)
{
    if (players[index]->initialCardValues[0] == "A" || players[index]->initialCardValues[1] == "A") { return true;}

    return false;
}

void GameManager::CalculatePlayerInitialHand(int index)
{
    int point = 0;
    int value1 = 0;
    int value2 = 0;

    bool isPointChoiceCorrect = false;

    if(DoesHandHaveACE(index))
    {
        if (players[index]->initialCardValues[0] == "A" && players[index]->initialCardValues[1] == "A")
        {
            value1 = 2;
            value2 = 12;
            std::cout << players[index]->nickName << " have 2 AS. You can choose 2, 12" << std::endl;
        }

        else if (players[index]->initialCardValues[0] != "A" && players[index]->initialCardValues[1] == "A")
        {
            value1 = 11 + ConvertCardToPoint(players[index]->initialCardValues[0]);
            value2 = 1 + ConvertCardToPoint(players[index]->initialCardValues[0]);
            std::cout << players[index]->nickName << " have 1 AS. You can choose " << value1 << " or " << value2 << std::endl;
        }

        else if (players[index]->initialCardValues[0] == "A" && players[index]->initialCardValues[1] != "A")
        {
            value1 = 11 + ConvertCardToPoint(players[index]->initialCardValues[1]);
            value2 = 1 + ConvertCardToPoint(players[index]->initialCardValues[1]);
            std::cout << players[index]->nickName << " have 1 AS. You can choose " << value1 << " or "
                      << value2 << std::endl;
        }

        do {
            std::cout << "Enter your point choice : ";
            std::cin >> point;

            if (point == value1 || point == value2)
            {
                isPointChoiceCorrect = true;
            }

            else
            {
                std::cout << "You cannot choose this point !! Try again!" << std::endl;
            }

        }while(!isPointChoiceCorrect);
    }

    else
    {
        point = (ConvertCardToPoint(players[index]->initialCardValues[0]) + ConvertCardToPoint(players[index]->initialCardValues[1]));
    }

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
    if (croupier == nullptr) return;

    int croupierValue = croupier->point;
    std::string croupierName = croupier->nickName;
    playerNumber--;

    if (croupierValue > blackjack)
    {
        for (int i = 0; i < playerNumber; ++i)
        {
            if (mainPlayers[i]->point > blackjack)
            {
                loserList.push_back(mainPlayers[i]);
                DecrementWallet(mainPlayers[i]);
                continue;
            }

            else
            {
                winnerList.push_back(mainPlayers[i]);
                IncrementWallet(mainPlayers[i]);
            }
        }
    }

    else
    {
        for (int i = 0; i < playerNumber; ++i)
        {
            if (mainPlayers[i]->point > blackjack || mainPlayers[i]->point < croupierValue)
            {
                loserList.push_back(mainPlayers[i]);
                DecrementWallet(mainPlayers[i]);
            }

            else if (mainPlayers[i]->point > croupierValue)
            {
                winnerList.push_back(mainPlayers[i]);
                IncrementWallet(mainPlayers[i]);
            }

            else if (mainPlayers[i]->point == croupierValue)
            {
                tiedPlayerList.push_back(mainPlayers[i]);
            }
        }
    }
}

void GameManager::PrintPlayersState()
{
    std::cout << "***** WINNER *****" << std::endl;
    for (auto winner : winnerList)
    {
        std::cout << "NAME : " << winner->nickName << ", WALLET : " << winner->wallet << std::endl;
    }

    std::cout << std::endl << "***** LOSER *****" << std::endl;
    for (auto loser : loserList)
    {
        std::cout << "NAME : " << loser->nickName << ", WALLET : " << loser->wallet << std::endl ;
    }

    std::cout << std::endl << "***** TIED *****" << std::endl;
    for (auto tied : tiedPlayerList)
    {
        std::cout << "NAME : " << tied->nickName << ", WALLET : " << tied->wallet << std::endl;
    }

    std::cout << std::endl << std::endl;
}

void GameManager::GameRoundEnd()
{
    std::cout << "This round ended! New round will start after 5 seconds!" << std::endl;
}

void GameManager::NewRoundTimer()
{
    const int newRoundBeginningTime = 5;
    int timer = newRoundBeginningTime;

    winnerList.clear();
    loserList.clear();
    tiedPlayerList.clear();

    for (int i = 0; i < newRoundBeginningTime; ++i)
    {
        std::cout << "Time Remaining : " << timer << std::endl;
        timer--;
        sleep(1);
    }

    system("cls");

    std::cout << std::endl;
    std::cout << "********** Welcome To New BlackJack Round !! **********" << std::endl;
    std::cout << "    **************** Best Of Luck!! ****************" << std::endl;
    playerNumber++;
}

void GameManager::IncrementWallet(Player* mainPlayer)
{
    if(mainPlayer->point == blackjack)
    {
        mainPlayer->wallet += (mainPlayer->bet * 2);
        return;
    }

    mainPlayer->wallet += mainPlayer->bet;
}

void GameManager::DecrementWallet(Player* mainPlayer)
{
    mainPlayer->wallet -= mainPlayer->bet;
}