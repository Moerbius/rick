#ifndef LOGOSTATE_H__
#define LOGOSTATE_H__

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "gamestate.h"



class CMainState : public CGameState
{
    public:

        void Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        static CMainState* Instance()
        {
            return &m_Mainstate;
        }

        Uint32 m_LastTick;
        bool vanishFlag;

    protected:
        CMainState()
        {
        }

    private:
        static CMainState m_Mainstate;

        SDL_Surface* bg;
        SDL_Surface* fader;
        int alpha;
};

#endif
