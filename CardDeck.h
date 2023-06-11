//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_CARDDECK_H
#define INC_21BLACKJACK_CARDDECK_H

#include <vector>

class Card;

class CardDeck {

    int oneTypeCardNumber;
    int totalCardNumberInDeck;
    int index;
    std::vector<Card*> deck;

public:
    CardDeck();
    std::vector<Card*>& GetDeck(); 
    int GetRestOfCardNumber();
    void DecreaseCardNumber();
};


#endif //INC_21BLACKJACK_CARDDECK_H
