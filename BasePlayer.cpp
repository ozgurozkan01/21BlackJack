//
// Created by ozgur on 6/30/2023.
//

#include "BasePlayer.h"

BasePlayer::BasePlayer()
{
    point = 0;
    nickName = "";
    for (auto card : initialCardValues)
    {
        card = "";
    }
}
