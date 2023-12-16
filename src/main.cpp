#include "./include/Game.hpp"

Game *game = nullptr;

int main(int, char **)
{
    game = new Game();

    game->Init("CHIP-8 emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

    if (!game->LoadMedia())
    {
        printf("Failed to load media!\n");
    }
    else
    {
        game->Render();
    }

    while (game->Running())
    {
        game->HandleEvents();
        //game->Update();
        //game->Render();
    }

    game->Clean();

    return 0;
}
