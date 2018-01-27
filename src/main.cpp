#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include <list>
#include "menu_entry.h"

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 768;

SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* loadTexture(std::string);

int selectedIndex = 0;
int currentXOffset = 0;

bool init()
{
    bool rVal = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        std::cout << "Initialization failed! SDL_Error: %s" << SDL_GetError() << std::endl;
        rVal = false;
    }
    else
    {
        std::cout << "Initialized!" << std::endl;
        gWindow = SDL_CreateWindow( "Window title", 
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_MAXIMIZED);
        if( gWindow == NULL )
        {
            std::cout << "Window creation failed! SDL_Error: %s" << SDL_GetError() << std::endl;
            rVal = false;
        }
        else
        {
            std::cout << "Window created!" << std::endl;
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            gSurface = SDL_GetWindowSurface( gWindow );
            if( gRenderer == NULL )
            {
                std::cout << "Creating renderer failed! SDL_Error: " << SDL_GetError() << std::endl;
                rVal = false;
            }
            else
            {
                if( !IMG_Init( IMG_INIT_PNG ) )
                {
                    std::cout << "SDL Image failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
                    rVal = false;
                }
            }
        }
    }

    return rVal;
}


void shutdown()
{
    SDL_DestroyWindow( gWindow );
    SDL_Quit();
}

void loop(std::list<MenuItem> menuItems)
{
    SDL_Event e;
    bool quit = false;

    while( !quit )
    {
        SDL_Rect rDest;
        while( SDL_PollEvent( &e ) != 0)
        {
            switch (e.type)
            {
                case SDL_KEYDOWN:
                    selectedIndex++;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    selectedIndex--;
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            
            }
        }

        std::list<MenuItem>::iterator it;
        if (selectedIndex >= menuItems.size())
        {
            selectedIndex = 0;
        }
        for (it = menuItems.begin(); it != menuItems.end(); it++)
        {
            int index = std::distance(menuItems.begin(), it);
            if (currentXOffset > (-300 * selectedIndex)) {
                currentXOffset--;
                usleep(100);
            }
            if (currentXOffset < (-300 * selectedIndex)) {
                currentXOffset++;
                usleep(100);
            }
            int targetYOffset = selectedIndex  == index ? 15 : 200;
            if (index == selectedIndex -1 || index == selectedIndex +1)
            {
                targetYOffset = 200;
            }
            int currentYOffset = (int)(*it).getYOffset();
            if (currentYOffset < targetYOffset) {
                (*it).setYOffset(++currentYOffset);
                usleep(100);
            }else if (currentYOffset > targetYOffset)
            {
                (*it).setYOffset(--currentYOffset);
                usleep(100);
            }
            (*it).setX(currentXOffset - (-300 * index)+500);
            (*it).setY(150);
            (*it).render();
        }
        SDL_RenderPresent( gRenderer );
        SDL_RenderClear( gRenderer );
    }
}
int main( int argc, char *args[] )
{
    init();
    std::cout << "Creating menu items" << std::endl;

    SDL_FillRect( gSurface, NULL, SDL_MapRGB( gSurface->format, 0x2F, 0xFF, 0xFA ) );
    SDL_UpdateWindowSurface( gWindow );

    std::list<MenuItem> menuItems;
    for (int i = 0; i < 5; i++)
    {
        menuItems.push_back(MenuItem(gRenderer));
    }
    
    loop(menuItems);

    return 0;
}
