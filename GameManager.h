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
    ~GameManager();
    void start();
    void update();
    static void gameRoundEnd();
    static int convertCardToPoint(std::string& card);
    void setPlayerNumber();
    void setPlayerName();
    void fillUpWallet();
    void placeBets();
    void dealInitialCard();
    bool doesHandHaveACE(int index);
    void calculatePlayerInitialHand(int index);
    void dealHitCard();
    void designatePlayersLastState();
    void incrementWallet(Player* mainPlayer);
    void decrementWallet(Player* mainPlayer);
    void printPlayersState();
    void newRoundTimer();
    std::string getDealCard();
};

#endif //INC_21BLACKJACK_GAMEMANAGER_H