#ifndef gameengine_h
#define gameengine_h

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "main.h"
#include <vector>
#include <SDL_mixer.h>

using namespace std;

class CGameState;

class CGameEngine
{
    public:

        void Init(const char* title, int width = WIDTH, int height = HEIGHT, int bpp = BPP, bool fullscreen = FULLSCREEN);

        void Cleanup();

        void ChangeState(CGameState* state);
        void PushState(CGameState* state);
        void PopState();

        void HandleEvents();
        void Update();
        void Draw();

        bool Running()
        {
            return m_running;
        }

        void Quit()
        {
            m_running = false;
        }

        SDL_Surface* screen;

    private:

        vector<CGameState*> states;

        bool m_running;
        bool m_fullscreen;

};

#endif
