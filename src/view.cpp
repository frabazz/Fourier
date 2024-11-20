#include <SDL2/SDL.h>
#include <iostream>
#include "view.hpp"

View::View(Model *model) {
  this->model = model;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    std::cout << "error init" << std::endl;
  window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 200, 200, 0);
  if (!window)
    std::cout << "failed to open window" << std::endl;
  renderer = SDL_CreateRenderer(window, -1, 0);
}

void View::render(){
  SDL_Event ev;
  while(SDL_PollEvent(&ev) > 0)
    this->emit(&ev);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void View::quit(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
