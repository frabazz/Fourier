#include "graphics/Plotter.hpp"
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <cfloat>
#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#define WIDTH 800
#define HEIGHT 500

std::shared_ptr<sample_data_t> generator(std::shared_ptr<dpair> range, int max_values){
    double max_y = -DBL_MAX, min_y = DBL_MAX;
    std::vector<dpair> values = std::vector<dpair>();
    double delta = (range->second - range->first)/static_cast<double>(max_values);
    double curr = range->first;
    for(int i = 0;i < max_values; ++i){
        values.push_back({curr, curr*curr });
        if(curr*curr < min_y)
            min_y = curr*curr;
        if(curr*curr > max_y)
            max_y = curr*curr;
        curr += delta;
    }

    sample_data res = {
        std::make_shared<std::vector<dpair>>(values),
        -100*100,
        100*100
    };
    std::cout << "total values: " << values.size() << std::endl;
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

    SDL_Rect plotterArea = {100, 100, 400, 200};
    dpair range = {-100, +100};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color blue = {0, 255, 255, 255};
    Plotter p = Plotter(&plotterArea, renderer, generator, std::make_shared<dpair>(range), &red, &blue);

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
