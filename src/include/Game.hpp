#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "stdio.h"

class Game{
    public:
        Game();
        ~Game();
        void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void HandleEvents();
        void Update();
        void Render();
        void Clean();
        bool Running(){ return isRunning; };
        bool LoadMedia();

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface* gPTCG = NULL;
        SDL_Surface* screenSurface = NULL;
        
        int count;
};


#endif /* Game_hpp */