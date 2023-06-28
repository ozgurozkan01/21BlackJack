//
// Created by ozgur on 6/28/2023.
//

#include "Player.h"

Player::Player()
{
    point = 0;
    nickName = "";
    for (auto card : initialCards)
    {
        card = "";
    }
}