//g++ -o main ./src/main.cpp ./src/include/Game.cpp -w -lSDL2 -lSDL2_image -g

#include "./include/Game.hpp"

Game *game = nullptr;

int main(int, char **)
{
    game = new Game();

    game->Init("CHIP-8 emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

    game->InitPNGLoad();

    if (!game->LoadMediaAsTexture())
    {
        printf("Failed to load media as texture!\n");
    }

    /* if (!game->LoadMedia())
    {
        printf("Failed to load media!\n");
    }
    else
    {
        //set default surface
        game->SetDefaultMedia();
    } */

    while (game->Running())
    {
        game->HandleEvents();
        //game->Update();
        game->Render();
    }

    game->Clean();

    return 0;
}
