#ifndef Game_hpp
#define Game_hpp

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Shader.hpp"

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
    void InitBufferObjectsAndSetupShaders();

    float vertices[18] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };

    unsigned int VBO;
    unsigned int VAO;
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