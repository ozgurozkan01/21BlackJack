//
// Created by ozgur on 6/4/2023.
//

#ifndef INC_21BLACKJACK_CARD_H
#define INC_21BLACKJACK_CARD_H

#include <string>
std::string cardValues[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                            "J", "Q", "K"};
const int cardAmount = 104;

class Card {

public:
    std::string value;

    Card(std::string cardValue);
};


#endif //INC_21BLACKJACK_CARD_H
