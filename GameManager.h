//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <string>

#define maxPlayerNumber 7

class CardDeck;

class GameManager {

    CardDeck* cardDeck;
    int playerNumber;
    std::string playersName[maxPlayerNumber];
    std::string playersCards[maxPlayerNumber][2];
    int playersPoints[maxPlayerNumber];
public:

    GameManager();
    void BeginPlay();
    void Tick();

    void SetPlayerNumber();
    void SetPlayerName();

    //Initial Part
    void DealInitialCard();
    void CalculatePlayerInitialHand();

    void DealHitCard();

    int ConvertCardToPoint(std::string& card);
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
