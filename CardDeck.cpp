//
// Created by ozgur on 6/5/2023.
//

#include "CardDeck.h"
#include "Card.h"
#include <iostream>
std::string validCardValues[] = {"A", "2", "3", "4", "5", "6",
                                 "7", "8", "9", "10", "J", "Q", "K"};

CardDeck::CardDeck()
{
    totalCardNumberInDeck = 52;
    index = 0;
    oneTypeCardNumber = totalCardNumberInDeck / (sizeof(validCardValues) / sizeof(validCardValues[0]));
    
    for (int i = 0; i < sizeof(validCardValues) / sizeof(validCardValues[0]); i++)
    {
        for (int j = 0; j < oneTypeCardNumber; ++j)
        {
            deck.push_back(new Card(validCardValues[i]));
            std::string cardValue = (*(deck.begin() + index))->GetCardValue();
            index++;
        }
    }
}

std::vector<Card*>& CardDeck::GetDeck()
{
    return deck;
}

void CardDeck::DecreaseCardNumber()
{
    totalCardNumberInDeck--;
}

int CardDeck::GetRestOfCardNumber() {
    return totalCardNumberInDeck;
}
