//
// Created by ozgur on 6/28/2023.
//

#ifndef INC_21BLACKJACK_PLAYER_H
#define INC_21BLACKJACK_PLAYER_H

#include <iostream>
#define initialHandCardNumber  2

class Player {

public:

    int point;
    std::string nickName;
    std::string initialCardValues[initialHandCardNumber];
    int wallet;
    int bet;

    Player();
};


#endif //INC_21BLACKJACK_PLAYER_H
