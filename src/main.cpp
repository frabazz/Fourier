#include "graphics/Plotter.hpp"
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#define WIDTH 500
#define HEIGHT 500

std::shared_ptr<sample_data_t> generator(std::shared_ptr<dpair> range, int max_values){
    double max_y = 0, min_y = 0;
    std::vector<dpair> values = std::vector<dpair>();
    double delta = (range->second - range->first)/static_cast<double>(max_values);
    double curr = range->first;
    for(int i = 0;i < max_values; ++i){
        values.push_back({curr, curr*curr });
        curr += delta;
    }

    sample_data res = {
        std::make_shared<std::vector<dpair>>(values),
        min_y,
        max_y
    };

    return std::make_shared<sample_data_t>(res);
}

int main(int argc, char* argv[]){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "error during initializing : " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        std::cout << "error during window creation: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event e;
    bool quit = false;

    SDL_Rect plotterArea = {100, 100, 200, 200};
    dpair range = {1,2};
    SDL_Color red = {255, 0, 0, 255};
    Plotter p = Plotter(&plotterArea, renderer, generator, std::make_shared<dpair>(range), &red, &red);

    while(!quit){
        if(SDL_PollEvent(&e) > 0)
            if(e.type == SDL_QUIT)
                quit = true;

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
