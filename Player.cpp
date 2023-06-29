//
// Created by ozgur on 6/28/2023.
//

#include "Player.h"
#include "Card.h"
Player::Player()
{
    point = 0;
    nickName = "";
    for (auto card : initialCardValues)
    {
        card = "";
    }
    wallet = 0;
    bet = 0;
}