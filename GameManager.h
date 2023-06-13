//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <vector>
#include <string>

#define maxPlayerNumber  7 // including croupier
#define initialHandCardNumber  2

class CardDeck;

class GameManager {



    CardDeck* cardDeck;

    // Player
    int playerNumber;
    std::vector<std::string> playersName;
    std::string playersInitialCards[maxPlayerNumber][initialHandCardNumber];
    int playersPoint[maxPlayerNumber];

    // Croupier
    std::string croupierName;
    std::string croupierInitalCards[initialHandCardNumber];
    int croupierPoint;

    std::vector<std::string> exactLosers;

public:

    GameManager();
    void BeginPlay();
    void Tick();

    void SetPlayerNumber();
    void SetPlayerName();

    // Initial Part
    void DealInitialCard();
    void CalculatePlayerInitialHand(int & index);

    // Hit Part
    void DealHitCard();

    void DesignatePlayersWinOrLose();

    int ConvertCardToPoint(std::string& card);
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
