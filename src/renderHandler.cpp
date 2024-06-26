#include "renderHandler.hpp"
#include "wave.hpp"
#include "./audio/workers.hpp"
#include "./graphics/Event.hpp"
#include "./graphics/Plotter.hpp"

#include <SDL_events.h>
#include <SDL_mouse.h>
#include <iostream>


using Component::Plotter;
using std::cout;
using std::endl;
using std::string;
using audio_workers::sample_read_worker;

RenderHandler::RenderHandler(int width, int heigth) {
  _width = width;
  _heigth = heigth;
}

bool RenderHandler::initSDL() {
  // TODO: add SDL error function

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "error during initializing : " << SDL_GetError() << endl;
    return false;
  }

  _window =
      SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       _width, _heigth, SDL_WINDOW_SHOWN);

  if (_window == NULL) {
    cout << "error during window creation: " << SDL_GetError() << endl;
    return false;
  }

  if (TTF_Init() < 0) {
    cout << "error during ttf init " << SDL_GetError() << endl;
    return false;
  }

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (_renderer == NULL)
    cout << "error during renderer initializing: " << SDL_GetError() << endl;
  
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_ADD);
  SDL_ShowCursor(0);
  cout << "SDL init" << endl;
  return true;
}

bool RenderHandler::initWav(string filename) {
  _wav = new Wave::WaveFile(filename);
  if (!_wav->open()) {
    cout << "error opening wav file" << endl;
    return false;
  }
  return true;
}

bool RenderHandler::initComponents() {

  dpair range = {0, 5000};
  spair units = {"sample", "dB"};

  SDL_Rect plotter_area = {100, 100, 400, 200};
  _signalPlotter = new Plotter(plotter_area, _renderer, range, units);

  return true;
}

void RenderHandler::renderLoop(bool *quit) {
  SDL_Event event;
  while (SDL_PollEvent(&event) > 0) {
    _event = &event; // some SDL magic(s**t) with event initialization
    if (event.type == SDL_QUIT){
      *quit = true;
      cout << "quitting" << endl;
    }
    else if (event.type == SDL_USEREVENT &&
             event.user.code == PLOTTER_RECALC) {
      plotter_recalc_ev *recalc_ev = (plotter_recalc_ev *)event.user.data1;

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
      
      sample_read_worker({_wav, recalc_ev->range, recalc_ev->min_y,
                          recalc_ev->max_y, recalc_ev->npoints,
                          recalc_ev->data});
    }

    _signalPlotter->feedEvent(&event);
  }

  // std::cout << "pollEvent duration : " << timer.measure() << std::endl;
  // p.feedEvent(&e);
  // std::cout << t.measure() << "ms\n";

  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
  _signalPlotter->render();
  SDL_RenderPresent(_renderer);
}

RenderHandler::~RenderHandler(){
  cout << "freeing sdl.." << endl;
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
  _wav->close();
}
