//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_CARDDECK_H
#define INC_21BLACKJACK_CARDDECK_H

#include <vector>

class Card;

class CardDeck {

    const int minCardNumberToShuffle = 50;
    int oneTypeCardNumber;
    int totalCardNumberInDeck;
    int currentCardNumberInDeck;
    int index;
    std::vector<Card*> deck;

public:

    CardDeck();

    std::vector<Card*>& getDeck();
    int getRestOfCardNumber();
    void decreaseCardNumber();
    void shuffleCardDeck();
    bool shouldDeckShuffle();
};


#endif //INC_21BLACKJACK_CARDDECK_H
