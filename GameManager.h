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
    int playerNumber;
    std::vector<std::string> playersName;
    std::string playersInitialCards[maxPlayerNumber][initialHandCardNumber];
    int playersPoint[maxPlayerNumber];

    std::vector<std::string> exactLosers;


public:

    GameManager();
    void BeginPlay();
    void Tick();

    void SetPlayerNumber();
    void SetPlayerName();

    // Initial Part
    void DealInitialCard();
    void CalculatePlayerInitialHand();

    // Hit Part
    void DealHitCard();

    void DesignatePlayersWinOrLose();

    int ConvertCardToPoint(std::string& card);
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
