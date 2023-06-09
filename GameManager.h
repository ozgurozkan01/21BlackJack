//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <vector>
#include <string>

#define playerNumberWithCroupier  8 // including croupier
#define mainPlayerNumber 7
#define blackjack 21

class Card;
class CardDeck;
class BasePlayer;
class Player; 
class Croupier;

class GameManager {

    BasePlayer* players[playerNumberWithCroupier]{};
    Player* mainPlayers[mainPlayerNumber]{};
    Croupier* croupier;
    CardDeck* cardDeck;

    std::vector<Player*> winnerList;
    std::vector<Player*> loserList;
    std::vector<Player*> tiedPlayerList;
    std::vector<Card*> cardAmountToPlay;

    int playerNumber;
    const int minBet = 10;
    const int maxBet = 10000;
    const int deckAmountToPlay = 5;

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
    bool DoesHandHaveACE(int index);
    void CalculatePlayerInitialHand(int index);

    // Hit Part
    void DealHitCard();

    static int ConvertCardToPoint(std::string& card);
    void DesignatePlayersLastState();
    void IncrementWallet(Player* mainPlayer);
    void DecrementWallet(Player* mainPlayer);

    void PrintPlayersState();
    static void GameRoundEnd();
    void NewRoundTimer();
    std::string GetDealCard();
};

#endif //INC_21BLACKJACK_GAMEMANAGER_H