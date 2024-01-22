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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    objectShader->use();
    objectShader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    objectShader->setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    objectShader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    objectShader->setFloat("material.shininess", 32.0f);

    objectShader->setVec3("light.ambient", glm::vec3(0.2f));
    objectShader->setVec3("light.diffuse", glm::vec3(0.5f)); // darken diffuse light a bit
    objectShader->setVec3("light.specular", glm::vec3(1.0f));

    objectShader->setVec3("viewPos", camera->cameraPos);
    lightPos = glm::vec3(cos(lastFrame / 1000) * 2.f, 1.0f, sin(lastFrame / 1000) * 2.f);
    objectShader->setVec3("lightPos", lightPos);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->cameraZoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view;
    view = camera->GetViewMatrix();
    objectShader->setMat4("projection", glm::value_ptr(projection));
    objectShader->setMat4("view", glm::value_ptr(view));

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    objectShader->setMat4("model", glm::value_ptr(model));

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // render de lamp
    lampShader->use();
    lampShader->setVec3("lightColor", lightColor);
    lampShader->setMat4("projection", glm::value_ptr(projection));
    lampShader->setMat4("view", glm::value_ptr(view));
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lampShader->setMat4("model", glm::value_ptr(model));

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    SDL_GL_SwapWindow(window);
}

/// @brief sets buffer objects and generates the shader program
void Game::Setup()
{
    objectShader = new Shader("./include/shaders/colors.vert", "./include/shaders/colors.frag");
    lampShader = new Shader("./include/shaders/light_cube.vert", "./include/shaders/light_cube.frag");

    // configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_textured_normals), cube_textured_normals, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // text
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float))); // norm
    glEnableVertexAttribArray(2);

    // configure the lightcube's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // pos
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
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
    oss << "material.texture" << textureIndex;
    std::string textureName = oss.str();

    objectShader->use();
    objectShader->setInt(textureName, textureIndex);
    std::cout << "set " + textureName + " unit" << std::endl;
}

void Game::Clean()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
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
//-----------------------------------------------------------------------------//
//////////////////////////// MESH CLASS /////////////////////////////////////////
//-----------------------------------------------------------------------------//

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

//-----------------------------------------------------------------------------//
//////////////////////////// MODEL CLASS ////////////////////////////////////////
//-----------------------------------------------------------------------------//

void Model::Draw(Shader &shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::loadModel(string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // process indices

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material,
                                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
    {
        vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
        }
        return textures;
    }
    return Mesh(vertices, indices, textures);
}
