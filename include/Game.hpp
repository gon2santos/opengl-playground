#ifndef Game_hpp
#define Game_hpp

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "assets/models.hpp"

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
    void UpdateFrameTiming();
    void LogCameraPosition();
    void GenTxtFramebuffer();
    unsigned int GenCubeMap(vector<std::string> faces);

    Shader *objectShader = nullptr;
    Shader *fbShader = nullptr;
    Shader *cmShader = nullptr;
    Model *modelOne;
    float count = 0.0f;

    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    glm::vec3 lightPos = glm::vec3(0.f, 1.0f, 0.f);

    unsigned int fbo;       // framebuffer obj
    unsigned int rbo;       // renderbuffer obj for stencil and depth buffering
    unsigned int fbTexture; // framebuffer texture for color buffering
    // framebuffer quad
    unsigned int quadVAO, quadVBO;
    // cube map
    unsigned int cmVAO, cmVBO;
    unsigned int cmtexture;

    vector<std::string> texture_faces = {
        "./include/assets/skybox/right.jpg",
        "./include/assets/skybox/left.jpg",
        "./include/assets/skybox/top.jpg",
        "./include/assets/skybox/bottom.jpg",
        "./include/assets/skybox/front.jpg",
        "./include/assets/skybox/back.jpg"};

    Camera *camera = nullptr;

    float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

private:
    bool isRunning;
    SDL_Window *window;
    SDL_GLContext maincontext;
    SDL_Event event;
};

#endif /* Game_hpp */