#include "../headers/SDLManager.hpp"
#include <iostream>

SDLManager::SDLManager() {}

void SDLManager::InitSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void SDLManager::EventPolling()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(!MouseMode)
        {
            switch(event.type)
            {
                case SDL_QUIT: actualWindow->isClosed = true; break;
                case SDL_KEYDOWN: if(virtualKeyBoard != NULL) virtualKeyBoard->KeyDownAction(&event); break;
                case SDL_MOUSEBUTTONDOWN: 
                                if(virtualMouse != NULL) 
                                {
                                   MouseMode = true; 
                                   SDL_GetMouseState(&virtualMouse->data.anchorCoordX, &virtualMouse->data.anchorCoordY);  
                                }
                            break;
            }
        }
        else
            if(event.type == SDL_MOUSEBUTTONUP)
                MouseMode = false;
            else
                virtualMouse->ButtonDownAction(&event);
    }
}

void SDLWindow::InitOpenGLWindow()
{
    this-> win = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000,  SDL_WINDOW_OPENGL);
    this-> context = SDL_GL_CreateContext(win); 
}

SDLWindow::SDLWindow()
{
    this->InitOpenGLWindow();
}

SDLWindow::~SDLWindow()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void KeyBoard::KeyDownAction(SDL_Event* _event)
{
    if(this->functionality->MovCtrl1 != NULL)
        (this->*functionality->MovCtrl1)(_event);
    
    if(this->functionality->MovCtrl2 != NULL)
        (this->*functionality->MovCtrl2)(_event);
}

void KeyBoard::WASD(SDL_Event* _event)
{
    switch(_event->key.keysym.sym)
    {
        case 'w': case 'W': actualCamBind -> UpdatePos(CAM_FORWARD); break;
        case 'a': case 'A': actualCamBind -> UpdatePos(CAM_LEFT); break;
        case 's': case 'S': actualCamBind -> UpdatePos(CAM_BACKWARD); break;
        case 'd': case 'D': actualCamBind -> UpdatePos(CAM_RIGHT); break; 
        default: break;
    }
}

void KeyBoard::ARROWS(SDL_Event* _event)
{
    switch(_event->key.keysym.sym)
    {
        case SDLK_UP: actualCamBind -> UpdatePos(CAM_FORWARD); break;    
        case SDLK_LEFT: actualCamBind -> UpdatePos(CAM_LEFT); break;
        case SDLK_DOWN: actualCamBind -> UpdatePos(CAM_BACKWARD); break;
        case SDLK_RIGHT: actualCamBind -> UpdatePos(CAM_RIGHT); break;
        default: break;
    }
}

void KeyBoard::KeyBoardEnable(int _enable)
{
    if(_enable > this->enabled)
    {
        switch(_enable)
        {
            case 1:      
                this->functionality->MovCtrl1 = &KeyBoard::WASD;
                    break;

            case 2:      
                this->functionality->MovCtrl2 = &KeyBoard::ARROWS;
                    break;

            case 3:
                this->functionality->MovCtrl1 = &KeyBoard::WASD;
                this->functionality->MovCtrl2 = &KeyBoard::ARROWS;
                    break;

            default: break;
        }
    
        enabled = _enable;
    }
}

void Mouse::ButtonDownAction(SDL_Event* _event)
{    
    if(this->functionality->MovCtrl1 != NULL)
        (this->*functionality->MovCtrl1)(_event);        
}

void Mouse::LookAround(SDL_Event* _event)
{
    int mouseCoordX;
    int mouseCoordY;

    if(_event->type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&mouseCoordX, &mouseCoordY);

        actualCamBind -> 
            UpdateDirVec(0.00005f*(mouseCoordY - data.anchorCoordY), 
                         0.00005f*(mouseCoordX - data.anchorCoordX));                
    }
}

void Mouse::MouseEnable(int _enable)
{
    if(_enable == 1)
    {
        this->functionality->MovCtrl1 = &Mouse::LookAround;
        enabled = _enable;
    }
}