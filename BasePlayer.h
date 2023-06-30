//
// Created by ozgur on 6/30/2023.
//

#ifndef INC_21BLACKJACK_BASEPLAYER_H
#define INC_21BLACKJACK_BASEPLAYER_H
#include <iostream>
#define initialHandCardNumber  2

class BasePlayer {

public:
    int point;
    std::string nickName;
    std::string initialCardValues[initialHandCardNumber];

    BasePlayer();
};


#endif //INC_21BLACKJACK_BASEPLAYER_H
