//
// Created by ozgur on 6/5/2023.
//

#ifndef INC_21BLACKJACK_CARDDECK_H
#define INC_21BLACKJACK_CARDDECK_H

class Card;

class CardDeck {

    int oneTypeCardNumber;
    int totalCardNumberInDeck;
    int index;
    Card* deck[];

public:
    CardDeck();
/*    Card ** GetDeck();*/
};


#endif //INC_21BLACKJACK_CARDDECK_H
