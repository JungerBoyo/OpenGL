#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP
#include <SDL2/SDL.h>
#include <vector>
#include "transformations.hpp"

enum { ENABLE_WASD = 1, ENABLE_ARROWS = 2 };
enum { ENABLE_MOUSE = 1 };

class KeyBoard;
class SDLManager;
class SDLWindow;
class Mouse;

class SDLManager
{
    public:
        SDLManager();
        void InitSDL();
        void EventPolling(KeyBoard* virtualKeyBoard = NULL, Mouse* virtualMouse = NULL);
        
        inline void SwitchWindow(SDLWindow* newWin)
            {   actualWindow = newWin;  }

    private:
        SDLWindow* actualWindow = NULL;
        bool MouseMode = false;
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
        typedef void(KeyBoard::*MovementControl)(SDL_Event*); 

        struct keyBoardFunctions
        {
            MovementControl MovCtrl1 = NULL;
            MovementControl MovCtrl2 = NULL;
        };

    public:
        inline KeyBoard(Camera* setCam) : actualCamBind(setCam), functionality(new keyBoardFunctions()) {}
        inline void SetCam(Camera* setCam) {    actualCamBind = setCam;    }

        void KeyDownAction(SDL_Event* event);

        void WASD(SDL_Event* event);
        void ARROWS(SDL_Event* event);

        void KeyBoardEnable(int enable);

    private:
        Camera* actualCamBind = NULL;
        keyBoardFunctions* functionality = NULL;
        int enabled = 0;
        float rapidity = 0.3f;
};

class Mouse
{
    private:
        typedef void(Mouse::*MovementControl)(SDL_Event*); 

        struct MouseFunctions
        {
            MovementControl MovCtrl1 = NULL;
        };

        struct MouseData
        {
            int anchorCoordX = 0;
            int anchorCoordY = 0;
        };

    public:
        inline Mouse(Camera* setCam) : actualCamBind(setCam), functionality(new MouseFunctions()), data(new MouseData()) {}
        inline void SetCam(Camera* setCam) { actualCamBind = setCam; }
    
        void ButtonDownAction(SDL_Event* event);
        void LookAround(SDL_Event* event);
        void MouseEnable(int enable);

    private:
        Camera* actualCamBind = NULL;
        MouseFunctions* functionality = NULL;
        int enabled = 0;

    public:
        MouseData* data = NULL;
};

#endif

