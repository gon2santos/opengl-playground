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
    else
    {
        std::cout << "Error initializing Subsystems. Error: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
    {
        screenSurface = SDL_GetWindowSurface(window);
    }
    else
    {
        std::cout << "Error initializing window" << SDL_GetError() << std::endl;
    }
    /* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
    {
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    } 
    else
    {
        std::cout << "Error initializing renderer" << SDL_GetError() << std::endl;
    }*/
    isRunning = true;
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
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
    // SDL_RenderClear(renderer);
    //  aca agregar cosas a renderear...
    // SDL_RenderPresent(renderer);
    //  Apply the image
    SDL_BlitSurface(gPTCG, NULL, screenSurface, NULL);
    // Update the surface
    SDL_UpdateWindowSurface(window);
}

void Game::Clean()
{
    // Deallocate surface
    SDL_FreeSurface(gPTCG);
    gPTCG = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_Quit();
    std::cout << "Subsystems cleaned" << std::endl;
}

bool Game::LoadMedia()
{
    // Loading success flag
    bool success = true;

    const char *path = "../assets/pocketTCG.bmp";

    // Load splash image
    gPTCG = SDL_LoadBMP(path);
    if (gPTCG == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        success = false;
    }

    return success;
}
