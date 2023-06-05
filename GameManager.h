//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_GAMEMANAGER_H
#define INC_21BLACKJACK_GAMEMANAGER_H
#include <string>

class Card;

class GameManager {

    int oneTypeCardNumber;
    int totalCardNumber;
    Card* cards[];

public:

    GameManager();
};


#endif //INC_21BLACKJACK_GAMEMANAGER_H
