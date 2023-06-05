//
// Created by ozgur on 6/5/2023.
//

#include "GameManager.h"
#include "Card.h"
#include <iostream>

std::string validCardValues[] = {"A", "2", "3", "4", "5", "6",
                                 "7", "8", "9", "10", "J", "Q", "K"};

GameManager::GameManager()
{
    totalCardNumber = 104;
    oneTypeCardNumber = totalCardNumber / (sizeof(validCardValues) / sizeof(validCardValues[0]));

    for (int i = 0; i < totalCardNumber; ++i)
    {
        cards[i] = new Card(validCardValues[]);
    }
}
