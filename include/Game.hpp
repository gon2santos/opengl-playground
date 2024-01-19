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
#include "Camera.hpp"
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

    unsigned int VBO, cubeVAO, lightCubeVAO;
    // unsigned int EBO;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    Shader *lightingShader;
    Shader *lightCubeShader;
    float count = 0.0f;
    unsigned int texture0;
    unsigned int texture1;

    glm::vec3 cubPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    Camera *camera = nullptr;

private:
    bool isRunning;
    SDL_Window *window;
    SDL_GLContext maincontext;
    SDL_Event event;
};

#endif /* Game_hpp */