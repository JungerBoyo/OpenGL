/*
#include "../headers/Buffers.hpp"
#include "../headers/Uniforms.hpp"
#include "../headers/shaders.hpp"
#include "../headers/VAOs.hpp"
#include "../headers/ErrorGL.hpp"
#include "../headers/transformations.hpp"
#include "../headers/SDLManager.hpp"
#include "../../textures/TextureImg.hpp"

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

GLuint indicesCube[] =
{
    0, 1, 2,
    0, 3, 1, // front
    3, 5, 1,
    3, 7, 5, // right
    2, 5, 6,
    2, 1, 5, // top
    4, 2, 6,
    4, 0, 2, // left
    4, 3, 0,
    4, 7, 3, // bottom
    7, 6, 5,
    7, 4, 6
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

    auto uniformCone = std::make_unique<Uniforms>((std::string[6]){"uModel", "uView", "uProj", "uSmplr01", "uTexCoords", "uOffset"}, 6, shaderCone);

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

    auto texImg1 = std::make_unique<TextureImg>("/home/carbonowy/CLionProjects/OpenGL/textures/tex01mp/Tex01.png", true);
    auto texImg2 = std::make_unique<TextureImg>("/home/carbonowy/CLionProjects/OpenGL/textures/tex03mp/tex03.png", true);

    //------------------------------------------------------------------------------------------------------------------
    GLuint tex012[2];
    DEBUG(glGenTextures(2, tex012));
    DEBUG(glBindTexture(GL_TEXTURE_2D, tex012[0]));
    DEBUG(glTexStorage2D(GL_TEXTURE_2D, texImg1->mipMapLvls(), GL_RGBA8, texImg1->Width(), texImg1->Height()));
    for(int i=0; i < texImg1->mipMapLvls(); i++)
    {
        DEBUG(glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, texImg1->Width(i), texImg1->Height(i), GL_RGBA, GL_UNSIGNED_BYTE,
                              (const void *) texImg1->DataMM(i)));
    }

    DEBUG(glBindTexture(GL_TEXTURE_2D, tex012[1]));
    DEBUG(glTexStorage2D(GL_TEXTURE_2D, texImg2->mipMapLvls(), GL_RGBA8, texImg2->Width(), texImg2->Height()));
    for(int i=0; i < texImg2->MipMapLvls(); i++)
    {
        DEBUG(glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, texImg2->Width(i), texImg2->Height(i), GL_RGBA, GL_UNSIGNED_BYTE,
                              (const void *) texImg2->DataMM(i)));
    }

    GLuint sampler01[2];
    DEBUG(glGenSamplers(2, sampler01));
    DEBUG(glBindSampler(tex012[0], sampler01[0]));
    DEBUG(glBindSampler(tex012[1], sampler01[1]));

    glm::vec4 offsets[2] = {{-6.0f, 0.0f, 0.0f, 0.0f} , {6.0f, 0.0f, 0.0f, 0.0f}};

    while(!WIN->isClosed)
    {
        glClearColor(0.3, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        uniformCone->BindUniformMat4(0, 1, GL_FALSE, coneMat->data());
        uniformCone->BindUniformMat4(1, 1, GL_FALSE, camera->CamMatData());

        uniformCone->BindUniformVec4(5, 1, &offsets[0].x);
        glBindTexture(GL_TEXTURE_2D, tex012[0]);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        uniformCone->BindUniformVec4(5, 1, &offsets[1].x);
        glBindTexture(GL_TEXTURE_2D, tex012[1]);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        SDL.EventPolling();
        coneMat->UpdateOne(0);
        WIN->SwapBuffers();
    }

    return 0;
}
*/

