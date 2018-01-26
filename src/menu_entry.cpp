#include "menu_entry.h"
#include <SDL2/SDL_image.h>


MenuItem::MenuItem(SDL_Renderer* _gRenderer)
{
    this->gRenderer = _gRenderer;
    this->texture = loadTexture( "resources/textures/texture.png" );
    this->X,Y = 10;
}

void MenuItem::render()
{
    SDL_Rect rDest;
    rDest.h = 128; rDest.w = 256; rDest.x = this->X; rDest.y = this->Y; 
    SDL_RenderCopy( this->gRenderer, this->texture, NULL, &rDest);
    //SDL_RenderPresent( this->gRenderer );
    std::cout << "Rendering element " << this << std::endl;
}

void MenuItem::setX(int _X)
{
    this->X = _X;
}

void MenuItem::setY(int _Y)
{
    this->Y = _Y;
}

SDL_Texture* MenuItem::loadTexture(std::string imagePath)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* tmpSurface = IMG_Load( imagePath.c_str() );
    if( tmpSurface == NULL )
    {
        std::cout << "Error loading texture! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( this->gRenderer, tmpSurface );
        if( newTexture == NULL )
        {
            std::cout << "Can't create texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface( tmpSurface );
    }
    return newTexture;
}