#ifndef LOGOSTATE_H__
#define LOGOSTATE_H__

#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "gamestate.h"



class CLogoState : public CGameState
{
    public:

        void Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(CGameEngine* game);
        void Update(CGameEngine* game);
        void Draw(CGameEngine* game);

        static CLogoState* Instance()
        {
            return &m_Logostate;
        }

        Uint32 m_LastTick;
        bool vanishFlag;

    protected:
        CLogoState()
        {
        }

    private:
        static CLogoState m_Logostate;

        SDL_Surface* bg;
        SDL_Surface* fader;
        int alpha;
};

#endif
