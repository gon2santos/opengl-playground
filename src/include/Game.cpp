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
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized" << std::endl;
    }
    else
    {
        std::cout << "Error initializing Subsystems. Error: " << SDL_GetError() << std::endl;
    }
    //Request opengl 3.2 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //Turn on double buffering with a 24bit Z buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN/* flags */);
    if (gWindow)
    {
        //gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
    else
    {
        std::cout << "Error initializing window: " << SDL_GetError() << std::endl;
    }
    maincontext = SDL_GL_CreateContext(gWindow);
    SDL_GL_SetSwapInterval(1);

    /* Clear our buffer with a red background */
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    /* Swap our back buffer to the front */
    SDL_GL_SwapWindow(gWindow);
    /* Wait 2 seconds */
    SDL_Delay(2000);

    /* Same as above, but green */
    glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(gWindow);
    SDL_Delay(2000);

    /* Same as above, but blue */
    glClearColor ( 0.0, 0.0, 1.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(gWindow);
    SDL_Delay(2000);

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();

    return;





    /* gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
    if (gRenderer)
    {
        SDL_SetRenderDrawColor(gRenderer, 25, 25, 25, 255);
    }
    else
    {
        std::cout << "Error initializing gRenderer: " << SDL_GetError() << std::endl;
    }
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = width;
    stretchRect.h = height;

    isRunning = true; */
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
        SDL_UpdateWindowSurface(gWindow);
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
    SDL_RenderClear(gRenderer);
    //  aca agregar cosas a renderear...
    SDL_RenderSetViewport( gRenderer, &fullvpRect ); //settear vp como ventana completa
    SDL_RenderCopy( gRenderer, gTexture, NULL, NULL ); //renderear imagen de fondo
    SDL_RenderSetViewport( gRenderer, &smallvpRect ); //settear vp como el mitad de ventana
    SDL_RenderCopy( gRenderer, viewportTexture, NULL, NULL ); //renderear otra textura en viewport mas chico
    SDL_RenderPresent(gRenderer);
    //  Apply the image
    //SDL_BlitSurface(gPTCG, NULL, gScreenSurface, NULL);
    // Update the surface
    //SDL_UpdateWindowSurface(gWindow);
}

void Game::Clean()
{
    // Deallocate surface
    SDL_FreeSurface(gPTCG);
    gPTCG = NULL;
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
    std::cout << "Subsystems cleaned" << std::endl;
}

bool Game::LoadMedia()
{
    std::string paths[5];
    paths[0] = "../assets/imgDEFAULT.bmp";
    paths[1] = "../assets/imgUP.png";
    paths[2] = "../assets/imgDOWN.bmp";
    paths[3] = "../assets/imgLEFT.bmp";
    paths[4] = "../assets/imgRIGHT.bmp";

    // Loading success flag
    bool success = true;

    // Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = LoadSurface(paths[KEY_PRESS_SURFACE_DEFAULT], "BMP");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    // Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadSurface(paths[KEY_PRESS_SURFACE_UP], "PNG");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    // Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadSurface(paths[KEY_PRESS_SURFACE_DOWN], "BMP");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    // Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadSurface(paths[KEY_PRESS_SURFACE_LEFT], "BMP");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    // Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadSurface(paths[KEY_PRESS_SURFACE_RIGHT], "BMP");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

SDL_Surface *Game::LoadSurface(std::string path, std::string format)
{
    // The final optimized image
    SDL_Surface *optimizedSurface = NULL;
    SDL_Surface *loadedSurface = NULL;
    // Load image at specified path
    if (format == "PNG")
    {
        loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
    }
    else if (format == "BMP")
    {
        loadedSurface = SDL_LoadBMP(path.c_str());
        if (loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return NULL;
        }
    }
    else
    {
        std::cout << "Incorrect img format: " << format << std::endl;
        return NULL;
    }

    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL)
    {
        printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    return optimizedSurface;
}

void Game::SetDefaultMedia()
{
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
    // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);
}

bool Game::InitPNGLoad()
{
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

SDL_Texture* Game::LoadTexture( std::string path ){
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); //NOTA: IMG_LoadTexture allows you to load a texture without having to create a temporary surface!
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool Game::LoadMediaAsTexture(){
    //Loading success flag
    bool success = true;

    //Load PNG texture
    gTexture = LoadTexture( "../assets/imgUP.png" );
    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}

bool Game::InitSmallViewport(){
    bool success = true;
    smallvpRect = { 10, (SCREEN_HEIGHT - (SCREEN_HEIGHT / 3) - 10) , SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3 };

    //Load PNG texture
    viewportTexture = LoadTexture( "../assets/viewporttest.png" );
    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}

bool Game::InitFullViewport(){
    bool success = true;
    fullvpRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    return success;
}

void Game::SDLDie(const char* msg){
    std::cout << msg << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(1);
}