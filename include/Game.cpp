#include "Game.hpp"

//-----------------------------------------------------------------------------//
//////////////////////////// GAME CLASS /////////////////////////////////////////
//-----------------------------------------------------------------------------//

Game::Game()
{
    camera = new Camera();
}
Game::~Game()
{
}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    std::cout << "Initializing Subsystems..." << std::endl;
    int flags = 0;

    if (fullscreen)
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN /* | SDL_WINDOW_FULLSCREEN */;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
        std::cout << "Subsystems initialized!" << std::endl;
    else
        std::cout << "Error initializing Subsystems. Error: " << SDL_GetError() << std::endl;

    // Request opengl 3.3 context with core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Turn on double buffering with a 24bit Z buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    window = SDL_CreateWindow("OpenGL context window",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_OPENGL);
    if (!window)
        SDLDie("failed to create window ");

    maincontext = SDL_GL_CreateContext(window);

    if (!maincontext)
        SDLDie("failed to create context ");

    // INITIALIZE GLAD:
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        std::cout << "Failed to initialize GLAD" << std::endl;

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);

    glClearColor(0.1f, 0.1f, 0.12f, 0.3f);
    isRunning = true;
    return;
}

void Game::HandleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        // LogCameraPosition();
        if (event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        if (event.key.keysym.sym == SDLK_n)
        {
            std::cout << camera->cameraZoom << std::endl;
            if (camera->cameraZoom < 100.0f)
                camera->cameraZoom += .1f * deltaTime;
        }
        if (event.key.keysym.sym == SDLK_m)
        {
            std::cout << camera->cameraZoom << std::endl;
            if (camera->cameraZoom > 1.0f)
                camera->cameraZoom -= .1f * deltaTime;
        }
        if (event.key.keysym.sym == SDLK_w)
        {
            camera->Move(CAMERA_FORWARD, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_s)
        {
            camera->Move(CAMERA_BACKWARD, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_a)
        {
            camera->Move(CAMERA_LEFT, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_d)
        {
            camera->Move(CAMERA_RIGHT, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_UP) // pitch up
        {
            camera->Look(CAMERA_LOOK_UP, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_DOWN) // pitch down
        {
            camera->Look(CAMERA_LOOK_DOWN, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_LEFT) // yaw up
        {
            camera->Look(CAMERA_LOOK_LEFT, deltaTime);
        }
        if (event.key.keysym.sym == SDLK_RIGHT) // yaw down
        {
            camera->Look(CAMERA_LOOK_RIGHT, deltaTime);
        }
        break;
    default:
        break;
    }
}

void Game::Update()
{
}

void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->cameraZoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    objectShader->setMat4("projection", glm::value_ptr(projection));
    objectShader->setMat4("view", glm::value_ptr(view));

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down
    objectShader->setMat4("model", glm::value_ptr(model));
    modelOne->Draw(*objectShader);

    SDL_GL_SwapWindow(window);
}

/// @brief compile shaders and load models
void Game::Setup()
{
    std::cout << "Loading..." << std::endl;
    count = SDL_GetTicks();
    // build and compile shaders
    objectShader = new Shader("./include/shaders/colors.vert", "./include/shaders/colors.frag");
    // load models
    modelOne = new Model("./include/assets/objects/backpack/backpack.obj");
    std::cout << "Loading... OK! (" << (SDL_GetTicks() - count) << "ms)" << std::endl;
}

void Game::UpdateFrameTiming()
{
    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::LogCameraPosition()
{
    std::cout << "cameraFront: " << camera->cameraFront.x << ","
              << camera->cameraFront.y << ","
              << camera->cameraFront.z << ","
              << std::endl;
    std::cout << "cameraPos: " << camera->cameraPos.x << ","
              << camera->cameraPos.y << ","
              << camera->cameraPos.z << ","
              << std::endl;
    std::cout << "cameraUp: " << camera->cameraUp.x << ","
              << camera->cameraUp.y << ","
              << camera->cameraUp.z << ","
              << std::endl;
    std::cout << "pitch: " << camera->pitch
              << std::endl;
    std::cout << "yaw: " << camera->yaw
              << std::endl;
}

void Game::Clean()
{
    ///@todo Adaptar cleaning a nueva estructura
    /* glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO); */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    std::cout << "Subsystems cleaned" << std::endl;
}

void Game::SDLDie(const char *msg)
{
    std::cout << msg << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(1);
}