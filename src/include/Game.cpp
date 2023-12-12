#include "Game.hpp"

Game::Game()
{
}
Game::~Game()
{
}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    std::cout << "Initializing Subsystems..." << std::endl;
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
        if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
        {
            std::cout << "Subsystems initialized" << std::endl;
        }
        else{
            std::cout << "Error initializing Subsystems" << std::endl;
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
        }
        else{
            std::cout << "Error initializing renderer" << std::endl;
        }
        
        isRunning = true;

    /* SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(3000); */
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
        isRunning = false;
        break;
        default:
        break;
    }
}

void Game::Update()
{
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    //aca agregar cosas a renderear
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Subsystems cleaned" << std::endl;
}
