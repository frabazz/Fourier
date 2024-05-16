#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <chrono>


#include "common.hpp"
#include "graphics/Plotter.hpp"
#include "graphics/PlotterWorker.hpp"
#include "graphics/Event.hpp"
#include "graphics/Timer.hpp"
#include "audio/wave.hpp"


#define WIDTH 800
#define HEIGHT 500
#define AUDIO_FILE "../assets/sin.wav"




int main(int argc, char* argv[]){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    Wave::WaveFile wav_file = Wave::WaveFile(AUDIO_FILE);
    if(!wav_file.open()){
        std::cout << "erroring opening wav file" << std::endl;
        return -1;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "error during initializing : " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        std::cout << "error during window creation: " << SDL_GetError() << std::endl;

    if(TTF_Init() < 0)
        std::cout << "error during ttf init " << SDL_GetError() << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

    events::Event e = events::Event();
    bool quit = false;

    dpair range = {0, 5000};
    spair units = {"sample", "dB"};
    SDL_Rect plotterArea = {100, 100, 400, 200};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color blue = {0, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};

    color_theme theme = {blue, red, black};

    SampleReadWorker sampleReadWorker = SampleReadWorker(&wav_file);

    PlotterConfig Plotconf ={
        &sampleReadWorker,
        &range,
        &units,
        &theme
    };


    Plotter p = Plotter(&plotterArea, renderer, Plotconf);
    //std::cout << "enterign render loop" << std::endl;
    SDL_Event ev;
    while(!quit){
        MyTimer::Timer t = MyTimer::Timer();


        if(SDL_PollEvent(&ev) > 0){
            e = events::Event(&ev);
            p.feedEvent(&e);
        }



        //events::Event::pollEvent(&e);
        if(e.isSDL() && e.sdl_event->type == SDL_QUIT){
            quit = true;
        }

        //std::cout << "pollEvent duration : " << timer.measure() << std::endl;
        //p.feedEvent(&e);
        std::cout << t.measure() << std::endl;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        p.render();
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    wav_file.close();


    return 0;


}
