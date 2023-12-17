#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "stdio.h"
#include <SDL2/SDL_image.h>
#include <string>

class Game
{
public:
    Game();
    ~Game();
    void Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool Running() { return isRunning; };
    bool LoadMedia();
    bool InitPNGLoad();
    SDL_Texture* LoadTexture( std::string path );
    SDL_Texture* gTexture = NULL;
    bool LoadMediaAsTexture();

    void SetDefaultMedia();

    SDL_Surface* LoadSurface( std::string path, std::string format );
    SDL_Surface* gKeyPressSurfaces[ 5 ];
    SDL_Surface* gCurrentSurface = NULL;

    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
    
    SDL_Rect stretchRect;

private:
    bool isRunning;
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    SDL_Surface *gPTCG = NULL;
    SDL_Surface *gScreenSurface = NULL;
    SDL_Event event;

    

    int count;
};

#endif /* Game_hpp */