//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_CARD_H
#define INC_21BLACKJACK_CARD_H
#include <string>

class Card {
    std::string value;

public:

    Card(std::string cardValue);
    std::string getCardValue();
};


#endif //INC_21BLACKJACK_CARD_H
