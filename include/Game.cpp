#include "Game.hpp"

Game::Game()
{
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

    glClearColor(0.2f, 0.2f, 0.0f, 0.5f);
    isRunning = true;
    return;
}

void Game::HandleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
    case SDL_KEYDOWN:
        isRunning = false;
        break;
    /* case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_UP)
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
        if (event.key.keysym.sym == SDLK_DOWN)
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
        if (event.key.keysym.sym == SDLK_LEFT)
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
        if (event.key.keysym.sym == SDLK_RIGHT)
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
        // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
        SDL_UpdateWindowSurface(window);
        break; */
    default:
        break;
    }
}

void Game::Update()
{
}

void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // float elapsedTime = SDL_GetTicks() / 1000.0; // elapsed time in seconds since sdl init
    // float greenValue = (sin(elapsedTime) / 2.0f) + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(shaderProgram, "dnmcolor");
    shaderProgram->use();
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
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

void Game::InitBufferObjectsAndSetupShaders()
{

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    shaderProgram = new Shader("./shaders/vertexShader.vs", "./shaders/fragmentShader.fs");

    // glVertexAttribPointer(indice, cant de componentes por atributo, tipo del componente, normalizado?, stride, offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);                   // position attibute
    glEnableVertexAttribArray(0);                                                                    // habilitar este atributo (pos)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // color attibute
    glEnableVertexAttribArray(1);                                                                    // habilitar este atributo (color)
}
