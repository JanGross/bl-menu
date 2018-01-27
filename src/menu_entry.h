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
        void setYOffset(int _offset);
        void setXOffset(int _offset);
        int getX();
        int getY();
        int getXOffset();
        int getYOffset();

    private:
        int X, Y, xOffset, yOffset;
        SDL_Texture* loadTexture(std::string imagePath);
        SDL_Renderer* gRenderer = NULL;
        SDL_Texture* texture;
};

#endif