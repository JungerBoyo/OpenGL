#include "../headers/SDLManager.hpp"

SDLManager :: SDLManager() {}

void SDLManager :: InitSDL()
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

void SDLManager :: EventPolling(KeyBoard* _virtualKeyBoard, Mouse* _MouseInput)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.key.keysym.sym == 'q')
            actualWindow->isClosed = true;

        switch(event.type)
        {
            case SDL_QUIT: actualWindow->isClosed = true; break;
            case SDL_KEYDOWN: if(_virtualKeyBoard != NULL) _virtualKeyBoard->KeyDownAction(&event); break;
        }
    }
}

void SDLWindow :: InitOpenGLWindow()
{
    this-> win = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500,  SDL_WINDOW_OPENGL);
    this-> context = SDL_GL_CreateContext(win); 
}

SDLWindow :: SDLWindow()
{
    this->InitOpenGLWindow();
}

SDLWindow :: ~SDLWindow()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void KeyBoard :: KeyDownAction(SDL_Event* _event)
{
    if(functionality->MovCtrl1 != NULL)
        (this->*functionality->MovCtrl1)(_event, 0.4f);
    
    if(functionality->MovCtrl2 != NULL)
        (this->*functionality->MovCtrl2)(_event, 0.4f);
}

void KeyBoard :: WASD(SDL_Event* _event, float _rapidity)
{
    switch(_event->key.keysym.sym)
    {
        case 'w': case 'W':  
                actualCamBind -> UpdateCamera(glm::vec3(0.0f, 0.0f, _rapidity));
            break;
        
        case 'a': case 'A': 
                actualCamBind -> UpdateCamera(glm::vec3(_rapidity, 0.0f, 0.0f));
            break;
        
        case 's': case 'S': 
                actualCamBind -> UpdateCamera(glm::vec3(0.0f, 0.0f,-_rapidity));
            break;
        
        case 'd': case 'D': 
                actualCamBind -> UpdateCamera(glm::vec3(-_rapidity, 0.0f, 0.0f));
            break;
        
        default: 
            break;
    }
}

void KeyBoard :: ARROWS(SDL_Event* _event, float _rapidity)
{
    switch(_event->key.keysym.sym)
    {
        case SDLK_UP: 
                actualCamBind -> UpdateCamera(glm::vec3(0.0f, 0.0f, _rapidity));
            break;
        
        case SDLK_LEFT: 
                actualCamBind -> UpdateCamera(glm::vec3(_rapidity, 0.0f, 0.0f));
            break;
        
        case SDLK_DOWN: 
                actualCamBind -> UpdateCamera(glm::vec3(0.0f, 0.0f,-_rapidity));
            break;
        
        case SDLK_RIGHT: 
                actualCamBind -> UpdateCamera(glm::vec3(-_rapidity, 0.0f, 0.0f));
            break;
        
        default: 
            break;
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
    }

    enabled = _enable;
}