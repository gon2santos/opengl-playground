// g++ -o main ./src/main.cpp ./src/glad.c ./include/Game.cpp -w -lSDL2 -lSDL2_image -g

#include "../include/Game.hpp"

Game *game = nullptr;

int main(int, char **)
{
    game = new Game();

    game->Init("CHIP-8 emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    game->InitBufferObjectsAndSetupShaders();

    while (game->Running())
    {
        game->HandleEvents();
        // game->Update();
        game->Render();
    }

    game->Clean();

    return 0;
}
