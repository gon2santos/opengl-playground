// g++ (-O0 sin optimizacion, para debug) -o main ./src/main.cpp ./src/glad.c ./include/Game.cpp ./include/Shader.cpp ./include/stb_image.cpp ./include/Camera.cpp -w -lSDL2 (-g agregar debug symbols)
#include "../include/Game.hpp"
Game *game = nullptr;
int main(int, char **)
{
    game = new Game();
    game->Init("CHIP-8 emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    game->Setup();

    game->Loadtexture(&game->texture0, "./include/assets/container2.png", GL_RGBA, 0, GL_CLAMP_TO_EDGE);
    game->Loadtexture(&game->texture1, "./include/assets/container2_specular.png", GL_RGBA, 1, GL_CLAMP_TO_EDGE);

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
