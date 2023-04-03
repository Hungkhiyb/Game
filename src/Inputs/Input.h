#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "Engine.h"

class Input
{
    public:
        Input();
        ~Input();

        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);

    private:
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif // INPUT_H
