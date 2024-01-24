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
            if (camera->cameraZoom < 100.0f)
                camera->cameraZoom += .1f * deltaTime;
        }
        if (event.key.keysym.sym == SDLK_m)
        {
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

    ////-------------------------first pass: bind new framebuffer--------------------
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // no stencil buffer
    glEnable(GL_DEPTH_TEST);
    //-------------------------draw scene in this framebuffer-----------------------------------
    objectShader->use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->cameraZoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    objectShader->setMat4("projection", glm::value_ptr(projection));
    objectShader->setMat4("view", glm::value_ptr(view));
    // light
    objectShader->setVec3("light.ambient", glm::vec3(.3f));
    objectShader->setVec3("light.diffuse", glm::vec3(0.7f));
    objectShader->setVec3("light.specular", glm::vec3(.2f));
    objectShader->setVec3("viewPos", camera->cameraPos);
    lightPos = glm::vec3(cos(lastFrame / 1000) * 2.f, 1.0f, sin(lastFrame / 1000) * 2.f);
    objectShader->setVec3("light.position", lightPos);
    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down
    objectShader->setMat4("model", glm::value_ptr(model));
    modelOne->Draw(*objectShader);

    ////-------------------------second pass: bind default framebuffer and draw textured quad--------------------
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(quadVAO);
    fbShader->use();
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, fbTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
    // Polygon mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    fbShader = new Shader("./include/shaders/fb.vert", "./include/shaders/fb.frag");

    // define quad
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    glEnable(GL_CULL_FACE);
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

void Game::GenTxtFramebuffer()
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // ---> color buffer (texture)
    glGenTextures(1, &fbTexture);
    glBindTexture(GL_TEXTURE_2D, fbTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // attach to fb as color attchmt
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbTexture, 0);
    // ---> depth and stencil buffer
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // attach to fb as depth and stencil attchmt
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    // check if framebuffer is complete and unbind
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Game::GenCubeMap()
{
    glGenTextures(1, &cmtexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cmtexture);
    // load images
    int width, height, nChannels;
    unsigned char *data;
    for (int i = 0; i < 6; i++)
    {
        data = stbi_load(texture_faces[i].c_str(), &width, &height, &nChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Game::Clean()
{
    ///@todo Adaptar cleaning a nueva estructura
    /* glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO); */
    glDeleteFramebuffers(1, &fbo);
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