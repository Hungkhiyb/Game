#include "Engine.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

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

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
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

    if(!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to load map!" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    TextureManager::GetInstance()->LoadMedia("background", "assets/backgrounds/Sky.png");
    TextureManager::GetInstance()->LoadMedia("player-idle", "assets/player-idle.png");
    TextureManager::GetInstance()->LoadMedia("player-run", "assets/player-run.png");
    TextureManager::GetInstance()->LoadMedia("player-jump-01", "assets/player-jump-01.png");
    TextureManager::GetInstance()->LoadMedia("player-jump-02", "assets/player-jump-02.png");
    TextureManager::GetInstance()->LoadMedia("player-jump-03", "assets/player-jump-03.png");
    TextureManager::GetInstance()->LoadMedia("player-jump-04", "assets/player-jump-04.png");
    TextureManager::GetInstance()->LoadMedia("player-jump-05", "assets/player-jump-05.png");
    TextureManager::GetInstance()->LoadMedia("player-attack-01", "assets/player-attack-01.png");

    player = new Warrior(new Properties("player-ilde", 200, 400, 32, 32));

    Camera::GetInstance()->setTarget(player->GetOrigin());

    return m_IsRunning = true;
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

void Engine::Update()
{
    m_LevelMap->Update();
    player->Update(0);
    Camera::GetInstance()->Update(0);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("background", 0, 0, 576 * 2, 324 * 2, 0.1);
    m_LevelMap->Render();
    player->Draw();
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



