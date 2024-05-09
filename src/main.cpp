#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

#include "common.hpp"
#include "graphics/Plotter.hpp"
#include "audio/wave.hpp"


#define WIDTH 800
#define HEIGHT 500


void generator2(generator_data data);

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

    dpair range = {0, 5000};
    spair units = {"t", "s"};
    SDL_Rect plotterArea = {100, 100, 400, 200};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color blue = {0, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};

    color_theme theme = {blue, red, black};

    PlotterConfig Plotconf ={
        generator2,
        &range,
        &units,
        &theme
    };


    Plotter p = Plotter(&plotterArea, renderer, Plotconf);

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


void generator2(generator_data data){
    Wave::WaveFile file = Wave::WaveFile("../assets/sin.wav");

    if(file.open()){
        //std::cout << "calulcating on range: " << data.range->first << " " << data.range->second << std::endl;
        double delta = (data.range->second - data.range->first)/static_cast<double>(data.npoints);
        /*
        file.seek()
        for(int i = 0;i < data.npoints - 1; ++i){
            double sample = 0.0;
            file.readSample(&sample);
            int cast_delta = i * delta;
            file.seek((i + 1) * delta);
            data.data->push_back({cast_delta, sample});
        }
        */

        file.seek(data.range->first);
        for(int i = 0; i < data.npoints - 1; ++i){
            double sample = 0.0;
            file.readSample(&sample);
            int cast_delta = i * delta;
            file.seek(data.range->first +  (i + 1)*delta);
            data.data->push_back({data.range->first + cast_delta, sample});
        }

        *data.min_y = -1.25;
        *data.max_y = 1.25;
        file.close();
        //std::cout << "gen vec of size " << data.data->size() << std::endl;
    }
    else
        std::cout << "error opening file" << std::endl;
}
