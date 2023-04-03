#include "Engine.h"

int main(int argc, char** argv)
{
    const int FPS = 60;
    const int frameTime = 1000 / FPS;
    int frameStart, frameEnd, frame;
    int i = 0;

    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        frameStart = SDL_GetTicks();

        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();

        frameEnd = SDL_GetTicks();
        frame = frameEnd - frameStart;

        if(frameTime > frame)
            SDL_Delay(frameTime - frame);


    }

    Engine::GetInstance()->Clean();
    return 0;
}
