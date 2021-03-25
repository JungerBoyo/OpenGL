#include "../headers/Buffers.hpp"
#include "../headers/Uniforms.hpp"
#include "../headers/shaders.hpp"
#include "../headers/VAOs.hpp"
#include "../headers/ErrorGL.hpp"
#include "../headers/transformations.hpp"
#include "../headers/SDLManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <stdexcept>
#include <string.h>
#include <vector>
#include <memory> 
#include <iostream>


GLuint indices[] =
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

//GLuint indices1[]
//{
//    0, 1, 5,
//    1, 3, 5,
//    3, 2, 5,
//    2, 0, 5,
//    3, 0, 1,
//    3, 2, 0
//};

VAOsManager vao;

std::shared_ptr<Camera> camera; 
std::unique_ptr<ModelTFMS> model1; 
std::unique_ptr<Uniforms> uniforms;

void init()
{   
    vao.GenVAO();
    vao.BindVAO(0);

    GLfloat vertices[] =
    {
        -1.0f, -1.0f, 1.0f, 1.0f, // Triangle 1
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 1.0f, // Triangle 2
        -1.0f, -1.0f,-1.0f, 1.0f,
         1.0f,  1.0f,-1.0f, 1.0f,
        -1.0f,  1.0f,-1.0f, 1.0f,
         1.0f, -1.0f,-1.0f, 1.0f
    };

    //GLfloat vertices1[] =
    //{
    //    -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.0f, 1.0f,
    //    -0.5f, -0.5f,-1.0f, 1.0f,
    //     0.5f, -0.5f,-1.0f, 1.0f,
    //     0.0f,  0.5f,-0.5f, 1.0f
    //};
//
    //GLfloat colors1[] =
    //{
    //    0.3f, 0.3f, 0.3f, 1.0f,
    //    0.3f, 0.4f, 0.4f, 1.0f,
    //    0.1f, 0.8f, 0.5f, 1.0f,
    //    0.9f, 0.8f, 0.6f, 1.0f,
    //    0.4f, 0.4f, 0.7f, 1.0f
    //};

    GLfloat colors[] =
    {
        0.1f, 0.1f, 0.1f, 1.0f,
        0.2f, 0.2f, 0.2f, 1.0f,
        0.3f, 0.3f, 0.3f, 1.0f,
        0.3f, 0.4f, 0.4f, 1.0f,
        0.1f, 0.8f, 0.5f, 1.0f,
        0.9f, 0.8f, 0.6f, 1.0f,
        0.4f, 0.4f, 0.7f, 1.0f,
        0.0f, 0.8f, 0.8f, 1.0f
    };

    std::unique_ptr<VBO> vertexBuffer = std::make_unique<VBO>(sizeof(vertices), vertices, sizeof(colors), colors);
    std::unique_ptr<IBO> indexBuffer = std::make_unique<IBO>(sizeof(indices), indices);
  
    std::shared_ptr<Shader> cubeShader = std::make_shared<Shader>("../shaders/VertexShader.GLSL", 
                                                                "../shaders/FragmentShader.GLSL", 
                                                                "../shaders/GeometryShader.GLSL");
    cubeShader->Bind();

    vao.EnableAttPtr(0);
        vao.VertexAttPtr(0, 4, GL_FLOAT, (const GLvoid*) 0);
    vao.EnableAttPtr(1);
        vao.VertexAttPtr(1, 4, GL_FLOAT, (const GLvoid*) sizeof(vertices));
    
    uniforms = std::make_unique<Uniforms>((std::string[4]){"proj", "view", "model", "camPos"}, cubeShader);
     
    glm::mat4 proj = glm::perspective(0.38f*M_PIf32, 1.0f, 0.5f, 10.0f);
        uniforms->BindUniformMat4(0, 1, GL_FALSE, &proj[0][0]);

    camera = std::make_shared<Camera>();
        uniforms->BindUniformMat4(1, 1, GL_FALSE, &camera->LookAt()[0][0]);

    model1 = std::make_unique<ModelTFMS>((glm::vec3){0.0f, 0.0f, -4.5f}, (std::vector<float>){{0.0f * M_PIf32}}, (std::vector<glm::vec3>){{0.0f, 1.0f, 0.0f}});
        uniforms->BindUniformMat4(2, 1, GL_FALSE, model1->ModelMatData());

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    uniforms->BindUniformMat4(1, 1, GL_FALSE, camera->CamMatData());
    uniforms->BindUniformVec4(3, 1, &(camera->GetActLookAtMat()*camera->GetCamPosition())[0]);
    uniforms->BindUniformMat4(2, 1, GL_FALSE, model1->ModelMatData());

    ASSERT(glDrawElements(GL_TRIANGLES, 36,  GL_UNSIGNED_INT, 0));
}

int main(int argc, char** argv)
{
    SDLManager SDL;
    SDL.InitSDL();

    std::shared_ptr<SDLWindow> WIN = std::make_shared<SDLWindow>();
    SDL.SwitchWindow(WIN);

    if(glewInit())
    {
        std :: cerr << "glewInit(): glew Initialization failed\n";
        return 1;
    }

    init();

    std::shared_ptr<KeyBoard> keyboard = std::make_shared<KeyBoard>(camera);
    keyboard -> KeyBoardEnable(ENABLE_WASD|ENABLE_ARROWS);

    std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>(camera);
    mouse -> MouseEnable(ENABLE_MOUSE);

    SDL.BindKeyBoard(keyboard);
    SDL.BindMouse(mouse);

    while(!WIN->isClosed)
    {
        Display();
        SDL.EventPolling();
        model1->UpdateModel(glm::vec3(0.0f,0.0f,0.0f), {0.01f, 0.005f}, {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)});
        WIN->SwapBuffers();
    }

    return 0;

}

