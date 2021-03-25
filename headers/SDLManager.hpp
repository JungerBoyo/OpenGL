#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
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
        void EventPolling();
        
        inline void SwitchWindow(std::shared_ptr<SDLWindow> newWin)
            {   actualWindow = newWin;  }

        inline void BindKeyBoard(std::shared_ptr<KeyBoard> vKeyBoard)
            {   virtualKeyBoard = vKeyBoard;    }
        
        inline void BindMouse(std::shared_ptr<Mouse> vMouse)
            {   virtualMouse = vMouse;  }

    private:
        std::shared_ptr<SDLWindow> actualWindow = NULL;
        std::shared_ptr<KeyBoard> virtualKeyBoard = NULL;
        std::shared_ptr<Mouse> virtualMouse = NULL;
        bool MouseMode = false;
};  

class SDLWindow : virtual public SDLManager
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
        inline KeyBoard(std::shared_ptr<Camera> setCam) : actualCamBind(setCam), functionality(new keyBoardFunctions()) {}
        inline void SetCam(std::shared_ptr<Camera> setCam) {    actualCamBind = setCam;    }

        void KeyDownAction(SDL_Event* event);

        void WASD(SDL_Event* event);
        void ARROWS(SDL_Event* event);

        void KeyBoardEnable(int enable);

    private:
        std::shared_ptr<Camera> actualCamBind = NULL;
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
        inline Mouse(std::shared_ptr<Camera> setCam) : actualCamBind(setCam), functionality(new MouseFunctions()) {}
        inline void SetCam(std::shared_ptr<Camera> setCam) { actualCamBind = setCam; }
    
        void ButtonDownAction(SDL_Event* event);
        void LookAround(SDL_Event* event);
        void MouseEnable(int enable);

    private:
        std::shared_ptr<Camera> actualCamBind = NULL;
        MouseFunctions* functionality = NULL;
        int enabled = 0;

    public:
        MouseData data;
};

#endif

