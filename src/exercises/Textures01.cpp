#include "../headers/Buffers.hpp"
#include "../headers/Uniforms.hpp"
#include "../headers/shaders.hpp"
#include "../headers/VAOs.hpp"
#include "../headers/ErrorGL.hpp"
#include "../headers/transformations.hpp"
#include "../headers/SDLManager.hpp"
#include "../../textures/TextureImg.h"

#include <stdexcept>
#include <vector>
#include <memory>
#include <time.h>
#include <iostream>

std::array<GLuint, 18> indicesCone =
{
    0, 1, 4,
    1, 3, 4,
    3, 2, 4,
    2, 0, 4,
    2, 1, 0,
    2, 3, 1
};

std::array<GLfloat, 20> verticesCone =
{
    -1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 1.0f,
     1.0f, -1.0f,-1.0f, 1.0f,
     0.0f,  1.5f, 0.0f, 1.0f
};
int main(int argc, char** argv)
{

    SDLManager SDL;
    SDL.InitSDL();

    auto WIN = std::make_shared<SDLWindow>();
    SDL.SwitchWindow(WIN);

    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // BOs AOs init ----------------------------------------------------------------------------------------------------
    VAOsManager vao;
    vao.GenVAO();
    vao.BindVAO(0);

    std::array<GLfloat, 36> dataBatch;
    std::copy(verticesCone.begin(), verticesCone.end(), dataBatch.data());

    auto vboCone = std::make_unique<VBO>(sizeof(dataBatch), dataBatch.data());
    auto iboCone = std::make_unique<IBO>(sizeof(indicesCone), indicesCone.data());
    auto shaderCone = std::make_shared<Shader>(
            "/home/carbonowy/CLionProjects/OpenGL/shaders/textureshex/VertexShader.GLSL",
            "/home/carbonowy/CLionProjects/OpenGL/shaders/textureshex/FragmentShader.GLSL",
            "/home/carbonowy/CLionProjects/OpenGL/shaders/textureshex/GeometryShader.GLSL"
    );
    shaderCone->Bind();

    auto uniformCone = std::make_unique<Uniforms>((std::string[5]){"uModel", "uView", "uProj", "uSmplr01", "uTexCoords"}, 5, shaderCone);

    glm::mat4 proj = glm::perspective(M_PIf32*0.38f, 1.0f, 0.5f, 100.0f);
    auto camera = std::make_shared<Camera>();

    glm::mat3x2 uTexCoords =
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    uniformCone->BindUniformMat4(2, 1, GL_FALSE, glm::value_ptr(proj));
    uniformCone->BindUniformMat4(1, 1, GL_FALSE, &camera->LookAt()[0][0]);
    uniformCone->BindUniformMat3x2(4, 1, GL_FALSE, glm::value_ptr(uTexCoords));

    vao.EnableAttPtr(0);
    vao.VertexAttPtr(0, 4, GL_FLOAT,  (const GLvoid*) 0);

    //------------------------------------------------------------------------------------------------------------------
    auto keyboard = std::make_shared<KeyBoard>(camera);
    auto mouse = std::make_shared<Mouse>(camera);

    keyboard->KeyBoardEnable(ENABLE_WASD);
    mouse->MouseEnable(ENABLE_MOUSE);

    SDL.BindKeyBoard(keyboard);
    SDL.BindMouse(mouse);
    //------------------------------------------------------------------------------------------------------------------
    auto coneMat = std::make_unique<ModelMatrices>(1);

    coneMat->AddAngle(0.002f, glm::vec3(1.0f, 0.0f, 0.0f), 0);
    coneMat->UpdateOne(0);

    //------------------------------------------------------------------------------------------------------------------

    auto texImg = std::make_unique<TextureImg>("/home/carbonowy/CLionProjects/OpenGL/textures/tex01mp/Tex01.png", true);

    //------------------------------------------------------------------------------------------------------------------
    GLuint tex01;
    DEBUG(glGenTextures(1, &tex01));
    DEBUG(glBindTexture(GL_TEXTURE_2D, tex01));
    DEBUG(glTexStorage2D(GL_TEXTURE_2D, texImg->mipMapLvls(), GL_RGBA8, texImg->Width(), texImg->Height()));


    for(int i=0; i<texImg->mipMapLvls(); i++)
    {
        DEBUG(glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, texImg->Width(i), texImg->Height(i), GL_RGBA, GL_UNSIGNED_BYTE,
                              (const void *) texImg->DataMM(i)));
    }


    GLuint sampler01;
    DEBUG(glGenSamplers(1, &sampler01));
    DEBUG(glBindSampler(tex01, sampler01));

    while(!WIN->isClosed)
    {
        glClearColor(0.3, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        uniformCone->BindUniformMat4(0, 1, GL_FALSE, coneMat->data());
        uniformCone->BindUniformMat4(1, 1, GL_FALSE, camera->CamMatData());
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        SDL.EventPolling();
        coneMat->UpdateOne(0);
        WIN->SwapBuffers();
    }

    return 0;
}


