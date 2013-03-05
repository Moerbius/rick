#include <stdio.h>

#include "resources.h"
#include "swpstate.h"
#include "gamestate.h"
#include "mainstate.h"



//CResources CResources::m_Resources;

CSWPState CSWPState::m_SWPstate;

/**
  *
  *     ***
  *
  */
void CSWPState::Init()
{
    SDL_Surface* temp = CResources::Instance()->LoadBitmap((char *)"data/main.dat", (char *)"SWPlogo.bmp");

    bg = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    // cria um fade in com o logo
    fader = SDL_CreateRGBSurface(SDL_SRCALPHA, bg->w,bg->h,
                                 bg->format->BitsPerPixel,
                                 bg->format->Rmask, bg->format->Gmask,
                                 bg->format->Bmask, bg->format->Amask);

    // preenche o fader de preto
    SDL_FillRect(fader, NULL, SDL_MapRGB(bg->format, 0, 0, 0));

    // inicia como opaco
    alpha = 255;

    SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

    vanishFlag = false;
    m_LastTick = 0;

    printf("CSWPState Init\n");
}

/**
  *
  *     ***
  *
  */
void CSWPState::Cleanup()
{
    SDL_FreeSurface(bg);
    SDL_FreeSurface(fader);

    printf("CSWPState Cleanup\n");
}

/**
  *
  *     ***
  *
  */
void CSWPState::Pause()
{
    printf("CSWPState Pause\n");
}

/**
  *
  *     ***
  *
  */
void CSWPState::Resume()
{
    printf("CSWPState Resume\n");
}

/**
  *
  *     ***
  *
  */
void CSWPState::HandleEvents(CGameEngine* game)
{
    SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->Quit();
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        game->Quit();
                        break;

                    default:
                        vanishFlag = true;
                        break;
                }
        }
    }
}

/**
  *
  *     ***
  *
  */
void CSWPState::Update(CGameEngine* game)
{
    if(!vanishFlag)
    {
        SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

        alpha--;

        if(alpha < 0)
        {
            alpha = 0;

            if (m_LastTick == 0)
                m_LastTick = SDL_GetTicks();
            else if (SDL_GetTicks() >= (m_LastTick + 2000))
                vanishFlag = true;
        }

    }
    else
    {
        SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

        alpha++;

        if(alpha > 255)
        {
            alpha = 255;

            // termina o SWP logo e inicia main -> mudar CSWPState
            game->ChangeState(CMainState::Instance());
        }

    }

//    SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

}

/**
  *
  *     ***
  *
  */
void CSWPState::Draw(CGameEngine* game)
{

//    SDL_Rect dstrect;
//    dstrect.x = (game->screen->w - bg->w) / 2;
//    dstrect.y = (game->screen->h - bg->h) / 2;

    SDL_BlitSurface(bg, NULL, game->screen, NULL);

    // não precisa de blit se for transparente
    if(alpha != 0)
        SDL_BlitSurface(fader, NULL, game->screen, NULL);

    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}



