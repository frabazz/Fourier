#include <SDL2/SDL.h>
#include <iostream>
#include "graphics/Box.hpp"
#include "view.hpp"

View::View(Model *model) {
  this->model = model;
  
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    std::cout << "error init" << std::endl;
  window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 400, 400, 0);
  if (!window)
    std::cout << "failed to open window" << std::endl;
  renderer = SDL_CreateRenderer(window, -1, 0);
  Component::_model = model; // static 
  Component::_renderer = renderer; // static

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  components = std::vector<Component*>();
  SDL_Rect renderArea = {50, 50, 100, 100};
  SDL_Color green = {0, 255, 0, 255}; // on color
  SDL_Color blue = {0, 0, 255, 255}; // off color
  Box* b = new Box(renderArea, green, blue);
  components.push_back(b);

  for(auto c : components)
    this->addListener(c);
}

void View::render(){
  SDL_Event ev;
  while(SDL_PollEvent(&ev) > 0)
    this->emit(&ev);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  for(auto c : components)
    c->render();
  
  SDL_RenderPresent(renderer);
}

void View::quit(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  for(auto c : components)
    delete c;
}
