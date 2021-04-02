#include "../headers/Buffers.hpp"
#include "../headers/Uniforms.hpp"
#include "../headers/shaders.hpp"
#include "../headers/VAOs.hpp"
#include "../headers/ErrorGL.hpp"
#include "../headers/transformations.hpp"
#include "../headers/SDLManager.hpp"

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

std::array<GLfloat, 20>  colorsCone =
{
    0.7f, 0.0f, 0.3f, 1.0f,
    0.0f, 0.4f, 0.7f, 1.0f,
    0.0f, 0.8f, 0.0f, 1.0f,
    0.6f, 0.2f, 0.6f, 1.0f,
    0.4f, 0.0f, 0.0f, 1.0f
};

std::array<GLfloat, 28> transfCone =
{
    -5.0f, 0.0f, 0.0f, 0.0f,
     5.0f, 0.0f, 0.0f, 0.0f,
     -5.0f, 2.0f, -5.0f, 0.0f,
     5.0f, 2.0f, -5.0f, 0.0f,
     3.0f, -2.0f, -2.0f, 0.0f,
     -3.0f, -2.0f, -2.0f, 0.0f,
     0.0f, 1.0f, -10.0f, 0.0f
};

void randRotations()
{

}
int main(int argc, char** argv)
{
    srand(time(NULL));

    SDLManager SDL;
    SDL.InitSDL();

    auto WIN = std::make_shared<SDLWindow>();
    SDL.SwitchWindow(WIN);

    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);

    // BOs AOs init
    VAOsManager vao;
    vao.GenVAO();
    vao.BindVAO(0);

    std::array<GLfloat, 68> dataBatch;
    std::copy(verticesCone.begin(), verticesCone.end(), dataBatch.data());
    std::copy(colorsCone.begin(), colorsCone.end(), dataBatch.data() + verticesCone.size());
    std::copy(transfCone.begin(), transfCone.end(), dataBatch.data() + verticesCone.size() + colorsCone.size());

    auto vboCone = std::make_unique<VBO>(sizeof(dataBatch), dataBatch.data());
    auto iboCone = std::make_unique<IBO>(sizeof(indicesCone), indicesCone.data());
    auto shaderCone = std::make_shared<Shader>(
                                                    "/home/carbonowy/CLionProjects/OpenGL/shaders/InstancedRenderingSh/VertexShader.GLSL",
                                                    "/home/carbonowy/CLionProjects/OpenGL/shaders/InstancedRenderingSh/FragmentShader.GLSL",
                                                    "/home/carbonowy/CLionProjects/OpenGL/shaders/InstancedRenderingSh/GeometryShader.GLSL"
                                                );
    shaderCone->Bind();

    auto uniformCone = std::make_unique<Uniforms>((std::string[3]){"uModel", "uView", "uProj"}, 3, shaderCone);

    glm::mat4 proj = glm::perspective(M_PIf32*0.38f, 1.0f, 0.5f, 100.0f);
    auto camera = std::make_shared<Camera>();

    uniformCone->BindUniformMat4(2, 1, GL_FALSE, glm::value_ptr(proj));
    uniformCone->BindUniformMat4(1, 1, GL_FALSE, &camera->LookAt()[0][0]);

    vao.EnableAttPtr(0);
    vao.EnableAttPtr(1);
    vao.EnableAttPtr(2);
    vao.VertexAttPtr(0, 4, GL_FLOAT,  (const GLvoid*) 0);
    vao.VertexAttPtr(1, 4, GL_FLOAT,  (const GLvoid*)  sizeof(verticesCone));
    vao.VertexAttPtr(2, 4, GL_FLOAT, (const void*)(sizeof(verticesCone) + sizeof(colorsCone)));
    vao.VertexAttDivisor(2, 1);

    auto keyboard = std::make_shared<KeyBoard>(camera);
    auto mouse = std::make_shared<Mouse>(camera);

    keyboard->KeyBoardEnable(ENABLE_WASD);
    mouse->MouseEnable(ENABLE_MOUSE);

    SDL.BindKeyBoard(keyboard);
    SDL.BindMouse(mouse);
    //-----------------------------------------------------------------------------------------------------------------
    auto conesMats = std::make_unique<ModelMatrices>(7);

    for(unsigned int i=0; i<transfCone.size()/4; i++)
    {
        glm::vec3 rotVecTmp;
        float rotSpeed;

        switch(rand()%3)
        {
            case 0: rotVecTmp = glm::vec3( 1.0f, 0.0f, 0.0f); break;
            case 1: rotVecTmp = glm::vec3( 0.0f, 1.0f, 0.0f); break;
            case 2: rotVecTmp = glm::vec3( 0.0f, 0.0f, 1.0f); break;
        }

        switch(rand()%5)
        {
            case 0: rotSpeed = 0.001f; break;
            case 1: rotSpeed = 0.002f; break;
            case 2: rotSpeed = 0.003f; break;
            case 3: rotSpeed = 0.004f; break;
            case 4: rotSpeed = 0.005f; break;
        }

        conesMats->AddAngle(rotSpeed, rotVecTmp, i);
    }

    conesMats->UpdateAll();

    //----------------------------------------------------------------------------------------------------------------
    while(!WIN->isClosed)
    {
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        uniformCone->BindUniformMat4(0, 7, GL_FALSE, conesMats->data());
        uniformCone->BindUniformMat4(1, 1, GL_FALSE, camera->CamMatData());

        glDrawElementsInstanced(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0, 7);

        conesMats->UpdateAll();
        SDL.EventPolling();
        WIN->SwapBuffers();
    }


}

