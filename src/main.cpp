#include "../headers/Buffers.hpp"
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

VAOsManager vao;
BufferManager Buffers;

Camera* camera; int cam;
Model* model; int mod; 

int pos;

void init()
{   
    vao.GenVA(1);
    vao.BindVA(0);

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

    GLfloat colors[] =
    {
        0.1f, 0.1f, 0.1f, 1.0f,
        0.2f, 0.2f, 0.2f, 1.0f,
        0.3f, 0.3f, 0.3f, 1.0f,
        0.3f, 0.4f, 0.4f, 1.0f,
        0.1f, 0.8f, 0.5f, 1.0f,
        0.9f, 0.8f, 0.6f, 1.0f,
        0.4f, 0.4f, 0.7f, 1.0f,
        0.0, 0.8f, 0.8f, 1.0f
    };

    Buffers.GenBuffers(1, GL_ARRAY_BUFFER);
    Buffers.BindBuffer(GL_ARRAY_BUFFER, 0);
    //Buffers.PushData(GL_ARRAY_BUFFER, &vertices); 
    Buffers.AllocateData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors));
    Buffers.PushSubdata(GL_ARRAY_BUFFER, &vertices, GL_STATIC_DRAW, 0);
    Buffers.PushSubdata(GL_ARRAY_BUFFER, &colors, GL_STATIC_DRAW, sizeof(vertices));


    Buffers.GenBuffers(1, GL_ELEMENT_ARRAY_BUFFER);
    Buffers.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    Buffers.PushData(GL_ELEMENT_ARRAY_BUFFER, &indices);

    //(0.0 0.0 -1.0 0.0)

    GLuint program = glCreateProgram();  
    Shaders* shMake = new Shaders("../shaders/VertexShader.GLSL", 
                                  "../shaders/FragmentShader.GLSL", 
                                  "../shaders/GeometryShader.GLSL", &program);
    ASSERT(glUseProgram(program));
  
    vao.EnableAttPtr(0);
    vao.EnableAttPtr(1);
    vao.VertexAttPtr(0, 4, GL_FLOAT);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) sizeof(vertices));
    
    // git
    

    int MVP = glGetUniformLocation(program, "MVP");
    glm::mat4 mvp = glm::perspective(0.38f*M_PIf32, 1.0f, 0.5f, 10.0f);
    ASSERT(glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]));

    camera = new Camera();
    model = new Model({0.0f, 0.0f, -4.5f}, {{0.0f * M_PIf32}}, {{0.0f, 1.0f, 0.0f}});

    cam = glGetUniformLocation(program, "view");
    ASSERT(glUniformMatrix4fv(cam, 1, GL_FALSE, &camera->LookAt()[0][0]));

    mod = glGetUniformLocation(program, "model");
    ASSERT(glUniformMatrix4fv(mod, 1, GL_FALSE, &model->GetActualModelMat()[0][0]));

    pos = glGetUniformLocation(program, "pos");
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(cam, 1, GL_FALSE, &camera->GetActLookAtMat()[0][0]);
    ASSERT(glUniform4fv(pos, 1, &(camera->GetActLookAtMat() * camera->GetCamPosition())[0]));
    glUniformMatrix4fv(mod, 1, GL_FALSE, &model->GetActualModelMat()[0][0]);

    ASSERT(glDrawElements(GL_TRIANGLES, 36,  GL_UNSIGNED_INT, 0));
}

int main(int argc, char** argv)
{
    SDLManager SDL;
    SDL.InitSDL();

    SDLWindow WIN;
    SDL.SwitchWindow(&WIN);

    if(glewInit())
    {
        std :: cerr << "glewInit(): glew Initialization failed\n";
        return 1;
    }

    init();

    KeyBoard* keyboard = new KeyBoard(camera);
    keyboard -> KeyBoardEnable(ENABLE_WASD|ENABLE_ARROWS);

    Mouse* mouse = new Mouse(camera);
    mouse -> MouseEnable(ENABLE_MOUSE);

    while(!WIN.isClosed)
    {
        Display();
        SDL.EventPolling(keyboard, mouse);
        model->UpdateModel(glm::vec3(0.0f,0.0f,0.0f), {0.01f, 0.005f}, {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)});
        WIN.SwapBuffers();
    }

    return 0;
}

