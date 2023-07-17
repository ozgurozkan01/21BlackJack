#include "GameManager.h"
int main() {

    GameManager* gameManager = new GameManager();

    gameManager->start();

    while(true)
    {
        gameManager->update();
    }

    return 0;
}
