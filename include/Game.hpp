#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "glad/glad.h"
#include <SDL2/SDL_image.h>
// #include <GL/gl.h> //modo inmediato como glBegin o glColor3f, no usar

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
    bool LoadMedia();
    bool InitPNGLoad();
    SDL_Texture *LoadTexture(std::string path);
    SDL_Texture *gTexture = NULL;
    SDL_Texture *viewportTexture = NULL;
    SDL_Rect smallvpRect;
    SDL_Rect fullvpRect;
    bool LoadMediaAsTexture();
    bool InitSmallViewport();
    bool InitFullViewport();
    void SDLDie(const char *msg);
    void InitBufferObjectsAndSetupShaders();

    void SetDefaultMedia();

    SDL_Surface *LoadSurface(std::string path, std::string format);
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

    SDL_Rect stretchRect;

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
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *sdl_renderer;
    SDL_GLContext maincontext;
    SDL_Surface *gPTCG = NULL;
    SDL_Surface *gScreenSurface = NULL;
    SDL_Event event;
    int count;
};

#endif /* Game_hpp */