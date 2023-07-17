//
// Created by ozgur on 6/5/2023.
//

#include "Card.h"

Card::Card(std::string cardValue)
{
    value = cardValue;
}

std::string Card::getCardValue() {
    return value;
}
