#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include <SDL.h>

class TextureManager
{
    public:
        TextureManager();
        ~TextureManager();

        static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }

        bool LoadMedia(std::string id, std::string filename);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, int x, int y, int width, int height, float scrollRatio, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManager* s_Instance;

};

#endif // TEXTUREMANAGER_H
