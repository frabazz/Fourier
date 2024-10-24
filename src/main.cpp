#include <SDL2/SDL.h>
#include <SDL2.h>
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "Event.hpp"
#include "audio/wave.hpp"
#include "audio/workers.hpp"
#include "common.hpp"
#include "graphics/Plotter.hpp"
#include "graphics/Timer.hpp"
#define WIDTH 800
#define HEIGHT 500
#define AUDIO_FILE "../assets/sin.wav"

using namespace audio_workers;

int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  Wave::WaveFile wav_file = Wave::WaveFile(AUDIO_FILE);
  if (!wav_file.open()) {
    std::cout << "erroring opening wav file" << std::endl;
    return -1;
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    std::cout << "error during initializing : " << SDL_GetError() << std::endl;

  window =
      SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL)
    std::cout << "error during window creation: " << SDL_GetError()
              << std::endl;

  if (TTF_Init() < 0)
    std::cout << "error during ttf init " << SDL_GetError() << std::endl;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

  bool quit = false;

  dpair range = {0, 5000};
  spair units = {"sample", "dB"};
  SDL_Rect plotterArea = {100, 100, 400, 200};

  

  Plotter p = Plotter(&plotterArea, renderer, &range, &units);
  // std::cout << "enterign render loop" << std::endl;
  SDL_Event ev;

  SDL_ShowCursor(0);

  while (!quit) {
    MyTimer::Timer t = MyTimer::Timer();
    while (SDL_PollEvent(&ev) > 0) {

      if (ev.type == SDL_QUIT)
        quit = true;
      else if (ev.type == SDL_USEREVENT && ev.user.code == PLOTTER_RECALC) {
	plotter_recalc_ev *recalc_ev = (plotter_recalc_ev*) ev.user.data1;
	
	recalc_ev->data->clear();
	/*
	sampleReadWorker.run({
	    recalc_ev->range,
	    recalc_ev->min_y,
	    recalc_ev->max_y,
	    recalc_ev->npoints,
	    recalc_ev->data
	  });
	*/
	
	sample_read_worker({
	    &wav_file,
	    recalc_ev->range,
	    recalc_ev->min_y,
	    recalc_ev->max_y,
	    recalc_ev->npoints,
	    recalc_ev->data
	});
	
      }

      p.feedEvent(&ev);
    }



    // std::cout << "pollEvent duration : " << timer.measure() << std::endl;
    // p.feedEvent(&e);
    // std::cout << t.measure() << "ms\n";

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

Cc: frabazz <francesco260403@gmail.com>
