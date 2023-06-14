//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <vector>
#include <string>

#define maxPlayerNumber  8 // including croupier
#define initialHandCardNumber  2

class CardDeck;

class GameManager {



    CardDeck* cardDeck;

    // Player
    int playerNumber;
    std::vector<std::string> playersName;
    std::string playersInitialCards[maxPlayerNumber][initialHandCardNumber];
    std::vector<int> playersPoint;

    std::vector<std::string> exactLosers;
    std::vector<std::string> exactWinners;
    std::vector<std::string> tiedPlayers;

public:

    GameManager();
    void BeginPlay();
    void Tick();

    void SetPlayerNumber();
    void SetPlayerName();

    // Initial Part
    void DealInitialCard();
    int CalculatePlayerInitialHand(std::string* card, std::string& name, int& point);

    // Hit Part
    void DealHitCard();

    void DesignatePlayersWinState();

    int ConvertCardToPoint(std::string& card);
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
