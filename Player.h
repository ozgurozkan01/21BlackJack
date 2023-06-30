//
// Created by ozgur on 6/28/2023.
//

#ifndef INC_21BLACKJACK_PLAYER_H
#define INC_21BLACKJACK_PLAYER_H

#include "BasePlayer.h"
#include <iostream>


class Player : public BasePlayer{

public:
    int wallet;
    int bet;

    Player();
};


#endif //INC_21BLACKJACK_PLAYER_H
