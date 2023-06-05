//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <string>

class CardDeck;

class GameManager {

    CardDeck* cardDeck;
    int playerAmount;
public:

    GameManager();
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
