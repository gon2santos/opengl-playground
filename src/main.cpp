#include "./include/Game.hpp"

Game *game = nullptr;

int main(int, char**){
    game = new Game();

    game->Init("CHIP-8 emulator", 0, 0, 600, 400, false);

    while(game->Running()){
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();

    return 0;
}
