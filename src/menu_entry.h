#ifndef MENU_ENTRY_H
#define MENU_ENTRY_H
#include <SDL2/SDL.h>
#include <iostream>


class MenuItem
{
    public :        
        MenuItem(SDL_Renderer* _gRenderer);
        void render();
        void setX(int _x);
        void setY(int _y);

    private:
        int X, Y;
        SDL_Texture* loadTexture(std::string imagePath);
        SDL_Renderer* gRenderer = NULL;
        SDL_Texture* texture;
};

#endif