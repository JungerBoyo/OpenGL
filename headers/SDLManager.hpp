#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP
#include <SDL2/SDL.h>
#include <vector>
#include "transformations.hpp"

enum { ENABLE_WASD = 1, ENABLE_ARROWS = 2};

class KeyBoard;
class SDLManager;
class SDLWindow;
class Mouse;

class SDLManager
{
    public:
        SDLManager();
        void InitSDL();
        void EventPolling(KeyBoard* virtualKeyBoard = NULL, Mouse* MouseInput = NULL);
        
        inline void SwitchWindow(SDLWindow* newWin)
            {   actualWindow = newWin;  }

    private:
        SDLWindow* actualWindow = NULL;
};  

class SDLWindow : public SDLManager
{
    public: 
        SDLWindow();
        ~SDLWindow();
        void InitOpenGLWindow();
        inline void SwapBuffers() {SDL_GL_SwapWindow(win);}
        
    private:
        SDL_Window* win;
        SDL_GLContext context;

    public:
        bool isClosed = false;
};

class KeyBoard
{

    private:
        typedef void(KeyBoard::*MovementControl)(SDL_Event*, float); 

        struct keyBoardFunctions
        {
            keyBoardFunctions()
            {
                MovCtrl1 = NULL;
                MovCtrl2 = NULL;
            }

            MovementControl MovCtrl1 = NULL;
            MovementControl MovCtrl2 = NULL;
        };

    public:
        inline KeyBoard(Camera* setCam) : actualCamBind(setCam), functionality(new keyBoardFunctions()) {}
        inline void SetCam(Camera* setCam) {    actualCamBind = setCam;    }

        void KeyDownAction(SDL_Event* event);

        void WASD(SDL_Event* event, float rapidity = 0.4f);
        void ARROWS(SDL_Event* event, float rapidity = 0.4f);

        void KeyBoardEnable(int enable);

    private:
        Camera* actualCamBind;
        keyBoardFunctions* functionality;
        int enabled = 0;
};

class Mouse
{
    public:
        Mouse();



};


#endif

