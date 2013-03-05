#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#ifdef __linux__
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#endif

#include "main.h"
#include "resources.h"
#include "logostate.h"



int main ( int argc, char** argv )
{
    CGameEngine game;

    // inicializa o jogo
    game.Init(TITLE);

    // mostra os logos
    game.ChangeState(CLogoState::Instance());

    while (game.Running())
    {
        game.HandleEvents();
        game.Update();
        game.Draw();
    }

    // limpa o engine
    game.Cleanup();

    return 0;
}
