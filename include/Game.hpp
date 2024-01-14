#ifndef Game_hpp
#define Game_hpp

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Shader.hpp"
#include "stb_image.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

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
    void SDLDie(const char *msg);
    void Setup();
    float vertexAttributes[24] = {
        /*pos*/ -0.5, 0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0,
        /*pos*/ 0.5, 0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0,
        /*pos*/ -0.5, -0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0,
        /*pos*/ 0.5, -0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0};

    int vertexIndices[6] = {
        0, 1, 2, 1, 2, 3};

    //                  | 1
    //                  |
    // (-0.5, 0.5)      |       (0.5, 0.5)
    //        0         |          1/5
    //                  |
    //                  |
    //                  |
    //-1 -------------------------------- 1
    //                  |
    //                  |
    //                  |
    //        2/3       |          4
    // (-0.5, -0.5)     |       (0.5, -0.5)
    //                  |
    //                  | -1

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    Shader *shaderProgram;
    float count = 0;

private:
    bool isRunning;
    SDL_Window *window;
    SDL_GLContext maincontext;
    SDL_Event event;
};

#endif /* Game_hpp */