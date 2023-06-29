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
class Player;

class GameManager {

    Player* players[maxPlayerNumber];
    CardDeck* cardDeck;

    int playerNumber;

    std::vector<std::string> exactWinnerList;
    std::vector<std::string> exactLoserList;
    std::vector<std::string> tiedPlayerList;

public:

    GameManager();
    void BeginPlay();
    void Tick();

    void SetPlayerNumber();
    void SetPlayerName();
    void PlaceBets();

    // Initial Part
    void DealInitialCard();
    void CalculatePlayerInitialHand(int index);

    // Hit Part
    void DealHitCard();

    void DesignateUnknownStatePlayer();
    int ConvertCardToPoint(std::string& card);
    void PrintPlayersState();
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
