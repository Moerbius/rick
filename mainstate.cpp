#include <stdio.h>

#include "resources.h"
#include "mainstate.h"
#include "gamestate.h"

Mix_Music *sndMainMusic = NULL;

CMainState CMainState::m_Mainstate;

/**
  *
  *     ***
  *
  */
void CMainState::Init()
{
    SDL_Surface* temp = CResources::Instance()->LoadBitmap((char *)"data/main.dat", (char *)"intro.bmp");

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

    printf("CMainState images Init\n");

    // ********* SOUND *********
//sndMainMusic = Mix_LoadMUS("rick1.wav");
    sndMainMusic = CResources::Instance()->LoadMusic((char *)"data/main.dat", (char *)"rick1.ogg");

    if(sndMainMusic == NULL)
    {
        printf("Error loading music");
        exit(1);
    }

    //Play the sndMainMusic main music
    if( Mix_PlayMusic(sndMainMusic, 1 ) == -1 )
    {
        printf("Error playing music");
        exit(1);
    }
    /*if( Mix_PlayChannel( -1, sndMainMusic, 0 ) == -1 )
    {
        exit(1);
    }*/

}

/**
  *
  *     ***
  *
  */
void CMainState::Cleanup()
{
    SDL_FreeSurface(bg);
    SDL_FreeSurface(fader);

    Mix_FreeMusic(sndMainMusic);

    Mix_CloseAudio();



    printf("CMainState Cleanup\n");
}

/**
  *
  *     ***
  *
  */
void CMainState::Pause()
{
    printf("CMainState Pause\n");
}

/**
  *
  *     ***
  *
  */
void CMainState::Resume()
{
    printf("CMainState Resume\n");
}

/**
  *
  *     ***
  *
  */
void CMainState::HandleEvents(CGameEngine* game)
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
void CMainState::Update(CGameEngine* game)
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
                vanishFlag = false;


        }

    }
    else
    {
        SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

        alpha++;

        if(alpha > 255)
        {
            alpha = 255;

            // termina o SDL logo e inicia o SWP logo -> mudar CLogoState
            //game->ChangeState(CMainState::Instance());
        }


    }

}

/**
  *
  *     ***
  *
  */
void CMainState::Draw(CGameEngine* game)
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


