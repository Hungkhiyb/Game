#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#include "Camera.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Tranform.h"
#include "Warrior.h"
#include "Input.h"
#include "MapParser.h"
#include "GameMap.h"

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWnWARD 1

class Engine {

    public:
        Engine();
        ~Engine();

        static Engine* GetInstance(){ return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }
        GameMap* GetMap(){ return m_LevelMap; }


        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool IsRunning(){ return m_IsRunning; }
        inline SDL_Renderer* GetRenderer(){ return m_Renderer; }

    private:
        bool m_IsRunning;

        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
};

#endif // ENGINE_H
