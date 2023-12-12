#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <iostream>

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

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
};


#endif /* Game_hpp */