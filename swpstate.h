#ifndef SWPSTATE_H__
#define SWPSTATE_H__

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "gamestate.h"



class CSWPState : public CGameState
{
    public:

        void Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        static CSWPState* Instance()
        {
            return &m_SWPstate;
        }

        Uint32 m_LastTick;
        bool vanishFlag;

    protected:
        CSWPState()
        {
        }

    private:
        static CSWPState m_SWPstate;

        SDL_Surface* bg;
        SDL_Surface* fader;
        int alpha;
};

#endif

