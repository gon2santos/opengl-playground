// g++ -O0 -o main ./src/main.cpp ./src/glad.c ./include/Game.cpp ./include/Shader.cpp ./include/stb_image.cpp ./include/Camera.cpp -w -lSDL2 -g

#include "../include/Game.hpp"
Game *game = nullptr;
int main(int, char **)
{
    game = new Game();
    game->Init("CHIP-8 emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    game->Setup();

    while (game->Running())
    {
        game->UpdateFrameTiming();
        game->HandleEvents();
        // game->Update();
        game->Render();
    }
    game->Clean();
    return 0;
}
