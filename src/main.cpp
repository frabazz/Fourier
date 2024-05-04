#include "graphics/Plotter.hpp"
#include <SDL_blendmode.h>
#include <SDL_render.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <SDL_ttf.h>

#define WIDTH 800
#define HEIGHT 500

std::shared_ptr<std::vector<dpair>> generator(std::shared_ptr<dpair> range, double* min_y, double* max_y, int npoints){
    //shit code only for testing
    std::vector<dpair> values = std::vector<dpair>();
    double delta = (range->second - range->first)/static_cast<double>(npoints);
    double curr = range->first;
    for(int i = 0;i < npoints; ++i){
        values.push_back({curr, curr*curr });
        curr += delta;
    }

    *min_y = -100*100;
    *max_y = 100*100;
    return std::make_shared<std::vector<dpair>>(values);
}

int main(int argc, char* argv[]){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "error during initializing : " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        std::cout << "error during window creation: " << SDL_GetError() << std::endl;

    if(TTF_Init() < 0)
        std::cout << "error during ttf init " << SDL_GetError() << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

    SDL_Event e;
    bool quit = false;

    SDL_Rect plotterArea = {100, 100, 400, 200};
    dpair range = {-100, +100};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color blue = {0, 255, 255, 255};
    Plotter p = Plotter(&plotterArea, renderer, generator, std::make_shared<dpair>(range), &red, &blue, "t", "s");

    while(!quit){
        if(SDL_PollEvent(&e) > 0){
            if(e.type == SDL_QUIT)
                quit = true;
            p.feedEvent(&e);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        p.render();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
