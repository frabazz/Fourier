#include "graphics/Plotter.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <vector>
#include "audio/wave.hpp"

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

std::shared_ptr<std::vector<dpair>> generator2(std::shared_ptr<dpair> range, double* min_y, double* max_y, int npoints){
    Wave::WaveFile file = Wave::WaveFile("assets/test.wav");
    if(file.open()){
        std::vector<dpair> values = std::vector<dpair>();
        double delta = (range->second - range->first)/static_cast<double>(npoints);
        for(int i = 0;i < npoints - 1; ++i){
            double sample = 0.0;
            file.readSample(&sample);
            int cast_delta = i * delta;
            file.seek((i + 1) * delta);
            values.push_back({cast_delta, sample});
        }

        *min_y = -1.25;
        *max_y = 1.25;
        file.close();
        return std::make_shared<std::vector<dpair>>(values);
    }
    else{
        std::cout << "error opening file" << std::endl;
        return NULL;
    }
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
    dpair range = {0, 100000};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color blue = {0, 255, 255, 255};
    Plotter p = Plotter(&plotterArea, renderer, generator2, std::make_shared<dpair>(range), &red, &blue, "t", "s");

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
