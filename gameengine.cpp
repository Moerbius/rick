#include <stdio.h>

#include "gameengine.h"
#include "gamestate.h"


/**
  *
  *     Inicializa a Class CGameEngine
  *
  */
void CGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
    int flags = 0;

    // inicializa o SDL
    SDL_Init(SDL_INIT_VIDEO);

    // inicializa o title bar
    SDL_WM_SetCaption(title, title);

    // coloca o jogo em full screen ou windowed
    if(fullscreen)
    {
        flags = SDL_FULLSCREEN;
    }

    // cria o screen surface
    screen = SDL_SetVideoMode(width, height, bpp,flags);

    m_fullscreen = fullscreen;
    m_running = true;

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        exit(1);
    }

    printf("CGameEngine Init\n");
}

/**
  *
  *     Trata da limpeza antes de sair do jogo :)
  *
  */
void CGameEngine::Cleanup()
{
    // limpa todos os estados
    while(!states.empty())
    {
        states.back()->Cleanup();
        states.pop_back();
    }

    // se tiver em fullscreen coloca em windoed outra vez para não interferir com os outros programas abertos...
    if(m_fullscreen)
    {
        screen = SDL_SetVideoMode(640, 480, 0, 0);
    }

    printf("CGameEngine Cleanup\n");

    // manda o SDL a baixo
    SDL_Quit();
}

/**
  *
  *     Muda o estado do jogo
  *
  */
void CGameEngine::ChangeState(CGameState* state)
{
    // limpa o estado actual
    if (!states.empty())
    {
        states.back()->Cleanup();
        states.pop_back();
    }

    // grava e inicializa o novo estado
    states.push_back(state);
    states.back()->Init();

}

/**
  *
  *     ***
  *
  */
void CGameEngine::PushState(CGameState* state)
{
    // coloca o estado actual em pausa
        if (!states.empty())
    {
        states.back()->Pause();
    }

    // guarda e inicializa o novo estado
    states.push_back(state);
    states.back()->Init();

}

/**
  *
  *     ***
  *
  */
void CGameEngine::PopState()
{
    // limpa o estado actual
    if (!states.empty())
    {
        states.back()->Cleanup();
        states.pop_back();
    }

    // volta ao estado anterior
    if (!states.empty())
    {
        states.back()->Resume();
    }
}

/**
  *
  *     Tratamento dos eventos
  *
  */
void CGameEngine::HandleEvents()
{
    // quem trata dos eventos são os estados
    states.back()->HandleEvents(this);
}

/**
  *
  *     Tratamento das actualizações do jogo
  *
  */
void CGameEngine::Update()
{
    // quem trata dos updates são os estados
    states.back()->Update(this);
}

/**
  *
  *     Tratamento do draw
  *
  */
void CGameEngine::Draw()
{
    // quem trata do draw são os estados
    states.back()->Draw(this);
}






