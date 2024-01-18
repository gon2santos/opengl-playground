#include "Game.hpp"

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

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);
    for (int i = 0; i < 3; i++)
    {
        GLMTransform(cubPos[i], 1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(window);
}

void Game::Setup() // sets buffer objects and generates the shader program
{
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // importante que se bindee despues del VAO!
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices_plane), vertexIndices_plane, GL_STATIC_DRAW);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAttributes_cube), vertexAttributes_cube, GL_STATIC_DRAW);
    shaderProgram = new Shader("./include/shaders/vertexShader.vert", "./include/shaders/fragmentShader.frag");

    // glVertexAttribPointer(indice, cant de componentes por atributo, tipo del componente, normalizado?, stride, offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);                   // position attibute
    glEnableVertexAttribArray(0);                                                                    // habilitar este atributo (pos)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // color attibute
    glEnableVertexAttribArray(1);                                                                    // habilitar este atributo (color)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float))); // texture attibute
    glEnableVertexAttribArray(2);                                                                    // habilitar este atributo (texture)

    glEnable(GL_DEPTH_TEST);
}

void Game::Loadtexture(unsigned int *texture, const char *filename, GLenum format, unsigned int textureIndex, GLint mode)
{
    int width, height, nrChannels;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode); // GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
    stbi_set_flip_vertically_on_load(true);                            // set flip loaded image on the y-axis
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "LoadTexture: Failed to load image data." << std::endl;
    }
    stbi_image_free(data);

    std::ostringstream oss;
    oss << "texture" << textureIndex;
    std::string textureName = oss.str();

    shaderProgram->use();
    shaderProgram->setInt(textureName, textureIndex);
    std::cout << "set " + textureName + " unit" << std::endl;
}

void Game::GLMTransform(glm::vec3 loc, int ticks) // transformar (orden en codigo transladar -> rotar -> escalar)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 view;
    view = glm::lookAt(camera->cameraPos,                       // cameraPos(position)
                       camera->cameraPos + camera->cameraFront, // cameraPos + cameraFront(direction)
                       camera->cameraUp);                       // cameraUp(up vector)
    model = glm::translate(model, loc);
    proj = glm::perspective(glm::radians(-45.0f), 800.0f / 600.0f, 1.0f, 100.0f);

    shaderProgram->use();
    int modelLoc = glGetUniformLocation(shaderProgram->ID, "model");
    int viewLoc = glGetUniformLocation(shaderProgram->ID, "view");
    int projLoc = glGetUniformLocation(shaderProgram->ID, "proj");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}

void Game::UpdateFrameTiming()
{
    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::Clean()
{
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
