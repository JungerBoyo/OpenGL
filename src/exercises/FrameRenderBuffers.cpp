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

int main(int argc, char** argv)
{

    SDLManager SDL;
    SDL.InitSDL();

    auto WIN = std::make_shared<SDLWindow>();
    SDL.SwitchWindow(WIN);

    glewInit();
    glEnable(GL_DEPTH_TEST|GL_BLEND|GL_CULL_FACE);
    // BOs AOs init ----------------------------------------------------------------------------------------------------
    VAOsManager vao;
    vao.GenVAO();
    vao.BindVAO(0);

    std::array<GLfloat, 20> dataBatch;
    std::copy(verticesCone.begin(), verticesCone.end(), dataBatch.data());

    auto vboCone = std::make_unique<VBO>(sizeof(dataBatch), dataBatch.data());
    auto iboCone = std::make_unique<IBO>(sizeof(indicesCone), indicesCone.data());
    auto shaderCone = std::make_shared<Shader>(
            "/home/carbonowy/CLionProjects/OpenGL/shaders/framebuffersShex/VertexShader.GLSL",
            "/home/carbonowy/CLionProjects/OpenGL/shaders/framebuffersShex/FragmentShader.GLSL",
            "/home/carbonowy/CLionProjects/OpenGL/shaders/framebuffersShex/GeometryShader.GLSL"
    );
    shaderCone->Bind();

    auto uniformCone = std::make_unique<Uniforms>((std::string[3]){"uModel", "uView", "uProj"}, 3, shaderCone);

    glm::mat4 proj = glm::perspective(M_PIf32*0.38f, 1.0f, 0.5f, 100.0f);
    auto camera = std::make_shared<Camera>();

    uniformCone->BindUniformMat4(2, 1, GL_FALSE, glm::value_ptr(proj));
    uniformCone->BindUniformMat4(1, 1, GL_FALSE, &camera->LookAt()[0][0]);

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
    coneMat->ScaleOne(glm::vec3(2.0f, 2.0f, 2.0f), 0);
    coneMat->UpdateOne(0);

    //------------------------------------------------------------------------------------------------------------------
    GLuint renderBuff[2];
    glGenRenderbuffers(2, renderBuff);

    glBindRenderbuffer(GL_RENDERBUFFER, renderBuff[0]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 1024, 1024);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuff[1]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1024, 1024);

    GLuint frmBuff;
    glGenFramebuffers(1, &frmBuff);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frmBuff);

    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuff[0]);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuff[1]);

    glEnable(GL_DEPTH_TEST|GL_CULL_FACE);

    while(!WIN->isClosed)
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frmBuff);

        glViewport(0, 0, 1024, 1024);
        glClearBufferfv(GL_COLOR, 0, (const float[4]) {0.3f, 0.2f, 0.2f, 1.0f});
        glClearBufferfv(GL_DEPTH, 0, (const float[1]){0.0f});

        uniformCone->BindUniformMat4(0, 1, GL_FALSE, coneMat->data());
        uniformCone->BindUniformMat4(1, 1, GL_FALSE, camera->CamMatData());
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        SDL.EventPolling();
        coneMat->UpdateOne(0);


        glBindFramebuffer(GL_READ_FRAMEBUFFER, frmBuff);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glViewport(0, 0, 1024, 1024);
        glClearBufferfv(GL_COLOR, 0, (const float[4]) {0.3f, 0.2f, 0.2f, 1.0f});
        glClearBufferfv(GL_DEPTH, 0, (const float[1]){0.0f});

        glBlitFramebuffer(0, 0, 1024, 1024, 0, 0, 1024, 1024, GL_COLOR_BUFFER_BIT, GL_LINEAR);

        WIN->SwapBuffers();
    }

    glInvalidateFramebuffer(GL_FRAMEBUFFER, 2, ((const GLenum[2]){GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT}));

    return 0;
}
