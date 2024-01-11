#ifndef Game_hpp
#define Game_hpp

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <iostream>

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

    SDL_Surface *gKeyPressSurfaces[5];
    SDL_Surface *gCurrentSurface = NULL;

    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};
    unsigned int VBO;
    unsigned int VAO;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "out vec4 vertexcolor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "   vertexcolor = vec4(0.2f, 0.0f, 0.3f, 0.1f);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec4 vertexcolor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "FragColor = vertexcolor;\n"
                                       "}\0";

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *sdl_renderer;
    SDL_GLContext maincontext;
    SDL_Event event;
    int count;
};

#endif /* Game_hpp */