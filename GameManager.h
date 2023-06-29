//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <vector>
#include <string>

#define maxPlayerNumber  8 // including croupier
#define blackjack 21


class CardDeck;
class Player;

class GameManager {

    Player* players[maxPlayerNumber];
    CardDeck* cardDeck;

    int playerNumber;

    const int minBet = 10;
    const int maxBet = 10000;

    std::vector<Player*> winnerList;
    std::vector<Player*> loserList;
    std::vector<Player*> tiedPlayerList;

public:

    GameManager();
    void BeginPlay();
    void Tick();

    void SetPlayerNumber();
    void SetPlayerName();
    void FillUpWallet();
    void PlaceBets();

    // Initial Part
    void DealInitialCard();
    void CalculatePlayerInitialHand(int index);

    // Hit Part
    void DealHitCard();

    int ConvertCardToPoint(std::string& card);
    void DesignatePlayersLastState();
    void BetsPayOut();
    void PrintPlayersState();
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
