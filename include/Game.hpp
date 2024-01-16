#ifndef Game_hpp
#define Game_hpp

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Shader.hpp"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    void Loadtexture(unsigned int *texture, const char *filename, GLenum format, unsigned int textureIndex, GLint mode);
    void GLMTransform();
    float vertexAttributes_plane[32] = {
        /*pos*/ -0.5, 0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0, /*txt*/ 0.0, 1.0,
        /*pos*/ 0.5, 0.5, 0.0, /*clr*/ 0.0, 0.5, 0.0, /*txt*/ 1.0, 1.0,
        /*pos*/ -0.5, -0.5, 0.0, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0, 0.0,
        /*pos*/ 0.5, -0.5, 0.0, /*clr*/ 0.3, 0.0, 0.3, /*txt*/ 1.0, 0.0};

    float vertexAttributes_cube[288] = {
        /*pos*/ -0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,
        /*pos*/ 0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ 0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ 0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ -0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ -0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,

        /*pos*/ -0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,
        /*pos*/ 0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ 0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ 0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ -0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ -0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,

        /*pos*/ -0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ -0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ -0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ -0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ -0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,
        /*pos*/ -0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,

        /*pos*/ 0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ 0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ 0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ 0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ 0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,
        /*pos*/ 0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,

        /*pos*/ -0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ 0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ 0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ 0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ -0.5f, -0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,
        /*pos*/ -0.5f, -0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,

        /*pos*/ -0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f,
        /*pos*/ 0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 1.0f,
        /*pos*/ 0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ 0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 1.0f, 0.0f,
        /*pos*/ -0.5f, 0.5f, 0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 0.0f,
        /*pos*/ -0.5f, 0.5f, -0.5f, /*clr*/ 0.0, 0.0, 0.5, /*txt*/ 0.0f, 1.0f};

    int vertexIndices_plane[6] = {
        0, 1, 2, 1, 2, 3};
    // Normalized device coordinates
    //                   | 1
    //                   |
    //  (-0.5, 0.5)      |       (0.5, 0.5)
    //         0         |          1
    //                   |
    //                   |
    //                   |
    //-1 -------------------------------- 1
    //                   |
    //                   |
    //                   |
    //         2         |          3
    //  (-0.5, -0.5)     |       (0.5, -0.5)
    //                   |
    //                   | -1

    // texture coordinates
    // |(0.0, 0.1)      (1.0, 1.0)
    // |+----------------+
    // ||    |      |    |
    // ||       --       |
    // ||  \__________/  |
    // |+----------------+__________
    //  (0.0, 0.0)      (1.0, 0.0)

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    Shader *shaderProgram;
    float count = 0.0f;
    unsigned int texture0;
    unsigned int texture1;

private:
    bool isRunning;
    SDL_Window *window;
    SDL_GLContext maincontext;
    SDL_Event event;
};

#endif /* Game_hpp */