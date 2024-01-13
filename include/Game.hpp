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
    void InitBufferObjectsAndSetupShaders();

    float vertices[36] = {
        // rectangulo
        // positions         // colors
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top left (first)
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // top right (first)
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right (first)
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top left (second)
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left (second)
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // bottom right (second)
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