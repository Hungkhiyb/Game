#include "Engine.h"

int main(int argc, char** argv)
{
    const int FPS = 60;
    int frame = SDL_GetTicks();
    int frameTime = 1000 / 60;
    int frameCount = 1;
    int i = 1;

    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
/*
        frame = SDL_GetTicks() - frame;
        if(frameTime > frame)
            SDL_Delay(frameTime - frame);*/
        if(frameCount % 60 == 0){
            std::cout << i << std::endl;
            i++;
        }
        frameCount++;
    }

    Engine::GetInstance()->Clean();
    return 0;
}
