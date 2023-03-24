#include "Engine.h"

Engine* Engine::s_Instance = nullptr;

Engine::Engine()
{

}

Engine::~Engine()
{
    //dtor
}

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        std::cerr << "Failed to initialize SDL: %s" << SDL_GetError();
        return false;
    }

    m_Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(m_Window == nullptr)
    {
        std::cerr << "Failed to create window SDL: %s" << SDL_GetError();
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        std::cerr << "Failed to create renderer SDL: %s" << SDL_GetError();
        return false;
    }

    return m_IsRunning = true;
}

void Engine::Events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            Quit();
            break;
    }
}

void Engine::Update()
{

}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}


bool Engine::Clean()
{
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        IMG_Quit();
        SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}



